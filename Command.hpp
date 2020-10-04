#pragma once

#include <string>

class Command {
private:
	unsigned m_param_count;
	unsigned m_return_count;
	std::string m_code;

	Command(unsigned param_count, unsigned return_count, std::string code)
	: m_param_count(param_count),
	  m_return_count(return_count),
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

	static Command push_a, push_b, push_c, push_d, push_e, push_f;

	static Command push_value(long value);

	static Command add, subtract, multiply, divide, mod, udivide, umod;
};
