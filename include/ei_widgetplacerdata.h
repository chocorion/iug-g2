#ifndef WIDGETPLACERDATA_H
#define WIDGETPLACERDATA_H

#include "ei_types.h"
#include "ei_widget.h"

namespace ei {

template<class T> class Value
{
    private:
        T _value;
        bool _default;

    public:
        Value() {
            return;
        }
        Value(T value, bool dft): _value(value), _default(dft){}

        bool isDefault() const
        {
            return _default;
        }

        T getValue() const {
            return _value;
        }

        void setValue(T new_value)
        {
            _value = new_value;
        }
};

class WidgetPlacerData
{
    private:
        Value<anchor_t> _anchor;

        Value<int> _x;
        Value<int> _y;
        Value<float> _width;
        Value<float> _height;

        Value<float> _rel_x;
        Value<float> _rel_y;
        Value<float> _rel_width;
        Value<float> _rel_height;

        


    
    public:
        WidgetPlacerData();
        WidgetPlacerData(Widget* widget);
        
        
        void set(
            anchor_t *anchor,
            int *x,
            int *y,
            float *width,
            float *height,
            float *rel_x,
            float *rel_y,
            float *rel_width,
            float *rel_height
        );
};
}
#endif

