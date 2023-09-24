//
// Created by vadim on 21.09.23.
//

#ifndef LIBMENU_TREE_HPP
#define LIBMENU_TREE_HPP

#include <vector>
#include <memory>
#include <optional>
#include <cstring>
#include <iterator>
#include <cstddef>

namespace libmenu::types { // begin libmenu::types namespace

template <typename T>
class node_type;

template <typename T>
using node = std::shared_ptr<node_type<T>>;

template <typename T, typename ...Args>
inline node<T> make_node(Args&& ... args) {
	return std::make_shared<node_type<T>>(args...);
}

template <typename T>
class node_type {
	T item_;
	std::vector<node<T>> nodes_;

public:
// TODO: inheritance from std::vector iterators and make own
//	using iterator = typename std::vector<node<T>>::iterator;
//	using const_iterator = typename std::vector<node<T>>::const_iterator;
//	using reverse_iterator = typename std::vector<node<T>>::reverse_iterator;
//	using const_reverse_iterator = typename std::vector<node<T>>::const_reverse_iterator;

	node_type(const T& item, std::size_t size = 0) : item_(item), nodes_(size) {}

	void addNode(const node<T>& node, std::size_t idx) {
		if (idx >= nodes_.size())
			throw std::runtime_error("id missmatch");

		nodes_[idx] = node;
	}

	void deleteNode(std::size_t idx) {
		if (idx >= nodes_.size() || nodes_[idx] == nullptr)
			throw std::runtime_error("id missmatch");
		nodes_[idx].reset();
	}

	void getSize() const {
		return nodes_.size();
	}

	bool isLeaf() const {
		return getSize() > 0;
	}

	node<T> operator[](std::size_t idx) {
		if (idx >= nodes_.size() || nodes_[idx] == nullptr)
			throw std::runtime_error("id missmatch");
		return nodes_[idx];
	}

	node<T> operator[](std::size_t idx) const {
		if (idx >= nodes_.size() || nodes_[idx] == nullptr)
			throw std::runtime_error("id missmatch");

		return nodes_[idx];
	}

	node_type<T>& operator=(const T& val) {
		item_ = val;
		return *this;
	}

	node_type<T>& operator=(T&& val) {
		std::swap(item_, val);
		return *this;
	}

	operator T() {
		return item_;
	}
};

} // end libmenu::types namespace

#endif //LIBMENU_TREE_HPP
