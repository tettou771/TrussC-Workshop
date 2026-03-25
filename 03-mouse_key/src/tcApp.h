#pragma once

#include <TrussC.h>
using namespace std;
using namespace tc;

class tcApp : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;

    void mousePressed(Vec2 pos, int button) override;
    void mouseReleased(Vec2 pos, int button) override;
    void mouseMoved(Vec2 pos) override;
    void mouseDragged(Vec2 pos, int button) override;
    void mouseScrolled(Vec2 delta) override;

    void windowResized(int width, int height) override;
    void filesDropped(const vector<string>& files) override;
    void exit() override;

    // drawing trail
    struct Point {
        Vec2 pos;
        Color color;
        float size;
    };
    vector<Point> trail;

    // current brush
    Color brushColor = Color(1.0f, 0.5f, 0.2f);
    float brushSize = 8.0f;

    Vec2 mousePos;
    bool mouseDown = false;
};
