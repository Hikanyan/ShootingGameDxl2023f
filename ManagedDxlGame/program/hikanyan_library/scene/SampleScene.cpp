#include "SampleScene.h"

#include "../tests/Test.h"


void SampleScene::init()
{
	add_game_object(obj_); //オブジェクトを追加
	obj_->set_name("obj"); //名前を設定
	obj_->add_component<Transform>(); //コンポーネントを追加
	obj_->get_transform().set_position(tnl::Vector3(100, 100, 0));
	obj_->get_transform().set_scale(tnl::Vector3(100, 100, 0));
	obj_->add_component<Test>();
	Debug::log("init{}", obj_->get_name());
}

void SampleScene::awake()
{
	obj_->awake();
}

void SampleScene::start()
{
	obj_->start();
}

void SampleScene::update(float delta_time)
{
	obj_->update(delta_time);
}

void SampleScene::fixed_update(float delta_time)
{
	obj_->fixed_update(delta_time);
}

void SampleScene::draw()
{
	obj_->draw();
}

void SampleScene::on_enable()
{
	obj_->on_enable();
	Debug::log("update{}", obj_->get_name());
}

void SampleScene::on_disable()
{
	obj_->on_disable();
	Debug::log("update{}", obj_->get_name());
}
