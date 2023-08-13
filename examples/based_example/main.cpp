#include <iostream>

#include <libmenu/Menu.hpp>

void fun(int* a) {
	std::cout << *a << std::endl;
}

int main() {
	int* a = new int(6);
	LibMenu::MenuItem<int> item;
	item.registerCallback(fun, a);
	item.execute();
	return 0;
}
