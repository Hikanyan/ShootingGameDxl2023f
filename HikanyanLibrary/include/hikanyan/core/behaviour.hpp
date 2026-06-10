#pragma once

#include <hikanyan/core/component.hpp>

namespace hikanyan {

class Behaviour : public Component {
public:
    ~Behaviour() override = default;

    [[nodiscard]] bool is_enabled() const override { return enabled_; }

    void set_enabled(bool enabled) {
        if (enabled_ == enabled) {
            return;
        }

        enabled_ = enabled;
        if (enabled_) {
            on_enable();
        } else {
            on_disable();
        }
    }

private:
    bool enabled_{true};
};

class MonoBehaviour : public Behaviour {
public:
    ~MonoBehaviour() override = default;
};

} // namespace hikanyan
