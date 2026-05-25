#include "tcApp.h"

// TC_HOT_RELOAD をコメントアウトすると、 ホットリロードが無効化されます
TC_HOT_RELOAD(tcApp)

void tcApp::setup() {
    // TrussC は 3D が最初から有効。 pushMatrix → translate → rotateX/Y/Z → drawBox など、 だけで 3D に入れる。

    // --- DirectionalLight ---
    // 平坦さ回避用。 ライトが当たるには setMaterial() が必要 (setColor だけだと無灯)
    light.setDirectional(Vec3(-0.5f, 1.0f, -0.5f));  // 左上手前から照らす方向
    light.setAmbient(0.25f, 0.25f, 0.30f);            // 影側もうっすら見える程度
    light.setDiffuse(0.90f, 0.90f, 0.85f);
    light.setSpecular(0.7f, 0.7f, 0.7f);
}

void tcApp::update() {
    time += getDeltaTime();
}

void tcApp::draw() {
    clear(0.08f);

    // 画面の中央を原点にして 3D を描く
    // TrussC のデフォルトは Y+ が下、 Z+ が手前。 何もしなければ Z=0 が画面の高さ
    float cx = getWidth()  / 2.0f;
    float cy = getHeight() / 2.0f;

    // --- ライティング有効化 ---
    addLight(light);
    setCameraPosition(cx, cy, 1000);     // specular 計算用にカメラ位置を渡す

    // ---- (1) Box ---- 左、 2 軸回転
    pushMatrix();
    translate(cx - 250, cy, 0);
    rotateY(time * 0.5f);
    rotateX(time * 0.3f);
    Material matBox = Material::plastic(Color(0.95f, 0.55f, 0.3f));
    setMaterial(matBox);
    drawBox(120);                       // 一辺 120 の立方体
    popMatrix();

    // ---- (2) Sphere ---- 中央、 Y 軸だけ回転
    pushMatrix();
    translate(cx, cy, 0);
    rotateY(time);
    Material matSphere = Material::plastic(Color(0.4f, 0.7f, 0.95f));
    setMaterial(matSphere);
    drawSphere(70, 24);                 // 半径 70、 分割 24 (= なめらか)
    popMatrix();

    // ---- (3) Cone ---- 右、 wireframe で (wireframe にはライト効かない)
    clearMaterial();
    pushMatrix();
    translate(cx + 250, cy, 0);
    rotateY(time * 0.7f);
    rotateZ(time * 0.4f);
    noFill();                            // ← fill 無効 = wireframe で描画される
    setStrokeWeight(1.5f);
    setColor(0.95f, 0.45f, 0.7f);
    drawCone(60, 130, 24);              // 底面半径 60、 高さ 130
    fill();
    popMatrix();

    // ---- (4) 軌道上の小さな立方体達 (中央の sphere の周りを回る) ----
    // lesson 2 の "orbit on orbit" を 3D に拡張したパターン
    pushMatrix();
    translate(cx, cy, 0);
    rotateY(time * 0.6f);
    Material matOrbit = Material::plastic(Color(0.9f, 0.9f, 0.9f));
    setMaterial(matOrbit);
    int n = 12;
    for (int i = 0; i < n; i++) {
        float a = TAU * i / n;
        float r = 180;
        Vec3 p(cos(a) * r, sin(a * 2 + time) * 30, sin(a) * r);  // XZ 平面で円、 Y もちょっと揺らす
        drawBox(p, 18);
    }
    popMatrix();

    // --- ライティング終了 ---
    clearMaterial();
    clearLights();

    // ---- 2D オーバーレイ (3D 描画後の 2D も普通に描ける) ----
    setColor(0.55f);
    drawBitmapString("3D  -  drawBox / drawSphere / drawCone  +  translate / rotateX/Y/Z", 20, 30);
    setColor(0.4f);
    drawBitmapString("Box (fill)              Sphere (fill)              Cone (wireframe)", 60, getHeight() - 40);

    // =========================================================
    // チャレンジ:
    //   1. drawBox / drawSphere / drawCone を入れ替えてみよう
    //   2. translate の Z を時間で揺らして「奥から手前」 に動かす
    //        translate(cx, cy, sin(time) * 200);
    //   3. 軌道 (4) の n や r を変えて密度・大きさを調整
    //   4. drawSphere の分割数を 4 にしてみる (ローポリ多面体になる)
    //   5. EasyCam を使えばマウスでぐりぐり視点が回せる:
    //        tcApp.h に EasyCam cam; を追加 → setup() で cam.enableMouseInput()
    //        → draw() の最初に cam.begin(); 最後に cam.end();
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
