#include "tcApp.h"

void tcApp::setup() {
}

void tcApp::update() {
    time += getDeltaTime();
}

void tcApp::draw() {
    clear(0.12f);

    // --- translate ---
    // translate(x,y) moves the origin. Everything drawn after is shifted.
    {
        pushMatrix();
        translate(120, 150);

        setColor(0.4f);
        drawLine(-40, 0, 40, 0); // x axis
        drawLine(0, -40, 0, 40); // y axis

        setColor(0.3f, 0.7f, 1.0f);
        drawRect(-25, -25, 50, 50); // rect at the new origin
        popMatrix();
    }

    // --- rotate ---
    // rotate(angle) rotates around current origin.
    // TAU = one full turn. TAU/4 = 90deg.
    {
        pushMatrix();
        translate(320, 150);
        rotate(time * 0.5f); // slow spin

        setColor(0.4f);
        drawLine(-50, 0, 50, 0);
        drawLine(0, -50, 0, 50);

        setColor(1.0f, 0.6f, 0.2f);
        drawRect(-25, -25, 50, 50);
        popMatrix();
    }

    // --- scale ---
    // scale(sx, sy) changes size around origin
    {
        pushMatrix();
        translate(520, 150);
        float s = 1.0f + sin(time * 2.0f) * 0.3f; // pulse
        scale(s, s);

        setColor(0.4f);
        drawLine(-40, 0, 40, 0);
        drawLine(0, -40, 0, 40);

        setColor(0.4f, 0.9f, 0.5f);
        drawCircle(0, 0, 30);
        popMatrix();
    }

    // --- nested: flower pattern ---
    // pushMatrix/popMatrix lets you nest transforms
    {
        pushMatrix();
        translate(780, 150);

        int petals = 8;
        for (int i = 0; i < petals; i++) {
            pushMatrix();
            rotate(TAU * i / petals + time * 0.3f);
            translate(40, 0); // move out from center

            setColor(1.0f, 0.4f, 0.6f, 0.7f);
            drawEllipse(0, 0, 15, 30);
            popMatrix();
        }

        // center
        setColor(1.0f, 0.9f, 0.3f);
        drawCircle(0, 0, 12);
        popMatrix();
    }

    // --- clock (rotate for hands) ---
    {
        pushMatrix();
        translate(320, 420);
        float r = 100;

        // face
        setColor(0.2f);
        drawCircle(0, 0, r);

        // hour marks
        for (int i = 0; i < 12; i++) {
            pushMatrix();
            rotate(TAU * i / 12.0f);
            setColor(0.6f);
            drawRect(-2, -r + 5, 4, 12);
            popMatrix();
        }

        // second hand
        float sec = fmod(time, 60.0f);
        pushMatrix();
        rotate(TAU * sec / 60.0f - TAU * 0.25f);
        setColor(1.0f, 0.3f, 0.3f);
        setStrokeWeight(1.5f);
        drawStroke(0, 0, r - 15, 0);
        popMatrix();

        // minute hand
        float min = fmod(time / 60.0f, 60.0f);
        pushMatrix();
        rotate(TAU * min / 60.0f - TAU * 0.25f);
        setColor(1.0f);
        setStrokeWeight(3.0f);
        drawStroke(0, 0, r - 25, 0);
        popMatrix();

        // hour hand
        float hr = fmod(time / 3600.0f, 12.0f);
        pushMatrix();
        rotate(TAU * hr / 12.0f - TAU * 0.25f);
        setColor(1.0f);
        setStrokeWeight(5.0f);
        drawStroke(0, 0, r - 45, 0);
        popMatrix();

        // center dot
        setColor(1.0f, 0.3f, 0.3f);
        drawCircle(0, 0, 4);

        popMatrix();
    }

    // =========================================================
    // 챌린지:
    //   화면 오른쪽 아래 (650, 420) 부근에 태양계 같은 걸
    //   그려보자
    //   - translate로 중심을 이동
    //   - 태양을 중앙에 그리기
    //   - pushMatrix -> rotate(time * speed) -> translate(거리, 0)
    //     -> 행성 그리기 -> popMatrix
    //   - 행성마다 speed와 거리를 다르게 하면 공전 궤도가 됨
    //   - 달: 행성의 push 안에서 다시 push -> rotate -> translate
    //     -> 작은 원 -> pop 하면 위성이 됨!
    // =========================================================

    setColor(0.4f);
    drawBitmapString("translate / rotate / scale / nested transforms", 20, 580);
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
