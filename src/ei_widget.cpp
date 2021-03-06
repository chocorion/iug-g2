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
#include "ei_eventmanager.h"

#include <functional>
#include <iostream>

using namespace std;

namespace ei {

	typedef struct {
		ei_callback_t* callbacks;
		Widget* widget;
	} param_t;

	uint32_t Widget::s_idGenerator = 0;

	/**
	 * \brief   Abstract class representing a widget
	 *          Every widget class specializes this base class by adding its own attributes.
	 */
	Widget::Widget(const widgetclass_name_t& class_name, Widget* parent): visibleState(true), name(class_name), parent(parent)
	{		
		geom_manager = nullptr;

		pick_id = s_idGenerator;
		s_idGenerator++;
		
		unsigned char red = (pick_id & 0x00ff0000) >> 16;
		unsigned char green = (pick_id & 0x0000ff00) >> 8;
		unsigned char blue = (pick_id & 0x000000ff);
		unsigned char alpha = 255;

		pick_color = {red,green,blue,alpha};

		if (parent)
		{
			parent->addChild(this);
		}

		content_rect = &screen_location;

    	EventManager::getInstance().bind(ei_ev_mouse_buttondown, this, "", this->focus, nullptr);
	}

	/**
	 * @brief   Destroys the widget. Removes it from screen if it is managed by a geometry manager.
	 *          Destroys all its descendants.
	 */
	Widget::~Widget()
	{
		return;

		//Dans le cas ou le parent n'est pas alloué dynamiquement ça plante...

		// for(Widget* child : children)
		// {
		// 	delete child;
		// }
		// TODO: actual cleaning
	}

	Widget *Widget::pick(uint32_t id)
	{
		if (pick_id == id) {
			// TODO: pick
		} 

		return nullptr;
	}


	void Widget::drawOffscreen(surface_t pick_surface, Rect *clipper)
	{
		//If clipper is null, we use screen location
		Rect where = (clipper)? limitRectToClipper(clipper) : screen_location;

		surface_t pick = hw_surface_create(pick_surface, &where.size);
		fill(pick, &pick_color, EI_FALSE);
		ei_copy_surface(pick_surface, pick, &where.top_left, EI_FALSE);
		hw_surface_free(pick);
	}

	Rect Widget::limitRectToClipper(Rect *clipper){
        
		int x = 0, y = 0;
		float width = screen_location.size.width();
		float height = screen_location.size.height();


		if(screen_location.top_left.x() < clipper->top_left.x())
		{
			x = clipper->top_left.x();
			width -= x - screen_location.top_left.x();
		}
		else if(screen_location.top_left.x() > clipper->top_left.x() + clipper->size.width())
			return Rect(Point(0, 0), Size(0, 0));
		else
			x = screen_location.top_left.x();
	
		if(screen_location.top_left.y() < clipper->top_left.y())
		{
			y = clipper->top_left.y();
			height -= y - screen_location.top_left.y();
		}
		else if(screen_location.top_left.y() > clipper->top_left.y() + clipper->size.height())
			return Rect(Point(0, 0), Size(0, 0));
		else
			y = screen_location.top_left.y();



		if(x + width > clipper->top_left.x() + clipper->size.width())
		{
			width = clipper->top_left.x() + clipper->size.width() - x;
		}

		if(y + height > clipper->top_left.y() + clipper->size.height())
		{
			height = clipper->top_left.y() + clipper->size.height() - y;
		}
		

		return Rect(Point(x, y), Size(width, height));

	}

	void Widget::draw(surface_t surface,
		surface_t pick_surface,
		Rect*     clipper)
	{
		drawOffscreen(pick_surface, clipper);
	}
	
	void Widget::geomnotify(Rect rect) {
		this->screen_location = rect;
	}

	void Widget::addChild(Widget* widget)
	{
		children.push_back(widget);
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

	bool_t Widget::focus(Widget* target, Event* event, void* user_param)
	{
		if(target->parent)
		{
			// Refocus toplevel widgets only
			if(target->name == "Toplevel")
			{
				target->parent->children.remove(((Widget*) target));
				target->parent->children.push_back(((Widget*) target));
			}

			if(target->parent->parent) {
				focus(target->parent, event, nullptr);
			} 
		}

		//Event can by used for another callback
		return EI_FALSE;
	}

	bool Widget::getVisibleState() const {
		return visibleState;
	}

	void Widget::setVisibleState(bool state) {
		visibleState = state;
	}
}