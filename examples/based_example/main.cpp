#include <iostream>

#include "libmenu/internal/tree.hpp"

using namespace libmenu::types;

int main() {
	auto n = make_node<int>(5, 5);

	for (int i = 0; i < 5; ++i)
		n->addNode(make_node<int>(i, 5), i);

	std::cout << *n << '\n';
	*n = 10;
	std::cout << *n << '\n';

	n->deleteNode(0);
	n->addNode(make_node<int>(0), 0);
	n->deleteNode(1);
	n->deleteNode(2);
	n->deleteNode(3);
	n->deleteNode(4);

	asm("nop");
	return 0;
}