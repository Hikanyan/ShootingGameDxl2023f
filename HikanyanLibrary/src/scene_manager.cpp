#include <hikanyan/scene/scene_manager.hpp>

#include <utility>

namespace hikanyan {

void SceneManager::add_scene(const std::string& name, std::shared_ptr<Scene> scene) {
    std::lock_guard lock(mutex_);
    scene->set_name(name);
    scenes_[name] = std::move(scene);
}

bool SceneManager::set_active_scene(const std::string& name) {
    std::lock_guard lock(mutex_);
    const auto iterator = scenes_.find(name);
    if (iterator == scenes_.end()) {
        return false;
    }

    active_scene_ = iterator->second;
    return true;
}

void SceneManager::set_current_scene(std::shared_ptr<Scene> scene) {
    std::lock_guard lock(mutex_);
    active_scene_ = std::move(scene);
}

std::shared_ptr<Scene> SceneManager::current_scene() const {
    std::lock_guard lock(mutex_);
    return active_scene_;
}

std::size_t SceneManager::scene_count() const {
    std::lock_guard lock(mutex_);
    return scenes_.size();
}

void SceneManager::load_scene(const std::string& name) {
    std::shared_ptr<Scene> scene;
    {
        std::lock_guard lock(mutex_);
        const auto iterator = scenes_.find(name);
        if (iterator == scenes_.end()) {
            return;
        }
        active_scene_ = iterator->second;
        scene = active_scene_;
    }

    scene->init();
}

void SceneManager::unload_scene(const std::string& name) {
    std::lock_guard lock(mutex_);
    scenes_.erase(name);

    if (active_scene_ && active_scene_->name() == name) {
        active_scene_.reset();
    }
}

void SceneManager::clear_current_scene() {
    std::shared_ptr<Scene> scene;
    {
        std::lock_guard lock(mutex_);
        scene = active_scene_;
        active_scene_.reset();
    }

    if (scene) {
        scene->clear();
    }
}

void SceneManager::start() {
    const auto scene = current_scene();
    if (scene) {
        scene->awake();
        scene->start();
    }
}

void SceneManager::update(float delta_time) {
    const auto scene = current_scene();
    if (scene) {
        scene->update(delta_time);
    }
}

void SceneManager::fixed_update(float fixed_delta_time) {
    const auto scene = current_scene();
    if (scene) {
        scene->fixed_update(fixed_delta_time);
    }
}

void SceneManager::draw() {
    const auto scene = current_scene();
    if (scene) {
        scene->draw();
    }
}

} // namespace hikanyan
