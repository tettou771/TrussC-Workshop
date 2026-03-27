#include "tcApp.h"

void tcApp::setup() {
    // --- RectNode: UI building block ---
    // RectNode = rectangle with position, size, rotation
    // addChild() creates parent-child relationship
    // Children use LOCAL coordinates (0,0 = parent's top-left)
    // When parent moves, children follow automatically

    // --- panel (parent) ---
    panel = make_shared<RectNode>();
    panel->enableEvents();
    panel->setPos(180, 120);
    panel->setSize(600, 350);
    addChild(panel);

    // --- boxes (children of panel) ---
    // position is relative to panel, not to screen!
    box1 = make_shared<ClickBox>(Color(0.5f, 0.2f, 0.2f));
    box1->setPos(30, 80);
    panel->addChild(box1);

    box2 = make_shared<ClickBox>(Color(0.2f, 0.5f, 0.2f));
    box2->setPos(200, 80);
    panel->addChild(box2);

    box3 = make_shared<ClickBox>(Color(0.2f, 0.2f, 0.5f));
    box3->setPos(370, 80);
    panel->addChild(box3);
}

void tcApp::update() {
}

void tcApp::draw() {
    clear(0.12f);

    // --- draw panel background ---
    // Node children are drawn automatically by TrussC.
    // But we draw the panel background here in the app's draw,
    // because RectNode itself is invisible (just a container).
    // The panel's draw could be overridden too, but for simplicity
    // we draw it from the app using the panel's position/size.

    // panel background
    float px = panel->getPos().x;
    float py = panel->getPos().y;
    float pw = panel->getWidth();
    float ph = panel->getHeight();

    setColor(0.18f);
    drawRectRounded(px, py, pw, ph, 12);
    noFill();
    setColor(0.3f);
    drawRectRounded(px, py, pw, ph, 12);
    fill();

    // panel title
    setColor(0.7f);
    drawBitmapString("Panel", px + 20, py + 25);
    setColor(0.4f);
    drawBitmapString("arrow keys to move", px + 80, py + 25);

    // box labels (drawn relative to panel for clarity)
    setColor(0.5f);
    drawBitmapString("click to toggle", px + 30, py + 170);

    // --- info ---
    setColor(0.6f);
    drawBitmapString("RectNode Parent-Child Demo", 20, 30);
    drawBitmapString("Panel position: (" + to_string((int)px) + ", " + to_string((int)py) + ")", 20, 50);
    drawBitmapString("Boxes use LOCAL coords (relative to panel)", 20, 65);
    drawBitmapString("Move panel with arrow keys -> boxes follow!", 20, 80);

    // =========================================================
    // Challenge:
    //   Add another level of child boxes below the existing ones!
    //   - Create a new ClickBox
    //   - box1->addChild(newBox) to make it a child of box1
    //   - setPos uses local coords within box1
    //   - When box1 moves, newBox follows along
    //
    //   Bonus: try creating a second panel!
    //   - panel2 = make_shared<RectNode>()
    //   - addChild(panel2) to add it to the app
    //   - Place new boxes at a different position
    // =========================================================

    setColor(0.4f);
    drawBitmapString("RectNode: enableEvents / addChild / local coords / hover & click", 20, 580);
}

void tcApp::keyPressed(int key) {
    // move panel with arrow keys
    float step = 10;
    float px = panel->getPos().x;
    float py = panel->getPos().y;
    if (key == SAPP_KEYCODE_LEFT)  px -= step;
    if (key == SAPP_KEYCODE_RIGHT) px += step;
    if (key == SAPP_KEYCODE_UP)    py -= step;
    if (key == SAPP_KEYCODE_DOWN)  py += step;
    panel->setPos(px, py);
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
