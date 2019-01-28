#include "ei_geometrymanager.h"

namespace ei
{
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
        GeometryManager* currendWidgetManager = widget->getGeometryManager();

        if (currendWidgetManager)
        {
            if (currendWidgetManager != this)
            {
                //The widget is already managed by another geometry manager.
                widget->getGeometryManager()->release(widget);
            }
            else
            {
                _dataMap[widget->getPick_id].set(
                    anchor,
                    x,
                    y,
                    width,
                    height,
                    rel_x,
                    rel_y,
                    rel_width,
                    rel_height
                );
                return;
            }

            //We need to add this widget to the list
            //The place is normaly free because widget id is uniq
            _dataMap[widget->getPick_id](
                anchor,
                x,
                y,
                width,
                height,
                rel_x,
                rel_y,
                rel_width,
                rel_height
            );
        }
    }

    void Placer::run(Widget* widget)
    {
        //Une importance ?
        Widget* parent = widget->getParent();
        
        //Faire attention aux paramêtres de taille du widget !
        // Placer::configure > widget::requestedSize > defaultSize 
        //                                              Ou est-elle ?


    }

    void Placer::release(Widget *widget)
    {
        if (_dataMap.find(widget->getPick_id) == _dataMap.end())
        {
            //The widget is not managed by this manager
            return;
        }
        
        _dataMap.erase(widget->getPick_id());
    }

    WidgetPlacerData::WidgetPlacerData(Widget* widget)
    {
        //Set all value to default
        _anchor = ei_anc_northwest;
        _x = 0;
        _y = 0;
        _width  = 0;
        _height = 0;

        _rel_x = 0.0;
        _rel_y = 0.0;

        Size* size = widget->get_requested_size();
        
        _rel_width  = size->width;
        _rel_height = size->height;
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