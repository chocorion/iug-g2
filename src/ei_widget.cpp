/**
 * @file    ei_widget.cpp
 *
 * @brief   API for widgets management: creation, configuration, hierarchy, redisplay.
 *
 *  Created by Adrien Boitelle on 04.02.19.
 *  Edited by Robin Navarro.
 */

#include "ei_widget.h"
#include "ei_geometrymanager.h"

#include <functional>
#include <iostream>

using namespace std;

namespace ei {

	uint32_t Widget::s_idGenerator = 0;

	/**
	 * \brief   Abstract class representing a widget
	 *          Every widget class specializes this base class by adding its own attributes.
	 */
	Widget::Widget(const widgetclass_name_t& class_name, Widget* parent) 
	{		
		name = class_name;
		parent = parent; // null if root
		geom_manager = nullptr;

		pick_id = s_idGenerator;
		s_idGenerator++;
		
		unsigned char red = (pick_id & 0xff000000) >> 24;
		unsigned char green = (pick_id & 0x00ff0000) >> 16;
		unsigned char blue = (pick_id & 0x0000ff00) >> 8;
		unsigned char alpha = (pick_id & 0x000000ff);

		pick_color = {red,green,blue,alpha};
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

	void Widget::draw(surface_t surface,
		surface_t pick_surface,
		Rect*     clipper)
	{
		if(geom_manager) {
			geom_manager->run(this);
		}

		for(Widget* child : children)
		{
			child->draw(surface, pick_surface, clipper);
		}
	}
	void Widget::geomnotify(Rect rect) {
		this->screen_location = rect;
	}

	uint32_t Widget::getPick_id() const
	{
		return pick_id;
	}

	color_t Widget::get_pick_color() const
	{
		return pick_color;
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
	
	void Widget::setGeometryManager(GeometryManager *geometryManager)
	{
		geom_manager = geometryManager;
	}

	Rect* Widget::getContentRect() const
	{
		return content_rect;
	}

	const Rect* Widget::getScreenLocation() const
	{
		return &screen_location;
	}
}