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

    int *border_width = new int(0);
    *border_width = 0;

    relief_t *relief = new relief_t();
    *relief = ei_relief_none;

    color_t  *black  = new color_t();
    *black = {0,0,0,255};
    
    fill(*img, black, EI_FALSE);

    char* blank_text = (char*)"";
    
    Rect* window = new Rect(Point(),*main_window_size);

    root->configure(
        main_window_size,
        black,
        border_width,
        relief,
        &blank_text,
        nullptr,
        black,
        new anchor_t(),
        img,
        &window,
        new anchor_t()
    );

    //Set the size of the widget to the window size
    root->geomnotify(*window);

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

            cout << widget_pick(mouseCoord)->getPick_id() << endl;
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

bool isColorEquals(const color_t color_1, const color_t color_2, bool use_alpha)
{
    return (
        color_1.red == color_2.red      &&
        color_1.green == color_2.green  &&
        color_1.blue == color_2.blue    &&
        (
            (use_alpha)?
                color_1.alpha == color_2.alpha:
                true
        )
        
    );
}

Widget* rec_widget_pick(const color_t color, Widget* widget)
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

    Widget* result;
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