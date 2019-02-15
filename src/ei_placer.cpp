#include "ei_geometrymanager.h"
#include "ei_widgetdatabank.h"
#include "ei_widgetplacerdata.h"

#include <iostream>

using namespace std;

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
                WidgetPlacerData *data = _widgetData.get(widget);

                if (!data)
                {
                    cerr << "Error in Placer::configure: No data found in the bank for this widget" << endl;
                    //Had to quit
                }
                
                data->set(
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
        }
        widget->setGeometryManager(this);
        //We need to add this widget to the list
        //The place is normaly free because widget id is uniq
        WidgetPlacerData* data = new WidgetPlacerData(widget);
        data->set(
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

        _widgetData.set(
            widget,
            data
        );
    }

    void Placer::run(Widget* widget)
    {
        std::list<Widget*> children = widget->getChildren();
        Rect* containerRect = widget->getContentRect();

        Widget* currentChild;
        const Rect* oldChildRect;
        Rect newChildRect;
        WidgetPlacerData* childData;
        point ancre;

        for (std::list<Widget*>::iterator it = children.begin(); it != children.end(); it++) //Post-inccrémentation dans la doc !
        {
            currentChild = (Widget *)(*it);
            oldChildRect = currentChild->getScreenLocation();  //ça fonctionne bien ce truc ?
            childData = _widgetData.get(currentChild);

            //Ancre point 
            ancre.x = childData->rel_x * containerRect->width  + childData->x;
            ancre.y = childData->rel_y * containerRect->height + childData->y;
            
            //Calculate width and height
            newChildRect.width = childData->rel_width * containerRect->width + childData->width;
            newChildRect.height = childData->rel_height * containerRect->height + childData->height;
            
            switch (childData->_anchor.getValue())
            {
                case ei_anc_none:   //Northwest by default
                case ei_anc_northwest:
                    newChildRect = ancre.x;
                    newChildRect = ancre.y;
                    break;
                
                case ei_anc_north:
                    newChildRect.x = ancre.x - newChildRect.width/2;
                    newChildRect.y = ancre.y;
                    break;
                
                case ei_anc_northeast:
                    newChildRect.x = ancre.x - newChildRect.width;
                    newChildRect.y = ancre.y;
                    break;

                case ei_anc_south:
                    newChildRect.x = ancre.x - newChildRect.width/2;
                    newChildRect.y = ancre.y - newChildRect.height;
                    break;

                case ei_anc_southwest:
                    newChildRect.x = ancre.x;
                    newChildRect.y = ancre.y - newChildRect.height;
                    break;

                case ei_anc_southeast:
                    newChildRect.x = ancre.x - newChildRect.width;
                    newChildRect.y = ancre.y - newChildRect.height;
                    break;

                case ei_anc_west:
                    newChildRect.x = ancre.x;
                    newChildRect.y = ancre.y - newChildRect.height/2;
                    break;

                case ei_anc_east:
                    newChildRect.x = ancre.x - newChildRect.width;
                    newChildRect.y = ancre.y - newChildRect.height;
                    break;
                default:
                    break;
            }

            //Vérifier si newChildRect et oldChildRect son différent ou non
            if (
                newChildRect.x != oldChildRect.x ||
                newChildRect.y != oldChildRect.y ||
                newChildRect.width != oldChildRect.width ||
                newChildRect.height != oldChildRect.height
            ) {
                run(current_child);
                current_child.geomNotify(newChildRect);
            }
        }
    }

    void Placer::release(Widget *widget)
    {
        _widgetData.remove(widget);
    }

}

    
