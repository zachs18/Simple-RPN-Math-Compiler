#include <stdexcept>
#include <cstring> // std::memcpy
#include <sys/mman.h> // mmap

#include "Function.hpp"

asm(R"(
.Lfunction_header_code_start:
	endbr64
	push	%rbp
	mov	%rsp,%rbp

	push	%rdi # at -8(%rbp)
	push	%rsi # at -16(%rbp)
	push	%rdx # at -24(%rbp)
	push	%rcx # at -32(%rbp)
	push	%r8 # at -40(%rbp)
	push	%r9 # at -48(%rbp)

.Lfunction_header_code_end:
)");

extern char function_header_code_start[] asm(".Lfunction_header_code_start");
extern char function_header_code_end[] asm(".Lfunction_header_code_end");

asm(R"(
.Lfunction_footer_code_start:
	pop	%rax

	mov	%rbp,%rsp
	pop	%rbp
	ret

.Lfunction_footer_code_end:
)");

extern char function_footer_code_start[] asm(".Lfunction_footer_code_start");
extern char function_footer_code_end[] asm(".Lfunction_footer_code_end");

Function::Function(std::vector<Command> &&commands_)
: m_commands(std::move(commands_))
{
	unsigned stack_size = 0;
	std::string code{function_header_code_start, function_header_code_end};
	for (const auto &command : m_commands) {
		//printf("stack_size: %u, param_count: %u, return_count: %u\n", stack_size, command.param_count(), command.return_count());
		if (stack_size < command.param_count()) throw std::invalid_argument("Function would pop value from empty stack");
		if (stack_size < command.required_stack_depth()) throw std::invalid_argument("Function would use value past end of stack");
		stack_size -= command.param_count();
		stack_size += command.return_count();

		code += command.code();
	}
	if (stack_size == 0) throw std::invalid_argument("Function would return from empty stack");

	code += std::string{function_footer_code_start, function_footer_code_end};

	void *code_binary = mmap(nullptr, code.size(), PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (code_binary == nullptr) {
		throw std::runtime_error("mmap failed");
	}

	std::memcpy(code_binary, &code[0], code.size());

	// maybe need a memory barrier here?

	if (mprotect(code_binary, code.size(), PROT_READ|PROT_EXEC) != 0) {
		munmap(code_binary, code.size());
		throw std::runtime_error("mprotect failed");
	}

	try {
		m_code = std::shared_ptr<void>{code_binary, [size = code.size()](void *binary) { munmap(binary, size); }};
//		std::shared_ptr<void> temp{code_binary, [size = code.size()](void *binary) { munmap(binary, size); }};
//		m_code = temp;
	} catch (std::bad_alloc const &ba) {
		munmap(code_binary, code.size());
		throw;
	}
}
