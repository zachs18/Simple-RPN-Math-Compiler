#include "Command.hpp"
#include <cstring> // memcpy

asm(R"(
.Lpush_a_code_start:
	mov	-8(%rbp),%rax
	push	%rax
.Lpush_a_code_end:
)");

extern char push_a_code_start[] asm(".Lpush_a_code_start");
extern char push_a_code_end[] asm(".Lpush_a_code_end");

Command Command::push_a{
	0, 1,
	std::string{
		push_a_code_start,
		push_a_code_end
	}
};


asm(R"(
.Lpush_b_code_start:
	mov	-16(%rbp),%rax
	push	%rax
.Lpush_b_code_end:
)");

extern char push_b_code_start[] asm(".Lpush_b_code_start");
extern char push_b_code_end[] asm(".Lpush_b_code_end");

Command Command::push_b{
	0, 1,
	std::string{
		push_b_code_start,
		push_b_code_end
	}
};


asm(R"(
.Lpush_c_code_start:
	mov	-24(%rbp),%rax
	push	%rax
.Lpush_c_code_end:
)");

extern char push_c_code_start[] asm(".Lpush_c_code_start");
extern char push_c_code_end[] asm(".Lpush_c_code_end");

Command Command::push_c{
	0, 1,
	std::string{
		push_c_code_start,
		push_c_code_end
	}
};


asm(R"(
.Lpush_d_code_start:
	mov	-32(%rbp),%rax
	push	%rax
.Lpush_d_code_end:
)");

extern char push_d_code_start[] asm(".Lpush_d_code_start");
extern char push_d_code_end[] asm(".Lpush_d_code_end");

Command Command::push_d{
	0, 1,
	std::string{
		push_d_code_start,
		push_d_code_end
	}
};


asm(R"(
.Lpush_e_code_start:
	mov	-40(%rbp),%rax
	push	%rax
.Lpush_e_code_end:
)");

extern char push_e_code_start[] asm(".Lpush_e_code_start");
extern char push_e_code_end[] asm(".Lpush_e_code_end");

Command Command::push_e{
	0, 1,
	std::string{
		push_e_code_start,
		push_e_code_end
	}
};


asm(R"(
.Lpush_f_code_start:
	mov	-48(%rbp),%rax
	push	%rax
.Lpush_f_code_end:
)");

extern char push_f_code_start[] asm(".Lpush_f_code_start");
extern char push_f_code_end[] asm(".Lpush_f_code_end");

Command Command::push_f{
	0, 1,
	std::string{
		push_f_code_start,
		push_f_code_end
	}
};


asm(R"(
.Ladd_code_start:
	pop	%rax
	add	%rax,(%rsp)
.Ladd_code_end:
)");

extern char add_code_start[] asm(".Ladd_code_start");
extern char add_code_end[] asm(".Ladd_code_end");

Command Command::add{
	2, 1,
	std::string{
		add_code_start,
		add_code_end
	}
};


asm(R"(
.Lsubtract_code_start:
	pop	%rax
	sub	%rax,(%rsp)
.Lsubtract_code_end:
)");

extern char subtract_code_start[] asm(".Lsubtract_code_start");
extern char subtract_code_end[] asm(".Lsubtract_code_end");

Command Command::subtract{
	2, 1,
	std::string{
		subtract_code_start,
		subtract_code_end
	}
};


asm(R"(
.Lmultiply_code_start:
	pop	%rax
	mulq	(%rsp)
	mov	%rax,(%rsp)
.Lmultiply_code_end:
)");

extern char multiply_code_start[] asm(".Lmultiply_code_start");
extern char multiply_code_end[] asm(".Lmultiply_code_end");

Command Command::multiply{
	2, 1,
	std::string{
		multiply_code_start,
		multiply_code_end
	}
};


asm(R"(
.Ldivide_code_start:
	pop	%rcx
	xor	%rdx,%rdx
	mov	(%rsp),%rax
	idiv	%rcx
	mov	%rax,(%rsp)
.Ldivide_code_end:
)");

extern char divide_code_start[] asm(".Ldivide_code_start");
extern char divide_code_end[] asm(".Ldivide_code_end");

Command Command::divide{
	2, 1,
	std::string{
		divide_code_start,
		divide_code_end
	}
};


asm(R"(
.Lmod_code_start:
	pop	%rcx
	xor	%rdx,%rdx
	mov	(%rsp),%rax
	idiv	%rcx
	mov	%rdx,(%rsp)
.Lmod_code_end:
)");

extern char mod_code_start[] asm(".Lmod_code_start");
extern char mod_code_end[] asm(".Lmod_code_end");

Command Command::mod{
	2, 1,
	std::string{
		mod_code_start,
		mod_code_end
	}
};


asm(R"(
.Ludivide_code_start:
	pop	%rcx
	xor	%rdx,%rdx
	mov	(%rsp),%rax
	div	%rcx
	mov	%rax,(%rsp)
.Ludivide_code_end:
)");

extern char udivide_code_start[] asm(".Ludivide_code_start");
extern char udivide_code_end[] asm(".Ludivide_code_end");

Command Command::udivide{
	2, 1,
	std::string{
		udivide_code_start,
		udivide_code_end
	}
};


asm(R"(
.Lumod_code_start:
	pop	%rcx
	xor	%rdx,%rdx
	mov	(%rsp),%rax
	div	%rcx
	mov	%rdx,(%rsp)
.Lumod_code_end:
)");

extern char umod_code_start[] asm(".Lumod_code_start");
extern char umod_code_end[] asm(".Lumod_code_end");

Command Command::umod{
	2, 1,
	std::string{
		umod_code_start,
		umod_code_end
	}
};


asm(R"(
.Lpush_value_code_start:
	movabs	$0,%rax
.Lpush_value_value_end:
	push	%rax
.Lpush_value_code_end:
)");

extern char push_value_code_start[] asm(".Lpush_value_code_start");
extern char push_value_value_end[] asm(".Lpush_value_value_end");
extern char push_value_code_end[] asm(".Lpush_value_code_end");

Command Command::push_value(long value) {
	std::string code{push_value_code_start, push_value_code_end};
	std::memcpy(&*(code.end()-(push_value_code_end-push_value_value_end)-8), &value, 8);
	return Command{
		0, 1,
		std::move(code)
	};
}
