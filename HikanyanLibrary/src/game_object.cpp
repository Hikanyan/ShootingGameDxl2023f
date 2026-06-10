#include <hikanyan/core/game_object.hpp>
#include <hikanyan/components/rigidbody2d.hpp>
#include <hikanyan/scene/scene.hpp>

#include <algorithm>
#include <atomic>

namespace hikanyan {

Object::Object() : id_(next_id()) {}

Object::Object(std::string name) : id_(next_id()), name_(std::move(name)) {}

Object::Id Object::next_id() {
    static std::atomic<Id> next{0};
    return ++next;
}

GameObject::GameObject() {
    add_component<Transform>();
}

GameObject::GameObject(std::string name) : Object(std::move(name)) {
    add_component<Transform>();
}

Transform& GameObject::transform() {
    return require_component<Transform>("Transform component not found");
}

const Transform& GameObject::transform() const {
    return require_component<Transform>("Transform component not found");
}

BoxCollider2D& GameObject::collider() {
    return require_component<BoxCollider2D>("BoxCollider2D component not found");
}

const BoxCollider2D& GameObject::collider() const {
    return require_component<BoxCollider2D>("BoxCollider2D component not found");
}

void GameObject::init() {
    for (const auto& component : components_ | std::views::values) {
        component->init();
    }
}

void GameObject::awake() {
    for (const auto& component : components_ | std::views::values) {
        component->awake();
    }
}

void GameObject::start() {
    for (const auto& component : components_ | std::views::values) {
        component->start();
    }
}

void GameObject::update(float delta_time) {
    for (const auto& component : components_ | std::views::values) {
        if (component->is_enabled()) {
            component->update(delta_time);
        }
    }
}

void GameObject::fixed_update(float fixed_delta_time) {
    for (const auto& component : components_ | std::views::values) {
        if (component->is_enabled()) {
            component->fixed_update(fixed_delta_time);
        }
    }
}

void GameObject::draw() {
    for (const auto& component : components_ | std::views::values) {
        if (component->is_enabled()) {
            component->draw();
        }
    }
}

void GameObject::on_enable() {
    for (const auto& component : components_ | std::views::values) {
        component->on_enable();
    }
}

void GameObject::on_disable() {
    for (const auto& component : components_ | std::views::values) {
        component->on_disable();
    }
}

void Rigidbody2D::fixed_update(float fixed_delta_time) {
    velocity_ += acceleration_ * fixed_delta_time;

    const auto movement = Vector3{velocity_.x * fixed_delta_time, velocity_.y * fixed_delta_time, 0.0f};
    owner().transform().translate(movement);
}

bool BoxCollider2D::intersects(const BoxCollider2D& other) const {
    const auto& my_position_3d = owner().transform().position();
    const auto& other_position_3d = other.owner().transform().position();
    return intersects_at(
        {my_position_3d.x, my_position_3d.y},
        other,
        {other_position_3d.x, other_position_3d.y}
    );
}

bool BoxCollider2D::intersects_at(const Vector2& position, const BoxCollider2D& other, const Vector2& other_position) const {
    const auto half_size = size_ / 2.0f;
    const auto other_half_size = other.size_ / 2.0f;
    const auto center = position + offset_;
    const auto other_center = other_position + other.offset_;

    if (center.x + half_size.x < other_center.x - other_half_size.x) {
        return false;
    }
    if (center.x - half_size.x > other_center.x + other_half_size.x) {
        return false;
    }
    if (center.y + half_size.y < other_center.y - other_half_size.y) {
        return false;
    }
    if (center.y - half_size.y > other_center.y + other_half_size.y) {
        return false;
    }

    return true;
}

Scene::Scene(std::string name) : name_(std::move(name)) {}

std::shared_ptr<GameObject> Scene::create_game_object(const std::string& name) {
    auto game_object = std::make_shared<GameObject>(name);
    add_game_object(game_object);
    return game_object;
}

void Scene::add_game_object(std::shared_ptr<GameObject> game_object) {
    game_objects_.push_back(std::move(game_object));
}

void Scene::remove_game_object(const std::shared_ptr<GameObject>& game_object) {
    game_objects_.remove(game_object);
}

void Scene::clear() {
    game_objects_.clear();
}

std::shared_ptr<GameObject> Scene::find_game_object_by_name(const std::string& name) const {
    const auto iterator = std::ranges::find_if(game_objects_, [&name](const auto& object) {
        return object && object->name() == name;
    });

    if (iterator == game_objects_.end()) {
        return nullptr;
    }

    return *iterator;
}

std::vector<std::shared_ptr<GameObject>> Scene::find_game_objects_by_condition(
    const std::function<bool(const std::shared_ptr<GameObject>&)>& condition) const {
    std::vector<std::shared_ptr<GameObject>> found_objects;

    for (const auto& game_object : game_objects_) {
        if (game_object && condition(game_object)) {
            found_objects.push_back(game_object);
        }
    }

    return found_objects;
}

void Scene::init() {
    for_each_active_game_object([](const auto& object) { object->init(); });
}

void Scene::awake() {
    for_each_active_game_object([](const auto& object) { object->awake(); });
}

void Scene::start() {
    for_each_active_game_object([](const auto& object) { object->start(); });
}

void Scene::update(float delta_time) {
    for_each_active_game_object([delta_time](const auto& object) { object->update(delta_time); });
}

void Scene::fixed_update(float fixed_delta_time) {
    for_each_active_game_object([fixed_delta_time](const auto& object) { object->fixed_update(fixed_delta_time); });
}

void Scene::draw() {
    for_each_active_game_object([](const auto& object) { object->draw(); });
}

void Scene::on_enable() {
    for_each_active_game_object([](const auto& object) { object->on_enable(); });
}

void Scene::on_disable() {
    for_each_active_game_object([](const auto& object) { object->on_disable(); });
}

void Scene::for_each_active_game_object(const std::function<void(const std::shared_ptr<GameObject>&)>& action) const {
    for (const auto& game_object : game_objects_) {
        if (game_object && game_object->active()) {
            action(game_object);
        }
    }
}

} // namespace hikanyan
