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
}

Application::~Application()
{
    hw_quit();
}

void Application::run()
{
}

void Application::invalidate_rect(const Rect &rect)
{
}

void Application::quit_request()
{
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