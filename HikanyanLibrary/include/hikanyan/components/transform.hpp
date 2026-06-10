#pragma once

#include <hikanyan/core/component.hpp>
#include <hikanyan/system/vector.hpp>

namespace hikanyan {

class Transform : public Component {
public:
    [[nodiscard]] const Vector3& position() const noexcept { return position_; }
    [[nodiscard]] const Vector3& rotation() const noexcept { return rotation_; }
    [[nodiscard]] const Vector3& scale() const noexcept { return scale_; }

    void set_position(const Vector3& position) noexcept { position_ = position; }
    void set_rotation(const Vector3& rotation) noexcept { rotation_ = rotation; }
    void set_scale(const Vector3& scale) noexcept { scale_ = scale; }

    void translate(const Vector3& amount) noexcept { position_ += amount; }

private:
    Vector3 position_{0.0f, 0.0f, 0.0f};
    Vector3 rotation_{0.0f, 0.0f, 0.0f};
    Vector3 scale_{1.0f, 1.0f, 1.0f};
};

} // namespace hikanyan
