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

axis_set_t Toplevel::getAxis() {
    return *resizable;
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
    this->color          = (color)?          color           : new color_t({0xFF, 0xFF, 0xFF, 0xff});
    this->border_width   = (border_width)?   border_width    : new int(4);
    this->title          = (title)?          title           : new const char*("Toplevel");
    this->closable       = (closable)?       closable        : new bool_t(EI_TRUE);
    this->resizable      = (resizable)?      resizable       : new axis_set_t(ei_axis_both);
    this->min_size       = (min_size)?       min_size        : new Size(160, 120);


    int default_border_width = 2;
    color_t default_font_color = {0x00, 0xFF, 0x00, 0xff};

    relief_t *none = new relief_t(ei_relief_none);
    
    // Use default font because no other parameter
    font_t *font = new font_t(hw_text_font_create(default_font_filename, font_default_size));

    anchor_t *topleft = new anchor_t(ei_anc_northwest);

    
    // CREATE MAIN TOPLEVEL FRAME
    main_frame = new Frame(this);
    //Use top-level color for the background
    main_frame->configure(
        nullptr, color, new int(default_border_width), none, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr
    );

    Placer *main_frame_placer = new Placer();
    main_frame_placer->configure(
        main_frame, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, new float(1.0), new float(1.0)
    );


    // CREATE RESIZE BUTTON
    if (resizable && *resizable != ei_axis_none)
    {
        resizeButton = new ResizeButton(this);
        resizeButton->configure(
            new Size(20.0, 20.0), &default_background_color, new int(2), nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr
        );
        
        Placer *resizeButtonPlacer = new Placer();
        resizeButtonPlacer->configure(
            (Widget*)resizeButton, new anchor_t(ei_anc_southeast), nullptr, nullptr, new float(20.0), new float(20.0),
            new float(1.0), new float(1.0), nullptr, nullptr
        );
    }
    else
    {
        resizeButton = nullptr;
    }


    // CREATE TOPPANEL
    topPanel = new TopPanel(this);

    topPanel->configure(&default_background_color, new int(default_border_width), none, 
        this->title, font, new color_t({0x0,0x0,0x0,0xff}), nullptr, nullptr, nullptr, nullptr
    );

    Placer* topPanelPlacer = new Placer();
    topPanelPlacer->configure(
        (Widget*)topPanel, nullptr, new int(0), new int(0), nullptr, new float(30.0),
        new float(0.0), new float(0.0), new float(1.0), nullptr
    );


    this->content_rect = &screen_location;
}

Size* Toplevel::getMinimalSize()
{
    return min_size;
}

} // namespace ei