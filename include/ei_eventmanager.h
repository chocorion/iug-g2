/**
 *  @file ei_eventmanager.h
 *  @brief  Manages event callbacks.
 *
 *  \author
 *  Created by François Bérard on 18.12.11.
 *  Modified by Pierre Bénard and Aurélie Bugeau
 *
 */

#ifndef EI_EVENTMANAGER_H
#define EI_EVENTMANAGER_H

#include "ei_event.h"
#include <unordered_map>

namespace ei {

class BoundEventBank;

/**
 * @brief Represent a bound event in memory
 */
class BoundEvent
{
    private:
        Widget*        _widget;
        tag_t          _tag;
        ei_callback_t  _callback;
        void*          _user_param;

        friend BoundEventBank;

    public:
        BoundEvent();

        BoundEvent(
            Widget* widget,
            tag_t tag,
            ei_callback_t callback,
            void* user_param
        );

        /**
         * @brief execute the callback function for this event
         */
        bool execute(Event* event);
};

/**
 * Manage all the bound events
 */
class BoundEventBank
{
    private:
        typedef std::unordered_map<ei_eventtype_t, std::list<BoundEvent*>*, std::hash<int>> bank_set;
        bank_set _bank;
    
    public:
        ~BoundEventBank();

        /**
         * @brief Get event data. 
         */
        std::list<BoundEvent*>* get(ei_eventtype_t event);

        /**
         * @brief add data for event in the bank.
         */
        void add(ei_eventtype_t event, BoundEvent* data);

        /**
         * @brief remove all event lied to a specific event type
         */
        void remove(ei_eventtype_t event);

        /**
         * @brief remove a specific bound event data
         */
        void remove(
            ei_eventtype_t event,
            Widget* widget,
            tag_t tag,
            ei_callback_t callback,
            void* user_param
        );
        
        /**
         * @brief remove the data if it's lied to event
         */
        void remove(ei_eventtype_t event, BoundEvent *data);

        /**
         * Find and execute the callback for the event by widget or tag
         * @param event the event to handle
         * @param Widget concerned by the event
         * @param tag of the event
         * 
         * @return true if the event was handle, else false
         */
        bool execute(Event* event, Widget* widget, tag_t tag);

};
/**
 * \brief Class that represents the event manager.
 */
class EventManager
{
public:
    /**
     * @return the singleton instance
     */
    static EventManager& getInstance() {
        static EventManager instance;
        return instance;
    }
private:
    EventManager();
    BoundEventBank _bank;

public:
    EventManager(EventManager const&)    = delete;
    void operator=(EventManager const&)  = delete;

    /**
     * \brief	Binds a callback to an event type and a widget or a tag.
     *
     * @param	eventtype	The type of the event.
     * @param	widget		The callback is only called if the event is related to this widget.
     *                      This parameter must be NULL if the "tag" parameter is not NULL.
     * @param	tag		The callback is only called if the event is related to a widget that
     *                  has this tag. A tag can be a widget class name, or the tag "all".
     *      			This parameter must be NULL is the "widget" parameter is not NULL.
     * @param	callback	The callback (i.e. the function to call).
     * @param	user_param	A user parameter that will be passed to the callback when it is called.
     */
    void bind (ei_eventtype_t eventtype,
               Widget*        widget,
               tag_t          tag,
               ei_callback_t  callback,
               void*          user_param);

    /**
     * \brief	Unbinds a callback from an event type and widget or tag.
     *
     * @param	eventtype, widget, tag, callback, user_param
     *			All parameters must have the same value as when
     *          \ref ei::EventManager::bind was called to create the binding.
     */
    void unbind (ei_eventtype_t eventtype,
                 Widget*        widget,
                 tag_t          tag,
                 ei_callback_t  callback,
                 void*          user_param);

    /**
     * @brief Execute the callback
     * @param event event to treat
     * @param widget the widget concerned by the event
     * 
     * @return true if the event is handled, else false
     */
    bool execute(Event *event, Widget* widget);

    /**
     * @brief Execute the callback
     * @param event event to treat
     * @param tag the tag concerned by the event
     * 
     * @return true if the event is handled, else false
     */
    bool execute(Event *event, tag_t tag);
};

}

#endif // EI_EVENTMANAGER_H
