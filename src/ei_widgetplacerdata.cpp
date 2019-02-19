#include "ei_widgetplacerdata.h"
#include "ei_types.h"
#include "ei_widget.h"

namespace ei {

WidgetPlacerData::WidgetPlacerData(): 
     _anchor(ei_anc_northwest, true),
     _x(0, true),
     _y(0, true),
     _width(0.0f, true),
     _height(0.0f, true),
     _rel_x(0.0f, true),
     _rel_y(0.0f, true),
     _rel_width(0.0f, true),
     _rel_height(0.0f, true) {}

 WidgetPlacerData::WidgetPlacerData(Widget* widget):
     _anchor(ei_anc_northwest, true),
     _x(0, true),
     _y(0, true),
     _width(0.0f, true),
     _height(0.0f, true),
     _rel_x(0.0f, true),
     _rel_y(0.0f, true)
 {
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