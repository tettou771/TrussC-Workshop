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

    // =========================================================
    // (1) 基本図形 — 引数の並び順をひとつずつ確認
    // =========================================================
    setColor(0.45f);
    drawBitmapString("(1) basic shapes  -  fill is the default", 30, 25);

    fill();

    setColor(0.3f, 0.7f, 1.0f);
    drawCircle(80, 95, 40);                     // (x, y, r)

    setColor(0.95f, 0.55f, 0.3f);
    drawRect(160, 55, 80, 80);                  // (x, y, w, h)

    // drawRectには角丸のバリエーションがあります
    //drawRectRounded(160, 55, 80, 80, 14);       // 角丸: 半径を 5 つ目の引数で
    //drawRectSquircle(160, 55, 80, 80, 14);       // 滑らかな角丸

    // 細い線 （とても軽いので大量に描ける）
    setColor(0.7f, 0.9f, 0.4f);
    setStrokeWeight(3.0f);
    drawLine(270, 60, 360, 135);                // (x1, y1, x2, y2)

    // 三角形
    setColor(0.95f, 0.4f, 0.65f);
    drawTriangle(420, 55, 390, 135, 460, 135);  // (x1,y1, x2,y2, x3,y3)

    // 弧(パックマンみたいなやつ)
    setColor(1.0f, 0.9f, 0.4f);
    drawArc(540, 95, 40, 0.5f, TAU - 0.5f);     // 弧 → fill すると扇形 (パックマン)

    // =========================================================
    // (2) fill / noFill / alpha — 同じ図形を別の見た目で
    // =========================================================
    setColor(0.45f);
    drawBitmapString("(2) fill / noFill / alpha", 30, 175);

    fill();
    setColor(1.0f, 0.7f, 0.6f);
    drawCircle(80, 240, 38);

    noFill();                                    // 線で描画（塗りつぶしなし）
    setStrokeWeight(2.0f);
    setColor(1.0f);
    drawCircle(175, 240, 38);

    fill();                                      // fill に戻す
    setColor(1.0f, 0.3f, 0.3f, 0.55f);          // 赤、4つめが alpha
    drawCircle(295, 240, 42);
    setColor(0.3f, 0.6f, 1.0f, 0.55f);          // 青、4つめが alpha
    drawCircle(340, 240, 42);

    // pushStyle で一時的な設定に入る
    pushStyle();
    noFill();
    setStrokeWeight(4.0f);
    setColor(1.0f, 0.9f, 0.4f);
    drawRectRounded(440, 207, 85, 70, 13);
    popStyle(); // 一時的な設定を抜ける

    // =========================================================
    // (3) drawStroke — 太い線。端の形 (Cap) が選べる
    //     縦に並べて長さ比較しやすく
    // =========================================================
    setColor(0.45f);
    drawBitmapString("(3) drawStroke  +  StrokeCap (compare lengths)", 30, 320);

    pushStyle();
    setStrokeWeight(18.0f);

    setStrokeCap(StrokeCap::Butt);
    setColor(0.5f, 0.7f, 0.95f);
    drawStroke(80, 355, 280, 355);
    setColor(0.5f);
    drawBitmapString("Butt", 300, 360);

    setStrokeCap(StrokeCap::Round);
    setColor(1.0f, 0.8f, 0.4f);
    drawStroke(80, 400, 280, 400);
    setColor(0.5f);
    drawBitmapString("Round", 300, 405);

    setStrokeCap(StrokeCap::Square);
    setColor(0.95f, 0.45f, 0.7f);
    drawStroke(80, 445, 280, 445);
    setColor(0.5f);
    drawBitmapString("Square", 300, 450);

    // 補助線 (端の位置を可視化したい時はコメント解除)
    // setColor(0.f);
    // drawLine(80, 355, 280, 355);
    // drawLine(80, 400, 280, 400);
    // drawLine(80, 445, 280, 445);

    popStyle();

    // =========================================================
    // (4) beginStroke — 連続した頂点で自由なパス
    // =========================================================
    setColor(0.45f);
    drawBitmapString("(4) beginStroke / vertex / endStroke", 30, 490);

    // ジグザグ (角の形 = StrokeJoin::Round で丸まる)
    pushStyle();
    setStrokeWeight(8.0f);
    setStrokeCap(StrokeCap::Round);
    setStrokeJoin(StrokeJoin::Round);
    setColor(0.4f, 0.9f, 0.75f);
    beginStroke();
    vertex(40, 555);
    vertex(120, 525);
    vertex(200, 575);
    vertex(280, 525);
    vertex(360, 575);
    vertex(440, 525);
    vertex(520, 575);
    endStroke();
    popStyle();

    // =========================================================
    // CHALLENGE — 右側の大きな図形をいじってみよう
    // =========================================================
    setColor(0.7f, 0.7f, 0.4f);
    drawBitmapString("CHALLENGE  -  try changing the values below", 620, 25);

    // ---- 五芒星 (beginStroke / 線) ----
    pushStyle();
    setStrokeWeight(10.0f);             // ← 太さを変えてみよう (1 〜 30)
    setStrokeCap(StrokeCap::Round);
    setStrokeJoin(StrokeJoin::Miter);  // ← Round / Bevel / Miter 切り替え
    setColor(0.95f, 0.7f, 0.4f);       // ← 色を変えてみよう
    int n = 5;                          // ← 角の数。 3=三角, 4=四角, 6=六角...
    float cx = 780, cy = 175, r = 100;
    beginStroke();
    for (int i = 0; i < n; i++) {
        float a = 2 * TAU * i / n;     // ← "2 *" を消すと普通の五角形に
        vertex(cx + sin(a) * r, cy - cos(a) * r);
    }
    endStroke(true);                    // true = 閉じる
    popStyle();

    setColor(0.5f);
    drawBitmapString("beginStroke  (line, closed)", 660, 305);

    // ---- 五角形 (beginShape / fill 版) ----
    pushStyle();
    fill();
    setColor(0.4f, 0.6f, 0.95f);
    cx = 780; cy = 440; r = 100;
    beginShape();
    for (int i = 0; i < n; i++) {
        float a = TAU * i / n; // 1周回って頂点を描画
        vertex(cx + sin(a) * r, cy - cos(a) * r);
    }
    endShape();
    popStyle();

    setColor(0.5f);
    drawBitmapString("beginShape  (fill)", 690, 570);

    // =========================================================
    // CHALLENGE のヒント:
    //   - StrokeWeight, StrokeJoin, 色, n (角の数) を変えるだけで雰囲気が変わる
    //   - n を増やすと円に近づく。 r を変えると大きさが変わる
    //   - 五芒星の "2 *" を消すと普通の五角形になる (n=5 で飛ばし描きが星型を作る)
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
