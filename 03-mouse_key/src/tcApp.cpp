#include "tcApp.h"

void tcApp::setup() {
}

void tcApp::update() {
}

void tcApp::draw() {
    clear(0.12f);

    // --- trail (draw all points) ---
    for (auto& p : trail) {
        setColor(p.color);
        drawCircle(p.pos.x, p.pos.y, p.size);
    }

    // --- cursor preview ---
    // mouse position follows cursor
    setColor(brushColor.r, brushColor.g, brushColor.b, 0.5f);
    drawCircle(mousePos.x, mousePos.y, brushSize);

    // --- color palette ---
    // 1-5 key to change color
    Color palette[] = {
        Color(1.0f, 0.5f, 0.2f), // 1: orange
        Color(0.2f, 0.7f, 1.0f), // 2: blue
        Color(0.3f, 0.9f, 0.4f), // 3: green
        Color(1.0f, 0.3f, 0.5f), // 4: pink
        Color(1.0f, 1.0f, 1.0f), // 5: white
    };

    for (int i = 0; i < 5; i++) {
        float x = 30 + i * 50;
        float y = 560;

        // highlight current
        if (brushColor.r == palette[i].r &&
            brushColor.g == palette[i].g &&
            brushColor.b == palette[i].b) {
            setColor(1.0f);
            noFill();
            drawCircle(x, y, 18);
            fill();
        }

        setColor(palette[i]);
        drawCircle(x, y, 14);
    }

    // --- brush size indicator ---
    setColor(0.5f);
    drawBitmapString("size: " + to_string((int)brushSize), 300, 555);
    drawBitmapString("[UP/DOWN] size  [1-5] color  [c] clear", 400, 555);
    drawBitmapString("drag to draw", 400, 575);
}

void tcApp::keyPressed(int key) {
    // --- color switch ---
    Color palette[] = {
        Color(1.0f, 0.5f, 0.2f),
        Color(0.2f, 0.7f, 1.0f),
        Color(0.3f, 0.9f, 0.4f),
        Color(1.0f, 0.3f, 0.5f),
        Color(1.0f, 1.0f, 1.0f),
    };
    if (key >= '1' && key <= '5') brushColor = palette[key - '1'];

    // --- brush size ---
    if (key == SAPP_KEYCODE_UP)   brushSize = min(brushSize + 2.0f, 50.0f);
    if (key == SAPP_KEYCODE_DOWN) brushSize = max(brushSize - 2.0f, 2.0f);

    // --- clear ---
    // TrussC에서는 대문자로 핸들링해
    if (key == 'C') trail.clear();
}
void tcApp::keyReleased(int key) {}

void tcApp::mousePressed(Vec2 pos, int button) {
    mouseDown = true;
    // add first point
    trail.push_back({pos, brushColor, brushSize});
}
void tcApp::mouseReleased(Vec2 pos, int button) {
    mouseDown = false;
}
void tcApp::mouseMoved(Vec2 pos) {
    mousePos = pos;
}
void tcApp::mouseDragged(Vec2 pos, int button) {
    mousePos = pos;
    // --- add points while dragging ---
    trail.push_back({pos, brushColor, brushSize});

    // =========================================================
    // 챌린지:
    //   드래그 궤적이 무지개색으로 변하게 만들어보자
    //   힌트:
    //   - setColorHSB(hue, sat, bri)로 색상을 지정할 수 있어
    //   - trail.size()를 사용하면 "몇 번째 점인지" 알 수 있어
    //   - hue = fmod(trail.size() * 0.01f, 1.0f) 같은 식으로
    //     그릴 때마다 색상이 조금씩 변해감
    //   - brushColor 대신 계산한 색을 Point에 넣으면 돼
    // =========================================================
}
void tcApp::mouseScrolled(Vec2 delta) {
    // scroll to change brush size
    brushSize = clamp(brushSize + delta.y * 2.0f, 2.0f, 50.0f);
}

void tcApp::windowResized(int width, int height) {}
void tcApp::filesDropped(const vector<string>& files) {}
void tcApp::exit() {}
