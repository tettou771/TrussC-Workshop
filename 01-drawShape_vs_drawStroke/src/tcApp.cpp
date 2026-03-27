#include "tcApp.h"

void tcApp::setup() {

}

void tcApp::update() {

}

void tcApp::draw() {
    clear(0.12f);

    // --- drawLine vs drawStroke ---
    // drawLine은 1px 고정. strokeWeight가 적용 안 됨
    setColor(0.5f, 0.5f, 0.5f);
    setStrokeWeight(20.0f);
    drawLine(60, 60, 300, 60);

    // drawStroke는 strokeWeight가 적용되는 두꺼운 선
    setColor(1.0f, 0.7f, 0.2f);
    drawStroke(60, 120, 300, 120);

    // --- StrokeCap 차이 ---
    // Butt: 끝점에서 딱 잘림
    setStrokeCap(StrokeCap::Butt);
    setColor(0.3f, 0.8f, 1.0f);
    drawStroke(60, 200, 250, 200);

    // Round: 끝점에 반원이 붙음
    setStrokeCap(StrokeCap::Round);
    drawStroke(60, 250, 250, 250);

    // Square: 반 너비만큼 연장됨
    setStrokeCap(StrokeCap::Square);
    drawStroke(60, 300, 250, 300);

    // --- beginStroke / endStroke로 자유로운 패스 ---
    setColor(0.9f, 0.3f, 0.5f);
    setStrokeWeight(10.0f);
    setStrokeCap(StrokeCap::Round);
    setStrokeJoin(StrokeJoin::Round);

    beginStroke();
    vertex(400, 80);
    vertex(500, 200);
    vertex(600, 80);
    vertex(700, 200);
    vertex(800, 80);
    endStroke();

    // close = true로 닫힌 패스
    setColor(0.4f, 0.9f, 0.6f);
    setStrokeWeight(10.0f);
    setStrokeJoin(StrokeJoin::Miter);

    beginStroke();
    vertex(450, 300);
    vertex(550, 250);
    vertex(650, 300);
    vertex(650, 400);
    vertex(450, 400);
    endStroke(true);

    // --- noFill 도형 스트로크와의 비교 ---
    // noFill + drawCircle은 균일한 윤곽선
    setColor(1.0f, 1.0f, 1.0f);
    noFill();
    drawCircle(150, 470, 60);

    // beginStroke + close로 그리는 원은 Cap/Join이 적용됨
    // TAU = 2pi = 한 바퀴 각도 (TrussC에서는 PI 대신 TAU를 사용)
    // TAU * 0.25 = 90도, TAU * 0.5 = 180도, TAU = 360도로 외우면 편함
    setColor(1.0f, 1.0f, 1.0f);
    setStrokeWeight(2.0f);
    int n = 40;
    beginStroke();
    for (int i = 0; i < n; i++) {
        float angle = TAU * i / n; // 0 ~ TAU를 n등분
        vertex(400 + cos(angle) * 60, 470 + sin(angle) * 60);
    }
    endStroke(true);

    // =========================================================
    // 챌린지:
    //   beginStroke를 사용해서 손그림 느낌의 별(오각별)을
    //   한붓그리기로 그려보자
    //   힌트:
    //   - 5개의 꼭짓점을 "하나 건너뛰어" 연결하면 별이 됨
    //   - 원주 위의 점은 cos/sin으로 구할 수 있어 (위 샘플 참고)
    //   - TAU * i / 5 로 오각형의 꼭짓점, 여기서 i를 0,2,4,1,3
    //     순서로 돌리면 한붓그리기 별이 됨 (즉 i*2 % 5)
    //   - endStroke(true)로 닫기
    //   - StrokeJoin::Round / Miter / Bevel로 인상이 꽤 달라짐
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
