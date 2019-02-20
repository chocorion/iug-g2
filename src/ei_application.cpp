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
#include <iostream>

using namespace std;

namespace ei
{
Frame *Application::root = new Frame(nullptr);

Application::Application(Size *main_window_size)
{
    hw_init();
    
    surface_t img = hw_create_window(main_window_size, EI_FALSE);

    int border_width = 0;
    relief_t relief = ei_relief_none;
    color_t black = {0,0,0,255};
    
    char* blank_text = (char*)"";
    
    Rect* window = new Rect(Point(),*main_window_size);

    root->configure(
        main_window_size,
        &black,
        &border_width,
        &relief,
        &blank_text,
        nullptr,
        &black,
        new anchor_t(),
        &img,
        &window,
        new anchor_t()
    );

    continue_running = true;
}

Application::~Application()
{
    hw_quit();
}

void Application::run()
{
    Event* event;

    while(continue_running)
    {
        event = hw_event_wait_next();

        // doExit = (
        //     (event->type == ei_ev_display && ((DisplayEvent*)event)->closed) ||
        //     (event->type == ei_ev_keydown && ((KeyEvent*)event)->key_sym == ALLEGRO_KEY_ESCAPE)
        // );

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
}

Widget *Application::widget_pick(const Point &where)
{
}

static Application *instance;
} // namespace ei