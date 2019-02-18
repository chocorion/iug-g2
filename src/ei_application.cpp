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
    Application::Application(Size *main_window_size) 
    {

    }

    Application::~Application() 
    {

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

    }

    surface_t Application::root_surface() 
    {

    }

    Widget *Application::widget_pick(const Point &where) 
    {

    }

    static Application *instance;
} // namespace ei