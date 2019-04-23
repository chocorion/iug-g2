#ifndef EI_RESIZEBUTTON_H
#define EI_RESIZEBUTTON_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_movableonclick.h"

namespace ei {

class ResizeButton : public Frame, public MovableOnClick {
    private:
        //Store the difference between where is the click and where is the bottom right corner. 
        Point click_offset;

    public:

        ResizeButton() {return;}
        ResizeButton(Widget* parent);
        /**
         * @brief Overidden function
         */
        static bool_t callback_move_button(Widget *widget, Event *event, void *user_param);

        /**
         * @brief Overidden function
         */
        static bool_t callback_on_click(Widget *widget, Event *event, void *user_param);
};

}

#endif