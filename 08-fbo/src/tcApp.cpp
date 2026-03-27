#include "tcApp.h"

void tcApp::setup() {
    // --- Fbo = offscreen canvas ---
    // allocate(w, h) creates a render texture
    // everything drawn between begin() / end() goes into the texture
    int samples = 4;
    TextureFormat format = TextureFormat::RGBA32F;
    trailFbo.allocate(960, 600, samples, format);
    trailFbo.begin(0, 0, 0, 1);
    trailFbo.end();

    // --- stamp: draw once in setup, reuse as many times as you want ---
    stampFbo.allocate(100, 100);
    stampFbo.begin(0, 0, 0, 0); // transparent background
    int n = 6;
    for (int i = 0; i < n; i++) {
        float angle = TAU * i / n;
        setColor(Color::fromHSB((float)i / n, 0.7f, 0.9f));
        drawCircle(50 + cos(angle) * 30, 50 + sin(angle) * 30, 12);
    }
    setColor(1.0f, 0.9f, 0.3f);
    drawCircle(50, 50, 10);
    stampFbo.end();
}

void tcApp::update() {
    time += getDeltaTime();
}

void tcApp::draw() {
    clear(0.12f);

    // --- trail: begin() preserves previous content ---
    trailFbo.begin();

    // fade previous content
    setColor(0, 0.03f);
    drawRect(0, 0, 960, 600);

    // draw moving circle
    float cx = 480 + cos(time * 1.5f) * 200;
    float cy = 300 + sin(time * 2.3f) * 150;
    setColor(0.3f, 0.8f, 1.0f);
    drawCircle(cx, cy, 10);

    trailFbo.end();

    // draw trail to screen
    setColor(1.0f);
    trailFbo.draw(0, 0);

    // draw stamp preview (bottom-right corner)
    setColor(1.0f);
    stampFbo.draw(840, 500, 80, 80);

    setColor(0.5f);
    drawBitmapString("[c] clear trail", 20, 580);

    // =========================================================
    // Challenge:
    //   Stamp the stampFbo wherever you click!
    //   Draw it inside trailFbo so it stays with the trail effect!
    //
    //   Hint:
    //   In mousePressed(), wrap stampFbo.draw() with trailFbo.begin/end
    //
    //   The stamps will slowly fade away with the trail
    // =========================================================
}

void tcApp::keyPressed(int key) {
    if (key == 'c' || key == 'C') {
        trailFbo.begin(0, 0, 0, 1);
        trailFbo.end();
    }
}
void tcApp::keyReleased(int key) {}

void tcApp::mousePressed(Vec2 pos, int button) {

}

void tcApp::mouseReleased(Vec2 pos, int button) {}
void tcApp::mouseMoved(Vec2 pos) {}
void tcApp::mouseDragged(Vec2 pos, int button) {}
void tcApp::mouseScrolled(Vec2 delta) {}

void tcApp::windowResized(int width, int height) {}
void tcApp::filesDropped(const vector<string>& files) {}
void tcApp::exit() {}
