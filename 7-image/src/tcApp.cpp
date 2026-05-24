#include "tcApp.h"

// TC_HOT_RELOAD をコメントアウトすると、 ホットリロードが無効化されます
TC_HOT_RELOAD(tcApp)

void tcApp::setup() {
    // --- Image: pixel-level access ---
    // allocate(w, h, channels)  create blank image
    // setColor(x, y, color)     write one pixel
    // getColor(x, y)            read one pixel
    // update()                  upload pixels to GPU
    // draw(x, y, w, h)          display on screen

    int size = 16;
    img.allocate(size, size, 4);
    img.setFilter(TextureFilter::Nearest); // sharp pixels, no blur
}

void tcApp::update() {
    time += getDeltaTime();

    // 毎フレーム setColor で書き換えて update() すれば動くテクスチャになる
    int size = 16;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            float hue = fmod((float)x / size + time * 0.1f, 1.0f);
            float bri = 1.0f - (float)y / size * 0.5f;
            img.setColor(x, y, Color::fromHSB(hue, 0.8f, bri));
        }
    }
    img.update();
}

void tcApp::draw() {
    clear(0.12f);

    // 中央に大きく表示 (拡大されてピクセルが見える)
    setColor(1.0f);
    img.draw(320, 60, 320, 320);

    // 実寸サイズも横に置いてみる (16x16 = 親指の爪くらい)
    img.draw(660, 60);

    setColor(0.5f);
    drawBitmapString("^ original size (16x16)", 660, 92);

    // --- getColor: ピクセル色を読む ---
    Color c = img.getColor(0, 0);  // 左上のピクセル色
    setColor(c);
    drawRect(320, 410, 60, 60);
    setColor(0.6f);
    drawBitmapString("getColor(0, 0)", 390, 445);

    // =========================================================
    // チャレンジ:
    //   update() のパターンを変えてみよう！
    //   今は横グラデーション (hue = x / size) を時間で流してる
    //
    //   アイデア:
    //   - チェッカー: (x + y) % 2 == 0 で白黒
    //   - 円: 中心からの距離で色を変える
    //     float d = sqrt((x-8)*(x-8) + (y-8)*(y-8));
    //   - ドット絵: 好きな座標に好きな色を置いてみよう
    //     img.setColor(3, 2, Color(1, 0, 0));
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
