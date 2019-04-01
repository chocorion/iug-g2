#ifndef EI_TOPPANEL_H
#define EI_TOPPANEL_H

#include "ei_types.h"
#include "ei_widget.h"
 
namespace ei
{

class TopPanel : public Frame {
    private:
        Point click_offset;

        Widget *CloseButton;
        Widget *ReduceButton;
        Widget *ResizeButton;

        void enableMoving();


    public:
        TopPanel();
        TopPanel(Widget *parent);

        virtual void geomnotify(Rect rect);

        virtual ~TopPanel();

        virtual void draw(surface_t surface,
                          surface_t pick_surface,
                          Rect *clipper);


        static bool_t callback_move_panel(Widget *widget, Event *event, void *user_param);
        static bool_t callback_released(Widget *widget, Event *event, void *user_param);
        /**
         * @brief Overridden function
         * 
         * @param closable Close button on the left-side of the panel
         * @param resizable Maximize and De-maximize window button. For future
         * @param reductible Button for hidde window. For the future
         */
        void configure(const color_t *color,
                       int *border_width,
                       relief_t *relief,
                       const char **text,
                       font_t *text_font,
                       color_t *text_color,
                       anchor_t *text_anchor,
                       surface_t *img,
                       Rect **img_rect,
                       anchor_t *img_anchor,
                       bool closable = true,
                       bool resizable = false,
                       bool reductible = false
                       );

        void sendClick(Point where);

};

}

#endif