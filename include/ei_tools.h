#ifndef EI_TOOLS_H
#define EI_TOOLS_H

#include "ei_draw.h"
#include "ei_types.h"

namespace ei {

/**
 * @brief Little class for storing usefull funcitons.
 * 
 */
class Tools
{   
    
    public :

        /**
         * @brief Find the anchor coordinate.
         * 
         * @param base The position of the target object.
         * @param box The position of the base container.
         * @param box_anchor The anchor type.
         * @return Point* The anchor coordinate.
         */
        static Point* findAnchor(Rect* base, Rect* box, anchor_t *box_anchor);


};

}

#endif // EI_TOOLS_H
