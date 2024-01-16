#include "InputManager.h"

void InputManager::update(float delta_time)
{
    if (tnl::Input::IsKeyDown(eKeys::KB_SPACE))
    {
        Debug::log("KB_SPACE");
    }
}
