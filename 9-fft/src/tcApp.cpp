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

    // 全描画用 FBO (MSAA 4x で 3D ワイヤフレームをきれいに)
    scene.allocate(getWidth(), getHeight(), 4);
}

void tcApp::update() {
    time += getDeltaTime();

    // ---- マイクから最新サンプルを取得 ----
    getMicAnalysisBuffer(samples.data(), FFT_SIZE);

    // ---- FFT → 各周波数 bin の強さに ----
    auto spectrum = fftReal(samples, WindowType::Hanning);  // 窓関数で漏れ抑制
    auto magRaw = fftMagnitude(spectrum);

    // ---- 512 bin (Nyquist まで) を NUM_BANDS 個に均等まとめ ----
    // 1 バンド = 16 bin ≈ 688Hz 分。
    // 厳密には人間の聴感は対数で、 低音域は数bin に潰れるけど、
    // workshop サンプルとしてわかりやすさ優先でリニア。
    const float MIC_GAIN = 0.05f;
    int binsPerBand = (FFT_SIZE / 2) / NUM_BANDS;
    for (int b = 0; b < NUM_BANDS; b++) {
        float sum = 0;
        for (int i = b * binsPerBand; i < (b + 1) * binsPerBand; i++) {
            sum += magRaw[i];
        }
        float val = sum / binsPerBand * MIC_GAIN;

        // attack 早く、 release 遅く (殴られて沈むイメージ)
        float smooth;
        if (val > magnitudes[b]) {
            smooth = 0.6f;
        }
        else {
            smooth = 0.15f;
        }
        magnitudes[b] += (val - magnitudes[b]) * smooth;
    }

    // ---- 3 帯域 (低/中/高) に再集約 ----
    // bands 0..7 → 低、 8..15 → 中、 16..31 → 高 (NUM_BANDS=32 前提)
    float lowSum = 0, midSum = 0, highSum = 0;
    int   lowN = 0,   midN = 0,   highN = 0;
    for (int b = 0; b < NUM_BANDS; b++) {
        if (b >= NUM_BANDS / 2) {
            highSum += magnitudes[b];
            highN++;
        }
        else if (b >= NUM_BANDS / 4) {
            midSum += magnitudes[b];
            midN++;
        }
        else {
            lowSum += magnitudes[b];
            lowN++;
        }
    }
    bass += (lowSum  / lowN  - bass) * 0.3f;
    mid  += (midSum  / midN  - mid)  * 0.3f;
    high += (highSum / highN - high) * 0.3f;

    // バス hit でフラッシュ (色反転)
    if (bass > 0.6f && flash < 0.5f) {
        flash = 1.0f;
    }
    flash *= 0.85f;
}

void tcApp::draw() {
    float cx = getWidth()  / 2.0f;
    float cy = getHeight() / 2.0f;

    // =========================================================
    // 1) 全部 FBO に「白い線、 黒背景」 で描く
    // =========================================================
    scene.begin(0, 0, 0, 1);

    // ---- 中央 icosphere (wireframe、 bass で膨張、 mid で回転) ----
    pushMatrix();
    translate(cx, cy, 0);
    rotateY(time * (0.3f + mid * 2.0f));
    rotateX(time * 0.15f);

    float r = 80 + bass * 200;
    int subdiv = 2 + (int)(high * 3);
    if (subdiv > 4) {
        subdiv = 4;
    }
    auto ico = createIcoSphere(r, subdiv);

    setStrokeWeight(1.5f);
    setColor(1.0f);
    ico.drawWireframe();
    popMatrix();

    // ---- 周囲のスパイクリング (各 FFT バンドが 1 本の縦棒) ----
    pushMatrix();
    translate(cx, cy, 0);
    rotateY(time * 0.2f);
    for (int b = 0; b < NUM_BANDS; b++) {
        float angle = TAU * b / NUM_BANDS;
        float ringR = 300;
        float spikeH = 10 + magnitudes[b] * 600;

        pushMatrix();
        translate(cos(angle) * ringR, 0, sin(angle) * ringR);
        rotateY(-angle);
        setColor(1.0f);
        drawBox(0, 0, 0, 6, spikeH, 6);
        popMatrix();
    }
    popMatrix();

    // ---- 水平に倒した内側リング (差し色) ----
    pushMatrix();
    translate(cx, cy, 0);
    rotateY(time * -0.3f);
    rotateX(HALF_TAU / 2);
    setStrokeWeight(1.0f);
    setColor(0.4f);
    auto inner = createIcoSphere(180 + mid * 100, 1);
    inner.drawWireframe();
    popMatrix();

    // ---- 2D オーバーレイ ----
    setColor(0.5f);
    drawBitmapString("9-fft  -  point mic at speakers  ('Gantz Graf' homage)", 20, 30);

    float barW = (float)getWidth() / NUM_BANDS;
    for (int b = 0; b < NUM_BANDS; b++) {
        float h = magnitudes[b] * 200;
        drawRect(b * barW + 2, getHeight() - h, barW - 4, h);
    }

    scene.end();

    // =========================================================
    // 2) 画面に合成
    //    flash なし: そのまま黒背景に描画
    //    flash あり: 白背景 + subtract で「白 - シーン」 → 反転表示
    // =========================================================
    bool invert = flash > 0.3f;
    if (invert) {
        clear(1.0f);
        setBlendMode(BlendMode::Subtract);
    }
    else {
        clear(0.0f);
    }

    setColor(1.0f);
    scene.draw(0, 0, getWidth(), getHeight());

    if (invert) {
        resetBlendMode();
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
