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
        Point ancre;

        for (std::list<Widget*>::iterator it = children.begin(); it != children.end(); it++) //Post-inccrémentation dans la doc !
        {
            currentChild = (Widget *)(*it);
            oldChildRect = currentChild->getScreenLocation();  //ça fonctionne bien ce truc ?
            childData = _widgetData.get(currentChild);

            //Ancre point 
            ancre.x() = childData->_rel_x * containerRect->size.width()  + childData->_x;
            ancre.y() = childData->_rel_y * containerRect->size.height() + childData->_y;
            

            //ATTENTION PRENDDRE EN COMPTE S'IL N'Y EN A PAS PAR DEFAULT !!

            //Calculate width and height
            newChildRect.size.width() = childData->_rel_width * containerRect->size.width() + childData->_width;
            newChildRect.size.height() = childData->_rel_height * containerRect->size.height() + childData->_height;
            
            switch (childData->_anchor.getValue())
            {
                case ei_anc_none:   //Northwest by default
                case ei_anc_northwest:
                    newChildRect.top_left = (
                        ancre.x(),
                        ancre.y()
                    );
                    break;
                
                case ei_anc_north:
                    newChildRect.top_left = (
                        ancre.x() - newChildRect.size.width()/2,
                        ancre.y()
                    );
                    break;
                
                case ei_anc_northeast:
                    newChildRect.top_left = (
                        ancre.x() - newChildRect.size.width(),
                        ancre.y()
                    );
                    break;

                case ei_anc_south:
                    newChildRect.top_left = (
                        ancre.x() - newChildRect.size.width()/2,
                        ancre.y() - newChildRect.size.height()
                    );
                    break;

                case ei_anc_southwest:
                    newChildRect.top_left = (
                        ancre.x(),
                        ancre.y() - newChildRect.size.height()
                    );
                    break;

                case ei_anc_southeast:
                    newChildRect.top_left = (
                        ancre.x() - newChildRect.size.width(),
                        ancre.y() - newChildRect.size.height()
                    );
                    break;

                case ei_anc_west:
                    newChildRect.top_left = (
                        ancre.x(),
                        ancre.y() - newChildRect.size.height()/2
                    );
                    break;

                case ei_anc_east:
                    newChildRect.top_left = (
                        ancre.x() - newChildRect.size.width(),
                        ancre.y() - newChildRect.size.height()
                    );
                    break;
                default:
                    break;
            }

            //Vérifier si newChildRect et oldChildRect son différent ou non
            if (
                newChildRect.top_left.x() != oldChildRect->top_left.x() ||
                newChildRect.top_left.y() != oldChildRect->top_left.y() ||
                newChildRect.size.width() != oldChildRect->size.width() ||
                newChildRect.size.height() != oldChildRect->size.height()
            ) {
                run(currentChild);
                currentChild->geomnotify(newChildRect);
            }
        }
    }

    void Placer::release(Widget *widget)
    {
        _widgetData.remove(widget);
    }

}

    
