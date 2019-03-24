#include "ei_eventmanager.h"
#include "ei_event.h"
#include <iostream>

using namespace std;


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
    std::list<BoundEvent*>::iterator it_list;

    for (it_list = (*l).begin(); it_list != (*l).end(); ++it_list)
    {
        free(*it_list);
    }

    _bank.erase(event);
}

void BoundEventBank::remove(ei_eventtype_t event, BoundEvent *data)
{
    std::list<BoundEvent*>* l = nullptr;

    l = get(event);

    if (!l)
    {
        return ;
    }
    std::list<BoundEvent*>::iterator it_list;

    for (it_list = (*l).begin(); it_list != (*l).end(); ++it_list)
    {
        if (*it_list == data) {
            free(*it_list);
            l->erase(it_list);

            break;
        }
    }
}

void BoundEventBank::remove(ei_eventtype_t event, Widget* widget,tag_t tag,
            ei_callback_t callback,
            void* user_param)
{
    cout << "\t\tIn banck remove : " << endl;
    std::list<BoundEvent*>* l = nullptr;

    l = get(event);

    if (!l)
    {
        return ;
    }
    std::list<BoundEvent*>::iterator it_list;

    cout << "\t\tLooking for : Widget -> " << widget << " Tag -> " << tag << " Callback -> " << &callback << " User param -> " << user_param << endl; 

    for (it_list = (*l).begin(); it_list != (*l).end(); )
    {
        cout << "\t\tCompare with: Widget -> " << (*it_list)->_widget << " Tag -> " << (*it_list)->_tag << " Callback -> " << &(*it_list)->_callback << " User param -> " << (*it_list)->_user_param << endl;
        if (
            (
                (widget != nullptr)?    // == was here. Bug I suppose
                    (*it_list)->_widget == widget :
                    (*it_list)->_tag == tag
            ) &&
            (*it_list)->_callback.target<bool_t(Widget *, Event *, void *)>() == callback.target<bool_t(Widget *, Event *, void *)>() &&    //Can't compare callback, we compare pointers
            (*it_list)->_user_param == user_param
        )
        //param->callback.target<bool_t(Widget *, Event *, void *)>()
        {
            cout << "\t\t EVENT FIND -> Remove it !" << endl;
            delete (*it_list);
            it_list = l->erase(it_list);
        } else {
            ++it_list;
        }
    }
}

bool BoundEventBank::execute(Event* event, Widget* widget, tag_t tag)
{
    std::list<BoundEvent*>* l = get(event->type);

    if (!l)
    {
        return false;
    }
    std::list<BoundEvent*>::iterator it_list;

    for (it_list = (*l).begin(); it_list != (*l).end(); ++it_list)
    {
        if (
            (widget)?
                (*it_list)->_widget == widget:
                (*it_list)->_tag    == tag
        )
        {
            if ((*it_list)->execute(event))
            {
                return true;
            }
        }
    }

    return false;
}

BoundEventBank::~BoundEventBank()
{
    bank_set::iterator it_bank;

    for (it_bank = _bank.begin(); it_bank != _bank.end(); ++it_bank)
    {
        remove(it_bank->first);
    }
}

EventManager::EventManager()
{
    return;
}

void EventManager::bind (ei_eventtype_t eventtype,
               Widget*        widget,
               tag_t          tag,
               ei_callback_t  callback,
               void*          user_param)
{
    BoundEvent *data = new BoundEvent(
        widget, tag, callback, user_param
    );

    _bank.add(eventtype, data);
}

void EventManager::unbind (ei_eventtype_t eventtype,
                 Widget*        widget,
                 tag_t          tag,
                 ei_callback_t  callback,
                 void*          user_param)
{
    cout << "\tCalling bank remove..." << endl;
    _bank.remove(eventtype, widget, tag, callback, user_param);
}





bool EventManager::execute(Event *event, Widget* widget)
{
    return _bank.execute(event, widget, "");
}

bool EventManager::execute(Event *event, tag_t tag)
{
    return _bank.execute(event, nullptr, tag);
}

}

