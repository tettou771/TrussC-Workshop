#include "tcApp.h"

void tcApp::setup() {

}

void tcApp::update() {

}

void tcApp::draw() {
    clear(0.12f);

    // --- drawLine vs drawStroke ---
    // drawLine は 1px 固定。strokeWeight は効かない
    setColor(0.5f, 0.5f, 0.5f);
    setStrokeWeight(20.0f);
    drawLine(60, 60, 300, 60);

    // drawStroke は strokeWeight が効く太い線
    setColor(1.0f, 0.7f, 0.2f);
    drawStroke(60, 120, 300, 120);

    // --- StrokeCap の違い ---
    // Butt: 端点でぴったり切れる
    setStrokeCap(StrokeCap::Butt);
    setColor(0.3f, 0.8f, 1.0f);
    drawStroke(60, 200, 250, 200);

    // Round: 端点に半円がつく
    setStrokeCap(StrokeCap::Round);
    drawStroke(60, 250, 250, 250);

    // Square: 半幅ぶん延長される
    setStrokeCap(StrokeCap::Square);
    drawStroke(60, 300, 250, 300);

    // --- beginStroke / endStroke で自由なパス ---
    setColor(0.9f, 0.3f, 0.5f);
    setStrokeWeight(10.0f);
    setStrokeCap(StrokeCap::Round);
    setStrokeJoin(StrokeJoin::Round);

    beginStroke();
    vertex(400, 80);
    vertex(500, 200);
    vertex(600, 80);
    vertex(700, 200);
    vertex(800, 80);
    endStroke();

    // close = true で閉じたパス
    setColor(0.4f, 0.9f, 0.6f);
    setStrokeWeight(10.0f);
    setStrokeJoin(StrokeJoin::Miter);

    beginStroke();
    vertex(450, 300);
    vertex(550, 250);
    vertex(650, 300);
    vertex(650, 400);
    vertex(450, 400);
    endStroke(true);

    // --- noFill の図形ストロークとの比較 ---
    // noFill + drawCircle は均一な輪郭線
    setColor(1.0f, 1.0f, 1.0f);
    noFill();
    drawCircle(150, 470, 60);

    // beginStroke + close で描く円は Cap/Join が効く
    // TAU = 2π = 一周分の角度（TrussCでは PI じゃなく TAU を使う）
    // TAU * 0.25 = 90°、TAU * 0.5 = 180°、TAU = 360° と覚えるとラク
    fill();
    setColor(1.0f, 1.0f, 1.0f);
    setStrokeWeight(2.0f);
    int n = 40;
    beginStroke();
    for (int i = 0; i < n; i++) {
        float angle = TAU * i / n; // 0 〜 TAU を n 分割
        vertex(400 + cos(angle) * 60, 470 + sin(angle) * 60);
    }
    endStroke(true);

    // =========================================================
    // チャレンジ:
    //   beginStroke を使って、手書き風の星（五芒星）を一筆書きで
    //   描いてみよう
    //   ヒント:
    //   - 5つの頂点を「1つ飛ばし」で結ぶと星になる
    //   - 円周上の点は cos/sin で出せる（上のサンプル参照）
    //   - TAU * i / 5 で五角形の頂点、ここで i を 0,2,4,1,3 の
    //     順に回すと一筆書きの星になる（つまり i*2 % 5）
    //   - endStroke(true) で閉じる
    //   - StrokeJoin::Round / Miter / Bevel で印象がかなり変わる
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
