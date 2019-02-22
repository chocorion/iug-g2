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

        int color_coef = 70;

        printf("rgb : %d, %d, %d\n", (unsigned char)(color->red * (color_coef + 100)),
               (unsigned char)(color->green * (color_coef + 100)),
               (unsigned char)(color->blue * (color_coef + 100)));

        color_t dark_color = {
            (unsigned char)(color->red * color_coef / 100),
            (unsigned char)(color->green * color_coef / 100),
            (unsigned char)(color->blue * color_coef / 100),
            255
        };


        color_t light_color = {
            (unsigned char)(color->red * (color_coef + 100)),
            (unsigned char)(color->green * (color_coef + 100)),
            (unsigned char)(color->blue * (color_coef + 100)),
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

        //text

        if(text_anchor){

            Point anchor;

            switch(*text_anchor){

                case ei_anc_none :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_center :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_north :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_northeast :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_east :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_southeast :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_south :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_southwest :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_west :
                    anchor = Point(base.top_left);
                    break;
                case ei_anc_northwest :
                    anchor = Point(base.top_left);
                    break;
                default:
                    break;
            }

            //draw_text(surface, &anchor, *text, *text_font, text_color);
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
		if(requested_size) this->requested_size = *requested_size;
		if(color) this->color = color;
		if(border_width) this->border_width = border_width;
        if(corner_radius) this->corner_radius = corner_radius;
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
