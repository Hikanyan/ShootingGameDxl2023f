#pragma once

#include <hikanyan/scene/scene.hpp>

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace hikanyan {

class SceneManager {
public:
    void add_scene(const std::string& name, std::shared_ptr<Scene> scene);
    [[nodiscard]] bool set_active_scene(const std::string& name);
    void set_current_scene(std::shared_ptr<Scene> scene);
    [[nodiscard]] std::shared_ptr<Scene> current_scene() const;
    [[nodiscard]] std::size_t scene_count() const;

    void load_scene(const std::string& name);
    void unload_scene(const std::string& name);
    void clear_current_scene();

    void start();
    void update(float delta_time);
    void fixed_update(float fixed_delta_time);
    void draw();

private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_;
    std::shared_ptr<Scene> active_scene_;
};

} // namespace hikanyan
