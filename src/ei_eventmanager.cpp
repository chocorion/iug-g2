#include "ei_eventmanager.h"
#include "ei_event.h"
namespace ei
{
BoundEvent::BoundEvent()
{
    return;
}

BoundEvent::BoundEvent(
            Widget* widget,
            tag_t tag,
            ei_callback_t callback,
            void* user_param
        ): 
        _widget(widget),
        _tag(tag),
        _callback(callback),
        _user_param(user_param) {}

bool BoundEvent::execute(Event* event)
{
    return _callback(_widget, event, _user_param);
}


std::list<BoundEvent*>* BoundEventBank::get(ei_eventtype_t event)
{
    if (_bank.find(event) == _bank.end())
    {
        return nullptr;
    }

    return _bank.at(event);
}

void BoundEventBank::add(ei_eventtype_t event, BoundEvent *data)
{
    std::list<BoundEvent*>* l = nullptr;

    l = get(event);

    if (!l)
    {
        _bank.insert(
            {event, (l = new std::list<BoundEvent*>)}
        );
    }
 
    l->push_back(data);
}

void BoundEventBank::remove(ei_eventtype_t event)
{

    std::list<BoundEvent*>* l = nullptr;

    l = get(event);

    if (!l)
    {
        return ;
    }

    std::unordered_map<ei_eventtype_t, std::list<BoundEvent*>*>::iterator it_bank;

    for (it_bank = _bank.begin(); it_bank != _bank.end(); ++it_bank)
    {
        std::list<BoundEvent*>::iterator it_list;

        std::list l = *(it_bank->second);
        for (it_list = l.begin(); it_list != l.end; ++it_list)
        {
            free(*it_list);
        }
    }
}

}

