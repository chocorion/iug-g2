#ifndef EI_TOPPANEL_H
#define EI_TOPPANEL_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_movableonclick.h"
 
namespace ei
{
/**
 * @brief Little structure for storing information about position on the screen.
 */
typedef struct {
    Rect oldPos;
    bool oldPosEnable;
    bool x_expend;
    bool y_expend;
} MoveData;


/**
 * @brief Represent the panel on the top of Toplevel (Can be used for every other widget)
 * 
 */
class TopPanel : public Frame, public MovableOnClick {
    private:
        //Position of the click in the panel reference
        Point click_offset;

        Widget *CloseButton;
        Widget *ReduceButton;
        Widget *ResizeButton;

        MoveData moveData = {
            Rect(),
            false,
            false,
            false
        };


    public:
        TopPanel();
        TopPanel(Widget *parent);

        /**
         * @brief Overidden function
         */
        static bool_t callback_move_panel(Widget *widget, Event *event, void *user_param);

        /**
         * @brief Overidden function
         */
        static bool_t callback_on_click(Widget* widget, Event *event, void* user_param);

        /**
         * @brief Overidden function
         */
        static bool_t resize_on_double_click(Widget *widget, Event *event, void *user_param);

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


};

}

#endif