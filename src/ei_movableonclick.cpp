#include "ei_movableonclick.h"

namespace ei {

MovableOnClick::MovableOnClick(Widget *w, ei_callback_t callback): widget(w), callback(callback) {
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, w, "", enableMoving, nullptr);
}

bool_t MovableOnClick::enableMoving(Widget* widget, Event* event, void* user_param) {
    EventManager::getInstance().bind(ei_ev_mouse_move, nullptr, "all", callback, nullptr);
    EventManager::getInstance().bind(ei_ev_mouse_buttonup, nullptr, "all", callback_released, nullptr);

    return EI_TRUE;
}

bool_t MovableOnClick::callback_released(Widget *widget, Event *event, void *user_param)
{
    EventManager::getInstance().unbind(
        ei_ev_mouse_move,
        widget,
        "all",
        callback,
        nullptr);

    //All tant que la fenêtre ne se déplace pas vraiment, car pas de dessin dans l'offscreen pour le moment
    EventManager::getInstance().unbind(
        ei_ev_mouse_buttonup,
        nullptr,
        "all",
        callback_released,
        nullptr);

    return EI_TRUE;
}
}