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
        cout << "Configure the widget !" << endl;

        GeometryManager* currendWidgetManager = widget->getGeometryManager();

        if (currendWidgetManager)
        {
            cout << "Already a manager for this widget !" << endl;
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

        const Rect* oldChildRect;
        Rect newChildRect;

        for (std::list<Widget*>::iterator it = children.begin(); it != children.end(); it++) //Post-inccrémentation dans la doc !
        {
            oldChildRect = ((Widget *)(*it))->getScreenLocation();  //ça fonctionne bien ce truc ?

            // switch (_dataMap.)
            // {
            //     case /* constant-expression */:
            //         /* code */
            //         break;
            
            //     default:
            //         break;
            }
    }
    void Placer::release(Widget *widget)
    {
        _widgetData.remove(widget);
    }

}

    
