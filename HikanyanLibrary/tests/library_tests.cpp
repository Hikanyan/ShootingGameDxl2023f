#include <hikanyan/hikanyan.hpp>

#include <cassert>
#include <memory>
#include <stdexcept>

namespace {

class CounterComponent final : public hikanyan::MonoBehaviour {
public:
    int started{0};
    int updated{0};
    int drawn{0};

    void start() override { ++started; }
    void update(float /*delta_time*/) override { ++updated; }
    void draw() override { ++drawn; }
};

void game_object_owns_components() {
    hikanyan::GameObject object{"object"};

    assert(object.name() == "object");
    assert(object.get_component<hikanyan::Transform>() != nullptr);

    auto& counter = object.add_component<CounterComponent>();
    assert(object.get_component<CounterComponent>() == &counter);
    assert(counter.owner_ptr() == &object);

    bool duplicated = false;
    try {
        object.add_component<CounterComponent>();
    } catch (const std::logic_error&) {
        duplicated = true;
    }
    assert(duplicated);
}

void lifecycle_respects_enabled_state() {
    hikanyan::GameObject object;
    auto& counter = object.add_component<CounterComponent>();

    object.start();
    object.update(0.016f);
    object.draw();
    assert(counter.started == 1);
    assert(counter.updated == 1);
    assert(counter.drawn == 1);

    counter.set_enabled(false);
    object.update(0.016f);
    object.draw();
    assert(counter.updated == 1);
    assert(counter.drawn == 1);
}

void scene_updates_active_objects_only() {
    hikanyan::Scene scene{"test"};
    auto active = scene.create_game_object("active");
    auto inactive = scene.create_game_object("inactive");
    auto& active_counter = active->add_component<CounterComponent>();
    auto& inactive_counter = inactive->add_component<CounterComponent>();
    inactive->set_active(false);

    scene.start();
    scene.update(0.016f);

    assert(active_counter.started == 1);
    assert(active_counter.updated == 1);
    assert(inactive_counter.started == 0);
    assert(inactive_counter.updated == 0);
    assert(scene.find_game_object_by_name("active") == active);
}

void physics_and_colliders_are_pure_cpp() {
    hikanyan::GameObject first{"first"};
    hikanyan::GameObject second{"second"};

    first.transform().set_position({0.0f, 0.0f, 0.0f});
    second.transform().set_position({0.5f, 0.5f, 0.0f});

    auto& first_collider = first.add_component<hikanyan::BoxCollider2D>();
    auto& second_collider = second.add_component<hikanyan::BoxCollider2D>();
    first_collider.set_size({1.0f, 1.0f});
    second_collider.set_size({1.0f, 1.0f});
    assert(first_collider.intersects(second_collider));

    auto& body = first.add_component<hikanyan::Rigidbody2D>();
    body.set_velocity({10.0f, 0.0f});
    first.fixed_update(0.5f);
    assert(first.transform().position().x == 5.0f);
}

void scene_manager_controls_current_scene() {
    hikanyan::SceneManager manager;
    auto scene = std::make_shared<hikanyan::Scene>();
    auto object = scene->create_game_object("object");
    auto& counter = object->add_component<CounterComponent>();

    manager.add_scene("main", scene);
    assert(manager.scene_count() == 1);

    manager.load_scene("main");
    manager.start();
    manager.update(0.016f);

    assert(manager.current_scene() == scene);
    assert(counter.started == 1);
    assert(counter.updated == 1);
}

} // namespace

int main() {
    game_object_owns_components();
    lifecycle_respects_enabled_state();
    scene_updates_active_objects_only();
    physics_and_colliders_are_pure_cpp();
    scene_manager_controls_current_scene();
    return 0;
}
