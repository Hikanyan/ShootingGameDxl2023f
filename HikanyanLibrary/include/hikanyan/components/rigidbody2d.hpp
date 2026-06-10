#pragma once

#include <hikanyan/core/behaviour.hpp>
#include <hikanyan/system/vector.hpp>

namespace hikanyan {

class Rigidbody2D : public Behaviour {
public:
    [[nodiscard]] const Vector2& velocity() const noexcept { return velocity_; }
    [[nodiscard]] const Vector2& acceleration() const noexcept { return acceleration_; }
    [[nodiscard]] float mass() const noexcept { return mass_; }

    void set_velocity(const Vector2& velocity) noexcept { velocity_ = velocity; }
    void set_acceleration(const Vector2& acceleration) noexcept { acceleration_ = acceleration; }
    void set_mass(float mass) noexcept { mass_ = mass <= 0.0f ? 1.0f : mass; }

    void add_force(const Vector2& force) noexcept { acceleration_ += force / mass_; }

    void fixed_update(float fixed_delta_time) override;

private:
    Vector2 velocity_{0.0f, 0.0f};
    Vector2 acceleration_{0.0f, 0.0f};
    float mass_{1.0f};
};

} // namespace hikanyan
