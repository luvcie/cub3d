# cub3D

A raycaster inspired by Wolfenstein 3D, built with the miniLibX library.

![42 Project](https://img.shields.io/badge/42-Project-blue)

## Features

- Textured walls (XPM format)
- Floor and ceiling colors from map config
- Smooth movement with delta-time
- Mouse look
- Minimap with ray visualization (toggle: `M`, `R`)
- Dynamic resolution switching (keys `1-6`)
- Sub-pixel edge blending (wall antialiasing)
- Collision detection with wall sliding

## Rendering

**Raycasting algorithm:** Supercover Bresenham grid traversal with fixed-point arithmetic

**Optimizations:**
- Branchless step selection via arithmetic (`go_x = err < 0`)
- Corner tolerance check prevents rays clipping through diagonal walls
- Integer error accumulator instead of floating-point DDA

## Build & Run

```bash
make
./cub3D maps/test.cub
```

## Controls

| Key | Action |
|-----|--------|
| `WASD` | Move |
| `←` `→` / Mouse | Look |
| `M` | Toggle minimap |
| `R` | Toggle ray debug |
| `H` | Help menu |
| `1-6` | Resolution presets |
| `ESC` | Quit |

---

Made with [Jujutsu](https://github.com/jj-vcs/jj)
