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

using namespace std;

namespace ei
{
Frame *Application::root = new Frame(nullptr);

Application::Application(Size *main_window_size)
{
}

Application::~Application()
{
}

void Application::run()
{
    bool doExit = false;
    Event* event;

    while(!doExit)
    {
        event = hw_event_wait_next();

        doExit = (
            (event->type == ei_ev_display && ((DisplayEvent*)event)->closed) ||
            (event->type == ei_ev_keydown && ((KeyEvent*)event)->key_sym == ALLEGRO_KEY_ESCAPE)
        );
    }
}

void Application::invalidate_rect(const Rect &rect)
{
}

void Application::quit_request()
{
}

Frame *Application::root_widget()
{
}

surface_t Application::root_surface()
{
}

Widget *Application::widget_pick(const Point &where)
{
}

static Application *instance;
} // namespace ei