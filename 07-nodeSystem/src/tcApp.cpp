#include "tcApp.h"

void tcApp::setup() {
    // --- RectNode: UI 구성 요소 ---
    // RectNode = 위치, 크기, 회전을 가진 사각형
    // addChild()로 부모-자식 관계를 만듦
    // 자식은 로컬 좌표를 사용 (0,0 = 부모의 좌상단)
    // 부모가 움직이면 자식도 자동으로 따라옴

    // --- 패널 (부모) ---
    panel = make_shared<RectNode>();
    panel->enableEvents();
    panel->setPos(180, 120);
    panel->setSize(600, 350);
    addChild(panel);

    // --- 박스 (패널의 자식) ---
    // 위치는 화면이 아닌 패널 기준의 상대 좌표!
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

    // --- 패널 배경 그리기 ---
    // Node의 자식은 TrussC가 자동으로 그려줌.
    // 하지만 패널 배경은 여기 app의 draw에서 그림.
    // RectNode 자체는 보이지 않으니까 (그냥 컨테이너).
    // 패널의 draw를 오버라이드할 수도 있지만, 간단하게
    // 패널의 위치/크기를 가져와서 앱에서 그리는 방식.

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
    // 챌린지:
    //   box 아래에 자식 박스를 하나 더 추가해보자
    //   - 새로운 ClickBox를 만들고
    //   - box1->addChild(newBox)로 box1의 자식으로 설정
    //   - setPos는 box1 안에서의 로컬 좌표
    //   - box1이 움직이면 newBox도 따라옴
    //
    //   추가로: 두 번째 패널을 만들어보자
    //   - panel2 = make_shared<RectNode>()
    //   - addChild(panel2)로 app에 추가
    //   - 다른 위치에 새로운 박스를 배치
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
