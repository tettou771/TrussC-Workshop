#include "tcApp.h"

void tcApp::setup() {
    // --- Image: 픽셀 단위 접근 ---
    // allocate(w, h, channels)  빈 이미지 생성
    // setColor(x, y, color)     픽셀 하나 쓰기
    // update()                  픽셀을 GPU에 업로드
    // draw(x, y, w, h)         화면에 표시

    int size = 16;

    // --- 정적 패턴 ---
    patternImg.allocate(size, size, 4);
    patternImg.setFilter(TextureFilter::Nearest); // 선명한 픽셀, 블러 없음

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            // 가로 그라데이션: x에 따라 색상이 변함
            float hue = (float)x / size;
            float bri = 1.0f - (float)y / size * 0.5f;
            patternImg.setColor(x, y, Color::fromHSB(hue, 0.8f, bri));
        }
    }
    patternImg.update();

    // --- 라이브 이미지 (같은 크기, 나중에 애니메이션) ---
    liveImg.allocate(size, size, 4);
    liveImg.setFilter(TextureFilter::Nearest);
}

void tcApp::update() {
    time += getDeltaTime();

    // --- 라이브 픽셀 업데이트 ---
    // setColor + update를 매 프레임 = 애니메이션
    int size = 16;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            // 같은 그라데이션이지만 시간에 따라 색상이 이동
            float hue = fmod((float)x / size + time * 0.1f, 1.0f);
            float bri = 1.0f - (float)y / size * 0.5f;
            liveImg.setColor(x, y, Color::fromHSB(hue, 0.8f, bri));
        }
    }
    liveImg.update();
}

void tcApp::draw() {
    clear(0.12f);

    // --- 정적 패턴 (setup에서 한 번만 설정) ---
    setColor(1.0f);
    patternImg.draw(60, 60, 320, 320);

    // original size for comparison (tiny!)
    patternImg.draw(60, 400);

    setColor(0.6f);
    drawBitmapString("static (16x16, Nearest filter)", 60, 45);
    drawBitmapString("^ original size", 85, 420);

    // --- 라이브 패턴 (매 프레임 업데이트) ---
    setColor(1.0f);
    liveImg.draw(500, 60, 320, 320);

    setColor(0.6f);
    drawBitmapString("live update (hue shifts with time)", 500, 45);

    // --- getColor: 픽셀 읽기 ---
    Color c = patternImg.getColor(0, 0);
    setColor(c);
    drawRect(60, 460, 50, 50);
    setColor(0.6f);
    drawBitmapString("getColor(0,0)", 120, 488);

    // =========================================================
    // 챌린지:
    //   setup()의 패턴을 바꿔보자!
    //   지금은 가로 그라데이션으로 되어 있어 (hue = x / size)
    //
    //   아이디어:
    //   - 체커보드: (x + y) % 2 == 0 으로 흑백
    //   - 원: 중심으로부터의 거리로 색 변경
    //     float d = sqrt((x-8)*(x-8) + (y-8)*(y-8));
    //   - 도트 그림: 원하는 좌표에 원하는 색을 넣어보자
    //     patternImg.setColor(3, 2, Color(1, 0, 0));
    // =========================================================

    setColor(0.4f);
    drawBitmapString("Image: allocate / setColor / getColor / update / draw", 20, 580);
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
