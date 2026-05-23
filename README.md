# TrussC Workshop (IAMAS version)

TrussC のワークショップ用サンプル。要点を絞った **6 レッスン**構成。

まずは実行してみて（VSCode などは F5）、画面を見たあとに `src/tcApp.h`, `src/tcApp.cpp` を眺めてみてください。「なるほどね」と思ったら ★ チャレンジに挑戦してみる、という流れです。

チャレンジには正解がありません。 思った通りに動いたら OK です。

## サンプル一覧

### 必修 (時間がなくてもここまでは触ろう)

#### `0-graphics`
基本図形 (circle / rect / line / triangle / ellipse / arc / rectRounded) と、 fill / noFill / alpha、 太いストローク (`drawStroke`, StrokeCap)、 自由なパス (`beginStroke` + `vertex`) を一気に紹介します。 同じ頂点でも `beginStroke` (輪郭) と `beginShape` (塗り) で見え方が変わる、という対比に注目。

**★ チャレンジ (軽め):** (4) の多角形を、 StrokeWeight・StrokeJoin・色・角の数 (n) を変えて遊んでみる。 数字を書き換えるだけ。

#### `1-mouseKey`
マウスのドラッグで線を引く、 キーで色 (1-5) と太さ (UP/DOWN) を変える、 `c` でクリア。 大文字でハンドリング (`if (key == 'C')`) する点だけ注意。

**★ チャレンジ:** ドラッグの軌跡が虹色になるように `setColorHSB` を使ってみる。

#### `2-mathGenerative`
クリエイティブコーディングの本丸。 sin / cos で波やリサジュー、 noise で滑らかなランダム、 random で固定パターン。

**★ チャレンジ:** noise を使ったフローフィールドのパーティクルアニメ。 ちょっとボリュームあるので、 時間があるときに。

### オプション (時間と気分があれば)

#### `3-transform`
`pushMatrix` / `popMatrix` の入れ子による translate / rotate / scale。 オレンジの正方形が回転、 緑の円が脈動、 ピンクの花パターン、 時計の針 — 「中心を動かしてから描く」という考え方。

**★ チャレンジ:** 太陽系の公転シミュ。 入れ子を使うと月もカンタンに付けられる。

#### `4-tween`
SPACE で動きが切り替わる UI 風アニメ。 コイン反転 (Back)、 メーター (Quint)、 豆腐 (Elastic)、 そして「ちょうどいい気持ちよさ」が EaseType でどう変わるかを比較。

**★ チャレンジ:** 下半分の Linear イージングを Cubic / Back / Elastic / Bounce などに変えて、 一番気持ちいいやつを探す。

#### `5-nodeSystem`
TrussC の特徴のひとつ、シーングラフ。 親パネルの中に子ボックスをぶら下げると、 親が動くと子もついてくる。 ローカル座標、 `enableEvents()` でホバー&クリック、 矢印キーで親を動かす。

**★ チャレンジ:** ボックスの下にさらに子ボックスを追加してみる。 または 2 つ目のパネルを作ってみる。

## 操作・実行のヒント

- **ビルド & 実行:** VSCode で F5。 コマンドラインなら各レッスンのフォルダで `t run` (TrussC CLI)
- **大文字に注意:** key イベントは大文字 ('C' / 'P' など) でくる
- **TAU:** TrussC は `PI` ではなく `TAU = 2π` を基準に使う。 全周 = TAU、 半周 = TAU/2、 直角 = TAU/4
- **色:** RGB は 0.0〜1.0 の float
