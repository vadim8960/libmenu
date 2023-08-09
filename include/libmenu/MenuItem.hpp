//
// Created by vadim on 09.08.23.
//

#ifndef LIBMENU_MENUITEM_HPP
#define LIBMENU_MENUITEM_HPP

namespace LibMenu {

class MenuItem {
public:
	MenuItem() = default;
	explicit MenuItem(MenuItem* parent) : _parent(parent) {}

	bool isRoot() const;

	MenuItem* getParent();
	const MenuItem* getParent() const;

private:
	MenuItem* _parent{};
};

}

#endif //LIBMENU_MENUITEM_HPP
