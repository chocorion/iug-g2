/**
 * @file    ei_frame.cpp
 *
 * @brief   Definition of a widget
 *
 *  Created by Adrien Boitelle on 15.02.19.
 */

#include "ei_widget.h"


using namespace std;

namespace ei {

	Button::Button(Widget* parent) : Widget("Button", parent)
	{
		
	}

	Button::~Button()
	{
	}

	void Button::draw(surface_t surface,
		surface_t pick_surface,
		Rect*     clipper)
	{
	}

	void Button::configure(Size *requested_size,
                   const color_t *color,
                   int *border_width,
                   int *corner_radius,
                   relief_t *relief,
                   const char **text,
                   font_t *text_font,
                   color_t *text_color,
                   anchor_t *text_anchor,
                   surface_t *img,
                   Rect **img_rect,
                   anchor_t *img_anchor)
	{
		this->requested_size = *requested_size;
		this->color = color;
		this->border_width = border_width;
		this->relief = relief;
		this->text = text;
		this->text_font = text_font;
		this->text_color = text_color;
		this->text_anchor = text_anchor;
		this->img = img;
		this->img_rect = img_rect;
		this->img_anchor;
	}
};
