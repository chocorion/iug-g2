/**
 * @file    ei_toplevel.cpp
 *
 * @brief   Definition of the toplevel widget
 *
 *  Created by Adrien Boitelle on 21.02.19.
 */

#include "ei_widget.h"
#include <iostream>
#include "ei_eventmanager.h"
#include "ei_toplevel.h"
#include "ei_geometrymanager.h"

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
    
    //Draw only the frame on clipper
    drawOffscreen(pick_surface, clipper);
}

void Toplevel::geomnotify(Rect rect)
{
    this->screen_location = rect;
    main_frame->geomnotify(rect);
}

void Toplevel::configure(Size *requested_size,
                         color_t *color,
                         int *border_width,
                         const char **title,
                         bool_t *closable,
                         axis_set_t *resizable,
                         Size *min_size)
{
    this->requested_size = (requested_size)? *requested_size : *(new Size(320, 240));
    this->color          = (color)?          color           : new color_t(default_background_color);
    this->border_width   = (border_width)?   border_width    : new int(4);
    this->title          = (title)?          title           : new const char*("Toplevel");
    this->closable       = (closable)?       closable        : new bool_t(EI_TRUE);
    this->resizable      = (resizable)?      resizable       : new axis_set_t(ei_axis_both);
    this->min_size       = (min_size)?       min_size        : new Size(160, 120);


    int default_border_width = 2;
    color_t default_font_color = {0x00, 0xFF, 0x00, 0xff};

    // CREATE MAIN TOPLEVEL FRAME

    main_frame = new Frame(nullptr);
    relief_t *none = new relief_t(ei_relief_none);
    //Use top-level color for the background
    main_frame->configure(nullptr, color, new int(default_border_width), none, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    // Temporaire !
    if (resizable && *resizable != ei_axis_none)
    {
        resizeButton = new Frame(nullptr);
        resizeButton->configure(nullptr, &default_background_color, new int(default_border_width), none, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    }
    else
    {
        resizeButton = nullptr;
    }

    // CREATE PANEL FRAME

    topPanel = new TopPanel(this);

    // Use default font because no other parameter
    font_t *font = new font_t();
    *font = hw_text_font_create(default_font_filename, font_default_size);

    anchor_t *topleft = new anchor_t;
    *topleft = ei_anc_northwest;
    topPanel->configure(&default_background_color, new int(default_border_width), none, 
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    Placer* topPanelPlacer = new Placer();
    topPanelPlacer->configure(
        (Widget*)topPanel, nullptr, new int(0), new int(0), nullptr, new float(40.0),
        new float(0.0), new float(0.0), new float(1.0), nullptr
    );
    cout << "After configure of topPanel's placer " << topPanel->getScreenLocation()->top_left.x() << " " << topPanel->getScreenLocation()->top_left.y() << " " << topPanel->getScreenLocation()->size.width() << " " << topPanel->getScreenLocation()->size.height() << endl;
    // topPanel->configure(&default_background_color, new int(default_border_width), none, 
    //     this->title, font, new color_t(default_font_color), nullptr, nullptr, nullptr, nullptr);

    this->content_rect = &screen_location;
}


} // namespace ei