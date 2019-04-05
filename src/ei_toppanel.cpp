#include "ei_toppanel.h"
#include "ei_geometrymanager.h"
#include "ei_event.h"
#include <iostream>

using namespace std;

namespace ei {


TopPanel::TopPanel() {
    return;
}

//Maybe we had to use parent in movable on click ?
TopPanel::TopPanel(Widget *parent):Frame(parent), MovableOnClick(this, callback_on_click, callback_move_panel) {}

void TopPanel::configure(const color_t *color,
                    int *border_width,
                    relief_t *relief,
                    const char **text,
                    font_t *text_font,
                    color_t *text_color,
                    anchor_t *text_anchor,
                    surface_t *img,
                    Rect **img_rect,
                    anchor_t *img_anchor,
                    bool closable,
                    bool resizable,
                    bool reductible)
{
    Frame::configure(
        nullptr, color, border_width, relief, text, text_font,
        text_color, text_anchor, img, img_rect, img_anchor
    );

    if (closable) {
        CloseButton = new Frame(this);
        ((Frame *)CloseButton)->configure(
            new Size(10.0, 10.0),
            new color_t({230, 30, 30, 255}),
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr, //Hum maybe will cause problems....
            nullptr
        );
        // ((Frame *)CloseButton)->configure(
        //     nullptr,//Just for the moment
        //     new color_t({230, 30, 30, 255}),
        //     nullptr,
        //     nullptr,
        //     new const char*("X"),
        //     nullptr,
        //     new color_t({40, 40, 40, 255}),
        //     new anchor_t(ei_anc_center),
        //     Frame::getImg(),
        //     nullptr, //Hum maybe will cause problems....
        //     nullptr
        // );

        Placer *CloseButtonPlacer = new Placer();
        CloseButtonPlacer->configure(
            CloseButton,
            nullptr,
            new int(6), new int(6),
            new float(15.0), new float(15.0),
            nullptr, nullptr, nullptr, nullptr
        );
    } else {
        CloseButton = nullptr;
    }

    //Not implemented for the moment
    ReduceButton = nullptr;
    ResizeButton = nullptr;

}

void TopPanel::draw(surface_t surface, surface_t pick_surface, Rect *clipper) {
    Frame::draw(surface, pick_surface, clipper);
}

bool_t TopPanel::callback_on_click(Widget *widget, Event *event, void *user_param)
{
    MouseEvent *e = static_cast<MouseEvent *>(event);
    TopPanel *toppanel = static_cast<TopPanel *>(widget);

    toppanel->click_offset = Point(
        e->where.x() - toppanel->getScreenLocation()->top_left.x(),
        e->where.y() - toppanel->getScreenLocation()->top_left.y()
    );

    return EI_TRUE;
}

bool_t TopPanel::callback_move_panel(Widget *widget, Event *event, void *user_param)
{
    MouseEvent *e = static_cast<MouseEvent *>(event);
    TopPanel *toppanel = static_cast<TopPanel *>(user_param);

    Rect ParentPos = Rect(
        Point(
            e->where.x() - toppanel->click_offset.x(),
            e->where.y() - toppanel->click_offset.y()),
        toppanel->getParent()->getScreenLocation()->size);

    toppanel->getParent()->geomnotify(ParentPos);
    //We had to do this because we bypass the normal use of geometryManager.
    // I think it's better if we can just run on child...
    for (Widget *w : toppanel->getParent()->getChildren())
    {
        if (w->getGeometryManager())
            w->getGeometryManager()->run(w);
    }

    return EI_TRUE;
}
}