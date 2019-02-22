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
		this->img = NULL;
		this->text = NULL;
}

Frame::~Frame()
{
}

void Frame::draw(surface_t surface,
				 surface_t pick_surface,
				 Rect *clipper) 
{
	Rect base = Rect(Point(screen_location.top_left.x(), screen_location.top_left.y()), Size((double)requested_size.width(), (double)requested_size.height()));
	Rect current = Rect(Point(base.top_left), Size(base.size));

	// PICK SURFACE
	drawOffscreen(pick_surface, clipper);

	// FRAME BACKGROUND
	surface_t fill_background = hw_surface_create(surface, &(base.size));
	fill(fill_background,color,EI_TRUE);
	ei_copy_surface(surface, fill_background, &base.top_left, EI_TRUE);

	// FRAME IMAGE
	if (img && parent)
	{
		ei_copy_surface(surface, *img, &base.top_left, EI_TRUE);
	}

	// FRAME TEXT
	if (text && text_font)
	{
		Size *text_size = new Size();
		hw_text_compute_size(*this->text, this->text_font, *text_size);

		Rect *position = new Rect(Point(), *text_size);

		Rect object = *position;
		anchor_t _anchor = ei_anc_center;
		Point anchor = Point(base.top_left.x() + base.size.width() / 2, base.top_left.y() + base.size.height() / 2);

		switch (_anchor)
		{
		case ei_anc_none: //Northwest by default
		case ei_anc_northwest:
			object.top_left = Point(
				anchor.x(),
				anchor.y());
			break;

		case ei_anc_north:
			object.top_left = Point(
				anchor.x() - object.size.width() / 2,
				anchor.y());
			break;

		case ei_anc_northeast:
			object.top_left = Point(
				anchor.x() - object.size.width(),
				anchor.y());
			break;

		case ei_anc_south:
			object.top_left = Point(
				anchor.x() - object.size.width() / 2,
				anchor.y() - object.size.height());
			break;

		case ei_anc_southwest:
			object.top_left = Point(
				anchor.x(),
				anchor.y() - object.size.height());
			break;

		case ei_anc_southeast:
			object.top_left = Point(
				anchor.x() - object.size.width(),
				anchor.y() - object.size.height());
			break;

		case ei_anc_west:
			object.top_left = Point(
				anchor.x(),
				anchor.y() - object.size.height() / 2);
			break;

		case ei_anc_east:
			object.top_left = Point(
				anchor.x() - object.size.width(),
				anchor.y() - object.size.height());
			break;

		case ei_anc_center:
			object.top_left = Point(
				anchor.x() - object.size.width() / 2,
				anchor.y() - object.size.height() / 2);
			break;
		default:
			break;
		}

		draw_text(surface, &(position->top_left), *text, text_font, text_color);
	}

	int color_coef = 50;
	color_t dark_color = {
            (unsigned char)(color->red * color_coef / 100),
            (unsigned char)(color->green * color_coef / 100),
            (unsigned char)(color->blue * color_coef / 100),
            255
        };

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
					  char **text,
					  font_t *text_font,
					  color_t *text_color,
					  anchor_t *text_anchor,
					  surface_t *img,
					  Rect **img_rect,
					  anchor_t *img_anchor)
{

	if (color)
		this->color = color;
	else
		this->color = &default_background_color;

	if (border_width)
		this->border_width = border_width;
	else
		this->border_width = 0;

	if (relief)
		this->relief = relief;
	else
	{
		this->relief = new relief_t;
		*this->relief = ei_relief_none;
	}

	if (text != NULL && img == NULL)
	{
		if (text)
			this->text = text;
		if (text_color)
			this->text_color = text_color;
		else
		{
			this->text_color = new color_t;
			*this->text_color = font_default_color;
		}

		if (text_anchor)
			this->text_anchor = text_anchor;
		else
		{
			this->text_anchor = new anchor_t;
			*this->text_anchor = ei_anc_center;
		}

		if (text_font)
			this->text_font = text_font;
		else
		{
			font_t *font = new font_t();
			*font = hw_text_font_create(default_font_filename, font_default_size);
			this->text_font = font;
		}
	}

	if (text == NULL && img != NULL)
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
			this->img_anchor = new anchor_t;
			*this->img_anchor = ei_anc_center;
		}
	}

	if (requested_size)
		this->requested_size = *requested_size;
	else
	{
		Size *default_size = new Size();

		if (this->text)
		{
			hw_text_compute_size(*this->text, this->text_font, *default_size);
		}
		else if (this->img)
		{
			*default_size = hw_surface_get_size(this->img);
		}

		this->requested_size = *default_size;
	}
}

surface_t *Frame::getImg()
{
	return img;
}
}; // namespace ei
