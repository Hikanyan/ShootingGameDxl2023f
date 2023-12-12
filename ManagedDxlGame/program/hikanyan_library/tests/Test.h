#pragma once
#include "../../hikanyan_library/include/mono_behaviour/MonoBehaviour.h"
#include "../../hikanyan_library/include/mono_behaviour/GameObject.h"
#include "../dxlib_ext/dxlib_ext.h"

class Test final : public MonoBehaviour
{
public:
    void start() override
    {
    }

    void update(float delta_time) override
    {
    }

    void draw() override
    {
        DrawBoxEx(owner_->get_transform().get_position(), owner_->get_transform().get_scale().x,
                  owner_->get_transform().get_scale().y, false);
    }
};
