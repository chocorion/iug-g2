/**
 *  @file application.h
 *  @brief  Manages the main steps of a graphical application: initialization, main window,
 *    main loop, quitting, resource freeing.
 *
 *  \author
 *  Created by Adrien Boitelle on 2019.02.18
 *
 */

#include "ei_application.h"
#include "hw_interface.h"
#include "ei_event.h"
#include "keycodes.h"
#include "ei_main.h"
#include "ei_geometrymanager.h"
#include <iostream>

using namespace std;

namespace ei
{
Frame *Application::root = new Frame(nullptr);

Application::Application(Size *main_window_size)
{
    hw_init();

    surface_t *img = new surface_t;
    *img = hw_create_window(main_window_size, EI_FALSE);
    _pick = hw_surface_create(*img, main_window_size);

    root->configure(
        main_window_size,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        img,
        NULL,
        NULL);

    root->geomnotify(*(new Rect(Point(),*main_window_size)));

    continue_running = true;

}

Application::~Application()
{
    hw_quit();
}

typedef enum
{
    MOUSE,
    TOUCH,
    OTHER
} mouse_e;

mouse_e need_picking(Event *event)
{
    if (
        event->type == ei_ev_mouse_buttondown ||
        event->type == ei_ev_mouse_buttonup   ||
        event->type == ei_ev_mouse_move)
    {
        return MOUSE;
    }
    else if (
        event->type == ei_ev_touch_begin ||
        event->type == ei_ev_touch_end   ||
        event->type == ei_ev_touch_move)
    {
        return TOUCH;
    }
    else
    {
        return OTHER;
    }
}

void Application::renderDisplayRec(Widget *widget)
{
    if (widget->getParent())
    {
        widget->draw(root_surface(), pick_surface(), widget->getParent()->getContentRect());
    }
    else
    {
        widget->draw(root_surface(), pick_surface(), nullptr);
    }

    for (Widget *child : widget->getChildren())
    {
        renderDisplayRec(child);
    }
}

void Application::renderDisplay()
{
    renderDisplayRec(root);

    linked_rect_t rects = linked_rect_t();
    rects.push_back(hw_surface_get_rect(root_surface()));
    hw_surface_update_rects(rects);


}

void Application::run()
{
    Event *event;

    mouse_e isMouseEvent;
    Point mouseCoord;
    Widget *concerned_widget;
    bool isEventHandled ;
    
    while (continue_running)
    {
        concerned_widget = nullptr;
        isEventHandled = false;
        cout << "Rendering display..."<<endl;
        renderDisplay();
        cout << "Waiting for event..." << endl;
        event = hw_event_wait_next();
        cout << "Computing..." << endl;
        
        //Search the good widget
        if ((isMouseEvent = need_picking(event)) != OTHER)
        {
            if (isMouseEvent == MOUSE)
            {
                mouseCoord = ((MouseEvent *)event)->where;
            }
            else if (isMouseEvent == TOUCH)
            {
                mouseCoord = ((TouchEvent *)event)->where;
            }
            
            concerned_widget = widget_pick(mouseCoord);
        }

        //Do handler with tag "all" in priority
        isEventHandled = EventManager::getInstance().execute(event, "all");

        if (!isEventHandled && concerned_widget)
        {
            isEventHandled = EventManager::getInstance().execute(event, concerned_widget);
        }

        //Something take a lot of memory at each handled event...
        delete event;
    }
}

void Application::invalidate_rect(const Rect &rect)
{
}

void Application::quit_request()
{
    continue_running = false;
}

Frame *Application::root_widget()
{
    return root;
}

surface_t Application::root_surface()
{
    return *(root->getImg());
}

surface_t Application::pick_surface()
{
    return _pick;
}

bool isColorEquals(const color_t color_1, const color_t color_2, bool use_alpha)
{
    return (
        color_1.red   == color_2.red   &&
        color_1.green == color_2.green &&
        color_1.blue  == color_2.blue  &&
        ((use_alpha) ? color_1.alpha == color_2.alpha : true)

    );
}

Widget *rec_widget_pick(const color_t color, Widget *widget)
{
    if (isColorEquals(widget->get_pick_color(), color, false))
    {
        return widget;
    }
    std::list<Widget *> l = widget->getChildren();

    if (l.size() == 0)
    {
        return nullptr;
    }

    Widget *result;
    for (std::list<Widget *>::iterator it = l.begin(); it != l.end(); ++it)
    {
        if ((result = rec_widget_pick(color, (*it))))
        {
            return result;
        }
    }

    return nullptr;
}

Widget *Application::widget_pick(const Point &where)
{
    color_t picking_color = hw_get_pixel(pick_surface(), where);

    return rec_widget_pick(picking_color, root);
}

static Application *instance;
} // namespace ei