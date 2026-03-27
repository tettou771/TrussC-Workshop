#include "tcApp.h"

void tcApp::setup() {

}

void tcApp::update() {

}

void tcApp::draw() {
    clear(0.12f);

    // --- basic shapes ---

    setColor(0.1f, 0.4f, 0.9f);
    drawCircle(120, 150, 60); // circle (x, y, r)
    drawRect(250, 90, 120, 120); // rectangle (x, y, w, h)
    drawLine(450, 90, 570, 210); // line (x1, y1, x2, y2)

    // triangle (x1, y1, x2, y2, x3, y3)
    drawTriangle(650, 90, 580, 210, 720, 210);

    // ellipse (x, y, w, h)
    drawEllipse(840, 150, 50, 80);

    // --- fill / outline only ---

    // filled (default)
    fill();
    setColor(1.0f, 1.0f, 1.0f);
    drawCircle(120, 370, 50);

    // outline only
    noFill();
    drawCircle(260, 370, 50);

    // smoother circle
    setCircleResolution(100);
    drawCircle(400, 370, 50);
    setCircleResolution(20); // default is 20

    // push/pop style
    pushStyle();
    fill();
    setColor(.0f, 1.0f, 1.0f);
    setStrokeWeight(1.0f);
    popStyle();

    // --- color alpha (transparency) ---
    fill();
    setColor(1.0f, 0.3f, 0.3f, 0.7f);
    drawCircle(550, 370, 60);
    setColor(0.3f, 0.3f, 1.0f, 0.7f);
    drawCircle(590, 370, 60);

    // --- rounded rectangle ---
    setColor(0.6f, 0.9f, 0.7f);
    drawRectRounded(720, 320, 140, 100, 20);

    // =========================================================
    // Challenge:
    //   Using the examples above, try drawing a traffic light
    //   in the bottom half of the screen (around y=450)
    //   - Start with a wide rounded rectangle as the base
    //   - Line up red, yellow, and green circles
    //   - Make only the "green" light look like it's glowing
    //     (dim the other two, make green bright + add alpha glow)
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
