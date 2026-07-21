# TrussC Workshop (IAMAS version)

TrussC のワークショップ用サンプル。 当日触る **6 レッスン** + 持ち帰り用の **4 サンプル (Extra)** 構成。

まずは実行してみて（VSCode などは F5）、 画面を見たあとに `src/tcApp.h`, `src/tcApp.cpp` を眺めてみてください。 「なるほどね」 と思ったら ★ チャレンジに挑戦してみる、 という流れです。

チャレンジには正解がありません。 思った通りに動いたら OK です。

## サンプル一覧

### 必修 (時間がなくてもここまでは触ろう)

#### `0-graphics`
基本図形 (circle / rect / line / triangle / ellipse / arc / rectRounded) と、 fill / noFill / alpha、 太いストローク (`drawStroke`, StrokeCap)、 自由なパス (`beginStroke` + `vertex`) を一気に紹介します。 同じ頂点でも `beginStroke` (輪郭) と `beginShape` (塗り) で見え方が変わる、 という対比に注目。

**★ チャレンジ (軽め):** (4) の多角形を、 StrokeWeight・StrokeJoin・色・角の数 (n) を変えて遊んでみる。 数字を書き換えるだけ。

#### `1-mouseKey`
マウスのドラッグで線を引く、 キーで色 (1-5) と太さ (UP/DOWN) を変える、 `c` でクリア。 大文字でハンドリング (`if (key == 'C')`) する点だけ注意。

**★ チャレンジ:** 右クリックドラッグで「対称描画」 モードにしてみよう。 `mouseDragged` の第2引数 `button` (0=左 / 1=右) と、 `getWidth()` を使って画面の反対側に点を足す。

#### `2-mathGenerative`
クリエイティブコーディングの本丸。 sin / cos で波・リサジュー・orbit on orbit、 noise で滑らかなランダム、 random で固定パターン。 全ブロックが `pushMatrix` + `translate` ベースで書かれているので「**ここの数字をいじる**」 が直感的。

**★ チャレンジ (軽め):** Lissajous の (3, 2) / orbit の (1.0, 3.2) / noise の zoom / sin の重ね合わせ、 数字を変えて模様の変化を楽しむ。

### オプション (時間と気分があれば)

#### `3-tween`
SPACE で動きが切り替わる UI 風アニメ。 コイン反転 (Back)、 メーター (Quint)、 豆腐 (Elastic)、 そして「ちょうどいい気持ちよさ」 が EaseType でどう変わるかを比較。 TrussC は ofxTween のような addon を入れなくても easing が内蔵されてる。

**★ チャレンジ:** 下半分の Linear イージングを Cubic / Back / Elastic / Bounce などに変えて、 一番気持ちいいやつを探す。

#### `4-nodeSystem`
TrussC の特徴のひとつ、 シーングラフ。 親パネルの中に子ボックスをぶら下げると、 親が動くと子もついてくる。 ローカル座標、 `enableEvents()` でホバー&クリック、 矢印キーで親を動かす。

**★ チャレンジ:** ボックスの下にさらに子ボックスを追加してみる。 または 2 つ目のパネルを作ってみる。

#### `5-sound`
3 つの音の入口。 `beep()` (1 行で UI 効果音)、 ChipSound (波形 + 周波数 + 長さで自作する旋律)、 そして音源ファイルの再生 (loop / pan / speed をキーで調整)。

**★ チャレンジ:** ChipSound の旋律 (notes 配列、 wave、 duration) を変える / マウスクリックで音程を変える / `music.setSpeed` を tween で滑らかに動かす — 自分で組み合わせる。

### Extra (持ち帰り用 — 当日は触らない予定。 家でいじってみてね)

ここから先はワークショップでは扱わないけど、 「TrussC でこんなこともできる」 を見せるためのサンプル群。

#### `6-fbo`
オフスクリーン描画 (`Fbo`)。 `begin()` / `end()` で囲った範囲がテクスチャに描かれる。 trail (前フレームを薄く残す) と stamp (一度だけ描いたパターンを何度も使う) の組み合わせで光跡を作る定番テクニック。

#### `7-image`
ピクセル単位のテクスチャ操作。 `allocate` / `setColor` / `getColor` / `update` / `draw`。 16x16 の小さな画像を時間で更新するアニメーション。 ドット絵やイメージプロセシングの入口。

#### `8-3d`
3D プリミティブ (`drawBox` / `drawSphere` / `drawCone`) と `translate` / `rotateX/Y/Z`。 DirectionalLight で陰影を付けて立体感を出す。 中央の球の周りを軌道周回する小さな立方体達は、 2-mathGenerative の "orbit on orbit" を 3D に拡張したもの。

#### `9-fft`
マイク入力 → FFT → 動く形状。 Autechre "Gantz Graf" オマージュの白黒ショーケース。 低域でアイコスフィアが膨張、 周囲のスパイクが各周波数バンドの強度を表す、 バス hit で画面反転 (FBO + Subtract blend)。 起動したらスピーカーで何か鳴らしてマイクに聞かせて。

## 操作・実行のヒント

- **ビルド & 実行:** VSCode で F5。 コマンドラインなら各レッスンのフォルダで `t run` (TrussC CLI)
- **大文字に注意:** key イベントは大文字 ('C' / 'P' など) でくる
- **TAU:** TrussC は `PI` ではなく `TAU = 2π` を基準に使う。 全周 = TAU、 半周 = TAU/2、 直角 = TAU/4
- **色:** RGB は 0.0〜1.0 の float
