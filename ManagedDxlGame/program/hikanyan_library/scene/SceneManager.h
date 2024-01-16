#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "SceneBase.h"
#include <future>  // 非同期処理に必要
#include <mutex>   // スレッドセーフな操作に必要
#include "../include/system/Singleton.h"
class SceneManager: public Singleton<SceneManager>
{
private:
    // シーンの名前とシーンのポインタを格納
    std::unordered_map<std::string, std::shared_ptr<SceneBase>> scenes_;
    // アクティブなシーン
    std::shared_ptr<SceneBase> active_scene_;
    // スレッドセーフな操作用のミューテックス
    mutable std::mutex scene_mutex_;


public:
    SceneManager() = default;

    // シーンの数を取得
    size_t get_scene_count() const
    {
        std::lock_guard lock(scene_mutex_);
        return scenes_.size();
    }

    // 新しいシーンを作成して追加
    void create_scene(const std::string& name);
    // 新しいシーンを追加
    void add_scene(const std::string& name, std::shared_ptr<SceneBase> scene);

    // アクティブなシーンを取得
    std::shared_ptr<SceneBase> get_active_scene() const;

    // シーンをロード（同期）
    void load_scene(const std::string& name);

    // シーンを非同期でロード
    std::future<void> load_scene_async(const std::string& name);

    // アクティブなシーンを設定
    bool set_active_scene(const std::string& name);

    // シーンを非同期でアンロード
    std::future<void> unload_scene_async(const std::string& name);
    // シーンを設定
    void set_current_scene(std::shared_ptr<SceneBase> scene);
    std::shared_ptr<SceneBase> get_current_scene() const;
    // シーンをアンロード
    void un_load_scene() const;

    
    void game_start();
    void game_main(float delta_time);
    void game_end();
    void draw_screen() const;
};
