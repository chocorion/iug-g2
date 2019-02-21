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
}
} // namespace ei