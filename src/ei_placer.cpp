#include "ei_geometrymanager.h"

namespace ei
{
    /**
     * \brief Configures the geometry of a widget using the "placer" geometry manager.
     *    If the widget was already managed by another geometry manager, then it is first
     *    removed from the previous geometry manager.
     *    If the widget was already managed by the "placer", then this calls simply updates
     *    the placer parameters: arguments that are not NULL replace previous values.
     *    When the arguments are passed as NULL, the placer uses default values (detailed in
     *    the argument descriptions below). If no size is provided (either absolute or
     *    relative), then the requested size of the widget is used, i.e., the minimal size
     *    required to display its content.
     *
     * @param widget    The widget to place.
     * @param anchor    How to anchor the widget to the position defined by the placer
     *        (defaults to ei_anc_northwest).
     * @param x   The absolute x position of the widget (defaults to 0).
     * @param y   The absolute y position of the widget (defaults to 0).
     * @param width   The absolute width for the widget (defaults to the requested width
     *        of the widget).
     * @param height    The absolute height for the widget (defaults to the requested height
     *        of the widget).
     * @param rel_x   The relative x position of the widget: 0.0 corresponds to the left
     *        side of the master, 1.0 to the right side (defaults to 0.0).
     * @param rel_y   The relative y position of the widget: 0.0 corresponds to the top
     *        side of the master, 1.0 to the bottom side (defaults to 0.0).
     * @param rel_width The relative width of the widget: 0.0 corresponds to a width of 0,
     *        1.0 to the width of the master (defaults to 0.0).
     * @param rel_height  The relative height of the widget: 0.0 corresponds to a height of 0,
     *        1.0 to the height of the master (defaults to 0.0).
     */
    void Placer::configure (Widget*    widget,
                    anchor_t*  anchor,
                    int*       x,
                    int*       y,
                    float*     width,
                    float*     height,
                    float*     rel_x,
                    float*     rel_y,
                    float*     rel_width,
                    float*     rel_height)
    {
        if (widget->getGeometryManager() != this) {
            //The widget is already managed by another geometry manager.
            widget->getGeometryManager()->release(widget);
            //We need to add this widget to the list...
        }
        
    }

    WidgetPlacerData::WidgetPlacerData()
    {
        //Set all value to default
        _anchor = ei_anc_northwest;
        _x = 0;
        _y = 0;
        _width  = 0;
        _height = 0;

        _rel_x = 0.0:
        _rel_y = 0.0;
        _rel_width  = 0.0;
        _rel_height = 0.0;
    }

    void WidgetPlacerData::set(
            anchor_t*  anchor,
            int*       x,
            int*       y,
            float*     width,
            float*     height,
            float*     rel_x,
            float*     rel_y,
            float*     rel_width,
            float*     rel_height)
    {
        if (anchor) {   _anchor = *anchor ; } 
        if (x)      {   _x      = *x ;      } 
        if (y)      {   _y      = *y ;      } 
        if (width)  {   _width  = *width ;  }
        if (height) {   _height = *height ; }
        if (rel_x)  {   _rel_x  = *rel_x ;  }
        if (rel_y)  {   _rel_y  = *rel_y ;  }

        if (rel_width) {  _rel_width  = *rel_width ;  }
        if (rel_height){  _rel_height = *rel_height;  }
    }

}