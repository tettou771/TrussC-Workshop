#pragma once

#include <TrussC.h>
using namespace std;
using namespace tc;

class tcApp : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;

    void mousePressed(Vec2 pos, int button) override;
    void mouseReleased(Vec2 pos, int button) override;
    void mouseMoved(Vec2 pos) override;
    void mouseDragged(Vec2 pos, int button) override;
    void mouseScrolled(Vec2 delta) override;

    void windowResized(int width, int height) override;
    void filesDropped(const vector<string>& files) override;
    void exit() override;

    // FFT buffers
    static constexpr int FFT_SIZE = 1024;
    static constexpr int NUM_BANDS = 32;   // 表示用にまとめるバンド数
    vector<float> samples;                  // mic からの生サンプル
    vector<float> magnitudes;               // FFT magnitude (NUM_BANDS 個に集約・スムーズ済み)

    float bass = 0, mid = 0, high = 0;     // 3 帯域に集約した値 (smooth)
    float flash = 0;                        // バス hit 時に 1 → 減衰

    Fbo scene;                              // 全部ここに描いて、 flash 時は subtract 合成
    float time = 0;
};
