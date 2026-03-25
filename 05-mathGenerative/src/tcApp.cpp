#include "tcApp.h"

void tcApp::setup() {
}

void tcApp::update() {
    time += getDeltaTime();
}

void tcApp::draw() {
    clear(0.12f);

    // --- sin wave ---
    // sin() returns -1 to 1. Use it to make smooth oscillation.
    {
        setColor(0.3f, 0.7f, 1.0f);
        setStrokeWeight(2.0f);
        beginStroke();
        for (int i = 0; i < 300; i++) {
            float x = 30 + i;
            float y = 100 + sin(i * 0.03f + time * 2.0f) * 40.0f;
            vertex(x, y);
        }
        endStroke();
    }

    // --- Lissajous curve ---
    // x = cos(a*t), y = sin(b*t) with different a,b makes beautiful curves
    {
        float cx = 520, cy = 100, r = 60;
        setColor(1.0f, 0.5f, 0.8f);
        setStrokeWeight(1.5f);
        beginStroke();
        int n = 300;
        for (int i = 0; i <= n; i++) {
            float t = TAU * i / n;
            float x = cx + cos(3 * t + time) * r;
            float y = cy + sin(2 * t) * r;
            vertex(x, y);
        }
        endStroke();
    }

    // --- noise landscape ---
    // noise(x, y) returns smooth random 0-1
    {
        setColor(0.4f, 0.9f, 0.5f);
        setStrokeWeight(2.0f);
        beginStroke();
        for (int i = 0; i < 400; i++) {
            float x = 30 + i * 2.0f;
            float n = noise(i * 0.01f, time * 0.3f);
            float y = 320 + n * 120.0f - 60.0f;
            vertex(x, y);
        }
        endStroke();
    }

    // --- noise circles ---
    // noise to wobble a circle's radius
    {
        float cx = 200, cy = 480;
        setColor(1.0f, 0.8f, 0.3f, 0.8f);
        setStrokeWeight(2.0f);
        int n = 120;
        beginStroke();
        for (int i = 0; i <= n; i++) {
            float angle = TAU * i / n;
            float r = 50 + noise(cos(angle) * 2.0f + 10, sin(angle) * 2.0f + 10, time * 0.5f) * 30.0f;
            vertex(cx + cos(angle) * r, cy + sin(angle) * r);
        }
        endStroke(true);
    }

    // --- random scatter (seeded) ---
    // random value from seed - same seed = same pattern
    {
        srand(42); // fixed seed: same dots every frame
        for (int i = 0; i < 100; i++) {
            float x = 500 + rand() % 400;
            float y = 380 + rand() % 200;
            float sz = 1 + rand() % 4;
            float bri = 0.3f + (rand() % 70) / 100.0f;
            setColor(bri, bri, bri * 1.2f);
            drawCircle(x, y, sz);
        }
    }

    // =========================================================
    // チャレンジ:
    //   noise を使ってパーティクルのフローフィールドを作ってみよう
    //   1. tcApp.h で vector<Vec2> particles を用意して、ランダムな位置で初期化
    //   2. update() で各パーティクルの位置から noise で角度を取得:
    //      float angle = noise(p.x * 0.005, p.y * 0.005, time) * TAU;
    //   3. その角度方向に少し移動:
    //      p.x += cos(angle) * 2;  p.y += sin(angle) * 2;
    //   4. draw() で小さい点として描画
    //   5. 画面外に出たらランダムにリセット
    //
    //   noiseField2dExample も参考に！
    // =========================================================

    setColor(0.4f);
    drawBitmapString("sin / Lissajous / noise / random", 20, 580);
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
