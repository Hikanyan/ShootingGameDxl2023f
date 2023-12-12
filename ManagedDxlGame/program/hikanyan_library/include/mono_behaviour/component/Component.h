#pragma once
#include "../Object.h"
class GameObject; // GameObjectの前方宣言。

class Component : public Object
{
protected:
    GameObject* owner_; // このコンポーネントを所有するGameObjectへのポインタ。
public:
    Component() : owner_(nullptr)
    {
    }

    [[nodiscard]] virtual bool is_enabled() const { return true; }

    ~Component() override
    = default;

    // 初期化処理を行います。
    virtual void init()
    {
    }

    // シーン開始時に呼ばれます。
    virtual void awake()
    {
    }

    // シーン開始時に呼ばれます。
    virtual void start()
    {
    }

    // 描画処理を行います。
    virtual void draw()
    {
    }

    // 毎フレーム呼ばれます。
    virtual void update(float delta_time)
    {
    }

    // 一定秒数ごとに呼ばれます。
    virtual void fixed_update(float fixed_delta_time)
    {
    }

    // コンポーネントが有効になった時に呼ばれます。
    virtual void on_enable()
    {
    }

    // コンポーネントが無効になった時に呼ばれます。
    virtual void on_disable()
    {
    }

    //instance化とdestroyは使わないのでコメントアウト
    // // コンポーネントをインスタンス化した時に呼ばれます。
    // virtual void instantiate()
    // {
    // }
    //
    // // コンポーネントが破棄される直前に呼ばれます。
    // virtual void destroy()
    // {
    // }

    // このコンポーネントを所有するGameObjectへの参照を設定します。
    virtual void set_owner(GameObject* gameObject)
    {
        owner_ = gameObject;
    }

    // このコンポーネントを所有するGameObjectへの参照を取得します。
    [[nodiscard]] virtual GameObject* get_owner() const
    {
        return owner_;
    }
};
