#pragma once

#include <hikanyan/components/box_collider2d.hpp>
#include <hikanyan/components/transform.hpp>
#include <hikanyan/core/behaviour.hpp>
#include <hikanyan/core/object.hpp>

#include <memory>
#include <ranges>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace hikanyan {

class GameObject : public Object {
public:
    GameObject();
    explicit GameObject(std::string name);
    ~GameObject() override = default;

    [[nodiscard]] bool active() const noexcept { return active_; }
    void set_active(bool active) noexcept { active_ = active; }

    [[nodiscard]] const std::string& tag() const noexcept { return tag_; }
    void set_tag(std::string tag) { tag_ = std::move(tag); }

    template <typename T>
    [[nodiscard]] T* get_component() const {
        const auto it = components_.find(std::type_index(typeid(T)));
        if (it == components_.end()) {
            return nullptr;
        }
        return dynamic_cast<T*>(it->second.get());
    }

    template <typename T, typename... Args>
    T& add_component(Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

        const auto type = std::type_index(typeid(T));
        if (components_.contains(type)) {
            throw std::logic_error("Component already exists on this GameObject");
        }

        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        auto& reference = *component;
        component->set_owner(this);
        components_.emplace(type, std::move(component));
        return reference;
    }

    template <typename T>
    void remove_component() {
        components_.erase(std::type_index(typeid(T)));
    }

    [[nodiscard]] Transform& transform();
    [[nodiscard]] const Transform& transform() const;
    [[nodiscard]] BoxCollider2D& collider();
    [[nodiscard]] const BoxCollider2D& collider() const;

    void init();
    void awake();
    void start();
    void update(float delta_time);
    void fixed_update(float fixed_delta_time);
    void draw();
    void on_enable();
    void on_disable();

private:
    template <typename T>
    [[nodiscard]] T& require_component(const char* message) const {
        auto* component = get_component<T>();
        if (component == nullptr) {
            throw std::runtime_error(message);
        }
        return *component;
    }

    std::unordered_map<std::type_index, std::shared_ptr<Component>> components_;
    std::string tag_;
    bool active_{true};
};

} // namespace hikanyan
