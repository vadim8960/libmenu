//
// Created by vadim on 23.08.23.
//

#ifndef LIBMENU_CALLABLE_HPP
#define LIBMENU_CALLABLE_HPP

#include <tuple>

template< typename Callable, typename Tuple, bool IsEnd, int Idx, int ...N >
struct execute_impl {
	static void execute(Callable f, Tuple&& tuple) {
		return execute_impl<Callable, Tuple,
							Idx == 1 + sizeof...(N),
							Idx,
							N...,
							sizeof...(N)>::execute(f, tuple);
	}
};

template< typename Callable, typename Tuple, int Idx, int ...N >
struct execute_impl<Callable, Tuple, true, Idx, N...> {
	static void execute(Callable f, Tuple&& tuple) {
		if (f) {
			return f(std::get<N>(std::forward<Tuple>(tuple))...);
		}
	}
};

template< typename Callable, typename Tuple, int... N >
void execute(Callable f, Tuple&& t) {
	typedef typename std::decay<Tuple>::type type;
	execute_impl<Callable, Tuple,
				 0 == std::tuple_size<type>::value,
				 std::tuple_size<type>::value>::execute(f, std::forward<Tuple>(t));
}

template< typename Callable, typename ...Args >
class Call {
	std::tuple<Args...> _args;
	Callable _func;
public:
	Call() = default;
	explicit Call(Callable func, Args&& ...args) : _func(func),
												   _args(std::make_tuple(std::forward<Args>(args)...)) {}
	void operator()() {
		if (_func)
			execute(_func, _args);
	}

	Call(const Call& other) {
		_args = other._args;
		_func = other._func;
	}

	Call(Call&& other) {
		_args = other._args;
		_func = other._func;
		other._args = {};
		other._func = nullptr;
	}

	Call& operator=(const Call& other) {
		_args = other._args;
		_func = other._func;
		return *this;
	}

	Call& operator=(Call&& other) {
		_args = other._args;
		_func = other._func;
		other._args = {};
		other._func = nullptr;
		return *this;
	}
};

template< typename Callable, typename ...Args >
Call<Callable, Args...> make_call(Callable callable, Args&& ...args) {
	return Call(std::forward<Callable>(callable), std::forward<Args>(args)...);
}

#endif //LIBMENU_CALLABLE_HPP
