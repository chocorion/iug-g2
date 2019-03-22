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

using namespace std;

namespace ei
{
Toplevel::Toplevel(Widget *parent) : Widget("Toplevel", parent)
{
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, this, "", this->callback_pressed, NULL);
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

    if (resizable && *resizable != ei_axis_none)
    {
        resize_button->draw(surface, pick_surface, clipper);
    }
    
    //Draw only the frame on clipper
    drawOffscreen(pick_surface, clipper);
}

void Toplevel::geomnotify(Rect rect)
{
    this->screen_location = rect;
    main_frame->geomnotify(rect);

    
    //TODO use percent not pixel
    Rect panel_location = Rect (
        rect.top_left,
        Size(
            rect.size.width(),
            35  
        )
    );
    panel_frame->geomnotify(panel_location);

    if (resizable && *resizable != ei_axis_none)
    {
        Rect button_location = Rect (
            Point(
                rect.top_left.x() + rect.size.width() - 30,
                rect.top_left.y() + rect.size.height() - 30
            ),
            Size(30, 30)
        );
        resize_button->geomnotify(button_location);
    }
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
    main_frame->configure(NULL, color, new int(default_border_width), none, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    // CREATE RESIZE BUTTON

    if (resizable && *resizable != ei_axis_none)
    {
        resize_button = new Frame(nullptr);
        resize_button->configure(NULL, &default_background_color, new int(default_border_width), none, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    }
    else
    {
        resize_button = NULL;
    }

    // CREATE PANEL FRAME

    panel_frame = new Frame(nullptr);

    // Use default font because no other parameter
    font_t *font = new font_t();
    *font = hw_text_font_create(default_font_filename, font_default_size);

    anchor_t *topleft = new anchor_t;
    *topleft = ei_anc_northwest;
    Size *panel_frame_size = new Size();
    panel_frame->configure(panel_frame_size, &default_background_color, new int(default_border_width), none, 
        this->title, font, &default_font_color, NULL, NULL, NULL, NULL);
}

const Rect* Toplevel::getPanelLocation() const
{
    return panel_frame->getScreenLocation();
}

const Rect* Toplevel::getResizeButtonLocation() const
{
    return resize_button->getScreenLocation();
}

bool_t Toplevel::callback_pressed(Widget* widget, Event* event, void* user_param)
{
    Toplevel* toplevel = static_cast<Toplevel*>(widget);
    MouseEvent* e = static_cast<MouseEvent*>(event);
    Point where = e->where;

    Rect const *panelRect        = toplevel->getPanelLocation();
    Rect const *resizeButtonRect = toplevel->getResizeButtonLocation();

    cout << "Toplevel clic on " << where.x() << " " << where.y() << endl;
    
    if (panelRect->hasIn(where))
    {
        cout << "Click on the panel !" << endl;
    } else if (resizeButtonRect->hasIn(where)) {
        cout << "Click on the button !" << endl;
    } else {
        return EI_FALSE;
    }
    //Penser à retourner EI_FALSE si on ne clique pas sur un des deux boutons
    return EI_TRUE;
}


// bool_t Toplevel::callback_move(Widget* widget, Event* event, void* user_param)
// {
//     MouseEvent* e = static_cast<MouseEvent*>(event);
//     Rect *panel  = panel_frame.getScreenLocation();
//     Rect *button = resize_button.getScreenLocation();

//     //Regarder ou qu'il est le clic !
//     if (e->where.x )
//     return EI_TRUE;
// }

// bool_t callback_panel_release(Widget* widget, Event* event, void* user_param)
// {
//     MouseEvent* e = static_cast<MouseEvent*>(event);
//     std::cout << "Click " << e->button_number << std::endl;
//     return EI_TRUE;
// }
} // namespace ei