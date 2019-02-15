#ifndef WIDGETPLACERDATA_H
#define WIDGETPLACERDATA_H

#include "ei_types.h"
#include "ei_widget.h"

namespace ei {

/**
 * @brief Represent a couple of (value, boolean). The boolean is used to know if the value is a default value.
 * 
 * @tparam T The type's value
 */
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

        /**
         * @return true if the value if a default value
         * @return false if the value isn't a default value
         */
        bool isDefault() const
        {
            return _default;
        }

        /**
         * @return T the value
         */
        T getValue() const {
            return _value;
        }

        /**
         * @brief Set the Value object
         * 
         * @param new_value 
         */
        void setValue(T new_value)
        {
            _value = new_value;
        }
};

class Placer;

/**
 * @brief Represent the widget's data about is localisation on the screen
 * 
 */
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

        friend Placer;


    
    public:
        WidgetPlacerData();
        WidgetPlacerData(Widget* widget);
        
        /**
         * @brief Set all the value of WidgetPlacerData
         * 
         * @param widget    The widget to place.
         * @param anchor    How to anchor the widget to the position defined by the placer
         *        (defaults to ei_anc_northwest).
         * @param x   The absolute x position of the widget (defaults to 0).
         * @param y   The absolute y position of the widget (defaults to 0).
         * @param width   The absolute width for the widget (defaults to the requested width
         *        of the widget).
         * @param height    The absolute height for the widget (defaults to the requested height
         *        of the widget).
         * @param rel_x   The relative x position of the widget: 0.0 corresponds to the left
         *        side of the master, 1.0 to the right side (defaults to 0.0).
         * @param rel_y   The relative y position of the widget: 0.0 corresponds to the top
         *        side of the master, 1.0 to the bottom side (defaults to 0.0).
         * @param rel_width The relative width of the widget: 0.0 corresponds to a width of 0,
         *        1.0 to the width of the master (defaults to 0.0).
         * @param rel_height  The relative height of the widget: 0.0 corresponds to a height of 0,
         *        1.0 to the height of the master (defaults to 0.0).
         */
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

