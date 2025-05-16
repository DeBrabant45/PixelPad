#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>

namespace PixelPad::Infrastructure
{
	class EventBus
	{
	public:
        template<typename Event>
        using HandlerFunc = std::function<void(const Event&)>;

        template<typename Event>
        void Subscribe(HandlerFunc<Event> handler)
        {
            auto& handlers = GetHandlers<Event>();
            handlers.push_back(std::move(handler));
        }

        template<typename Event>
        void Publish(const Event& event) const
        {
            auto& handlers = GetHandlers<Event>();
            for (const auto& handler : handlers)
            {
                handler(event);
            }
        }

	private:
        template<typename Event>
        std::vector<HandlerFunc<Event>>& GetHandlers() const
        {
            static std::vector<HandlerFunc<Event>> handlers;
            return handlers;
        }
	};
}