#include "tcApp.h"

void tcApp::setup() {

}

void tcApp::update() {

}

void tcApp::draw() {
    clear(0.12f);

    // --- 基本図形 ---

    setColor(0.1f, 0.4f, 0.9f);
    drawCircle(120, 150, 60); // 円 (x, y, r)
    drawRect(250, 90, 120, 120); // 四角形 (x, y, w, h)
    drawLine(450, 90, 570, 210); // 線 (x1, y1, x2, y2)

    // 三角形 (x1, y1, x2, y2, x3, y3)
    drawTriangle(650, 90, 580, 210, 720, 210);

    // 楕円 (x, y, w, h)
    drawEllipse(840, 150, 50, 80);

    // --- 塗り / 線だけ ---

    // 塗りつぶし（デフォルト）
    fill();
    setColor(1.0f, 1.0f, 1.0f);
    drawCircle(120, 370, 50);

    // 輪郭だけ
    noFill();
    drawCircle(260, 370, 50);

    // 滑らかに描画
    setCircleResolution(100);
    drawCircle(400, 370, 50);
    setCircleResolution(20); // default is 20

    // push/pop style
    pushStyle();
    fill();
    setColor(.0f, 1.0f, 1.0f);
    setStrokeWeight(1.0f);
    popStyle();

    // --- 色の透明度 (alpha) ---
    fill();
    setColor(1.0f, 0.3f, 0.3f, 0.7f);
    drawCircle(550, 370, 60);
    setColor(0.3f, 0.3f, 1.0f, 0.7f);
    drawCircle(590, 370, 60);

    // --- 角丸四角形 ---
    setColor(0.6f, 0.9f, 0.7f);
    drawRectRounded(720, 320, 140, 100, 20);

    // =========================================================
    // チャレンジ:
    //   上のサンプルを参考に、画面の下半分（y=450あたり）に
    //   信号機を描いてみよう
    //   - 横長の角丸四角形をベースに
    //   - 赤・黄・緑の円を並べる
    //   - 「青信号」だけ光ってる感じにしてみよう
    //     (他の2つは暗め、緑だけ明るく＋alphaで光彩を足すとか)
    // =========================================================
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
