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
	class Widget
	{
	public:

		/**
		 * @brief   Construct a new instance of a widget of some particular class, as a descendant of an existing widget.
		 *
		 *      The widget is not displayed on screen until it is managed by a geometry manager.
		 *
		 * @param   class_name  The name of the class of the widget that is to be created.
		 * @param   parent      A pointer to the parent widget. Cannot be NULL except for the root widget.
		 */
		Widget(const widgetclass_name_t& class_name, Widget* parent) 
		{
			this.widgetclass_name_t = class_name;
			this.parent = parent;
		}

		/**
		 * @brief   Destroys the widget. Removes it from screen if it is managed by a geometry manager.
		 *          Destroys all its descendants.
		 */
		virtual ~Widget()
		{
			foreach(Widget child : this.children)
			{
				delete child;
			}
		}

		/**
		 * \brief   Method that draws the widget.
		 *
		 * @param   surface     Where to draw the widget. The actual location of the widget in the
		 *                      surface is stored in its "screen_location" field.
		 * @param   pick_surface  Offscreen buffer to draw the widget \ref pick_id
		 * @param   clipper     If not NULL, the drawing is restricted within this rectangle
		 *                      (expressed in the surface reference frame).
		 */
		virtual void draw(surface_t surface, surface_t pick_surface, Rect* clipper) 
		{

		}

		/**
		 * \brief   Method that is called to notify the widget that its geometry has been modified
		 *      by its geometry manager.
		 *
		 * @param   rect        The new rectangular screen location of the widget
		 *                      (i.e., = widget->screen_location).
		 */
		virtual void geomnotify(Rect rect)
		{

		}

		Widget* pick(uint32_t id)
		{

		}
		uint32_t getPick_id() const
		{

		}

		Widget *getParent() const
		{

		}
	};
}