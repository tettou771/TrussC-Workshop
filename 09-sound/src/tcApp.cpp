#include "tcApp.h"

void tcApp::setup() {
    // --- beep(): built-in debug sounds ---
    // beep()              default ping
    // beep(Beep::success) preset sounds
    // No setup needed, just call it in keyPressed!

    // --- ChipSound: build your own sound ---
    // ChipSoundNote defines a single tone
    // ChipSoundBundle combines multiple notes
    // .build() turns it into a playable Sound

    // Jump: rising tones
    {
        ChipSoundBundle bundle;
        for (int i = 0; i < 5; i++) {
            ChipSoundNote n;
            n.wave = Wave::Square;
            n.hz = 150.0f * pow(1.3f, (float)i);
            n.duration = 0.04f;
            n.volume = 0.3f;
            bundle.add(n, i * 0.03f);
        }
        jumpSound = bundle.build();
    }

    // Laser: falling tones + ADSR for sharp attack
    {
        ChipSoundBundle bundle;
        for (int i = 0; i < 8; i++) {
            ChipSoundNote n;
            n.wave = Wave::Square;
            n.hz = 1200.0f * pow(0.85f, (float)i);
            n.duration = 0.03f;
            n.volume = 0.3f;
            n.attack = 0.001f;
            n.decay = 0.005f;
            n.sustain = 0.8f;
            n.release = 0.01f;
            bundle.add(n, i * 0.02f);
        }
        laserSound = bundle.build();
    }

    // Explosion: noise + low rumble
    {
        ChipSoundBundle bundle;
        ChipSoundNote boom;
        boom.wave = Wave::Noise;
        boom.duration = 0.3f;
        boom.volume = 0.5f;
        bundle.add(boom, 0.0f);

        ChipSoundNote rumble;
        rumble.wave = Wave::Square;
        rumble.hz = 60.0f;
        rumble.duration = 0.25f;
        rumble.volume = 0.3f;
        bundle.add(rumble, 0.0f);

        explosionSound = bundle.build();
    }

    // =========================================================
    // チャレンジ:
    //   新しいキー (A など) に、自分だけの ChipSound を作ろう！
    //
    //   ここに追加:
    //     ChipSoundNote n;
    //     n.wave = Wave::Triangle;  // 波形を選ぶ
    //     n.hz = 440.0f;            // 音の高さ
    //     n.duration = 0.2f;        // 長さ
    //     n.volume = 0.3f;          // 音量
    //     mySound = n.build();      // Sound にする
    //
    //   keyPressed() に追加:
    //     case 'A': mySound.play(); break;
    //
    //   tcApp.h にも Sound mySound; を追加するのを忘れずに
    // =========================================================
}

void tcApp::update() {
}

void tcApp::draw() {
    clear(0.12f);

    // --- key guide ---
    setColor(0.8f, 0.8f, 0.4f);
    drawBitmapString("beep() - built-in sounds", 40, 40);

    setColor(0.7f);
    drawBitmapString(
        "1: ping       2: success    3: error\n"
        "4: coin       5: warning    6: click",
        40, 70);

    setColor(0.4f, 0.8f, 0.8f);
    drawBitmapString("ChipSound - custom sounds", 40, 160);

    setColor(0.7f);
    drawBitmapString(
        "Q: jump       W: laser      E: explosion",
        40, 190);

    // show last played sound name
    if (!lastPlayed.empty()) {
        setColor(1.0f);
        drawBitmapString(lastPlayed, 40, 260);
    }
}

void tcApp::keyPressed(int key) {
    // --- beep presets ---
    switch (key) {
        case '1': beep(Beep::ping);    lastPlayed = "ping";    break;
        case '2': beep(Beep::success); lastPlayed = "success"; break;
        case '3': beep(Beep::error);   lastPlayed = "error";   break;
        case '4': beep(Beep::coin);    lastPlayed = "coin";    break;
        case '5': beep(Beep::warning); lastPlayed = "warning"; break;
        case '6': beep(Beep::click);   lastPlayed = "click";   break;

        // --- chip sounds ---
        case 'Q': jumpSound.play();      lastPlayed = "jump";      break;
        case 'W': laserSound.play();     lastPlayed = "laser";     break;
        case 'E': explosionSound.play(); lastPlayed = "explosion"; break;
    }
}
void tcApp::keyReleased(int key) {}

void tcApp::mousePressed(Vec2 pos, int button) {}
void tcApp::mouseReleased(Vec2 pos, int button) {}
void tcApp::mouseMoved(Vec2 pos) {}
void tcApp::mouseDragged(Vec2 pos, int button) {}
void tcApp::mouseScrolled(Vec2 delta) {}

void tcApp::windowResized(int width, int height) {}
void tcApp::filesDropped(const vector<string>& files) {}
void tcApp::exit() {}
