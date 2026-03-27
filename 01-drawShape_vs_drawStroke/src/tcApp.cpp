#include "tcApp.h"

void tcApp::setup() {

}

void tcApp::update() {

}

void tcApp::draw() {
    clear(0.12f);

    // --- drawLine vs drawStroke ---
    // drawLine is always 1px. strokeWeight has no effect on it.
    setColor(0.5f, 0.5f, 0.5f);
    setStrokeWeight(20.0f);
    drawLine(60, 60, 300, 60);

    // drawStroke respects strokeWeight for thick lines
    setColor(1.0f, 0.7f, 0.2f);
    drawStroke(60, 120, 300, 120);

    // --- StrokeCap types ---
    // Butt: cuts off exactly at the endpoint
    setStrokeCap(StrokeCap::Butt);
    setColor(0.3f, 0.8f, 1.0f);
    drawStroke(60, 200, 250, 200);

    // Round: adds a semicircle at each endpoint
    setStrokeCap(StrokeCap::Round);
    drawStroke(60, 250, 250, 250);

    // Square: extends by half the stroke width
    setStrokeCap(StrokeCap::Square);
    drawStroke(60, 300, 250, 300);

    // --- beginStroke / endStroke for freeform paths ---
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

    // close = true to make a closed path
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

    // --- comparing noFill shapes with strokes ---
    // noFill + drawCircle gives a uniform outline
    setColor(1.0f, 1.0f, 1.0f);
    noFill();
    drawCircle(150, 470, 60);

    // a circle drawn with beginStroke + close has Cap/Join effects
    // TAU = 2pi = one full turn (TrussC uses TAU instead of PI)
    // TAU * 0.25 = 90deg, TAU * 0.5 = 180deg, TAU = 360deg
    setColor(1.0f, 1.0f, 1.0f);
    setStrokeWeight(2.0f);
    int n = 40;
    beginStroke();
    for (int i = 0; i < n; i++) {
        float angle = TAU * i / n; // divide 0..TAU into n parts
        vertex(400 + cos(angle) * 60, 470 + sin(angle) * 60);
    }
    endStroke(true);

    // =========================================================
    // Challenge:
    //   Use beginStroke to draw a hand-drawn style star
    //   (pentagram) in a single stroke
    //   Hints:
    //   - Connect 5 points by skipping one each time to make a star
    //   - Points on a circle come from cos/sin (see example above)
    //   - TAU * i / 5 gives pentagon vertices; visit them in order
    //     0, 2, 4, 1, 3 for a single-stroke star (i.e. i*2 % 5)
    //   - Use endStroke(true) to close the shape
    //   - StrokeJoin::Round / Miter / Bevel changes the look a lot
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
