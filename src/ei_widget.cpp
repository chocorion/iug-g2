/**
 * @file    ei_widget.cpp
 *
 * @brief   API for widgets management: creation, configuration, hierarchy, redisplay.
 *
 *  Created by Adrien Boitelle on 04.02.19.
 */

#include "ei_widget.h"

#include <functional>

namespace ei {
	/**
	 * \brief   Abstract class representing a widget
	 *          Every widget class specializes this base class by adding its own attributes.
	 */
	Widget::Widget(const widgetclass_name_t& class_name, Widget* parent) 
	{
		name = class_name;
		parent = parent;

		// TODO: root ?
	}

	/**
	 * @brief   Destroys the widget. Removes it from screen if it is managed by a geometry manager.
	 *          Destroys all its descendants.
	 */
	Widget::~Widget()
	{
		for(Widget* child : children)
		{
			delete child;
		}
		// TODO: actual cleaning
	}

	Widget *Widget::pick(uint32_t id)
	{
		if (pick_id == id) {
			// TODO: pick
		} 

		return nullptr;
	}
	uint32_t Widget::getPick_id() const
	{
		return pick_id;
	}

	Widget *Widget::getParent() const
	{
		return parent;
	}

	std::list<Widget *> Widget::getChildren() const
	{
		return children;
	}

	GeometryManager *Widget::getGeometryManager() const
	{
		return geom_manager;
	}

	Size Widget::get_requested_size() const
	{
		return requested_size;
	}
}