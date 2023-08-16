#include <iostream>

#include <libmenu/Menu.hpp>
#include <thread>

void func1(int a) {
	std::cout << "func1 with arguments: a = " << a << std::endl;
}

void func2(int a, int& b) {
	std::cout << "func2 with arguments: a = " << a << ", b = " << b << std::endl;
}

struct A {
	int b;
};

void func_class(A& a) {
	std::cout << "func_class with b = " << a.b << std::endl;
}

void func3(int a, int b, int c) {}

void func4(int a, int b, int c, int d) {}

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
			std::apply(_func, _args);
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
	auto call1 = make_call(func1, 5);
	call1();
	int n = 10;
	auto call2 = make_call(func2, 1, std::move(n));
	call2();
	A classs;
	classs.b = 100;
	auto call_class = make_call(func_class, std::move(classs));
	call_class();
//	decltype(&func1) f1 = func1;
//	void (* f)(int) = wrapper<decltype(&func1), &func1>;
//	void (* f2)(int, int) = wrapper<void (*)(int, int), &func2>;
//	std::thread t;
//	function(&func1, 1);
//	function(&func2, 1, 2);
//	std::invoke(func1, 1);
//	int* a = new int(6);
//	LibMenu::MenuItem item;
//	item.registerCallback(fun, a);
//	item.execute();
	return 0;
}
