#ifndef WIDGETDATABANK_H
#define WIDGETDATABANK_H

#include "ei_widgetplacerdata.h"
#include "ei_widget.h"
#include <unordered_map>

namespace ei {

/**
 * @brief Manage a unordered_map of all widget's data
 * 
 */
class WidgetDataBank
{
    private:
        std::unordered_map<uint32_t, WidgetPlacerData*> _dataMap;
    
    public:
        WidgetDataBank();
        ~WidgetDataBank();

        /**
         * @param widget widget we want the data
         * @return WidgetPlacerData* The widgetPlacerData associated
         */
        WidgetPlacerData* get(Widget* widget);

        /**
         * @param widget widget we want to set the datas
         * @param data   pointer to the new datas
         */
        void  set(Widget* widget, WidgetPlacerData* data);

        /**
         * @param widget widget we want remove and delete datas
         */
        void remove(Widget* widget);

};
}
#endif