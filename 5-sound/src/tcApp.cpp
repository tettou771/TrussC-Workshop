// =============================================================================
// 5-sound - サウンド入門
//
//   beep()         一行で UI フィードバック
//   ChipSound      波形 + 周波数 + 長さで自分で組み立てる旋律
//   Sound::load    ファイル読み込み + ループ再生 + ボリューム / パン / スピード
//
// 同梱音源:
//   "113 2b loose-pants 4.2 mono" by astro_denticle (CC0)
//   https://freesound.org/
// =============================================================================

#include "tcApp.h"

// TC_HOT_RELOAD をコメントアウトすると、ホットリロードが無効化されます
TC_HOT_RELOAD(tcApp)

void tcApp::setup() {
    // --- ChipSound: ファミコン風の旋律を組み立て ---
    // ChipSoundNote 1個 = 1音、 ChipSoundBundle で並べると旋律になる
    // wave: Sin / Square / Triangle / Sawtooth / Noise
    {
        ChipSoundBundle bundle;
        float t = 0;
        int notes[] = { 60, 64, 67, 72, 67, 64, 60 };  // ド ミ ソ ド ソ ミ ド (MIDI)
        for (int n : notes) {
            ChipSoundNote note;
            note.wave = ChipSoundNote::Wave::Square;
            note.hz = 440.0f * pow(2.0f, (n - 69) / 12.0f); // MIDI → Hz
            note.duration = 0.18f;
            note.volume = 0.3f;
            bundle.add(note, t);
            t += 0.18f;
        }
        chip = bundle.build();
    }

    // --- 音源ファイル読み込み ---
    string path = getDataPath("beat_loop.wav");
    if (music.load(path)) {
        music.setLoop(true);
        music.setVolume(0.6f);
        musicLoaded = true;
    }
}

void tcApp::update() {
}

void tcApp::draw() {
    clear(0.12f);

    // --- タイトル ---
    setColor(0.9f);
    drawBitmapString("5-sound", 30, 40);

    // --- 操作説明 ---
    setColor(0.6f);
    float y = 80;
    drawBitmapString("[1] beep ping       [2] beep success       [3] beep error", 30, y); y += 22;
    drawBitmapString("[Q] ChipSound: one note    [W] ChipSound: melody (do mi so do ...)", 30, y); y += 22;
    drawBitmapString("[SPACE] BGM play / stop (loops)", 30, y); y += 22;
    drawBitmapString("[A/D] BGM pan (left/right)   [Z/X] BGM speed   [click] beep ping", 30, y); y += 40;

    // --- 状態表示 ---
    setColor(0.5f);
    drawBitmapString("BGM:", 30, y);
    if (musicLoaded) {
        setColor(colors::lime);
        drawBitmapString("loaded (beat_loop.wav)", 90, y);
    }
    y += 22;

    if (musicLoaded) {
        if (music.isPlaying()) setColor(colors::lime);
        else                   setColor(0.5f);
        drawBitmapString(string("status: ") + (music.isPlaying() ? "PLAYING" : "stopped"), 30, y); y += 22;
        setColor(0.5f);
        drawBitmapString(format("volume: {:.0f}%   pan: {:+.1f}   speed: {:.1f}x",
            music.getVolume() * 100, music.getPan(), music.getSpeed()), 30, y); y += 30;
    }

    // --- 最後に鳴ったやつを表示 (1.5秒間ハイライト) ---
    float age = getElapsedTime() - lastActionTime;
    if (age < 1.5f && !lastAction.empty()) {
        float alpha = 1.0f - age / 1.5f;
        setColor(colors::cyan.r, colors::cyan.g, colors::cyan.b, alpha);
        drawBitmapString("♪ " + lastAction, 30, getHeight() - 60);
    }

    // =========================================================
    // チャレンジ (好きなだけ):
    //
    //   - ChipSound の旋律を変える: notes[] の中身、 wave、 duration
    //       wave を Triangle / Sawtooth に変えると音色が一変
    //   - mousePressed で beep() の代わりに ChipSoundNote をその場で組んで .play()
    //       ピッチを mouse.x にすると 「左右でドレミ」 みたいなインタラクションに
    //   - music.setSpeed を tween で滑らかに遷移
    //       4-tween で覚えた Tween<float> を組合せると凝った演出に
    // =========================================================
}

void tcApp::keyPressed(int key) {
    if (key == '1') { beep(Beep::ping);    lastAction = "beep(ping)";    lastActionTime = getElapsedTime(); }
    if (key == '2') { beep(Beep::success); lastAction = "beep(success)"; lastActionTime = getElapsedTime(); }
    if (key == '3') { beep(Beep::error);   lastAction = "beep(error)";   lastActionTime = getElapsedTime(); }

    if (key == 'Q') {
        ChipSoundNote note{ChipSoundNote::Wave::Square, 880.0f, 0.15f, 0.3f};
        note.build().play();
        lastAction = "ChipSound 1音 (A5 square)";
        lastActionTime = getElapsedTime();
    }
    if (key == 'W') {
        chip.play();
        lastAction = "ChipSound 旋律";
        lastActionTime = getElapsedTime();
    }

    if (key == ' ') {
        if (!musicLoaded) return;
        if (music.isPlaying()) {
            music.stop();
            lastAction = "BGM 停止";
        } else {
            music.play();
            lastAction = "BGM 再生";
        }
        lastActionTime = getElapsedTime();
    }

    // BGM のパン (左右)
    if (key == 'A') music.setPan(clamp(music.getPan() - 0.2f, -1.0f, 1.0f));
    if (key == 'D') music.setPan(clamp(music.getPan() + 0.2f, -1.0f, 1.0f));
    // BGM のスピード (ピッチも変わる)
    if (key == 'Z') music.setSpeed(clamp(music.getSpeed() - 0.1f, 0.25f, 4.0f));
    if (key == 'X') music.setSpeed(clamp(music.getSpeed() + 0.1f, 0.25f, 4.0f));
}

void tcApp::keyReleased(int key) {}

void tcApp::mousePressed(Vec2 pos, int button) {
    beep();
    lastAction = "click → beep()";
    lastActionTime = getElapsedTime();
}

void tcApp::mouseReleased(Vec2 pos, int button) {}
void tcApp::mouseMoved(Vec2 pos) {}
void tcApp::mouseDragged(Vec2 pos, int button) {}
void tcApp::mouseScrolled(Vec2 delta) {}

void tcApp::windowResized(int width, int height) {}
void tcApp::filesDropped(const vector<string>& files) {}
void tcApp::exit() {}
