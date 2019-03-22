#ifndef EI_TOPLEVEL_H
#define EI_TOPLEVEL_H

#include "ei_widget.h"
#include "ei_draw.h"
#include "ei_types.h"
#include "ei_tools.h"

#include <functional>

namespace ei {


class Toplevel : public Widget
{
  public:
    static bool_t callback_pressed(Widget *widget, Event *event, void *user_param);
    static bool_t callback_released(Widget *widget, Event *event, void *user_param);
    static bool_t callback_move_panel(Widget *widget, Event *event, void *user_param);
    static bool_t callback_move_resize_button(Widget *widget, Event *event, void *user_param);
    
    Toplevel(Widget *parent);

    virtual ~Toplevel();

    virtual void draw(surface_t surface,
                      surface_t pick_surface,
                      Rect *clipper);

    /**
     * @brief   Configures the attributes of widgets of the class "toplevel".
     *
     * @param   widget      The widget to configure.
     * @param   requested_size  The content size requested for this widget, this does not include
     *              the decorations (border, title bar). The geometry manager may
     *              override this size due to other constraints.
     *              Defaults to (320x240).
     * @param   color       The color of the background of the content of the widget. Defaults
     *                      to \ref ei_default_background_color.
     * @param   border_width    The width in pixel of the border of the widget. Defaults to 4.
     * @param   title       The string title diplayed in the title bar. Defaults to "Toplevel".
     * @param   closable    If true, the toplevel is closable by the user, the toplevel must
     *                      show a close button in its title bar. Defaults to \ref EI_TRUE.
     * @param   resizable   Defines if the widget can be resized horizontally and/or vertically
     *                      by the user. Defaults to \ref ei_axis_both.
     * @param   min_size    For resizable widgets, defines the minimum size. Defaults to (160, 120).
     */
    void configure(Size *requested_size,
                   color_t *color,
                   int *border_width,
                   const char **title,
                   bool_t *closable,
                   axis_set_t *resizable,
                   Size *min_size);

    void geomnotify(Rect rect);
    const Rect* getPanelLocation() const;
    const Rect *getResizeButtonLocation() const;


    private : color_t *color;
    int *border_width;
    const char **title;
    bool_t *closable;
    axis_set_t *resizable;
    Size *min_size;

    Frame *main_frame;
    Frame *panel_frame;
    Frame *resize_button;

    //Offset for the click on the panel/resize button
    Point tmp_offset;
};

}
#endif