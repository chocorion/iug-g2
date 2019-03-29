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
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, this, "", this->callback_pressed, nullptr);
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

void Toplevel::setPanelLocation() {
    Rect panel_location = Rect(
        screen_location.top_left,
        Size(
            screen_location.size.width(),
            35
        )
    );

    panel_frame->geomnotify(panel_location);
}

void Toplevel::setResizeButtonLocation() {
    Rect button_location = Rect(
        Point(
            screen_location.top_left.x() + screen_location.size.width() - 30,
            screen_location.top_left.y() + screen_location.size.height() - 30),
        Size(30, 30)
    );

    resize_button->geomnotify(button_location);
}

void Toplevel::geomnotify(Rect rect)
{
    this->screen_location = rect;
    main_frame->geomnotify(rect);

    setPanelLocation();
    
    if (resizable && *resizable != ei_axis_none)
    {
        setResizeButtonLocation();
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
    main_frame->configure(nullptr, color, new int(default_border_width), none, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    // CREATE RESIZE BUTTON

    if (resizable && *resizable != ei_axis_none)
    {
        resize_button = new Frame(nullptr);
        resize_button->configure(nullptr, &default_background_color, new int(default_border_width), none, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    }
    else
    {
        resize_button = nullptr;
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
        this->title, font, &default_font_color, nullptr, nullptr, nullptr, nullptr);
}

const Rect* Toplevel::getPanelLocation() const
{
    return panel_frame->getScreenLocation();
}

const Rect* Toplevel::getResizeButtonLocation() const
{
    return resize_button->getScreenLocation();
}

typedef struct {
    ei_eventtype_t event;
    Widget* widget;
    ei_callback_t callback;
} param_t;

//Called when we click on the Toplevel
bool_t Toplevel::callback_pressed(Widget* widget, Event* event, void* user_param)
{
    Toplevel* toplevel = static_cast<Toplevel*>(widget);
    MouseEvent* e = static_cast<MouseEvent*>(event);
    Point where = e->where;

    Rect const *panelRect        = toplevel->getPanelLocation();
    Rect const *resizeButtonRect = toplevel->getResizeButtonLocation();



    cout << "Toplevel is in " << toplevel->screen_location.top_left.x() << " " << toplevel->screen_location.top_left.y() << endl;


    
    //Quand on clique sur la barre en haut de Toplevel
    if (panelRect->hasIn(where))
    {
        //Calculate offSet with the top_left corner :
        toplevel->tmp_offset = Point (
            where.x() - toplevel->screen_location.top_left.x(),
            where.y() - toplevel->screen_location.top_left.y()
        );


        param_t* param = new param_t;
            param->event = ei_ev_mouse_move;
            param->widget = widget;
            param->callback = callback_move_panel;

        EventManager::getInstance().bind(ei_ev_mouse_move, widget, "", toplevel->callback_move_panel, nullptr);
        EventManager::getInstance().bind(ei_ev_mouse_buttonup, nullptr, "all", callback_released, (void *)param);

    //Quand on clique sur le bouton de redimensionnement :
    } else if (resizeButtonRect->hasIn(where)) {
        //Calculate offSet with the bottom_rigth corner :
        toplevel->tmp_offset = Point(
            toplevel->screen_location.top_left.x() + toplevel->screen_location.size.width() - where.x(),
            toplevel->screen_location.top_left.y() + toplevel->screen_location.size.height() - where.y()
        );


        param_t *param = new param_t;
            param->event = ei_ev_mouse_move;
            param->widget = widget;
            param->callback = callback_move_resize_button;

        EventManager::getInstance().bind(ei_ev_mouse_move, widget, "", callback_move_resize_button, nullptr);
        EventManager::getInstance().bind(ei_ev_mouse_buttonup, nullptr, "all", callback_released, (void *)param);
    } else {
        return EI_FALSE;
    }
    return EI_TRUE;
}

bool_t Toplevel::callback_released(Widget *widget, Event *event, void *user_param) {

    cout << "UNBIND !" << endl;
    param_t* param = (param_t*) user_param;

    //int (*const *ptr)(int, int) = arg.target<int (*)(int, int)>();
    //cout << "Pointer : " <<  param->callback.target<bool_t(Widget *, Event *, void *)>();

    //cout << "Pointeur : " << ptr << endl;
    EventManager::getInstance().unbind(
        param->event,
        param->widget,
        "",
        param->callback,
        nullptr);

    //All tant que la fenêtre ne se déplace pas vraiment, car pas de dessin dans l'offscreen pour le moment
    EventManager::getInstance().unbind(
        ei_ev_mouse_buttonup,
        nullptr,
        "all",
        callback_released,
        user_param
    );

    delete param;

    return EI_TRUE;
}

bool_t Toplevel::callback_move_panel(Widget *widget, Event *event, void *user_param) {
    cout << "Moving toplevel !" << endl;

    MouseEvent* e = static_cast<MouseEvent*>(event);
    Toplevel* toplevel = static_cast<Toplevel*>(widget);

    //Bypass the geometrymanager
    //Attention ! bouge seulement la frame et pas le panel et tout le bazarre !
    toplevel->screen_location.top_left = Point(
        e->where.x() - toplevel->tmp_offset.x(),
        e->where.y() - toplevel->tmp_offset.y()
    );

    toplevel->setPanelLocation();
    toplevel->setResizeButtonLocation();
    toplevel->main_frame->geomnotify(toplevel->screen_location);

    std::list<Widget *> l;
    for (std::list<Widget *>::iterator it = (l = widget->getChildren()).begin(); it != l.end(); ++it)
    {

        cout << "Running geometryManager on child.." << endl;
        
        GeometryManager *child_manager;
        if ((child_manager = (*it)->getGeometryManager()))
        {
            //Use the manager of the child
            child_manager->run((*it));
        }
    }

    return EI_TRUE;
    //Désactiver le gestionnaire de géométrie skip avec geomnotify ? => Run sur tous ses fils après ?

}
bool_t Toplevel::callback_move_resize_button(Widget *widget, Event *event, void *user_param) {
    MouseEvent* e = static_cast<MouseEvent*>(event);
    Toplevel* toplevel = static_cast<Toplevel*>(widget);

    cout << "Resize not implemented !" << endl;

    return EI_FALSE;

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