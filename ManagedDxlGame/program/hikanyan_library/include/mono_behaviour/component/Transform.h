#pragma once
#include "Component.h"
#include "../dxlib_ext/dxlib_ext.h"

class Transform : public Component
{
private:
    tnl::Vector3 position_{0, 0, 0};
    tnl::Vector3 rotation_{0, 0, 0};
    tnl::Vector3 scale_{1, 1, 1};

public:
    Transform() = default;

    // positionプロパティ
    tnl::Vector3 get_position() const { return position_; }
    void set_position(const tnl::Vector3& value) { position_ = value; }

    // rotationプロパティ
    tnl::Vector3 get_rotation() const { return rotation_; }
    void set_rotation(const tnl::Vector3& value) { rotation_ = value; }

    // scaleプロパティ
    tnl::Vector3 get_scale() const { return scale_; }
    void set_scale(const tnl::Vector3& value) { scale_ = value; }
};
