#pragma once

#include <hikanyan/core/component.hpp>
#include <hikanyan/system/vector.hpp>

namespace hikanyan {

class BoxCollider2D : public Component {
public:
    [[nodiscard]] const Vector2& size() const noexcept { return size_; }
    [[nodiscard]] const Vector2& offset() const noexcept { return offset_; }

    void set_size(const Vector2& size) noexcept { size_ = size; }
    void set_offset(const Vector2& offset) noexcept { offset_ = offset; }

    [[nodiscard]] bool intersects(const BoxCollider2D& other) const;
    [[nodiscard]] bool intersects_at(const Vector2& position, const BoxCollider2D& other, const Vector2& other_position) const;

    virtual void on_trigger_enter_2d(BoxCollider2D& /*other*/) {}
    virtual void on_collision_enter_2d(BoxCollider2D& /*other*/) {}

private:
    Vector2 size_{1.0f, 1.0f};
    Vector2 offset_{0.0f, 0.0f};
};

} // namespace hikanyan
