#pragma once

#include <string>
#include <vector>

class Command {
private:
	unsigned m_param_count;
	unsigned m_return_count;
	unsigned m_required_stack_depth;
	std::string m_code;

	Command(unsigned param_count, unsigned return_count, std::string const &code)
	: Command(param_count, return_count, 0, code)
	{}
	Command(unsigned param_count, unsigned return_count, unsigned required_stack_depth, std::string const &code)
	: m_param_count(param_count),
	  m_return_count(return_count),
	  m_required_stack_depth(required_stack_depth),
	  m_code(code)
	{}
public:
	Command(Command const&) = default;
	Command(Command&&) = default;
	Command &operator=(Command const&) = default;
	Command &operator=(Command&&) = default;
	~Command() = default;

	std::string code() const { return m_code; }

	unsigned param_count() const { return m_param_count; }
	unsigned return_count() const { return m_return_count; }
	unsigned required_stack_depth() const { return m_required_stack_depth; }

	static Command push_a, push_b, push_c, push_d, push_e, push_f;

	static Command push_value(long value);

	static Command add, subtract, multiply, divide, mod, udivide, umod;

	static Command push_stack_index(unsigned index);
	static Command pop_stack_index(unsigned index);

	static Command while_loop(std::vector<Command> const &commands);
};
