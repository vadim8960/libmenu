//
// Created by vadim on 09.08.23.
//

#include "MenuItem.hpp"

bool LibMenu::MenuItem::isRoot() const {
	return _parent == nullptr;
}

LibMenu::MenuItem* LibMenu::MenuItem::getParent() {
	return _parent;
}

const LibMenu::MenuItem* LibMenu::MenuItem::getParent() const {
	return _parent;
}
