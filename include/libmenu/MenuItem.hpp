//
// Created by vadim on 09.08.23.
//

#ifndef LIBMENU_MENUITEM_HPP
#define LIBMENU_MENUITEM_HPP

#include <functional>

namespace LibMenu {

template< class Context >
using LibMenuCallback = std::function<void(Context*)>;

template< class Context >
class MenuItem {
public:
	MenuItem() = default;
	explicit MenuItem(MenuItem* parent) : _parent(parent) {}

	bool isRoot() const {
		return _parent == nullptr;
	}

	MenuItem* getParent() {
		return _parent;
	}
	const MenuItem* getParent() const {
		return _parent;
	}

	bool registerCallback(LibMenuCallback<Context> callback, Context* context = nullptr) {
		_callback = callback;
		_context = context;
		return true;
	}
	void execute() {
		if (_callback)
			_callback(_context);
	}

private:
	MenuItem* _parent{};
	LibMenuCallback<Context> _callback;
	Context* _context;
};

}

#endif //LIBMENU_MENUITEM_HPP
