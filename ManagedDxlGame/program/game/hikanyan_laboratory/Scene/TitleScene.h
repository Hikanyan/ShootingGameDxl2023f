#pragma once
#include "../hikanyan_library/scene/SceneBase.h"

class TitleScene final : public SceneBase
{
public:
    TitleScene() = default;
    virtual ~TitleScene() override = default;
    
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
    std::shared_ptr<GameObject> title_text_ui_object = std::make_shared<GameObject>();
    std::shared_ptr<GameObject> input_enter_object = std::make_shared<GameObject>();
    
};
