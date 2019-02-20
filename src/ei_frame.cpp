/**
 * @file    ei_frame.cpp
 *
 * @brief   Definition of a widget
 *
 *  Created by Adrien Boitelle on 15.02.19.
 */

#include "ei_widget.h"
#include <iostream>

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
		Rect base = Rect(Point(screen_location.top_left.x(),screen_location.top_left.y()),Size((double) requested_size.width(),(double) requested_size.height()));
		Rect current = Rect(Point(base.top_left),Size(base.size));

		surface_t pick = hw_surface_create(pick_surface, &base.size);
		fill(pick,&pick_color,EI_TRUE); // warning: check alpha
		ei_copy_surface(pick_surface,pick,&base.top_left,EI_FALSE);
		
		
		for(int i = 0; i < *border_width; i++) {
			printf("%lf-%lf-%d-%d\n",current.size.width(),current.size.height(),current.top_left.x(),current.top_left.y());
			
			/*
			// Polyline does not work

			linked_point_t points;
			points.push_front(Point(current.top_left.x(),current.top_left.y()));
			points.push_front(Point(current.top_left.x() + current.size.width(),current.top_left.y()));
			points.push_front(Point(current.top_left.x() + current.size.width(),current.top_left.y() + current.size.height()));
			points.push_front(Point(current.top_left.x(),current.top_left.y() + current.size.height()));
			points.push_front(Point(current.top_left.x(),current.top_left.y()));

			draw_polyline(surface,points,*color,clipper);
			*/

			// Patchwork because of polyline
			draw_line(surface,Point(current.top_left.x(),current.top_left.y()),Point(current.top_left.x() + current.size.width(),current.top_left.y()),*color,clipper);
			draw_line(surface,Point(Point(current.top_left.x() + current.size.width(),current.top_left.y())),Point(current.top_left.x() + current.size.width(),current.top_left.y() + current.size.height()),*color,clipper);
			draw_line(surface,Point(current.top_left.x() + current.size.width(),current.top_left.y() + current.size.height()),Point(current.top_left.x(),current.top_left.y() + current.size.height()),*color,clipper);
			draw_line(surface,Point(current.top_left.x(),current.top_left.y() + current.size.height()),Point(current.top_left.x(),current.top_left.y()),*color,clipper);

			if(current.size.height() >= 2) current.size.height() -= 2;
			if(current.size.width() >= 2) current.size.width() -= 2;
			current.top_left.x() += 1;
			current.top_left.y() += 1;
		}

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
		if(requested_size) this->requested_size = *requested_size;
		if(color) this->color = color;
		if(border_width) this->border_width = border_width;
		if(relief) this->relief = relief;
		if(text) this->text = text;
		if(text_font) this->text_font = text_font;
		if(text_color) this->text_color = text_color;
		if(text_anchor) this->text_anchor = text_anchor;
		if(img) this->img = img;
		if(img_rect) this->img_rect = img_rect;
		if(img_anchor) this->img_anchor = img_anchor;


	}

	surface_t *Frame::getImg() {
		return img;
	}
};
