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
class node;

template <typename T, typename ...Args>
inline node<T> *make_node(Args&& ...args) {
	return new node<T>(std::forward<Args>(args)...);
}

template <typename T, typename ...Args>
using root = std::shared_ptr<node<T>>;

template <typename T, typename ...Args>
inline root<T> make_root(Args&& ...args) {
	return std::make_shared<node<T>>(std::forward<Args>(args)...);
}

template <typename T>
class node {
	T item_;
	std::vector<node<T> *> nodes_;

	using node_pointer = node<T> *;

public:
// TODO: inheritance from std::vector iterators and make own
//	using iterator = typename std::vector<node<T>>::iterator;
//	using const_iterator = typename std::vector<node<T>>::const_iterator;
//	using reverse_iterator = typename std::vector<node<T>>::reverse_iterator;
//	using const_reverse_iterator = typename std::vector<node<T>>::const_reverse_iterator;

	node(const T& item, std::size_t size = 0) : item_(item), nodes_(size) {}

	node(const node<T>& node_) = delete;

	node(node<T>&& node_) noexcept {
		std::swap(item_, node_.item_);
		std::swap(nodes_, node_.nodes_);
	}

	node<T> *operator=(const node<T>& lhs) = delete;

	node<T>& operator=(node<T>&& lhs) noexcept {
		std::swap(item_, lhs.item_);
		std::swap(nodes_, lhs.nodes_);
		return *this;
	}

	void deleteNode(std::size_t idx) {
		if (idx >= nodes_.size())
			throw std::runtime_error("id missmatch");

		if (nodes_[idx])
			delete nodes_[idx];
	}

	std::size_t size() const {
		return nodes_.size();
	}

	bool isLeaf() const {
		return size() == 0;
	}

	node_pointer& get(std::size_t idx) {
		if (idx >= nodes_.size())
			throw std::runtime_error("id missmatch");
		return nodes_[idx];
	}

	node_pointer& get(std::size_t idx) const {
		if (idx >= nodes_.size())
			throw std::runtime_error("id missmatch");

		return nodes_[idx];
	}

	node<T>& operator=(const T& val) {
		item_ = val;
		return *this;
	}

	node<T>& operator=(T&& val) {
		std::swap(item_, val);
		return *this;
	}

	operator T() {
		return item_;
	}

	~node() {
		for (size_t i = 0; i < size(); ++i)
			deleteNode(i);
	}
};

} // end libmenu::types namespace

#endif //LIBMENU_TREE_HPP
