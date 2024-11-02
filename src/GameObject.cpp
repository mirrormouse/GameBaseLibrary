#include "GameObject.h"

GameObject::GameObject(int updateInterval, int drawOrder)
    : updateInterval(updateInterval), drawOrder(drawOrder), lastUpdateTime(std::chrono::steady_clock::now())
{
}

void GameObject::CheckAndCallFixedUpdate()
{
    if (updateInterval > 0)
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();

        if (elapsedTime >= updateInterval)
        {
            FixedUpdate();
            lastUpdateTime = currentTime;
        }
    }
}