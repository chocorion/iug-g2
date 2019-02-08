#include "ei_widgetdatabank.h"
#include <unordered_map>
namespace ei {

WidgetDataBank::~WidgetDataBank()
{
    for (std::unordered_map<uint32_t, WidgetPlacerData>::iterator it = _dataMap.begin(); it != _dataMap.end(); it++) //Post-inccrémentation dans la doc !
    {
        delete &it;//A vérifier
    }
}
    
WidgetPlacerData* WidgetDataBank::get(Widget* widget)
{
    if (_dataMap.find(widget->getPick_id()) == _dataMap.end())
        {
            return nullptr;
        }
        
        return &_dataMap.at(widget->getPick_id());
}


void  WidgetDataBank::set(Widget* widget, WidgetPlacerData* data)
{
    _dataMap.insert(
            {widget->getPick_id(), *data}
        );
}
void WidgetDataBank::remove(Widget* widget)
{
    if (_dataMap.find(widget->getPick_id()) == _dataMap.end())
        {
            return;
        }
        delete &_dataMap.at(widget->getPick_id());
        _dataMap.erase(widget->getPick_id());
    }
}