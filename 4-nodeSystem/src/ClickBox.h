#pragma once

// =============================================================================
// ClickBox
//   クリックで on/off が切り替わる色付きボックス
//   RectNode を継承して、 自分の見た目 (draw) とマウス処理 (onMousePress) を持つ
// =============================================================================

#include <TrussC.h>
using namespace tc;

class ClickBox : public RectNode {
public:
    Color color;
    bool  active = false;   // クリックでトグル

    ClickBox(Color c = Color(0.3f, 0.3f, 0.4f));

    void draw() override;

protected:
    bool onMousePress(Vec2 local, int button) override;
};
