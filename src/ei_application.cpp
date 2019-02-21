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
    
    surface_t* img = new surface_t;
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
        NULL
    );

    continue_running = true;
}

Application::~Application()
{
    hw_quit();
}

typedef enum {MOUSE, TOUCH, OTHER} mouse_e;

mouse_e need_picking(Event* event) {
    if (
        event->type == ei_ev_mouse_buttondown ||
        event->type == ei_ev_mouse_buttonup   ||
        event->type == ei_ev_mouse_move
    )
    {
        return MOUSE;
    } else if (
        event->type == ei_ev_touch_begin      ||
        event->type == ei_ev_touch_end        ||
        event->type == ei_ev_touch_move
    )
    {
        return TOUCH;
    } else 
    {
        return OTHER;
    }
}

void Application::renderDisplay()
{

    std::list<Widget*> children = root->getChildren();

    root->draw(this->root_surface(),pick_surface(),nullptr);

    for (std::list<Widget*>::iterator it = children.begin(); it != children.end(); ++it)
    {
        (*it)->draw(root_surface(), pick_surface(), nullptr);
    }

    linked_rect_t* rects = new linked_rect_t();
    rects->push_back(hw_surface_get_rect(root_surface()));
    hw_surface_update_rects(*rects);
}

void Application::run()
{
    Event* event;
    
    mouse_e isMouseEvent; 
    Point mouseCoord;
    

    while(continue_running)
    {
        
        renderDisplay();
        
        cout << "Waiting for event..." << endl;
        event = hw_event_wait_next();

        //Search the good widget
        if ((isMouseEvent = need_picking(event)) != OTHER)
        {
            if (isMouseEvent == MOUSE)
            {
                mouseCoord = ((MouseEvent*)event)->where;
                cout << "\tMouse event in " << mouseCoord.x() << " " << mouseCoord.y() << endl;
            }
            else if (isMouseEvent == TOUCH)
            {
                mouseCoord = ((TouchEvent*)event)->where;
                cout << "\tTouch event in " << mouseCoord.x() << " " << mouseCoord.y() << endl;
            }

            widget_pick(mouseCoord);
            //Faire une rechercher récursive à partir de la racine dans les widgets pour trouver à qui correspond la couleure prise dans l'offscreen picking
        }

        EventManager::getInstance().execute(event, "all");

        


        
    }
}

void Application::invalidate_rect(const Rect &rect)
{
}

void Application::quit_request()
{
    std::cout << "QUIT REQUEST CATCHED !" << std::endl;
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

Widget *Application::widget_pick(const Point &where)
{
    color_t picking_color = hw_get_pixel(pick_surface(), where);
    cout << "\t\tColor in screen picking : " << (int) picking_color.red << " : " << (int) picking_color.green << " : " << (int) picking_color.blue << " : " << (int) picking_color.alpha << endl;
}

static Application *instance;
} // namespace ei