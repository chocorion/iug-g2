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
        //drawing shapes

        Rect base = Rect(Point(screen_location.top_left.x(),screen_location.top_left.y()),Size((double) requested_size.width(),(double) requested_size.height()));
        Rect top = Rect(Point(base.top_left),Size(base.size));
        Rect bottom = Rect(Point(base.top_left),Size(base.size));
        Rect flat = Rect(Point(screen_location.top_left.x() + *border_width, screen_location.top_left.y() + *border_width),
                                 Size((double) (requested_size.width() - *border_width * 2),(double) (requested_size.height() - *border_width * 2)));
        Rect current = Rect(Point(base.top_left),Size(base.size));

        int color_coef = 50;

        color_t dark_color = {
            (unsigned char)(color->red * color_coef / 100),
            (unsigned char)(color->green * color_coef / 100),
            (unsigned char)(color->blue * color_coef / 100),
            255
        };


        color_t light_color = {
            (unsigned char)(color->red * (color_coef + 100) + (color->red != 0) * (255 - color_coef / 100 * 255)),
            (unsigned char)(color->green * (color_coef + 100)+ (color->green != 0) * (255 - color_coef / 100 * 255)),
            (unsigned char)(color->blue * (color_coef + 100)+ (color->blue != 0) * (255 - color_coef / 100 * 255)),
            255
        };

        drawOffscreen(pick_surface, clipper);

        linked_point_t top_points = rounded_frame(top, (float)*corner_radius, BT_TOP);
        linked_point_t bottom_points = rounded_frame(bottom, (float)*corner_radius, BT_BOTTOM);
        linked_point_t flat_points = rounded_frame(flat, (float)*corner_radius, BT_FULL);

        draw_polygon(surface, top_points, light_color, clipper);
        draw_polygon(surface, bottom_points, dark_color, clipper);
        draw_polygon(surface, flat_points, *color, clipper);

        //end shapes

        // FRAME IMAGE
		if(img && parent) {
			ei_copy_surface(surface, img, &base.top_left, EI_TRUE);
		}

		// FRAME TEXT
		if(text) {

			Size* text_size = new Size();
			hw_text_compute_size(*text, *text_font, *text_size);
			Rect* textBox = new Rect(Point(),*text_size);

			Point* where = Tools::findAnchor(&base, textBox, text_anchor);

			draw_text(surface, where, *text, *text_font, text_color);
		}
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
		if (color)
			this->color = color;
		else
			this->color = &default_background_color;

		if (border_width)
			this->border_width = border_width;
		else
			this->border_width = 0;
		
		if (corner_radius)
			this->corner_radius = corner_radius;
		else
			this->corner_radius = 0;
		

		if (relief)
			this->relief = relief;
		else
		{
			this->relief = new relief_t;
			*this->relief = ei_relief_none;
		}

			if (!img)
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
};
