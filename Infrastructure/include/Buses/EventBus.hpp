#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstddef>

namespace PixelPad::Infrastructure
{
    class EventBus
    {
    public:
        template<typename Event>
        using HandlerFunc = std::function<void(const Event&)>;

        using SubscriptionToken = size_t;

        template<typename Event>
        SubscriptionToken Subscribe(HandlerFunc<Event> handler)
        {
            auto& handlers = GetHandlers<Event>();
            SubscriptionToken token = ++m_lastToken;
            handlers.emplace_back(token, std::move(handler));

            return token;
        }

        template<typename Event>
        void Unsubscribe(SubscriptionToken token)
        {
            auto& handlers = GetHandlers<Event>();

            const auto isMatchingToken = [token](const auto& handlerPair)
            {
               const auto& [handlerToken, _] = handlerPair;
               return handlerToken == token;
            };

            handlers.erase(std::remove_if(handlers.begin(), handlers.end(), isMatchingToken),
                handlers.end());
        }

        template<typename Event>
        void Publish(const Event& event) const
        {
            auto& handlers = GetHandlers<Event>();
            for (const auto& [token, handler] : handlers)
            {
                handler(event);
            }
        }

    private:
        template<typename Event>
        std::vector<std::pair<SubscriptionToken, HandlerFunc<Event>>>& GetHandlers() const
        {
            static std::vector<std::pair<SubscriptionToken, HandlerFunc<Event>>> handlers;
            return handlers;
        }

        SubscriptionToken m_lastToken = 0;
    };
}