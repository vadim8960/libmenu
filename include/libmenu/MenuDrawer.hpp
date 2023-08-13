//
// Created by vadim on 13.08.23.
//

#ifndef LIBMENU_MENUDRAWER_HPP
#define LIBMENU_MENUDRAWER_HPP

#include "MenuDrawerImpl.hpp"

class MenuDrawer {
public:

protected:
	MenuDrawerImpl* getImpl();

private:
	MenuDrawerImpl* _impl;
};

#endif //LIBMENU_MENUDRAWER_HPP
