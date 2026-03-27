# TrussC Workshop

This is sample code for the TrussC workshop.

Each project covers a different topic, with usage examples and a "Challenge" section at the end of the source code.

Start by running the project (F5 in VSCode, etc.), see what it does, and then take a look at tcApp.h and tcApp.cpp. Once it clicks, try tackling the challenge!

There's no single correct answer for the challenges -- if it works the way you intended, you're good.

## Samples

### 00-basicGraphics

Basic shape drawing. Lines, circles, rectangles, triangles, and more.

### 01-drawShape_vs_drawStroke

In Processing, you can put caps on thick strokes to round the ends, or bevel the corners of polylines. openFrameworks couldn't do that, which was annoying, so I made an addon called ofxStroke.

TrussC has this built in, so expressive line drawing is a lot easier out of the box.

### 02-tween

Smooth acceleration and deceleration for animations.

Even a plain rectangle can look like wobbly tofu, or give your UI that satisfying snap -- motion matters a lot. Tweening usually requires an external addon, so TrussC includes it natively.

### 03-mouse_key

How to handle mouse and key events.

Pretty straightforward, so a quick skim should be enough. One thing to note: key events use uppercase letters. For example: `if (key == 'C')`.

### 04-transform

Translating, rotating, and scaling coordinates.

If you've used oF or Processing, you're probably already familiar with pushMatrix() and popMatrix().

### 05-mathGenerative

Generative graphics using sin, cos, and noise.

Drawing waves, Lissajous curves, organic noise-driven motion -- this is the good stuff in creative coding.

### 06-imageTexture

Pixel-level image manipulation.

Allocate an Image, write pixels with setColor, upload to the GPU with update, and display with draw. Once you've got this flow down, you can do procedural textures and real-time image processing.

### 07-nodeSystem

Parent-child relationships using RectNode.

Add a child to a parent with addChild, and when the parent moves, the children follow. Everything is drawn in local coordinates, which is great for building UI panels and buttons. Call enableEvents() to get mouse hover and click events.

### 08-fbo

FBO (offscreen rendering) sample.

Everything drawn between begin() and end() becomes a texture. Note that TextureFormat uses different enum values than oF -- keep that in mind.

### 09-sound

beep() and ChipSound sample.

beep() is a built-in preset sound, handy for debug feedback and UI sounds. ChipSound lets you build your own sounds by specifying waveform, frequency, and duration. Easy to make retro NES-style sound effects.
