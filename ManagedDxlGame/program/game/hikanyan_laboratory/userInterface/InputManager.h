#pragma once
#include "../hikanyan_library/include/mono_behaviour/MonoBehaviour.h"

class InputManager : public MonoBehaviour {
public:
    InputManager() = default;
    virtual ~InputManager() override = default;
    
    void update(float delta_time) override;
    void fixed_update(float delta_time) override;
};
