#include "tcApp.h"

// TC_HOT_RELOAD をコメントアウトすると、ホットリロードが無効化されます
// 複雑なコードで問題が起きる時場合や、release buildする場合は無効化推奨です
TC_HOT_RELOAD(tcApp)

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
    if (key >= '1' && key <= '5') {
        brushColor = palette[key - '1'];

        // ちょっとした音を鳴らすメソッド
        beep(Beep::click);

        // おまけ: 他の音の鳴らし方
        // beep(Beep::error);
        // beep(Beep::info);
        // beep(Beep::warning);
        // beep(Beep::error);
        // beep(Beep::success);
        // beep(Beep::click);
        // beep(Beep::coin);
    }
    
    // --- brush size ---
    if (key == SAPP_KEYCODE_UP)   brushSize = min(brushSize + 2.0f, 50.0f);
    if (key == SAPP_KEYCODE_DOWN) brushSize = max(brushSize - 2.0f, 2.0f);

    // --- clear ---
    // TrussC では大文字でハンドリングします
    if (key == 'C') {
        trail.clear();
        beep(Beep::warning);
    }
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
    // チャレンジ:
    //   ★ 右クリックドラッグで「対称描画」モードにしてみよう
    //   - mouseDragged の第2引数 button は 0=左 / 1=右
    //   - 右クリック時は、 マウス位置の点を1つ追加するだけじゃなく、
    //     画面の反対側にも点を追加する
    //
    //   ヒント:
    //   - 画面の幅: getWidth()、 高さ: getHeight()
    //   - 横対称なら、 x を「画面の幅から引いた値」にすると反対側
    //
    //   発展:
    //   - 縦対称も足すと十字対称
    //   - さらに足すと 4分割の万華鏡
    //   - cos / sin で回転すれば 6方向 / 8方向 の対称にもできる
    //     (0-graphics の (4) 多角形を思い出して)
    // =========================================================
}
void tcApp::mouseScrolled(Vec2 delta) {
    // scroll to change brush size
    brushSize = clamp(brushSize + delta.y * 2.0f, 2.0f, 50.0f);
}

void tcApp::windowResized(int width, int height) {}
void tcApp::filesDropped(const vector<string>& files) {}
void tcApp::exit() {}
