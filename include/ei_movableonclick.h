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
    
/**
 * @brief 
 * 
 */
class MovableOnClick {
    private:
        //Store the user callbacks, for deletting in destructor
        ei_callback_t *callbacks;


    public:
      ~MovableOnClick();
      MovableOnClick(){return;}

      /**
       * @brief Construct a new Movable On Click object
       * 
       * @param widget the widget to move
       * @param callback_on_click widget function to call on click
       * @param callback_on_move widget function to call on move
       */
      MovableOnClick(Widget *widget, ei_callback_t callback_on_click, ei_callback_t callback_on_move);

      /**
       * @brief Function called by MovableOnclick on click
       * 
       * @param widget the widget concerned by the click
       * @param event The event object
       * @param user_param parameters of the callback
       * @return bool_t return if the callback treat the event
       */
      static bool_t enableMoving(Widget *widget, Event *event, void *user_param);

      /**
       * @brief Function called by MovableOnclick on buttonUp
       * 
       * @param widget the widget concerned by the click
       * @param event The event object
       * @param user_param parameters of the callback
       * @return bool_t return if the callback treat the event
       */
      static bool_t callback_released(Widget *widget, Event *event, void *user_param);
};
}

#endif