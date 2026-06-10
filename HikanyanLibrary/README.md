# HikanyanLibrary

`HikanyanLibrary` は、既存プロジェクト内の `hikanyan_library` からコンポーネントパターンの核だけを切り出した、Dxライブラリ非依存のピュア C++ ライブラリです。

## 目的

- `GameObject` に `Component` を追加して振る舞いを組み立てる Unity 風の設計を提供します。
- Dxライブラリやゲームエンジン固有 API に依存しません。
- 描画や入力はアプリケーション側で実装し、ライブラリはオブジェクト管理・ライフサイクル・基本コンポーネントに集中します。

## 必要環境

- C++20 対応コンパイラ
- CMake 3.20 以上

## ビルド

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 基本的な使い方

```cpp
#include <hikanyan/hikanyan.hpp>

class PlayerController final : public hikanyan::MonoBehaviour {
public:
    void update(float delta_time) override {
        auto& transform = owner().transform();
        auto position = transform.position();
        position.x += 100.0f * delta_time;
        transform.set_position(position);
    }
};

int main() {
    hikanyan::SceneManager scenes;
    auto scene = std::make_shared<hikanyan::Scene>();

    auto player = scene->create_game_object("player");
    player->add_component<PlayerController>();

    scenes.set_current_scene(scene);
    scenes.start();
    scenes.update(1.0f / 60.0f);
}
```

## 提供する主な型

- `hikanyan::Object`: ID と名前を持つ基底オブジェクト
- `hikanyan::GameObject`: コンポーネントの所有者
- `hikanyan::Component`: 全コンポーネントの基底クラス
- `hikanyan::Behaviour`: 有効/無効を切り替えられるコンポーネント
- `hikanyan::MonoBehaviour`: ゲームロジック用の基底クラス
- `hikanyan::Transform`: 位置・回転・スケール
- `hikanyan::Rigidbody2D`: 速度・加速度を持つ簡易 2D 物理コンポーネント
- `hikanyan::BoxCollider2D`: AABB の当たり判定コンポーネント
- `hikanyan::Scene`: `GameObject` の集合とライフサイクル管理
- `hikanyan::SceneManager`: 現在のシーンの切り替え・更新

## Dxライブラリから切り離した点

- `DrawString` や `DrawBoxEx` のような描画 API は含めていません。
- `tnl::Vector3` の代わりに、ライブラリ内で `Vector2` / `Vector3` を定義しています。
- 入力や画像、音声などのプラットフォーム依存処理は利用側に委ねます。
