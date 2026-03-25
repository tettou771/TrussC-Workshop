#include "tcApp.h"

void tcApp::setup() {
    // --- Image: pixel-level access ---
    // allocate(w, h, channels)  create blank image
    // setColor(x, y, color)     write one pixel
    // update()                  upload pixels to GPU
    // draw(x, y, w, h)         display on screen

    int size = 16;

    // --- static pattern ---
    patternImg.allocate(size, size, 4);
    patternImg.setFilter(TextureFilter::Nearest); // sharp pixels, no blur

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            // horizontal gradient: hue changes with x
            float hue = (float)x / size;
            float bri = 1.0f - (float)y / size * 0.5f;
            patternImg.setColor(x, y, Color::fromHSB(hue, 0.8f, bri));
        }
    }
    patternImg.update();

    // --- live image (same size, animated later) ---
    liveImg.allocate(size, size, 4);
    liveImg.setFilter(TextureFilter::Nearest);
}

void tcApp::update() {
    time += getDeltaTime();

    // --- live pixel update ---
    // setColor + update every frame = animation
    int size = 16;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            // same gradient, but hue shifts over time
            float hue = fmod((float)x / size + time * 0.1f, 1.0f);
            float bri = 1.0f - (float)y / size * 0.5f;
            liveImg.setColor(x, y, Color::fromHSB(hue, 0.8f, bri));
        }
    }
    liveImg.update();
}

void tcApp::draw() {
    clear(0.12f);

    // --- static pattern (set once in setup) ---
    setColor(1.0f);
    patternImg.draw(60, 60, 320, 320);

    // original size for comparison (tiny!)
    patternImg.draw(60, 400);

    setColor(0.6f);
    drawBitmapString("static (16x16, Nearest filter)", 60, 45);
    drawBitmapString("^ original size", 85, 420);

    // --- live pattern (updated every frame) ---
    setColor(1.0f);
    liveImg.draw(500, 60, 320, 320);

    setColor(0.6f);
    drawBitmapString("live update (hue shifts with time)", 500, 45);

    // --- getColor: read a pixel ---
    Color c = patternImg.getColor(0, 0);
    setColor(c);
    drawRect(60, 460, 50, 50);
    setColor(0.6f);
    drawBitmapString("getColor(0,0)", 120, 488);

    // =========================================================
    // チャレンジ:
    //   setup() のパターンを変えてみよう！
    //   今は横グラデーションになっている（hue = x / size）
    //
    //   アイデア:
    //   - チェッカー: (x + y) % 2 == 0 で白黒
    //   - 円: 中心からの距離で色を変える
    //     float d = sqrt((x-8)*(x-8) + (y-8)*(y-8));
    //   - ドット絵: 好きな座標に好きな色を置いてみよう
    //     patternImg.setColor(3, 2, Color(1, 0, 0));
    // =========================================================

    setColor(0.4f);
    drawBitmapString("Image: allocate / setColor / getColor / update / draw", 20, 580);
}

void tcApp::keyPressed(int key) {}
void tcApp::keyReleased(int key) {}

void tcApp::mousePressed(Vec2 pos, int button) {}
void tcApp::mouseReleased(Vec2 pos, int button) {}
void tcApp::mouseMoved(Vec2 pos) {}
void tcApp::mouseDragged(Vec2 pos, int button) {}
void tcApp::mouseScrolled(Vec2 delta) {}

void tcApp::windowResized(int width, int height) {}
void tcApp::filesDropped(const vector<string>& files) {}
void tcApp::exit() {}
