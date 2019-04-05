#ifndef EI_TOPLEVEL_H
#define EI_TOPLEVEL_H

#include "ei_widget.h"
#include "ei_draw.h"
#include "ei_types.h"
#include "ei_tools.h"
#include "ei_toppanel.h"
#include "ei_resizebutton.h"

#include <functional>

namespace ei {


class Toplevel : public Widget
{
  public:
    
    Toplevel(Widget *parent);

    virtual ~Toplevel();

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

    axis_set_t getAxis();

  private: 
    color_t *color;
    int *border_width;
    const char **title;
    bool_t *closable;
    axis_set_t *resizable;
    Size *min_size;
    TopPanel *topPanel;
    ResizeButton *resizeButton;
    Frame *main_frame;
};

}
#endif