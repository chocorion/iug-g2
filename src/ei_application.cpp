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
Frame *Application::pick = new Frame(nullptr);

Application::Application(Size *main_window_size)
{
    hw_init();
    
    surface_t* img = new surface_t;
    surface_t* pick_surface = new surface_t;
    *img = hw_create_window(main_window_size, EI_FALSE);
    *pick_surface = hw_surface_create(*img, main_window_size);

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

    pick->configure(
        main_window_size,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        pick_surface,
        NULL,
        NULL
    );
}

Application::~Application()
{
    hw_quit();
}

void Application::run()
{
    Event* event;

    // Initial draw
    root->draw(this->root_surface(),pick_surface(),nullptr);

    std::list<Widget*> children = root->getChildren();

    

    while(continue_running)
    {
        cout << "Waiting an event... Press something for drawing... (spoiler -> la frame s'affiche pas)" << endl;
        event = hw_event_wait_next();

        // doExit = (
        //     (event->type == ei_ev_display && ((DisplayEvent*)event)->closed) ||
        //     (event->type == ei_ev_keydown && ((KeyEvent*)event)->key_sym == ALLEGRO_KEY_ESCAPE)
        // );

        EventManager::getInstance().execute(event, "all");

        cout << "drawing root's children !" << endl;
        for (std::list<Widget*>::iterator it = children.begin(); it != children.end(); ++it)
        {
            (*it)->draw(root_surface(), pick_surface(), nullptr);
        }

        linked_rect_t* rects = new linked_rect_t();
        rects->push_back(hw_surface_get_rect(root_surface()));
        hw_surface_update_rects(*rects);
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

Frame *Application::pick_widget()
{
    return pick;
}

surface_t Application::pick_surface()
{
    return *(pick->getImg());
}

Widget *Application::widget_pick(const Point &where)
{
}

static Application *instance;
} // namespace ei