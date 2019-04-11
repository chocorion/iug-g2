#include "ei_toppanel.h"
#include "ei_geometrymanager.h"
#include "ei_event.h"
#include <iostream>
#include "ei_application.h"

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
            nullptr,
            new color_t({230, 30, 30, 255}),
            nullptr,
            nullptr,
            new const char*("*"),
            nullptr,
            new color_t({40, 40, 40, 255}),
            new anchor_t(ei_anc_center),
            nullptr,
            nullptr,
            nullptr
        );

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


bool_t TopPanel::callback_on_click(Widget *widget, Event *event, void *user_param)
{
    MouseEvent *e = static_cast<MouseEvent *>(event);
    TopPanel *toppanel = static_cast<TopPanel *>(widget);

    //Save the click coordinate in panel reference
    toppanel->click_offset = Point(
        e->where.x() - toppanel->getScreenLocation()->top_left.x(),
        e->where.y() - toppanel->getScreenLocation()->top_left.y()
    );

    return EI_TRUE;
}

bool_t TopPanel::callback_move_panel(Widget *widget, Event *event, void *user_param)
{
    static Rect oldPos;
    static bool oldPosEnable = false;
    static bool x_expend = false;
    static bool y_expend = false;
    
    MouseEvent *e = static_cast<MouseEvent *>(event);
    TopPanel *toppanel = static_cast<TopPanel *>(user_param);

    Rect ParentPos = Rect(
        Point(
            e->where.x() - toppanel->click_offset.x(),
            e->where.y() - toppanel->click_offset.y()),
        toppanel->getParent()->getScreenLocation()->size);

    Rect winPos = Rect(*(toppanel->getParent()->getParent()->getScreenLocation()));

    if (ParentPos.top_left.x() < 0 && !y_expend) {
        if (!oldPosEnable){
            oldPos = Rect(
                Point(
                    0,
                    ParentPos.top_left.y()
                ),
                ParentPos.size
            );
            oldPosEnable = true;
            x_expend = true;

        }
        ParentPos = Rect(
            Point(
                0,
                0
            ),
            Size(
                winPos.size.width()/2,
                winPos.size.height()
            )
        );
    } else if (ParentPos.top_left.x() + ParentPos.size.width() > winPos.size.width() && !y_expend) {
        if (!oldPosEnable) {
            oldPos = Rect(
                Point(
                    ParentPos.top_left.x() - ((ParentPos.top_left.x() + ParentPos.size.width()) - winPos.size.width()),
                    ParentPos.top_left.y()
                ),
                ParentPos.size
            );

            x_expend = true;
            oldPosEnable = true;
        }

        ParentPos = Rect(
            Point(
                winPos.size.width()/2,
                0
            ),
            Size(
                winPos.size.width()/2,
                winPos.size.height()
            )
        );
    } else if (oldPosEnable && !y_expend)
    {
        oldPosEnable = false;
        x_expend = false;
        ParentPos = oldPos;
    }

    if (ParentPos.top_left.y() < 0 && !x_expend) {
        if (!oldPosEnable) {
            oldPos = Rect(
                Point(
                    0,
                    0
                ),
                ParentPos.size
            );
            oldPosEnable = true;
            y_expend = true;
        }
        ParentPos = Rect(
            Point(
                0,
                0
            ),
            Size(
                winPos.size.width(),
                winPos.size.height()/2
            )
        );  
            
    } else if (ParentPos.top_left.y() + ParentPos.size.height() > winPos.size.height() && !x_expend) {
        if (!oldPosEnable) {
            oldPos = Rect(
                Point(
                    0,
                    ParentPos.top_left.y() - ((ParentPos.top_left.y() + ParentPos.size.height()) - winPos.size.height())
                ),
                ParentPos.size
            );
            oldPosEnable = true;
            y_expend = true;
        }
        ParentPos = Rect(
            Point(
                0,
                winPos.size.height()/2
            ),
            Size(
                winPos.size.width(),
                winPos.size.height()/2
            )
        );
    } else if (oldPosEnable && ! x_expend) {
        oldPosEnable = false;
        y_expend = false;
        ParentPos = oldPos;
    }

    toppanel->getParent()->geomnotify(ParentPos);
    //We had to do this because we bypass the normal use of geometryManager.
    // I think it's better if we can just run on child in geometryManager::run
    for (Widget *w : toppanel->getParent()->getChildren())
    {
        if (w->getGeometryManager())
            w->getGeometryManager()->run(w);
    }

    return EI_TRUE;
}
}