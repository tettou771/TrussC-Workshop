#include "tcApp.h"

void tcApp::setup() {

}

void tcApp::update() {

}

void tcApp::draw() {
    clear(0.12f);

    // --- 기본 도형 ---

    setColor(0.1f, 0.4f, 0.9f);
    drawCircle(120, 150, 60); // 원 (x, y, r)
    drawRect(250, 90, 120, 120); // 사각형 (x, y, w, h)
    drawLine(450, 90, 570, 210); // 선 (x1, y1, x2, y2)

    // 삼각형 (x1, y1, x2, y2, x3, y3)
    drawTriangle(650, 90, 580, 210, 720, 210);

    // 타원 (x, y, w, h)
    drawEllipse(840, 150, 50, 80);

    // --- 채우기 / 윤곽선만 ---

    // 채우기 (기본값)
    fill();
    setColor(1.0f, 1.0f, 1.0f);
    drawCircle(120, 370, 50);

    // 윤곽선만
    noFill();
    drawCircle(260, 370, 50);

    // 부드럽게 그리기
    setCircleResolution(100);
    drawCircle(400, 370, 50);
    setCircleResolution(20); // default is 20

    // push/pop style
    pushStyle();
    fill();
    setColor(.0f, 1.0f, 1.0f);
    setStrokeWeight(1.0f);
    popStyle();

    // --- 색상 투명도 (alpha) ---
    fill();
    setColor(1.0f, 0.3f, 0.3f, 0.7f);
    drawCircle(550, 370, 60);
    setColor(0.3f, 0.3f, 1.0f, 0.7f);
    drawCircle(590, 370, 60);

    // --- 둥근 모서리 사각형 ---
    setColor(0.6f, 0.9f, 0.7f);
    drawRectRounded(720, 320, 140, 100, 20);

    // =========================================================
    // 챌린지:
    //   위의 샘플을 참고해서 화면 아래쪽 (y=450 부근)에
    //   신호등을 그려보자
    //   - 가로로 긴 둥근 모서리 사각형을 베이스로
    //   - 빨강, 노랑, 초록 원을 나란히 배치
    //   - "초록불"만 켜진 느낌으로 만들어보자
    //     (나머지 2개는 어둡게, 초록만 밝게 + alpha로 빛나는 효과 등)
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
