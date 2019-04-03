#include "ei_geometrymanager.h"


#include <iostream>

using namespace std;

namespace ei
{

Placer::Placer():
    _anchor(ei_anc_northwest),
     _x(0),
     _y(0),
     _width(0.0f),
     _height(0.0f),
     _rel_x(0.0f),
     _rel_y(0.0f),
     _rel_width(0.0f),
     _rel_height(0.0f),
     _is_default_width(true),
     _is_default_height(true) {}

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
        GeometryManager* currentGeometryManager = widget->getGeometryManager();

        if (currentGeometryManager != this)
        {
            //The widget is already managed by another geometry manager.
            if (currentGeometryManager)
            {
                widget->getGeometryManager()->release(widget);
            }
            widget->setGeometryManager(this);
        }
        
        if (anchor) {   _anchor = *anchor ; } 
        if (x)      {   _x = *x ;           } 
        if (y)      {   _y = *y ;           } 

        if (width)  {
            _width = *width   ; 
            _is_default_width = false;
        }

        if (height) {
            _height = *height ; 
            _is_default_height = false;
        }

        if (rel_x)  {   _rel_x = *rel_x ;   }
        if (rel_y)  {   _rel_y = *rel_y ;   }

        if (rel_width) {  
            _rel_width = *rel_width;
            _is_default_width = false;
        }
        if (rel_height){
            _rel_height = *rel_height;
            _is_default_height = false;
        }

        //First run for the widget
        run(widget);
        
    }

    void Placer::run(Widget* widget)
    {
        Rect* container = nullptr;
        Widget* parent  = nullptr;

        cout << "Before " << widget->getScreenLocation()->top_left.x() << " " << widget->getScreenLocation()->top_left.y() << " " << widget->getScreenLocation()->size.width() << " " << widget->getScreenLocation()->size.height() << endl;

        if ((parent = widget->getParent()))
        {
            container = parent->getContentRect();
            cout << " Parent : " << container->top_left.x() << " " << container->top_left.y() << " " << container->size.width() << " " << container->size.height() << endl;
            if (!container)
            {
                cerr << "Error in placer run: parent widget don't have content_rect !" << endl;
                exit(EXIT_FAILURE);
            }
            cout << "\n\tx : " << _x << "\n\ty : " << _y << "\n\twidth : " << _width << "\n\theight : " << _height << "\n\trel_x : " << _rel_x << "\n\trel_y : " << _rel_y;
            cout << "\n\trel_width : " << _rel_width << "\n\trel_height : " << _rel_height << "\n\tis default width : " << _is_default_width << "\n\tis default height : " << _is_default_height << endl;   

        } else
        {
            cerr << "You cant' call\n\tPlacer::run on root widget !" << endl;
            exit(EXIT_FAILURE);
        }

        const Rect* current_widget_location = widget->getScreenLocation();
        Rect new_widget_location;



        Point anchor = Point(
            _rel_x * container->size.width()  + _x + container->top_left.x(),
            _rel_y * container->size.height() + _y + container->top_left.y()
        );

        double width = (_is_default_width) ?
            widget->get_requested_size().width() :
            _rel_width * container->size.width() + _width;

        double height = (_is_default_height) ?
            widget->get_requested_size().height() :
            _rel_height * container->size.height() + _height;
        
            //Calculate width and height 
        new_widget_location.size = Size(
            width,
            height
        );
            
        switch (_anchor)
        {
            case ei_anc_none:   //Northwest by default
            case ei_anc_northwest:
                new_widget_location.top_left = Point(
                    anchor.x(),
                    anchor.y()
                );
                break;
            
            case ei_anc_north:
                new_widget_location.top_left = Point(
                    anchor.x() - new_widget_location.size.width()/2,
                    anchor.y()
                );
                break;
            
            case ei_anc_northeast:
                new_widget_location.top_left = Point(
                    anchor.x() - new_widget_location.size.width(),
                    anchor.y()
                );
                break;

            case ei_anc_south:
                new_widget_location.top_left = Point(
                    anchor.x() - new_widget_location.size.width()/2,
                    anchor.y() - new_widget_location.size.height()
                );
                break;

            case ei_anc_southwest:
                new_widget_location.top_left = Point(
                    anchor.x(),
                    anchor.y() - new_widget_location.size.height()
                );
                break;

            case ei_anc_southeast:
                new_widget_location.top_left = Point(
                    anchor.x() - new_widget_location.size.width(),
                    anchor.y() - new_widget_location.size.height()
                );
                break;

            case ei_anc_west:
                new_widget_location.top_left = Point(
                    anchor.x(),
                    anchor.y() - new_widget_location.size.height()/2
                );
                break;

            case ei_anc_east:
                new_widget_location.top_left = Point(
                    anchor.x() - new_widget_location.size.width(),
                    anchor.y() - new_widget_location.size.height()
                );
                break;

            case ei_anc_center:
                 new_widget_location.top_left = Point(
                    anchor.x() - new_widget_location.size.width()/2,
                    anchor.y() - new_widget_location.size.height()/2
                );
                break;
            default:
                break;
        }

            //Vérifier si newChildRect et oldChildRect son différent ou non
        cout << "After " << new_widget_location.top_left.x() << " " << new_widget_location.top_left.y() << " " << new_widget_location.size.width() << " " << new_widget_location.size.height() << endl;
        if (
            new_widget_location.top_left.x() != current_widget_location->top_left.x() ||
            new_widget_location.top_left.y() != current_widget_location->top_left.y() ||
            new_widget_location.size.width() != current_widget_location->size.width() ||
            new_widget_location.size.height() != current_widget_location->size.height())
        {
            widget->geomnotify(new_widget_location);
            std::list<Widget *> l;
            for (std::list<Widget *>::iterator it = (l = widget->getChildren()).begin(); it != l.end(); ++it)
            {
                GeometryManager *child_manager;
                if ((child_manager = (*it)->getGeometryManager()))
                {
                    //Use the manager of the child
                    child_manager->run((*it));
                }
            }
            }
        }

    void Placer::release(Widget *widget)
    {
        widget->setGeometryManager(nullptr);
    }

}

    
