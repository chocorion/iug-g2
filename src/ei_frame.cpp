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

	Frame::Frame(Widget* parent)
	{
		super(parent);
	}

	Frame::~Frame()
	{
		super();
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

	}
};

}