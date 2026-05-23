#include "tcApp.h"

void tcApp::setup() {

}

void tcApp::update() {

}

void tcApp::draw() {
    clear(0.12f);

    // =========================================================
    // (1) 基本図形 — 引数の並び順をひとつずつ確認
    // =========================================================
    fill();

    setColor(0.3f, 0.7f, 1.0f);
    drawCircle(80, 110, 45);                    // (x, y, r)

    setColor(0.95f, 0.55f, 0.3f);
    drawRect(160, 65, 90, 90);                  // (x, y, w, h)

    setColor(0.7f, 0.9f, 0.4f);
    setStrokeWeight(3.0f);
    drawLine(280, 70, 380, 150);                // (x1, y1, x2, y2)

    setColor(0.95f, 0.4f, 0.65f);
    drawTriangle(440, 65, 400, 155, 480, 155);  // (x1,y1, x2,y2, x3,y3)

    setColor(0.55f, 0.7f, 0.95f);
    drawEllipse(550, 110, 50, 80);              // (x, y, w, h)

    setColor(1.0f, 0.9f, 0.4f);
    drawArc(650, 110, 45, 0.5f, TAU - 0.5f);    // 弧 → fill すると扇形 (パックマン)

    setColor(0.65f, 0.9f, 0.7f);
    drawRectRounded(720, 65, 90, 90, 16);       // 角丸: 半径を 5 つ目の引数で

    setColor(0.45f);
    drawBitmapString("(1) basic shapes  — fill is the default", 30, 45);

    // =========================================================
    // (2) fill / noFill / alpha — 同じ図形を別の見た目で
    // =========================================================
    setColor(0.45f);
    drawBitmapString("(2) fill / noFill / alpha", 30, 200);

    fill();
    setColor(1.0f, 0.7f, 0.6f);
    drawCircle(80, 270, 40);

    noFill();                                    // ここから先は輪郭だけ
    setStrokeWeight(2.0f);
    setColor(1.0f);
    drawCircle(180, 270, 40);

    fill();                                      // fill に戻す
    setColor(1.0f, 0.3f, 0.3f, 0.55f);          // 4 つめが alpha
    drawCircle(310, 270, 45);
    setColor(0.3f, 0.6f, 1.0f, 0.55f);
    drawCircle(360, 270, 45);
    setColor(0.4f, 1.0f, 0.4f, 0.55f);
    drawCircle(335, 305, 45);

    // pushStyle で「いま設定」を一時保存
    pushStyle();
    noFill();
    setStrokeWeight(4.0f);
    setColor(1.0f, 0.9f, 0.4f);
    drawRectRounded(460, 235, 90, 75, 14);
    popStyle();                                  // 復元 (この後は fill のまま)

    // =========================================================
    // (3) drawStroke — 太い線。端の形 (Cap) が選べる
    // =========================================================
    setColor(0.45f);
    drawBitmapString("(3) drawStroke  +  StrokeCap (Butt / Round / Square)", 30, 360);

    pushStyle();
    setStrokeWeight(18.0f);

    setStrokeCap(StrokeCap::Butt);
    setColor(0.5f, 0.7f, 0.95f);
    drawStroke(30, 405, 220, 405);
    setColor(0.5f);
    drawBitmapString("Butt", 230, 410);

    setStrokeCap(StrokeCap::Round);
    setColor(1.0f, 0.8f, 0.4f);
    drawStroke(310, 405, 500, 405);
    setColor(0.5f);
    drawBitmapString("Round", 510, 410);

    setStrokeCap(StrokeCap::Square);
    setColor(0.95f, 0.45f, 0.7f);
    drawStroke(580, 405, 770, 405);
    setColor(0.5f);
    drawBitmapString("Square", 780, 410);
    popStyle();

    // =========================================================
    // (4) beginStroke — 連続した頂点で自由なパス
    // =========================================================
    setColor(0.45f);
    drawBitmapString("(4) beginStroke / vertex / endStroke  — ★ try changing values below", 30, 470);

    // ジグザグ (角の形 = StrokeJoin::Round で丸まる)
    pushStyle();
    setStrokeWeight(8.0f);
    setStrokeCap(StrokeCap::Round);
    setStrokeJoin(StrokeJoin::Round);
    setColor(0.4f, 0.9f, 0.75f);
    beginStroke();
    vertex(40, 540);
    vertex(110, 510);
    vertex(180, 560);
    vertex(250, 510);
    vertex(320, 560);
    endStroke();
    popStyle();

    // ★ あなたが遊ぶ場所: 多角形をひとつ
    pushStyle();
    setStrokeWeight(8.0f);          // ← 太さを変えてみよう (1 〜 30)
    setStrokeCap(StrokeCap::Round);
    setStrokeJoin(StrokeJoin::Miter); // ← Round / Bevel / Miter 切り替え
    setColor(0.95f, 0.7f, 0.4f);    // ← 色を変えてみよう
    int n = 5;                       // ← 角の数。 3=三角, 4=四角, 6=六角...
    float cx = 480, cy = 535, r = 35;
    beginStroke();
    for (int i = 0; i < n; i++) {
        float a = TAU * i / n - TAU * 0.25f;
        vertex(cx + cos(a) * r, cy + sin(a) * r);
    }
    endStroke(true);                 // true = 閉じる
    popStyle();

    // ラベル: stroke 版
    setColor(0.45f);
    drawBitmapString("beginStroke", 446, 500);

    // 比較用 fill 版 (同じ頂点でも fill だと中身が塗りつぶされる)
    pushStyle();
    fill();
    setColor(0.4f, 0.6f, 0.95f);
    beginShape();
    for (int i = 0; i < n; i++) {
        float a = TAU * i / n - TAU * 0.25f;
        vertex(620 + cos(a) * r, cy + sin(a) * r);
    }
    endShape();
    popStyle();

    setColor(0.45f);
    drawBitmapString("beginShape (fill)", 580, 500);

    // =========================================================
    // CHALLENGE (軽め):
    //   (4) の ★ 多角形をいじってみよう
    //   - StrokeWeight, StrokeJoin, 色, n (角の数) を変えるだけ
    //   - 試行錯誤して気に入った形を作ってみる
    //   ヒント: n を増やすと円に近づく。 r を変えると大きさが変わる
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
