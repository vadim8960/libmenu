#include <iostream>
#include <tuple>

#include <libmenu/Menu.hpp>
#include <thread>

struct A {
	int b{};
	A() {}
	A(A&& other) {
		b = other.b;
		other.b = 0;
	}
	A(const A& other) {
		b = other.b;
	}
};

void func1(int a) {
	std::cout << "func1 with arguments: a = " << a << std::endl;
}

void func2(int a, int& b) {
	std::cout << "func2 with arguments: a = " << a << ", b = " << b << std::endl;
}

void func_class(A& a) {
	std::cout << "func_class with b = " << a.b << std::endl;
}

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

int main() {
//	std::tuple<int, int> t1 = std::make_tuple(5, 6);
//	execute(func2, t1);
//	std::tuple<A> t3 = std::make_tuple(A());
//	execute(func_class, t3);

	int a = 6;
	auto call = make_call(func2, 5, std::forward<int>(a));
	call();

//	int* a = new int(6);
//	LibMenu::MenuItem item;
//	item.registerCallback(fun, a);
//	item.execute();
	return 0;
}
