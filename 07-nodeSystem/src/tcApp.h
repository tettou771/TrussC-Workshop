#pragma once

#include <TrussC.h>
using namespace std;
using namespace tc;

// =============================================================================
// ClickBox: a colored box that responds to hover and click
// =============================================================================
class ClickBox : public RectNode {
public:
    Color color;
    bool active = false;

    ClickBox(Color c = Color(0.3f, 0.3f, 0.4f)) : color(c) {
        enableEvents();
        setSize(140, 70);
    }

    void draw() override {
        // active = brighter
        Color c = active ? Color(color.r + 0.3f, color.g + 0.3f, color.b + 0.3f) : color;
        setColor(c);
        drawRectRounded(0, 0, getWidth(), getHeight(), 8);

        // hover highlight
        if (isMouseOver()) {
            setColor(1.0f, 1.0f, 1.0f, 0.15f);
            drawRectRounded(0, 0, getWidth(), getHeight(), 8);
        }

        // active indicator
        if (active) {
            setColor(1.0f);
            drawCircle(getWidth() - 15, 15, 5);
        }
    }

protected:
    bool onMousePress(Vec2 local, int button) override {
        (void)local; (void)button;
        active = !active; // toggle on click
        return true;
    }

    bool onMouseRelease(Vec2 local, int button) override {
        (void)local; (void)button;
        return true;
    }
};

// =============================================================================
// Main app
// =============================================================================
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

    // panel (parent) containing boxes (children)
    shared_ptr<RectNode> panel;
    shared_ptr<ClickBox> box1, box2, box3;
};
