#include <iostream>

#include "libmenu/internal/tree.hpp"

using namespace libmenu::types;

int main() {

	root<int> n = make_root<int>(5, 5);

	for (int i = 0; i < n->size(); ++i) {
		n->get(i) = make_node<int>(i, 5);
		auto& temp_node = n->get(i);
		for (int j = 0; j < temp_node->size(); ++j) {
			temp_node->get(j) = make_node<int>(i, 5);
		}
	}

	std::cout << *n << '\n';
	*n = 10;
	std::cout << *n << '\n' << '\n';

	std::cout << *(n->get(2)) << std::endl;
	*(n->get(2)) = 5;
	std::cout << *(n->get(2)) << std::endl;
	*n->get(2) = 10;
	std::cout << *(n->get(2)) << std::endl;

	asm("nop");
	return 0;
}