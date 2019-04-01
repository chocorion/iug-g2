#include "ei_movableonclick.h"

namespace ei {

MovableOnClick::MovableOnClick(Widget *w, ei_callback_t callback_on_click, ei_callback_t callback_on_move)
{
    callbacks = new ei_callback_t[2];
    callbacks[0] = callback_on_click;
    callbacks[1] = callback_on_move;

    EventManager::getInstance().bind(ei_ev_mouse_buttondown, w, "", enableMoving, (void*)callbacks);
}

bool_t MovableOnClick::enableMoving(Widget* widget, Event* event, void* user_param) {
    ei_callback_t* callbacks = (ei_callback_t*) user_param;

    callbacks[0](widget, event, nullptr);
    EventManager::getInstance().bind(ei_ev_mouse_move, nullptr, "all", callbacks[1], nullptr);
    EventManager::getInstance().bind(ei_ev_mouse_buttonup, nullptr, "all", callback_released, user_param);

    return EI_TRUE;
}

bool_t MovableOnClick::callback_released(Widget *widget, Event *event, void *user_param)
{

    EventManager::getInstance().unbind(
        ei_ev_mouse_move,
        nullptr,
        "all",
        ((ei_callback_t*)user_param)[1],
        nullptr);

    //All tant que la fenêtre ne se déplace pas vraiment, car pas de dessin dans l'offscreen pour le moment
    EventManager::getInstance().unbind(
        ei_ev_mouse_buttonup,
        nullptr,
        "all",
        callback_released,
        user_param);

    return EI_TRUE;
}
MovableOnClick::~MovableOnClick() {
    delete callbacks;
}
}