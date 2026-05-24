#include "ClickBox.h"

ClickBox::ClickBox(Color c) : color(c) {
    enableEvents();             // これで hover / click が拾える
    setSize(140, 70);
}

void ClickBox::draw() {
    // active なら少し明るく
    Color c = active
        ? Color(color.r + 0.3f, color.g + 0.3f, color.b + 0.3f)
        : color;
    setColor(c);
    drawRectRounded(0, 0, getWidth(), getHeight(), 8);

    // hover 中はうっすら白でハイライト
    if (isMouseOver()) {
        setColor(1.0f, 1.0f, 1.0f, 0.15f);
        drawRectRounded(0, 0, getWidth(), getHeight(), 8);
    }

    // active の印 (右上の白い丸)
    if (active) {
        setColor(1.0f);
        drawCircle(getWidth() - 15, 15, 5);
    }
}

bool ClickBox::onMousePress(Vec2 local, int button) {
    (void)local;
    (void)button;
    active = !active;
    return true;       // true = このイベントは自分が消費した
}
