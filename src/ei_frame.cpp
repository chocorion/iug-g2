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

	Frame::Frame(Widget* parent) : Widget("Frame", parent)
	{
		
	}

	Frame::~Frame()
	{
	}

	void Frame::draw(surface_t surface,
		surface_t pick_surface,
		Rect*     clipper)
	{
	}

	void Frame::configure(Size*           requested_size,
		const color_t*  color,
		int*            border_width,
		relief_t*       relief,
		char**          text,
		font_t*         text_font,
		color_t*        text_color,
		anchor_t*       text_anchor,
		surface_t*      img,
		Rect**          img_rect,
		anchor_t*       img_anchor)
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
