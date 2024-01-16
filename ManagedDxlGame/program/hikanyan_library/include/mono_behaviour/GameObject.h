#pragma once
#include "Object.h"
#include "../dxlib_ext/dxlib_ext.h"
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <ranges>
#include <stdexcept>

#include "Behaviour.h"
#include "component/Transform.h"
#include "component/BoxCollider2D.h"


class GameObject : public Object
{
public:
    GameObject() = default;
    ~GameObject() override = default;

    // object* を受け取るコンストラクタ
    explicit GameObject(Object* obj)
    {
        if (const auto* casted_obj = dynamic_cast<GameObject*>(obj))
        {
            // object の各プロパティを個別にコピー
            this->set_id(casted_obj->get_id());
            this->set_name(casted_obj->get_name());
            this->tag_value_ = casted_obj->tag_value_;
            this->components_ = casted_obj->components_;
            // その他必要なプロパティがあればここに追加
        }
        else
        {
            // 適切なエラー処理
            throw std::invalid_argument("Invalid object type for game_object constructor");
        }
    }

    // タグのgetter/setter
    std::string get_tag() const
    {
        return tag_value_;
    }

    void set_tag(const std::string& value)
    {
        tag_value_ = value;
    }

    void set_active(const bool value)
    {
        is_active_ = value;
    }

    bool get_active() const
    {
        return is_active_;
    }

    // コンポーネントを取得する
    template <typename T>
    T* get_component() const
    {
        if (const auto it = components_.find(std::type_index(typeid(T))); it != components_.end())
        {
            return dynamic_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    // コンポーネントを追加する
    template <typename T, typename... Args>
    T* add_component(Args&&... args)
    {
        const auto type_index = std::type_index(typeid(T));
        if (components_.contains(type_index))
        {
            throw std::logic_error("Component already exists");
        }
        auto newComponent = std::make_shared<T>(std::forward<Args>(args)...);
        T* component_ptr = newComponent.get();
        components_[type_index] = std::move(newComponent);
        //set_ownerをする
        component_ptr->set_owner(this);
        return component_ptr;
    }

    // コンポーネントを削除する
    template <typename T>
    void remove_component()
    {
        if (const auto it = components_.find(std::type_index(typeid(T))); it != components_.end())
        {
            components_.erase(it);
        }
    }

    // 特定のコンポーネントへのアクセスメソッド
    Transform& get_transform() const
    {
        return *get_component_required<Transform>("Transform component not found");
    }

    // 特定のコンポーネントへのアクセスメソッド
    BoxCollider2D& get_collider() const
    {
        return *get_component_required<BoxCollider2D>("BoxCollider2D component not found");
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components_; // コンポーネントの辞書
    std::string tag_value_;
    bool is_active_ = true;

    // 必須コンポーネントを取得するヘルパーメソッド
    template <typename T>
    T* get_component_required(const char* error_message) const
    {
        auto* comp = get_component<T>();
        if (!comp)
        {
            const std::string full_error = std::string(error_message) + " for type: " + typeid(T).name();
            throw std::runtime_error(full_error);
        }
        return comp;
    }

public:
    // コンポーネントの初期化
    void init()
    {
        for (const auto& comp : components_ | std::views::values)
        {
            comp->init();
        }
    }

    // シーン開始時に一度だけ呼ばれる
    void awake()
    {
        for (const auto& comp : components_ | std::views::values)
        {
            comp->awake();
        }
    }

    // 最初のフレームの更新前に一度だけ呼ばれる
    void start()
    {
        for (const auto& comp : components_ | std::views::values)
        {
            comp->start();
        }
    }

    // 描画処理
    void draw()
    {
        for (const auto& comp : components_ | std::views::values)
        {
            comp->draw();
        }
    }

    // 毎フレーム呼ばれる更新処理
    void update(float delta_time)
    {
        for (const auto& comp : components_ | std::views::values)
        {
            if (comp->is_enabled())
            {
                comp->update(delta_time);
            }
        }
    }

    // 定期的な時間間隔で呼ばれる更新処理
    void fixed_update(float fixed_delta_time)
    {
        for (const auto& comp : components_ | std::views::values)
        {
            if (comp->is_enabled())
            {
                comp->fixed_update(fixed_delta_time);
            }
        }
    }


    // コンポーネントが有効になった時に呼ばれる
    void on_enable()
    {
        for (const auto& comp : components_ | std::views::values)
        {
            comp->on_enable();
        }
    }

    // コンポーネントが無効になった時に呼ばれる
    void on_disable()
    {
        for (const auto& comp : components_ | std::views::values)
        {
            comp->on_disable();
        }
    }
};
