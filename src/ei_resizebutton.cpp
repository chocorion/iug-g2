#include "ei_resizebutton.h"
#include "ei_toplevel.h"
#include "ei_eventmanager.h"
#include "ei_geometrymanager.h"

#include <iostream>

using namespace std;

namespace ei {

ResizeButton::ResizeButton(Widget *parent) : Frame(parent), MovableOnClick(this, callback_on_click, callback_move_button) {}

bool_t ResizeButton::callback_on_click(Widget *widget, Event *event, void *user_param)
{
    MouseEvent *e = static_cast<MouseEvent *>(event);
    ResizeButton *resizeButton = static_cast<ResizeButton *>(widget);

    //Save the click coordinate in panel reference
    resizeButton->click_offset = Point(
        resizeButton->getScreenLocation()->size.width() + resizeButton->getScreenLocation()->top_left.x() - e->where.x(),
        resizeButton->getScreenLocation()->size.height() + resizeButton->getScreenLocation()->top_left.y() - e->where.y()
    );

    return EI_TRUE;
}

bool_t ResizeButton::callback_move_button(Widget *widget, Event *event, void *user_param)
{
    MouseEvent *e = static_cast<MouseEvent *>(event);
    ResizeButton *resizeButton = static_cast<ResizeButton *>(user_param);

    const Rect* parentLocation = resizeButton->getParent()->getScreenLocation();
    const Rect* containerLocation = resizeButton->getParent()->getParent()->getScreenLocation();

    const Point bottom_right = Point(
        e->where.x() + resizeButton->click_offset.x(),
        e->where.y() + resizeButton->click_offset.y()
    );

    Size newSize = Size(
        bottom_right.x() - parentLocation->top_left.x(),
        bottom_right.y() - parentLocation->top_left.y()
    );

    Rect newRect = *(parentLocation);

    switch(((Toplevel*)(resizeButton->getParent()))->getAxis())
    {
        case ei_axis_x:
            newRect.size = Size(newSize.width(), parentLocation->size.height());
            break;
        case ei_axis_y:
            newRect.size = Size(parentLocation->size.width(), newSize.height());
            break;
        default:
            newRect.size = newSize;
            break;
    }


    //Verify that the new position of the widget still in the parent
    if(bottom_right.x() > containerLocation->top_left.x() + containerLocation->size.width())
    {
        newRect.size = Size(
            containerLocation->top_left.x() + containerLocation->size.width() - parentLocation->top_left.x(),
            newRect.size.height()
        );
    }
    if(bottom_right.y() > containerLocation->top_left.y() + containerLocation->size.height())
    {
        newRect.size = Size(
            newRect.size.width(),
            containerLocation->top_left.y() + containerLocation->size.height() - parentLocation->top_left.y()
        );
    }

    //Verify that the widget isn't to small. It works only with topLevel parent, but for the moment only toplevel can be resized.
    if (newRect.size.width() < ((Toplevel*)(resizeButton->getParent()))->getMinimalSize()->width())
    {
        newRect.size = Size(
            ((Toplevel*)(resizeButton->getParent()))->getMinimalSize()->width(),
            newRect.size.height()
        );
    }
    if (newRect.size.height() < ((Toplevel*)(resizeButton->getParent()))->getMinimalSize()->height())
    {
        newRect.size = Size(
            newRect.size.width(),
            ((Toplevel*)(resizeButton->getParent()))->getMinimalSize()->height()
        );
    }

    resizeButton->getParent()->geomnotify(newRect);
    //We had to do this because we bypass the normal use of geometryManager.
    // I think it's better if we can just run on child in geometryManager::run
    for (Widget *w : resizeButton->getParent()->getChildren())
    {
        if (w->getGeometryManager())
            w->getGeometryManager()->run(w);
    }

    return EI_TRUE;
}

}