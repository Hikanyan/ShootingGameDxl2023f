#include "InputManager.h"

InputManager::InputManager() {
    // コンストラクタでの初期化
}

InputManager::~InputManager() {
    // リソースの解放
}

void InputManager::initialize() {
    // 入力デバイスの初期化
}

void InputManager::update() {
    // 入力の状態を更新
}

bool InputManager::is_key_down(tnl::Input::eKeys key) {
    // キーボードの特定のキーが押されているかをチェック
    return tnl::Input::IsKeyDown(key);
}

bool InputManager::is_key_up(int key)
{
    return false;
}

bool InputManager::is_key_pressed(int key)
{
    return false;
}

bool InputManager::is_mouse_down(int button)
{
    return false;
}

bool InputManager::is_mouse_up(int button)
{
    return false;
}

bool InputManager::is_mouse_pressed(int button)
{
    return false;
}

tnl::Vector3 InputManager::get_mouse_position()
{
    return {};
}

bool InputManager::is_pad_button_down(int button)
{
    return false;
}

bool InputManager::is_pad_button_up(int button)
{
    return false;
}

bool InputManager::is_pad_button_pressed(int button)
{
    return false;
}

tnl::Vector3 InputManager::get_pad_stick_position(int stick)
{
    return {};
}

