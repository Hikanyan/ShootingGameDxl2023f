#pragma once
#include "SceneBase.h"

class SampleScene final : public SceneBase
{
public:
    SampleScene() = default;
    virtual ~SampleScene() override = default;

    // シーン固有の初期化
    void init() override;
    void awake() override;
    void start() override;
    void update(float delta_time) override;
    void fixed_update(float delta_time) override;
    void draw() override;
    void on_enable() override;
    void on_disable() override;

private:
    //オブジェクトをコンストラクタで生成する

    //落ちることがあるので、スマートポインタを使う
    std::shared_ptr<GameObject> obj_ = std::make_shared<GameObject>(); //動的にメモリを確保
};
