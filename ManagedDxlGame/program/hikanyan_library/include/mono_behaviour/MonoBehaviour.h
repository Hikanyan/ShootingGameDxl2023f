#pragma once
#include "Behaviour.h"
#include "Debug.h"
#include "GameObject.h"
#include "..\..\scene\SceneManager.h"

class MonoBehaviour : public Behaviour
{
protected:
    MonoBehaviour() = default;

public:
    ~MonoBehaviour() override = default;

    // イベントメソッド
    void init() override
    {
    }

    void awake() override
    {
    }

    void start() override
    {
    }

    void draw() override
    {
    }

    void update(float delta_time) override
    {
    }

    void fixed_update(float fixed_delta_time) override
    {
    }

    void on_enable() override
    {
    }

    void on_disable() override
    {
    }


    // ログメソッド（必要に応じて修正または削除）
    static void log(const std::string& message)
    {
        Debug::log(message);
    }

    static void log_warning(const std::string& message)
    {
        Debug::log_warning(message);
    }

    static void log_error(const std::string& message)
    {
        Debug::log_error(message);
    }
};
