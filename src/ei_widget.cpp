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

			// TODO: root ?
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
			// TODO: actual cleaning
		}

		Widget* pick(uint32_t id)
		{
			if (this.pick_id == id) {
				// TODO: pick
			} 
		}
		uint32_t getPick_id() const
		{
			return pick_id;
		}

		Widget *getParent() const
		{
			return this.parent;
		}
	};
}