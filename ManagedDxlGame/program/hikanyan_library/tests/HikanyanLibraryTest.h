#pragma once
#include <memory>
#include "Test.h"
#include "../../hikanyan_library/include/mono_behaviour/MonoBehaviour.h"
#include "../../hikanyan_library/include/mono_behaviour/GameObject.h"
class BoxCollider2D;
class Transform;

//Sceneに配置するときに必要なコンポーネント
class HikanyanLibraryTest final : public MonoBehaviour
{
private:


public:
    HikanyanLibraryTest()
    {
        // コンストラクタでは何もしない（あるいは別の初期化コードを書く）
    };


    //Unityのinspectorで表示する変数
    void init() override
    {
        //unique_ptrとは、動的に確保したメモリを自動的に解放するためのクラス
        const auto obj = std::make_unique<GameObject>(); //動的にメモリを確保
        obj->set_name("obj"); //名前を設定
        obj->add_component<Transform>(); //transformコンポーネントを追加
        obj->get_transform().set_position(tnl::Vector3(0, 0, 0));
        obj->get_transform().set_rotation(tnl::Vector3(0, 0, 0));
        obj->get_transform().set_scale(tnl::Vector3(1, 1, 1));
        obj->add_component<BoxCollider2D>(); //box_collider_2dコンポーネントを追加

        Debug::log(std::format("objの名前は{}です", obj->get_name()));

        auto* my_object = new GameObject(); //動的にメモリを確保
        my_object->set_name("my_object"); //名前を設定
        my_object->add_component<Transform>(); // transformコンポーネントを追加
        my_object->get_transform().set_position(tnl::Vector3(0, 0, 0));
        my_object->get_transform().set_rotation(tnl::Vector3(0, 0, 0));
        my_object->get_transform().get_scale() = tnl::Vector3(1, 1, 1);

        auto* my_object2 = new GameObject(); //動的にメモリを確保
        my_object2->set_name("test"); //名前を設定
        my_object2->add_component<Transform>(); // transformコンポーネントを追加
        my_object2->add_component<Test>(); // testコンポーネントを追加
    };


    // 他のメソッド（Update, FixedUpdate等）もここに追加する
};
