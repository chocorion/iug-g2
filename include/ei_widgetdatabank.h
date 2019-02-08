#ifndef WIDGETDATABANK_H
#define WIDGETDATABANK_H

#include "ei_widgetplacerdata.h"
#include "ei_widget.h"
#include <unordered_map>

namespace ei {

class WidgetDataBank
{
    private:
        std::unordered_map<uint32_t, WidgetPlacerData*> _dataMap;
    
    public:
        ~WidgetDataBank();
        WidgetPlacerData* get(Widget* widget);
        void  set(Widget* widget, WidgetPlacerData* data);
        void remove(Widget* widget);

};
}
#endif