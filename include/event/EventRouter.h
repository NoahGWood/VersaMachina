#pragma once
#include <common/Base.h>
#include <event/Event.h>
#include <event/EventData.h>
#include <event/EventType.h>
#include <event/EventCategory.h>

namespace VM
{
    class EventRouter {
        public:
            using Callback = std::function<bool(Event& e)>;

            void Subscribe(EventCategory cat, EventType type, Callback cb){
                std::scoped_lock lock(m_ListenerMutex);
                m_Listeners[cat][type].emplace_back(std::move(cb));
            }
            void Emit(Event evt){ // Actually, queues the event
                std::scoped_lock lock(m_QueueMutex);
                m_QueuedEvents.emplace_back(std::move(evt));
            }

            void DrainQueuedEvents(){
                std::vector<Event> draining;
                {
                    std::scoped_lock lock(m_QueueMutex);
                    std::swap(draining, m_QueuedEvents);
                }
                for(auto& evt : draining){
                    EmitQueue(evt);
                }
            }
        private:
            void EmitQueue(Event& e){
                std::scoped_lock lock(m_ListenerMutex);
                auto catIt = m_Listeners.find(e.category);
                if(catIt != m_Listeners.end()){
                    auto typeIt = catIt->second.find(e.type);
                    if(typeIt != catIt->second.end()){
                        for(auto& cb : typeIt->second){
                            if(cb(e) || e.handled) break;
                        }
                    }
                }
            }
            std::mutex m_ListenerMutex;
            std::mutex m_QueueMutex;
            std::vector<Event> m_QueuedEvents;
            std::unordered_map<EventCategory, std::unordered_map<EventType, std::vector<Callback>>> m_Listeners;
    };
} // namespace VM
