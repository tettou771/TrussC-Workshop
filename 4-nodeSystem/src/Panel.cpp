#include "Panel.h"

Panel::Panel(const std::string& t) : title(t) {
    setSize(600, 350);
}

void Panel::draw() {
    // 背景
    setColor(0.18f);
    drawRectRounded(0, 0, getWidth(), getHeight(), 12);

    // 枠線
    noFill();
    setColor(0.3f);
    drawRectRounded(0, 0, getWidth(), getHeight(), 12);
    fill();

    // タイトル
    setColor(0.7f);
    drawBitmapString(title, 20, 25);
}
