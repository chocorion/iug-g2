#ifndef MOVABLEONCLICK_H
#define MOVABLEONCLICK_H

#include "ei_draw.h"
#include "ei_types.h"
#include "ei_tools.h"
#include "ei_widget.h"
#include "ei_event.h"
#include "ei_eventmanager.h"

#include <functional>

namespace ei{

class MovableOnClick {
    private:
        ei_callback_t callback;

    public:
        MovableOnClick(Widget* widget, ei_callback_t callback);
        static bool_t enableMoving(Widget* widget, Event* event, void* user_param);
        static bool_t callback_released(Widget *widget, Event *event, void *user_param);
};
}

#endif