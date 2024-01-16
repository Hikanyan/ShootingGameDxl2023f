#pragma once
#include "component.h"
#include "../GameObject.h"
#include <string>
#include "../dxlib_ext/dxlib_ext.h"

class Text : public Component
{
public:
    // テキストの揃え方
    enum class TextAlignment
    {
        Left,
        Center,
        Right
    };

private:
    std::string text_; // テキストの内容


    TextAlignment alignment_ = TextAlignment::Left; // デフォルトは左寄せ
public:
    Text() = default;
    ~Text() override = default;

    // テキストの内容を設定する
    void set_text(const std::string& text)
    {
        text_ = text;
    }

    // テキストの内容を取得する
    const std::string& get_text() const
    {
        return text_;
    }


    // テキストの配置を設定する
    void set_alignment(TextAlignment alignment)
    {
        alignment_ = alignment;
    }

    // 描画処理を行う
    void draw() override
    {
        int x = owner_->get_transform().get_position().x;
        int y = owner_->get_transform().get_position().y;

        switch (alignment_)
        {
        case TextAlignment::Center:
            x -= GetDrawStringWidth(text_.c_str(), text_.length()) / 2;
            break;
        case TextAlignment::Right:
            x -= GetDrawStringWidth(text_.c_str(), text_.length());
            break;
        case TextAlignment::Left:
        default:
            // 左寄せの場合は特に調整は不要
            break;
        }

        DrawString(x, y, text_.c_str(), GetColor(255, 255, 255));
    }
};
