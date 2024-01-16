#pragma once
#include "../hikanyan_library/include/mono_behaviour/MonoBehaviour.h"

class InputManager : public MonoBehaviour {
public:
    // コンストラクタとデストラクタ
    InputManager();
    ~InputManager();

    // 入力の初期化と更新メソッド
    void initialize();
    void update();

    // キーボード入力の処理メソッド
    bool is_key_down(tnl::Input::eKeys key);
    bool is_key_up(int key);
    bool is_key_pressed(int key);

    // マウス入力の処理メソッド
    bool is_mouse_down(int button);
    bool is_mouse_up(int button);
    bool is_mouse_pressed(int button);
    tnl::Vector3 get_mouse_position();

    // ゲームパッド入力の処理メソッド
    bool is_pad_button_down(int button);
    bool is_pad_button_up(int button);
    bool is_pad_button_pressed(int button);
    tnl::Vector3 get_pad_stick_position(int stick);

private:
    // 入力状態を保持するためのプライベートメンバ変数
    // 例: キーボード状態、マウス状態、ゲームパッド状態など
};
