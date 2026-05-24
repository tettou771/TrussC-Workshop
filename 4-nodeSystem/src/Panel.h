#pragma once

// =============================================================================
// Panel
//   タイトル + 角丸背景つきのコンテナ Node。
//   addChild() で UI 部品 (ClickBox など) をぶら下げる。
//   ClickBox と同じく RectNode 派生、 自分で draw() を持つ。
// =============================================================================

#include <TrussC.h>
#include <string>
using namespace tc;

class Panel : public RectNode {
public:
    std::string title;

    Panel(const std::string& title = "Panel");

    void draw() override;
};
