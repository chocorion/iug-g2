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

namespace ei
{

Frame::Frame(Widget *parent) : Widget("Frame", parent)
{
	img = nullptr;
	text = nullptr;
}

Frame::~Frame()
{
}

void Frame::draw(surface_t surface,
				 surface_t pick_surface,
				 Rect *clipper) 
{
	// PICK SURFACE
	drawOffscreen(pick_surface, clipper);

	// FRAME BACKGROUND
	surface_t fill_background = hw_surface_create(surface, &getScreenLocation()->size);
	
	fill(fill_background, color, EI_FALSE);
	ei_copy_surface(surface, fill_background, &getScreenLocation()->top_left, EI_FALSE);
	hw_surface_free(fill_background);
	// FRAME IMAGE
	if (img && parent)
	{
		ei_copy_surface(surface, *img, &getScreenLocation()->top_left, EI_TRUE);
	}

	// FRAME TEXT
	if (text && text_font)
	{
		Size text_size = Size();
		hw_text_compute_size(*text, *text_font, text_size);
		Rect textBox = Rect(Point(), text_size);

		Point* where = Tools::findAnchor(&screen_location, &textBox, text_anchor);
		draw_text(surface, where, *text, *text_font, text_color);
		delete where;
		
	}

	int color_coef = 50;
	color_t dark_color =
	{
        (unsigned char)(color->red   * color_coef / 100),
        (unsigned char)(color->green * color_coef / 100),
        (unsigned char)(color->blue  * color_coef / 100),
        255
    };

	Rect current = Rect(Point(getScreenLocation()->top_left), Size(getScreenLocation()->size));
	// FRAME BORDER
	if (border_width)
	{
		for (int i = 0; i < *border_width; i++)
		{

			linked_point_t points;
			points.push_front(Point(current.top_left.x(),current.top_left.y()));
			points.push_front(Point(current.top_left.x() + current.size.width(),current.top_left.y()));
			points.push_front(Point(current.top_left.x() + current.size.width(),current.top_left.y() + current.size.height()));
			points.push_front(Point(current.top_left.x() - 1,current.top_left.y() + current.size.height())); // -1 because of a hole otherwise appearing
			points.push_front(Point(current.top_left.x(),current.top_left.y()));

			draw_polyline(surface,points,dark_color,clipper);

			if (current.size.height() >= 2)
				current.size.height() -= 2;
			if (current.size.width() >= 2)
				current.size.width() -= 2;
				
			current.top_left.x() += 1;
			current.top_left.y() += 1;
		}
	}
}

void Frame::configure(Size *requested_size,
					  const color_t *color,
					  int *border_width,
					  relief_t *relief,
					  const char **text,
					  font_t *text_font,
					  color_t *text_color,
					  anchor_t *text_anchor,
					  surface_t *img,
					  Rect **img_rect,
					  anchor_t *img_anchor)
{
	this->color 		= (color)? color : &default_background_color;
	this->border_width  = (border_width)? border_width : new int(0);
	this->relief 		= (relief)? relief : new relief_t(ei_relief_none);

	if (text != nullptr && img == nullptr)
	{
		if (text)
			this->text = text;

		this->text_color = (text_color)? text_color : new color_t(font_default_color);
		this->text_anchor = (text_anchor)? text_anchor : new anchor_t(ei_anc_center);
		this->text_font = (text_font)? text_font : new font_t(hw_text_font_create(default_font_filename, font_default_size));
	}

	if (text == nullptr && img != nullptr)
	{
		if (img) {
			this->img = img;
		}
		if (img_rect)
			this->img_rect = img_rect;

		if (img_anchor)
			this->img_anchor = img_anchor;
		else
		{
			this->img_anchor = new anchor_t(ei_anc_center);
		}
	}

	if (requested_size)
		this->requested_size = *requested_size;
	else
	{
		Size default_size;

		if (this->text)
		{
			hw_text_compute_size(*(this->text), *(this->text_font), default_size);
		}
		else if (this->img)
		{
			default_size = hw_surface_get_size(this->img);
		}

		this->requested_size = default_size;
	}
}

surface_t *Frame::getImg()
{
	return img;
}
}; // namespace ei
