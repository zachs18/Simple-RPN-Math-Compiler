#include "Command.hpp"
#include <cstring>
#include <stdexcept>

asm(R"(
.Lwhile_loop_header_code_start:
	mov	(%rsp),%rax
	test	%rax,%rax
	je	.+1024 # force rel32
.Lwhile_loop_header_branch_offset_end:
.Lwhile_loop_header_code_end:
)");

extern char while_loop_header_code_start[] asm(".Lwhile_loop_header_code_start");
extern char while_loop_header_branch_offset_end[] asm(".Lwhile_loop_header_branch_offset_end");
extern char while_loop_header_code_end[] asm(".Lwhile_loop_header_code_end");

asm(R"(
.Lwhile_loop_footer_code_start:
	mov	(%rsp),%rax
	test	%rax,%rax
	jne	.+1024 # force rel32
.Lwhile_loop_footer_branch_offset_end:
.Lwhile_loop_footer_code_end:
)");

extern char while_loop_footer_code_start[] asm(".Lwhile_loop_footer_code_start");
extern char while_loop_footer_branch_offset_end[] asm(".Lwhile_loop_footer_branch_offset_end");
extern char while_loop_footer_code_end[] asm(".Lwhile_loop_footer_code_end");

Command Command::while_loop(std::vector<Command> const &commands) {
	std::string body_code;
	unsigned required_stack_depth = 1;
	signed stack_difference = 0;
	for (const auto &command : commands) {
		if (required_stack_depth + stack_difference < (long) command.param_count()) {
			required_stack_depth = command.param_count() - stack_difference;
		}
		if (required_stack_depth + stack_difference < (long) command.required_stack_depth()) {
			required_stack_depth = command.required_stack_depth() - stack_difference;
		}

		stack_difference -= command.param_count();
		stack_difference += command.return_count();

		body_code += command.code();
	}

	if (stack_difference != 0) {
		throw std::invalid_argument("Does not currently support while loops that change stack depth");
	}

	std::string header_code{while_loop_header_code_start, while_loop_header_code_end};
	std::string footer_code{while_loop_footer_code_start, while_loop_footer_code_end};

	unsigned long header_branch_offset_offset = (while_loop_header_branch_offset_end - while_loop_header_code_start) - sizeof(signed);
	signed header_branch_offset = body_code.size() + footer_code.size() + (while_loop_header_code_end - while_loop_header_branch_offset_end);

	unsigned long footer_branch_offset_offset = (while_loop_footer_branch_offset_end - while_loop_footer_code_start) - sizeof(signed);
	signed footer_branch_offset = -body_code.size() - header_code.size() - (while_loop_footer_branch_offset_end - while_loop_footer_code_start);

	std::memcpy(&*(header_code.begin() + header_branch_offset_offset), &header_branch_offset, sizeof(signed));
	std::memcpy(&*(footer_code.begin() + footer_branch_offset_offset), &footer_branch_offset, sizeof(signed));

	return Command{
		0, 0, required_stack_depth,
		header_code + body_code + footer_code
	};
}
