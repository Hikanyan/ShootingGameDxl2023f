#pragma once

#include <hikanyan/core/object.hpp>
#include <stdexcept>

namespace hikanyan {

class GameObject;

class Component : public Object {
public:
    Component() = default;
    ~Component() override = default;

    [[nodiscard]] virtual bool is_enabled() const { return true; }

    virtual void init() {}
    virtual void awake() {}
    virtual void start() {}
    virtual void update(float /*delta_time*/) {}
    virtual void fixed_update(float /*fixed_delta_time*/) {}
    virtual void draw() {}
    virtual void on_enable() {}
    virtual void on_disable() {}

    void set_owner(GameObject* owner) noexcept { owner_ = owner; }
    [[nodiscard]] GameObject* owner_ptr() noexcept { return owner_; }
    [[nodiscard]] const GameObject* owner_ptr() const noexcept { return owner_; }

    [[nodiscard]] GameObject& owner() {
        if (owner_ == nullptr) {
            throw std::runtime_error("Component has no owner GameObject");
        }
        return *owner_;
    }

    [[nodiscard]] const GameObject& owner() const {
        if (owner_ == nullptr) {
            throw std::runtime_error("Component has no owner GameObject");
        }
        return *owner_;
    }

private:
    GameObject* owner_{nullptr};
};

} // namespace hikanyan
