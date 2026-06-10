#pragma once

#include <hikanyan/core/game_object.hpp>

#include <functional>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace hikanyan {

class Scene {
public:
    explicit Scene(std::string name = {});
    virtual ~Scene() = default;

    [[nodiscard]] const std::string& name() const noexcept { return name_; }
    void set_name(std::string name) { name_ = std::move(name); }

    virtual std::shared_ptr<GameObject> create_game_object(const std::string& name);
    virtual void add_game_object(std::shared_ptr<GameObject> game_object);
    virtual void remove_game_object(const std::shared_ptr<GameObject>& game_object);
    virtual void clear();

    [[nodiscard]] std::shared_ptr<GameObject> find_game_object_by_name(const std::string& name) const;
    [[nodiscard]] std::vector<std::shared_ptr<GameObject>> find_game_objects_by_condition(
        const std::function<bool(const std::shared_ptr<GameObject>&)>& condition) const;

    virtual void init();
    virtual void awake();
    virtual void start();
    virtual void update(float delta_time);
    virtual void fixed_update(float fixed_delta_time);
    virtual void draw();
    virtual void on_enable();
    virtual void on_disable();

protected:
    void for_each_active_game_object(const std::function<void(const std::shared_ptr<GameObject>&)>& action) const;

private:
    std::string name_;
    std::list<std::shared_ptr<GameObject>> game_objects_;
};

} // namespace hikanyan
