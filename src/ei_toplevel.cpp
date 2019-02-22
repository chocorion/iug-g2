/**
 * @file    ei_toplevel.cpp
 *
 * @brief   Definition of the toplevel widget
 *
 *  Created by Adrien Boitelle on 21.02.19.
 */

#include "ei_widget.h"
#include <iostream>

using namespace std;

namespace ei
{
Toplevel::Toplevel(Widget *parent) : Widget("Toplevel", parent)
{
}

Toplevel::~Toplevel()
{
}

void Toplevel::draw(surface_t surface,
                    surface_t pick_surface,
                    Rect *clipper)
{
    main_frame->draw(surface, pick_surface, clipper);
    panel_frame->draw(surface, pick_surface, clipper);
    resize_button->draw(surface, pick_surface, clipper);
}

void Toplevel::geomnotify(Rect rect)
{
    this->screen_location = rect;

    
}

void Toplevel::configure(Size *requested_size,
                         color_t *color,
                         int *border_width,
                         const char **title,
                         bool_t *closable,
                         axis_set_t *resizable,
                         Size *min_size)
{
    if (requested_size)
        this->requested_size = *requested_size;
    else
    {
        this->requested_size = *(new Size(320, 240));
    }

    if (color)
        this->color = color;
    else
    {
        this->color = new color_t;
        *this->color = default_background_color;
    }

    if (border_width)
        this->border_width = border_width;
    else
    {
        this->border_width = new int(4);
    }

    if (title)
        this->title = title;
    else
    {
        this->title = new char *;
        *this->title = "Toplevel";
    }

    if (closable)
        this->closable = closable;
    else
    {
        this->closable = new bool_t;
        *this->closable = EI_TRUE;
    }

    if (resizable)
        this->resizable = resizable;
    else
    {
        this->resizable = new axis_set_t;
        *this->resizable = ei_axis_both;
    }

    if (min_size)
        this->min_size = min_size;
    else
    {
        this->min_size = new Size(160, 120);
    }

    int default_border_width = 2;
    color_t default_font_color = {0x00, 0xFF, 0x00, 0xff};

    // CREATE MAIN TOPLEVEL FRAME

    main_frame = new Frame(this);

    relief_t *none = new relief_t;
    *none = ei_relief_none;
    main_frame->configure(NULL, &default_background_color, new int(default_border_width), none, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    // CREATE RESIZE BUTTON

    if (resizable)
    {
        resize_button = new Button(this);

        resize_button->configure(NULL, &default_background_color, NULL, new int(0), none, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    }
    else
    {
        resize_button = NULL;
    }

    // CREATE PANEL FRAME

    panel_frame = new Frame(this);

    // Use default font because no other parameter
    font_t *font = new font_t();
    *font = hw_text_font_create(default_font_filename, font_default_size);

    anchor_t *topleft = new anchor_t;
    *topleft = ei_anc_northwest;

    panel_frame->configure(NULL, &default_background_color, new int(default_border_width), none, NULL, font, &default_font_color, topleft, NULL, NULL, NULL);
}
} // namespace ei