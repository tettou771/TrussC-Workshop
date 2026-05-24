#include "tcApp.h"

// TC_HOT_RELOAD をコメントアウトすると、 ホットリロードが無効化されます
TC_HOT_RELOAD(tcApp)

void tcApp::setup() {
    // --- Panel を作って app の子にする ---
    panel = make_shared<Panel>("Panel  (arrow keys to move)");
    panel->setPos(180, 120);
    addChild(panel);

    // --- ClickBox を 3 つ、 panel の子にする ---
    // 座標は panel から見た「ローカル座標」。 panel が動くと box もついてくる。
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

    // tcApp 自身の draw は背景クリアと「画面外の情報表示」 だけ。
    // Panel と ClickBox は自分の draw() を持っているので、 ここで描く必要はない。
    setColor(0.6f);
    drawBitmapString("Node System  —  one class per file (.h / .cpp)", 20, 30);

    setColor(0.45f);
    drawBitmapString("Panel:    Panel.h / Panel.cpp", 20, 55);
    drawBitmapString("ClickBox: ClickBox.h / ClickBox.cpp", 20, 70);
    drawBitmapString("tcApp:    tcApp.h / tcApp.cpp  (assemble & arrange only)", 20, 85);

    Vec3 p = panel->getPos();
    drawBitmapString("Panel position: (" + to_string((int)p.x) + ", " + to_string((int)p.y) + ")", 20, 115);

    setColor(0.5f);
    drawBitmapString("click each box to toggle    arrow keys move the whole panel", 20, 560);

    // =========================================================
    // チャレンジ:
    //   ★ 新しい class を作って Node ファミリーに加えてみよう
    //   - 例: ClickBox を継承して「クリック数を表示する CounterBox」
    //   - 例: 自分の振る舞いを持つ「RoundButton」 や「Slider」
    //
    //   手順:
    //     1. src/Foo.h を作って class Foo : public RectNode を宣言
    //     2. src/Foo.cpp を作って draw() / onMousePress() を実装
    //     3. tcApp.h で #include "Foo.h"
    //     4. tcApp::setup() で make_shared<Foo>() → panel->addChild(...)
    //
    //   CMakeLists は触らなくて OK (src/ の .cpp / .h は自動で拾われる)
    //
    //   小さくてもファイル分けるのが流儀。
    //   「中身が 30 行しかないから 1 ファイルにまとめる」 をしないこと。
    //   class が育った時に分け直すコストを払うより、 最初から分けておく。
    // =========================================================
}

void tcApp::keyPressed(int key) {
    // panel を矢印キーで動かす。 子の box は自動的についてくる。
    Vec3 p = panel->getPos();
    float step = 10;
    if (key == SAPP_KEYCODE_LEFT)  p.x -= step;
    if (key == SAPP_KEYCODE_RIGHT) p.x += step;
    if (key == SAPP_KEYCODE_UP)    p.y -= step;
    if (key == SAPP_KEYCODE_DOWN)  p.y += step;
    panel->setPos(p);
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
