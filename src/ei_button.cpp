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

        Rect base = Rect(Point(screen_location.top_left.x(),screen_location.top_left.y()),Size((double) requested_size.width(),(double) requested_size.height()));
        Rect current = Rect(Point(base.top_left),Size(base.size));

        drawOffscreen(pick_surface, clipper);

        linked_point_t points = rounded_frame(base,45, BT_FULL);

       /* points.push_front(Point(current.top_left.x(),current.top_left.y()));
        points.push_front(Point(current.top_left.x() + current.size.width(),current.top_left.y()));
        points.push_front(Point(current.top_left.x() + current.size.width(),current.top_left.y() + current.size.height()));
        points.push_front(Point(current.top_left.x(),current.top_left.y() + current.size.height()));
        points.push_front(Point(current.top_left.x(),current.top_left.y()));*/

        draw_polygon(surface, points, *color, clipper);
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
};
