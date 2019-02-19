#include "ei_eventmanager.h"
#include "ei_event.h"
namespace ei
{
BoundEvent::BoundEvent()
{
    return;
}

BoundEvent::BoundEvent(
            Widget* widget,
            tag_t tag,
            ei_callback_t callback,
            void* user_param
        ): 
        _widget(widget),
        _tag(tag),
        _callback(callback),
        _user_param(user_param) {}

bool BoundEvent::execute(Event* event)
{
    return _callback(_widget, event, _user_param);
}

}

