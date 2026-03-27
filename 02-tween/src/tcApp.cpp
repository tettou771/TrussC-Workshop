#include "tcApp.h"

void tcApp::setup() {
    flipTween.from(0).to(0);
    meterTween.from(0).to(0);
    tofuTween.from(0).to(0);
    challengeT.from(0).to(0);
}

void tcApp::update() {
}

void tcApp::draw() {
    clear(0.12f);

    int n = 200; // arc vertex count

    // --- coin flip (Back) ---
    // circle with white top and gray bottom. Press space to flip by TAU/2
    {
        float angle = flipTween.getValue();
        float cx = 160, cy = 170, r = 50;

        pushStyle();
        setStrokeCap(StrokeCap::Butt);
        setStrokeWeight(r);

        // White half (top at angle=0)
        setColor(0.9f);
        beginStroke();
        for (int i = 0; i <= n; i++) {
            float theta = angle + TAU * 0.5f + TAU * 0.5f * i / n;
            vertex(cx + cos(theta) * r * 0.5f, cy + sin(theta) * r * 0.5f);
        }
        endStroke();

        // Gray half (bottom at angle=0)
        setColor(0.4f);
        beginStroke();
        for (int i = 0; i <= n; i++) {
            float theta = angle + TAU * 0.5f * i / n;
            vertex(cx + cos(theta) * r * 0.5f, cy + sin(theta) * r * 0.5f);
        }
        endStroke();

        popStyle();
    }

    // --- meter (Quint) ---
    // an arc grows from nothing and wraps around to form a full circle
    {
        float maxTheta = meterTween.getValue();
        float cx = 480, cy = 170, r = 50;

        if (abs(maxTheta) > 0.01f) {
            pushStyle();
            setStrokeCap(StrokeCap::Butt);
            setStrokeWeight(14);
            setColor(1.0f, 0.6f, 0.2f);

            beginStroke();
            for (int i = 0; i <= n; i++) {
                // top (-TAU/4) start, clockwise
                float theta = -TAU * 0.25f + maxTheta * i / n;
                vertex(cx + cos(theta) * r, cy + sin(theta) * r);
            }
            endStroke();

            popStyle();
        }
    }

    // --- tofu (Elastic) ---
    // a tall rectangle morphs into a square. Area, bottom-y, and center-x stay the same.
    // the Elastic easing makes it wobble like jelly
    {
        float t = tofuTween.getValue();
        float cx = 800;
        float w0 = 70, h0 = 140;
        float area = w0 * h0;
        float sqSide = sqrt(area);
        float bottomY = 250;

        float h = lerp(h0, sqSide, t);
        float w = area / h;

        setColor(0.95f, 0.95f, 0.85f);
        drawRect(cx - w * 0.5f, bottomY - h, w, h);
    }

    // =========================================================
    // Challenge:
    //   The two rounded rectangles below use EaseType::Linear.
    //   Change them to a different easing to make the motion
    //   feel like a slick UI transition!
    //
    //   Find the challengeT lines in keyPressed() and
    //   just swap EaseType::Linear for something else!
    //   e.g.: Cubic, Back, Elastic, Bounce, Quint ...
    // =========================================================
    {
        float t = challengeT.getValue();

        float centerX = 480;
        float leftX = centerX - 100;
        float rightX = centerX + 100;
        float fullW = 100, fullH = 130;
        float halfW = fullW/2, halfH = fullH/2;
        float cy = 440;
        float corner = 8;

        // Rect A: center <-> left
        float ax = lerp(centerX, leftX, t);
        float aw = lerp(fullW, halfW, t);
        float ah = lerp(fullH, halfH, t);

        // Rect B: right <-> center
        float bx = lerp(rightX, centerX, t);
        float bw = lerp(halfW, fullW, t);
        float bh = lerp(halfH, fullH, t);

        setColor(0.3f, 0.6f, 1.0f);
        drawRectRounded(ax - aw * 0.5f, cy - ah * 0.5f, aw, ah, corner);

        setColor(1.0f, 0.4f, 0.5f);
        drawRectRounded(bx - bw * 0.5f, cy - bh * 0.5f, bw, bh, corner);
    }

    // instruction
    setColor(0.4f);
    drawBitmapString("space: toggle", 20, 580);
}

void tcApp::keyPressed(int key) {
    if (key == ' ') {
        toggled = !toggled;

        if (toggled) {
            flipTween.from(0).to(TAU * 0.5f)
                .duration(0.8f).ease(EaseType::Back, EaseMode::InOut).start();
            meterTween.from(0).to(TAU)
                .duration(1.0f).ease(EaseType::Quint, EaseMode::InOut).start();
            tofuTween.from(0).to(1)
                .duration(1.0f).ease(EaseType::Elastic, EaseMode::Out).start();

            // ↓ Challenge: try changing EaseType::Linear, InOut to something else!
            challengeT.from(0).to(1)
                .duration(0.8f).ease(EaseType::Linear, EaseMode::InOut).start();
        } else {
            flipTween.from(TAU * 0.5f).to(0)
                .duration(0.8f).ease(EaseType::Back, EaseMode::InOut).start();
            meterTween.from(TAU).to(0)
                .duration(1.0f).ease(EaseType::Quint, EaseMode::InOut).start();
            tofuTween.from(1).to(0)
                .duration(1.0f).ease(EaseType::Elastic, EaseMode::Out).start();

            // ↓ change this one to the same easing too
            challengeT.from(1).to(0)
                .duration(0.8f).ease(EaseType::Linear, EaseMode::InOut).start();
        }
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
