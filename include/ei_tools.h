/**
 *  @file ei_eventmanager.h
 *  @brief  Manages event callbacks.
 *
 *  \author
 *  Created by François Bérard on 18.12.11.
 *  Modified by Pierre Bénard and Aurélie Bugeau
 *
 */

#ifndef EI_TOOLS_H
#define EI_TOOLS_H

#include "ei_draw.h"
#include "ei_types.h"

namespace ei {

class Tools
{   
    
    public :

        static Point* findAnchor(Rect* base, Rect* box, anchor_t *box_anchor);


};

}

#endif // EI_TOOLS_H
