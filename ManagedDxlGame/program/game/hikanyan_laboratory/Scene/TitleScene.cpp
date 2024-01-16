#include "TitleScene.h"
#include "../hikanyan_library/include/mono_behaviour/component/Text.h"
#include "../userInterface/InputManager.h"

void TitleScene::init()
{
    // 新しいGameObjectインスタンスを作成し、初期設定を行う
    title_text_ui_object = new_game_object("title_text_ui_object");
    title_text_ui_object->get_transform().set_position(
        tnl::Vector3(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT * 0.2, 0));
    title_text_ui_object->add_component<Text>();
    title_text_ui_object->get_component<Text>()->set_alignment(Text::TextAlignment::Center);
    title_text_ui_object->get_component<Text>()->set_text("タイトルシーンシーンシーンシーンシーンシーンシーンシーンシーンシーンシーンシーンシーンシーンシーンシーン");
    input_enter_object = new_game_object("input_enter_object");
    input_enter_object->add_component<InputManager>();
    

    SceneBase::init();
}

void TitleScene::awake()
{
    SceneBase::awake();
}

void TitleScene::start()
{
    SceneBase::start();
}

void TitleScene::update(float delta_time)
{
    
    
    SceneBase::update(delta_time);
}

void TitleScene::fixed_update(float delta_time)
{
    SceneBase::fixed_update(delta_time);
}

void TitleScene::draw()
{
    SceneBase::draw();
}

void TitleScene::on_enable()
{
    SceneBase::on_enable();
}

void TitleScene::on_disable()
{
    SceneBase::on_disable();
}
