#include "tcApp.h"

// TC_HOT_RELOAD をコメントアウトすると、 ホットリロードが無効化されます
TC_HOT_RELOAD(tcApp)

// =============================================================================
// 9-fft  -  FFT で音 → 形状を動かす (Autechre "Gantz Graf" オマージュ)
//
// マイクから拾った音を FFT して、 低/中/高 域のエネルギーで
// 中央の icosphere と周囲のスパイクリングを駆動する。
// 起動したら **スピーカーから何か鳴らしてマイクに聞かせて** ください。
//
// (ワークショップ用というよりはショーケース寄り)
// =============================================================================

void tcApp::setup() {
    // マイク開始 (44100Hz)
    getMicInput().start(44100);

    samples.resize(FFT_SIZE, 0.0f);
    magnitudes.assign(NUM_BANDS, 0.0f);
}

void tcApp::update() {
    time += getDeltaTime();

    // ---- マイクから最新サンプルを取得 ----
    getMicAnalysisBuffer(samples.data(), FFT_SIZE);

    // ---- FFT ----
    auto spectrum = fftReal(samples, WindowType::Hanning);  // 窓関数で漏れ抑制
    auto magRaw = fftMagnitude(spectrum);

    // ---- 半分だけ使う (Nyquist まで) → NUM_BANDS に対数まとめ ----
    // FFT は対称なので前半 N/2 だけ意味がある。
    // さらに人間の聴感は対数なので、 低周波を細かく、 高周波を粗くまとめる。
    int half = FFT_SIZE / 2;
    for (int b = 0; b < NUM_BANDS; b++) {
        float t0 = (float)b / NUM_BANDS;
        float t1 = (float)(b + 1) / NUM_BANDS;
        int lo = (int)(pow(2.0f, t0 * 10.0f) - 1);          // 1〜1023 へ対数展開
        int hi = (int)(pow(2.0f, t1 * 10.0f) - 1);
        if (hi > half) hi = half;
        if (lo >= hi) hi = lo + 1;

        float sum = 0;
        for (int i = lo; i < hi; i++) sum += magRaw[i];
        float val = sum / (hi - lo);

        // スムージング (attack 早く、 release 遅く — 殴られて沈むイメージ)
        float target = val * 0.05f;
        float smooth = (target > magnitudes[b]) ? 0.6f : 0.15f;
        magnitudes[b] += (target - magnitudes[b]) * smooth;
    }

    // ---- 3 帯域に集約 ----
    auto bandAvg = [&](int from, int to) {
        float s = 0;
        for (int i = from; i < to; i++) s += magnitudes[i];
        return s / (to - from);
    };
    float bassTarget = bandAvg(0, NUM_BANDS / 4);
    float midTarget  = bandAvg(NUM_BANDS / 4, NUM_BANDS * 2 / 4);
    float highTarget = bandAvg(NUM_BANDS * 2 / 4, NUM_BANDS);

    bass += (bassTarget - bass) * 0.3f;
    mid  += (midTarget  - mid)  * 0.3f;
    high += (highTarget - high) * 0.3f;

    // バス hit でフラッシュ (色反転)
    if (bass > 0.6f && flash < 0.5f) flash = 1.0f;
    flash *= 0.85f;
}

void tcApp::draw() {
    // 背景は黒。 バス hit で一瞬白に反転 (Gantz Graf の鋭いカット感)
    float bg = flash * 0.95f;
    clear(bg);

    float cx = getWidth()  / 2.0f;
    float cy = getHeight() / 2.0f;
    bool inv = flash > 0.3f;             // 色反転判定

    // ---- 中央 icosphere (wireframe、 bass で膨張、 mid で回転) ----
    pushMatrix();
    translate(cx, cy, 0);
    rotateY(time * (0.3f + mid * 2.0f));
    rotateX(time * 0.15f);

    float r = 80 + bass * 200;
    int subdiv = 2 + (int)(high * 3);
    if (subdiv > 4) subdiv = 4;
    auto ico = createIcoSphere(r, subdiv);

    setStrokeWeight(1.5f);
    setColor(inv ? 0.0f : 1.0f);
    ico.drawWireframe();
    popMatrix();

    // ---- 周囲のスパイクリング (各 FFT バンドが 1 本の縦棒) ----
    pushMatrix();
    translate(cx, cy, 0);
    rotateY(time * 0.2f);                // ゆっくり全体回転

    for (int b = 0; b < NUM_BANDS; b++) {
        float angle = TAU * b / NUM_BANDS;
        float ringR = 300;
        float spikeH = 10 + magnitudes[b] * 600;

        pushMatrix();
        translate(cos(angle) * ringR, 0, sin(angle) * ringR);
        rotateY(-angle);                 // 棒を中心向きに
        setColor(inv ? 0.0f : 1.0f);
        drawBox(0, 0, 0, 6, spikeH, 6);
        popMatrix();
    }
    popMatrix();

    // ---- 水平に倒した内側リング (バンドを後ろから見せる差し色) ----
    pushMatrix();
    translate(cx, cy, 0);
    rotateY(time * -0.3f);
    rotateX(HALF_TAU / 2);
    setStrokeWeight(1.0f);
    setColor(inv ? 0.0f : 0.4f);
    auto inner = createIcoSphere(180 + mid * 100, 1);
    inner.drawWireframe();
    popMatrix();

    // ---- 2D オーバーレイ ----
    setColor(inv ? 0.0f : 0.5f);
    drawBitmapString("9-fft  -  point mic at speakers  ('Gantz Graf' homage)", 20, 30);

    // 画面下に FFT スペクトルバー
    float barW = (float)getWidth() / NUM_BANDS;
    for (int b = 0; b < NUM_BANDS; b++) {
        float h = magnitudes[b] * 200;
        drawRect(b * barW + 2, getHeight() - h, barW - 4, h);
    }
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
void tcApp::exit() {
    getMicInput().stop();
}
