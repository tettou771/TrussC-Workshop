#pragma once

#include <TrussC.h>
#include "ClickBox.h"
#include "Panel.h"
using namespace std;
using namespace tc;

// =============================================================================
// tcApp
//   このサンプルでは UI 部品を 「1 クラス = 1 ファイルペア (.h / .cpp)」
//   で分けている。 ClickBox は ClickBox.h / ClickBox.cpp、 Panel は Panel.h
//   / Panel.cpp。 tcApp はそれらを 「組み立てて配置するだけ」 に専念。
//   コードが短くてもファイル分けする — これが Node ベースのコーディング流儀。
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

private:
    shared_ptr<Panel>    panel;
    shared_ptr<ClickBox> box1, box2, box3;
};
