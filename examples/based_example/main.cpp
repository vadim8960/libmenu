#include <iostream>

#include "libmenu/internal/tree.hpp"

using namespace libmenu::types;

int main() {

	node<int> n{5, 5};
	n.addNode<0>(n);
	return 0;
}