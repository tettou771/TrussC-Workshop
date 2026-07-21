#include "tcApp.h"
#include "TrussC.h"

void tcApp::setup() {
}

void tcApp::update() {
    time += getDeltaTime();
}

void tcApp::draw() {
    clear(0.12f);

    // --- sin wave ---
    // sin() は -1〜1 を返す。 これで滑らかな波を作る
    {
        // pushMatrix()を使うと、座標系を変更できる.
        // ここでは、(30, 100)の位置に座標系を移動している.
        pushMatrix();
        translate(30, 100);

        setColor(0.3f, 0.7f, 1.0f);
        setStrokeWeight(2.0f);
        beginStroke();
        for (int i = 0; i < 300; i++) {
            Vec2 p;
            p.x = i;
            p.y = sin(i * 0.03f + time * 2.0f) * 40.0f;
            vertex(p);
        }
        endStroke();

        popMatrix();
    }

    // --- Lissajous curve ---
    // x = cos(a*t), y = sin(b*t)  a と b の整数比で模様が決まる
    {
        pushMatrix();
        translate(520, 100);

        setColor(1.0f, 0.5f, 0.8f);
        setStrokeWeight(1.5f);
        beginStroke();
        int N = 300;
        float r = 60;
        for (int i = 0; i <= N; i++) {
            float t = TAU * i / N;
            Vec2 p;
            p.x = cos(3 * t + time) * r;
            p.y = sin(2 * t) * r;
            vertex(p);
        }
        endStroke();

        popMatrix();
    }

    // --- orbit on orbit ---
    // 2つの円の合成。 s1 と s2 の比でいろんな軌道が出てくる
    {
        pushMatrix();
        translate(750, 100);

        // 全体の回転は rotate でも可能。
        // translate が並行移動で、rotate が回転移動。
        rotate(time * 0.1f);

        // scaleをかけるとサイズ変更も可能
        // scale(2.0); // 2倍サイズ

        setColor(0.95f, 0.75f, 0.4f);
        setStrokeWeight(1.5f);
        beginStroke();
        float r1 = 40, r2 = 30;
        float s1 = 1.0, s2 = 3.2;
        for (int i = 0, N = 1000; i <= N; ++i) {
            float t = TAU * 10 * i / N;
            Vec2 p;
            p.x = r1 * sin(s1 * t) + r2 * cos(s2 * t);
            p.y = r1 * cos(s1 * t) + r2 * sin(s2 * t);
            vertex(p);
        }
        endStroke();

        popMatrix();
    }

    // --- noise landscape ---
    // noise(x, y) は滑らかな乱数 (0〜1) を返す
    {
        pushMatrix();
        translate(30, 320);

        setColor(0.4f, 0.9f, 0.5f);
        setStrokeWeight(2.0f);
        beginStroke();
        for (int i = 0; i < 400; i++) {
            float n = noise(i * 0.01f, time * 0.3f);
            Vec2 p;
            p.x = i * 2.0f;
            p.y = n * 120.0f - 60.0f;
            vertex(p);
        }
        endStroke();

        popMatrix();
    }

    // --- noise circles ---
    // 半径を noise でゆらして、 にゅるにゅる動くアメーバ
    {
        pushMatrix();
        translate(200, 480);

        setColor(1.0f, 0.8f, 0.3f, 0.8f);
        setStrokeWeight(2.0f);
        int N = 120;
        beginStroke();
        for (int i = 0; i <= N; i++) {
            float angle = TAU * i / N;
            float r = 50 + noise(cos(angle) * 2.0f + 10,
                                 sin(angle) * 2.0f + 10,
                                 time * 0.5f) * 30.0f;
            Vec2 p;
            p.x = cos(angle) * r;
            p.y = sin(angle) * r;
            vertex(p);
        }
        endStroke(true);

        popMatrix();
    }

    // --- random scatter (seeded) ---
    // 固定 seed なら毎フレーム同じ模様
    {
        pushMatrix();
        translate(500, 380);

        srand(42); // 固定 seed: 同じ点が再現される
        fill();
        for (int i = 0; i < 100; i++) {
            Vec2 p;
            p.x = rand() % 400;
            p.y = rand() % 200;
            float sz = 1 + rand() % 4;
            float bri = 0.3f + (rand() % 70) / 100.0f;
            setColor(bri, bri, bri * 1.2f);
            drawCircle(p.x, p.y, sz);
        }

        popMatrix();
    }

    // =========================================================
    // チャレンジ (軽め、 好きなだけ): 数字を変えて遊ぶ
    //
    //   Lissajous の「(3, 2)」を別の整数ペアに
    //       (5, 4) / (7, 3) / (3, 5) / (5, 7) — 模様が劇的に変わる
    //
    //   orbit on orbit の s1, s2 を変える
    //       (1.0, 3.2) を (2.0, 5.0) や (1.0, 2.5) に
    //
    //   noise landscape の noise(i * 0.01f, time * 0.3f) の 0.01
    //       0.001 = なだらか / 0.1 = ガタガタ
    //
    //   noise circles の振れ幅 (* 30.0f)
    //       0 で完璧な円、 200 にすると形が崩壊
    //
    //   sin wave に2つ目の波を足す
    //       p.y = sin(i*0.03 + time*2) * 40
    //            + sin(i*0.08 + time) * 20;
    //
    //   時間で動かす: 静的なやつに「+ time」を加えると動き出す
    //       例えば noise circles の noise の引数の最後に + time * 1.0
    // =========================================================

    setColor(0.4f);
    drawBitmapString("sin / Lissajous / orbit / noise / random", 20, 580);
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
