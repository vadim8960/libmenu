//
// Created by vadim on 21.09.23.
//

#ifndef LIBMENU_TREE_HPP
#define LIBMENU_TREE_HPP

#include <vector>
#include <array>
#include <memory>

namespace libmenu::types { // begin libmenu::types namespace

using std::shared_ptr;
using std::vector;
using std::array;
using std::size_t;
using std::make_shared;

template <typename T>
class node {
	T item_;
	vector<shared_ptr<node>> nodes_;

public:
	node(T item, size_t size) : nodes_(size) {
		item_ = item;
	}

	node(const node& other) {
		item_ = other.item_;
		nodes_ = other.nodes_;
	}

	node& operator=(const node& other) {
		item_ = other.item_;
		nodes_ = other.nodes_;
	}

	template <const size_t ID>
	void addNode(node<T>& node) {
		nodes_[ID] = node;
	}
};

} // end libmenu::types namespace

#endif //LIBMENU_TREE_HPP
