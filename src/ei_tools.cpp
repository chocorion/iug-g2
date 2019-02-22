#include "ei_tools.h"


#include <iostream>

using namespace std;

namespace ei
{

    Point* Tools::findAnchor(Rect* base, Rect* box, anchor_t *box_anchor)
    {
       
    
        anchor_t _anchor = *box_anchor;
        Point* anchor = new Point(base->top_left.x()+base->size.width()/2,base->top_left.y()+base->size.height()/2);

        switch (_anchor)
        {
            case ei_anc_none:   //Northwest by default
            case ei_anc_northwest:
                anchor = new Point(
                    anchor->x() - base->size.width() / 2,
                    anchor->y() - base->size.height() / 2
                );
                break;
            
            case ei_anc_north:
                anchor = new Point(
                    anchor->x() - box->size.width()/2,
                    anchor->y() - base->size.height() / 2
                );
                break;
            
            case ei_anc_northeast:
                anchor = new Point(
                    anchor->x() + base->size.width() / 2 - box->size.width(),
                    anchor->y() - base->size.height() / 2
                );
                break;

            case ei_anc_south:
                anchor = new Point(
                    anchor->x() - box->size.width()/2,
                    anchor->y() + base->size.height() / 2 - box->size.height()
                );
                break;

            case ei_anc_southwest:
                anchor = new Point(
                    anchor->x() - base->size.width() / 2,
                    anchor->y() + base->size.height() / 2 - box->size.height()
                );
                break;

            case ei_anc_southeast:
                anchor = new Point(
                    anchor->x() + base->size.width() / 2 - box->size.width(),
                    anchor->y() + base->size.height() / 2 - box->size.height()
                );
                break;

            case ei_anc_west:
                anchor = new Point(
                    anchor->x() - base->size.width() / 2,
                    anchor->y() - box->size.height()/2
                );
                break;

            case ei_anc_east:
                anchor = new Point(
                    anchor->x() + base->size.width() / 2 - box->size.width(),
                    anchor->y() - box->size.height()
                );
                break;

            case ei_anc_center:
                anchor = new Point(
                    anchor->x() - box->size.width()/2,
                    anchor->y() - box->size.height()/2
                );
                break;
            default:
                break;
        }

        return anchor;

    }
}