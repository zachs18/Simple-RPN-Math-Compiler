#include "Command.hpp"
#include <cstring> // memcpy

extern char push_a_code_start[];
extern char push_a_code_end[];

const Command Command::push_a{
	0, 1,
	std::string{
		push_a_code_start,
		push_a_code_end
	}
};


extern char push_b_code_start[];
extern char push_b_code_end[];

const Command Command::push_b{
	0, 1,
	std::string{
		push_b_code_start,
		push_b_code_end
	}
};


extern char push_c_code_start[];
extern char push_c_code_end[];

const Command Command::push_c{
	0, 1,
	std::string{
		push_c_code_start,
		push_c_code_end
	}
};


extern char push_d_code_start[];
extern char push_d_code_end[];

const Command Command::push_d{
	0, 1,
	std::string{
		push_d_code_start,
		push_d_code_end
	}
};


extern char push_e_code_start[];
extern char push_e_code_end[];

const Command Command::push_e{
	0, 1,
	std::string{
		push_e_code_start,
		push_e_code_end
	}
};


extern char push_f_code_start[];
extern char push_f_code_end[];

const Command Command::push_f{
	0, 1,
	std::string{
		push_f_code_start,
		push_f_code_end
	}
};


extern char and_code_start[];
extern char and_code_end[];

const Command Command::and_{
	2, 1,
	std::string{
		and_code_start,
		and_code_end
	}
};


extern char xor_code_start[];
extern char xor_code_end[];

const Command Command::xor_{
	2, 1,
	std::string{
		xor_code_start,
		xor_code_end
	}
};


extern char or_code_start[];
extern char or_code_end[];

const Command Command::or_{
	2, 1,
	std::string{
		or_code_start,
		or_code_end
	}
};


extern char add_code_start[];
extern char add_code_end[];

const Command Command::add{
	2, 1,
	std::string{
		add_code_start,
		add_code_end
	}
};


extern char subtract_code_start[];
extern char subtract_code_end[];

const Command Command::subtract{
	2, 1,
	std::string{
		subtract_code_start,
		subtract_code_end
	}
};


extern char multiply_code_start[];
extern char multiply_code_end[];

const Command Command::multiply{
	2, 1,
	std::string{
		multiply_code_start,
		multiply_code_end
	}
};


extern char divide_code_start[];
extern char divide_code_end[];

const Command Command::divide{
	2, 1,
	std::string{
		divide_code_start,
		divide_code_end
	}
};


extern char mod_code_start[];
extern char mod_code_end[];

const Command Command::mod{
	2, 1,
	std::string{
		mod_code_start,
		mod_code_end
	}
};


extern char udivide_code_start[];
extern char udivide_code_end[];

const Command Command::udivide{
	2, 1,
	std::string{
		udivide_code_start,
		udivide_code_end
	}
};


extern char umod_code_start[];
extern char umod_code_end[];

const Command Command::umod{
	2, 1,
	std::string{
		umod_code_start,
		umod_code_end
	}
};


extern char push_value_code_start[];
extern char push_value_value_end[];
extern char push_value_code_end[];

Command Command::push_value(long value) {
	std::string code{push_value_code_start, push_value_code_end};
	std::memcpy(&*(code.end()-(push_value_code_end-push_value_value_end)-8), &value, 8);
	return Command{
		0, 1,
		std::move(code)
	};
}


extern char push_from_stack_index_top_code_start[];
extern char push_from_stack_index_top_value_end[];
extern char push_from_stack_index_top_code_end[];

Command Command::push_from_stack_index_top(unsigned index) {
	std::string code{push_from_stack_index_top_code_start, push_from_stack_index_top_code_end};
	std::memcpy(&*(code.end()-(push_from_stack_index_top_code_end-push_from_stack_index_top_value_end)-4), &index, 4);
	return Command{
		0, 1, index+1,
		std::move(code)
	};
}


extern char pop_to_stack_index_top_code_start[];
extern char pop_to_stack_index_top_value_end[];
extern char pop_to_stack_index_top_code_end[];

Command Command::pop_to_stack_index_top(unsigned index) {
	std::string code{pop_to_stack_index_top_code_start, pop_to_stack_index_top_code_end};
	std::memcpy(&*(code.end()-(pop_to_stack_index_top_code_end-pop_to_stack_index_top_value_end)-4), &index, 4);
	return Command{
		1, 0, index+2,
		std::move(code)
	};
}


extern char push_from_stack_index_bottom_code_start[];
extern char push_from_stack_index_bottom_value_end[];
extern char push_from_stack_index_bottom_code_end[];

Command Command::push_from_stack_index_bottom(unsigned index) {
	unsigned negative_index = -index;
	std::string code{push_from_stack_index_bottom_code_start, push_from_stack_index_bottom_code_end};
	std::memcpy(&*(code.end()-(push_from_stack_index_bottom_code_end-push_from_stack_index_bottom_value_end)-4), &negative_index, 4);
	return Command{
		0, 1, index+1,
		std::move(code)
	};
}


extern char pop_to_stack_index_bottom_code_start[];
extern char pop_to_stack_index_bottom_value_end[];
extern char pop_to_stack_index_bottom_code_end[];

Command Command::pop_to_stack_index_bottom(unsigned index) {
	unsigned negative_index = -index;
	std::string code{pop_to_stack_index_bottom_code_start, pop_to_stack_index_bottom_code_end};
	std::memcpy(&*(code.end()-(pop_to_stack_index_bottom_code_end-pop_to_stack_index_bottom_value_end)-4), &negative_index, 4);
	return Command{
		1, 0, index+2,
		std::move(code)
	};
}
