#include <stdio.h>
#include <stdlib.h>

#include "ei_main.h"
#include "ei_application.h"
#include "ei_event.h"
#include "ei_geometrymanager.h"
#include "ei_widget.h"
#include "hw_interface.h"

using namespace ei;

/*
 * ei_main --
 *
 *	Main function of the application.
 */
int ei_main(int argc, char** argv)
{
    Size screen_size = Size(600, 600);
    color_t root_bgcol = { 0xFF, 0x7f, 0xb4, 0xff };

    Size frame_size = Size(300, 200);
    int frame_x = 150;
    int frame_y = 200;
    color_t frame_color = { 0xaa, 0x00, 0x00, 0xff };
    relief_t frame_relief = ei_relief_raised;
    int frame_border_width = 6;

    Size button_size = Size(300, 200);
    int button_x = 150;
    int button_y = 200;
    color_t button_color = { 0xaa, 0x00, 0x00, 0xff };
    relief_t button_relief = ei_relief_raised;
    int button_border_width = 6;
    int button_corner_radius = 45;
    anchor_t button_anchor = ei_anc_southeast;

    /* Create the application and change the color of the background. */
    Application* app = new Application(&screen_size);
    app->root_widget()->configure(&screen_size, &root_bgcol, NULL, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL);

    /* Create, configure and place the frame on screen. */
    /*Frame* frame = new Frame(app->root_widget());
    frame->configure(&frame_size, &frame_color, &frame_border_width,
                     &frame_relief, NULL, NULL, NULL, NULL, NULL, NULL, NULL);*/
    Button* button = new Button(app->root_widget());
    button->configure(&button_size, &button_color, &button_border_width, &button_corner_radius,
                     &button_relief,NULL,NULL, NULL, &button_anchor,NULL, NULL, NULL);


    Placer* p = new Placer();
    //p->configure(frame, NULL, &frame_x, &frame_y, NULL, NULL, NULL, NULL, NULL, NULL);
    p->configure(button, NULL, &button_x, &button_y, NULL, NULL, NULL, NULL, NULL, NULL);
    
    /* Run the application's main loop. */
    app->run();

    /* We just exited from the main loop. Terminate the application (cleanup). */
    delete app;
    delete p;

    return (EXIT_SUCCESS);
}
