#include "ei_movableonclick.h"
#include <iostream>

using namespace std;

namespace ei {

typedef struct {
    ei_callback_t* callbacks;
    Widget* widget;
} param_t;

MovableOnClick::MovableOnClick(Widget *w, ei_callback_t callback_on_click, ei_callback_t callback_on_move)
{
    param_t *p = new param_t;
    callbacks = new ei_callback_t[2];
    callbacks[0] = callback_on_click;
    callbacks[1] = callback_on_move;
    p->callbacks = callbacks;
    p->widget = w;
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, w, "", enableMoving, (void*)p);
}

bool_t MovableOnClick::enableMoving(Widget* widget, Event* event, void* user_param) {
    cout << "MovableOnClick => Activation !" << endl;
    ei_callback_t* callbacks = ((param_t*) user_param)->callbacks;

    callbacks[0](widget, event, nullptr);
    EventManager::getInstance().bind(ei_ev_mouse_move, nullptr, "all", callbacks[1], (void *)((param_t *)user_param)->widget);
    EventManager::getInstance().bind(ei_ev_mouse_buttonup, nullptr, "all", callback_released, user_param);

    return EI_TRUE;
}

bool_t MovableOnClick::callback_released(Widget *widget, Event *event, void *user_param)
{
    cout << "MovableOnClick => Desactivation !" << endl;
    EventManager::getInstance().unbind(
        ei_ev_mouse_move,
        nullptr,
        "all",
        ((param_t *)user_param)->callbacks[1],
        (void *)((param_t *)user_param) -> widget);

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