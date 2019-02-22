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
}
void Toplevel::configure(Size *requested_size,
                         color_t *color,
                         int *border_width,
                         const char **title,
                         bool_t *closable,
                         axis_set_t *resizable,
                         Size *min_size)
{
    if(requested_size) this->requested_size = *requested_size;
    else {
        this->requested_size = *(new Size(320,240));
    }

    if(color) this->color = color;
    else {
        this->color = new color_t;
        *this->color = default_background_color;
    }

    if(border_width) this->border_width = border_width;
    else {
        this->border_width = new int(4);
    }

    if(title) this->title = title;
    else {
        this->title = new char*;
        *this->title = "Toplevel";
    }

    if(closable) this->closable = closable;
    else {
        this->closable = new bool_t;
        *this->closable = EI_TRUE;
    }

    if(resizable) this->resizable = resizable;
    else {
        this->resizable = new axis_set_t;
        *this->resizable = ei_axis_both;
    }

    if(min_size) this->min_size = min_size;
    else {
        this->min_size = new Size(160,120);
    }
}
} // namespace ei