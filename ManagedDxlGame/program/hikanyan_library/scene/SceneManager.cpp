#include "SceneManager.h"

void SceneManager::create_scene(const std::string& name)
{
    std::lock_guard<std::mutex> lock(scene_mutex_);
    scenes_[name] = std::make_shared<SceneBase>();
}

void SceneManager::add_scene(const std::string& name, std::shared_ptr<SceneBase> scene)
{
    std::lock_guard<std::mutex> lock(scene_mutex_);
    scenes_[name] = std::move(scene);
}

std::shared_ptr<SceneBase> SceneManager::get_active_scene() const
{
    std::lock_guard<std::mutex> lock(scene_mutex_);
    return active_scene_;
}

void SceneManager::load_scene(const std::string& name)
{
    std::lock_guard<std::mutex> lock(scene_mutex_);
    if (const auto it = scenes_.find(name); it != scenes_.end())
    {
        active_scene_ = it->second;
        active_scene_->init(); // 初期化処理
    }
}

std::future<void> SceneManager::load_scene_async(const std::string& name)
{
    return std::async(std::launch::async, [this, name]
    {
        load_scene(name);
    });
}

bool SceneManager::set_active_scene(const std::string& name)
{
    std::lock_guard<std::mutex> lock(scene_mutex_);
    if (const auto it = scenes_.find(name); it != scenes_.end())
    {
        active_scene_ = it->second;
        return true;
    }
    return false;
}

std::future<void> SceneManager::unload_scene_async(const std::string& name)
{
    return std::async(std::launch::async, [this, name]
    {
        std::lock_guard<std::mutex> lock(scene_mutex_);
        scenes_.erase(name);
        if (active_scene_ && active_scene_->get_name() == name)
        {
            active_scene_ = nullptr;
        }
    });
}

void SceneManager::set_current_scene(std::shared_ptr<SceneBase> scene)
{
    un_load_scene();
    active_scene_ = std::move(scene);
}

std::shared_ptr<SceneBase> SceneManager::get_current_scene() const
{
    return active_scene_;
}

void SceneManager::un_load_scene() const
{
    if (active_scene_)
    {
        active_scene_->scene_destroy();
    }
}

void SceneManager::game_start()
{
    if (active_scene_)
    {
        active_scene_->awake();
        active_scene_->start();
    }
}

void SceneManager::game_main(float delta_time)
{
    static float accumulator = 0.0f;
    const float fixedDeltaTime = 0.02f; // 例えば、Unityの0.02秒（50回/秒）

    if (active_scene_)
    {
        // 通常の更新処理
        active_scene_->update(delta_time);

        // 固定更新処理用のアキュムレーターを更新
        accumulator += delta_time;
        while (accumulator >= fixedDeltaTime)
        {
            // 固定タイムステップで固定更新処理を実行
            active_scene_->fixed_update(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }
    }

    // 描画処理
    draw_screen();
}

void SceneManager::game_end()
{
    // ゲーム終了時の処理
}

void SceneManager::draw_screen() const
{
    if (active_scene_)
    {
        active_scene_->draw();
    }
}
