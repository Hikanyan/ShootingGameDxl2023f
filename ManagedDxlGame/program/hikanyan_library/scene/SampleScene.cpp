#include "SampleScene.h"

#include "../tests/Test.h"


void SampleScene::init()
{
	// 新しいGameObjectインスタンスを作成し、初期設定を行う
	obj_ = new_game_object("obj");
	// その他のオブジェクト固有の設定
	obj_->get_transform().set_position(tnl::Vector3(100, 100, 0));
	obj_->get_transform().set_scale(tnl::Vector3(100, 100, 0));
	obj_->add_component<Test>(); // 追加のコンポーネント設定

	obj_1 = new_game_object("obj_1");
	obj_1->get_transform().set_position(tnl::Vector3(200, 200, 0));
	obj_1->get_transform().set_scale(tnl::Vector3(100, 100, 0));
	obj_1->add_component<Test>();

	SceneBase::init();
	// 初期化ログを出力
	Debug::log("init{}", obj_->get_name());
}

void SampleScene::awake()
{
	SceneBase::awake();
}

void SampleScene::start()
{
	SceneBase::start();
}

void SampleScene::update(float delta_time)
{
	SceneBase::update(delta_time);
}

void SampleScene::fixed_update(float delta_time)
{
	SceneBase::fixed_update(delta_time);
}

void SampleScene::draw()
{
	SceneBase::draw();
}

void SampleScene::on_enable()
{
	SceneBase::on_enable();
}

void SampleScene::on_disable()
{
	SceneBase::on_disable();
}
