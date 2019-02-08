#include "ei_geometrymanager.h"
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
                _dataMap[widget->getPick_id()].set(
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
        _dataMap.insert(
            std::make_pair<uint32_t, WidgetPlacerData>(widget->getPick_id(), WidgetPlacerData(widget))
        );

        //On le fait deux fois, redondance de code à corriger !
        _dataMap[widget->getPick_id()].set(
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

    void Placer::run(Widget* widget)
    {
        //Une importance ?
        Widget* parent = widget->getParent();
        
        std::list<Widget*> children = widget->getChildren();

        for (std::list<Widget*>::iterator it = children.begin(); it != children.end(); it++) //Post-inccrémentation dans la doc !
        {
            //Bien lire le cahier des charges
        }


    }

    void Placer::release(Widget *widget)
    {
        if (_dataMap.find(widget->getPick_id()) == _dataMap.end())
        {
            //The widget is not managed by this manager
            return;
        }
        
        _dataMap.erase(widget->getPick_id());
    }

    WidgetPlacerData::WidgetPlacerData(): 
        _anchor(ei_anc_northwest, true),
        _x(0, true),
        _y(0, true),
        _width(0.0f, true),
        _height(0.0f, true),
        _rel_x(0.0f, true),
        _rel_y(0.0f, true),
        _rel_width(0.0f, true),
        _rel_height(0.0f, true) {
            cout << "Create WidgetPlacerData with default constructor !" << endl;
        }

    WidgetPlacerData::WidgetPlacerData(Widget* widget):
        _anchor(ei_anc_northwest, true),
        _x(0, true),
        _y(0, true),
        _width(0.0f, true),
        _height(0.0f, true),
        _rel_x(0.0f, true),
        _rel_y(0.0f, true)
    {
        cout << "Create WidgetPlacerData with complete constructor !" << endl;
        Size size = widget->get_requested_size();

        _rel_width  = Value<float>(size.width(), false);
        _rel_height = Value<float>(size.height(), false);
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
        if (anchor) {   _anchor.setValue(*anchor) ; } 
        if (x)      {   _x.setValue(*x) ;      } 
        if (y)      {   _y.setValue(*y) ;      } 
        if (width)  {   _width.setValue(*width) ;  }
        if (height) {   _height.setValue(*height) ; }
        if (rel_x)  {   _rel_x.setValue(*rel_x) ;  }
        if (rel_y)  {   _rel_y.setValue(*rel_y) ;  }

        if (rel_width) {  _rel_width.setValue(*rel_width) ;  }
        if (rel_height){  _rel_height.setValue(*rel_height);  }
    }

}