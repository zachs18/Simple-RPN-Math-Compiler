#pragma once

#include <vector>
#include <memory>

#include "Command.hpp"

namespace detail {
	template<int Argc>
	struct helper;

	template<>
	struct helper<0> { using type = long(); };
	template<>
	struct helper<1> { using type = long(long); };
	template<>
	struct helper<2> { using type = long(long,long); };
	template<>
	struct helper<3> { using type = long(long,long,long); };
	template<>
	struct helper<4> { using type = long(long,long,long,long); };
	template<>
	struct helper<5> { using type = long(long,long,long,long,long); };
	template<>
	struct helper<6> { using type = long(long,long,long,long,long,long); };
};

class Function {
private:
	std::vector<Command> m_commands;
	std::shared_ptr<void> m_code;

	template<int Argc>
	using helper = detail::helper<Argc>;

public:
	Function(std::vector<Command> &&commands);

	template<int Argc>
	typename helper<Argc>::type *get(void) const& {
		return reinterpret_cast<typename helper<Argc>::type*>(m_code.get());
	}

	template<int Argc>
	std::shared_ptr<typename helper<Argc>::type> get_shared(void) const {
		return std::shared_ptr<typename helper<Argc>::type>{
			m_code,
			reinterpret_cast<typename helper<Argc>::type*>(m_code.get())
		};
	}

	operator std::shared_ptr<long(long,long)>(void) const {
		return std::shared_ptr<long(long,long)>{
			m_code,
			reinterpret_cast<long(*)(long,long)>(m_code.get())
		};
	}

	operator std::shared_ptr<long(long,long,long)>(void) const {
		return std::shared_ptr<long(long,long,long)>{
			m_code,
			reinterpret_cast<long(*)(long,long,long)>(m_code.get())
		};
	}

	operator std::shared_ptr<long(long,long,long,long)>(void) const {
		return std::shared_ptr<long(long,long,long,long)>{
			m_code,
			reinterpret_cast<long(*)(long,long,long,long)>(m_code.get())
		};
	}

	operator std::shared_ptr<long(long,long,long,long,long)>(void) const {
		return std::shared_ptr<long(long,long,long,long,long)>{
			m_code,
			reinterpret_cast<long(*)(long,long,long,long,long)>(m_code.get())
		};
	}

	operator std::shared_ptr<long(long,long,long,long,long,long)>(void) const {
		return std::shared_ptr<long(long,long,long,long,long,long)>{
			m_code,
			reinterpret_cast<long(*)(long,long,long,long,long,long)>(m_code.get())
		};
	}
};
