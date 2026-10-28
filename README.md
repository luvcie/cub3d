*This project has been created as part of the 42 curriculum by lucpardo, pramos-c.*

# cub3D

A raycaster inspired by Wolfenstein 3D, built on SDL2 through a MiniLibX-style API.

![42 Project](https://img.shields.io/badge/42-Project-blue)

## Description

cub3D renders a textured 3D view of a maze described by a `.cub` scene file.
The file declares the four wall textures, the floor and ceiling colors, and a
2D grid that defines the level layout and the player spawn. The player walks
through the level in first person using the keyboard and mouse, while the
engine casts one ray per screen column in real time to draw the textured
walls together with the ceiling and floor. The goal of the project is to
explore the fundamentals of raycasting, texture mapping, and real time
graphics programming in C.

## Instructions

### Requirements

Linux (tested on Ubuntu, Fedora, and NixOS), a C compiler, GNU make, the SDL2
development files, and pkg-config. The code is compiled as C2y (`-std=c2y`), so
use a recent GCC or Clang.

On Debian or Ubuntu:

```bash
sudo apt install libsdl2-dev pkg-config
```

On Fedora:

```bash
sudo dnf install SDL2-devel pkgconf-pkg-config
```

On NixOS, the dependencies are in `shell.nix`.

### Build

```bash
make         # build cub3D
make clean   # remove object files
make fclean  # remove object files and the executable
make re      # fclean followed by make
```

On NixOS, run the build inside the shell:

```bash
nix-shell --run make
```

### Run

The program expects exactly one argument, a path to a `.cub` scene file:

```bash
./cub3D maps/test.cub
```

Example maps are available in `maps/` (`test.cub`, `corridor.cub`, `maze.cub`,
`pillars.cub`, `test_big.cub`).

### Scene file format

A `.cub` file contains two blocks. First the configuration identifiers, in any
order:

| Identifier | Meaning |
|------------|---------|
| `NO <path>` | North wall texture (`.xpm`) |
| `SO <path>` | South wall texture (`.xpm`) |
| `WE <path>` | West wall texture (`.xpm`) |
| `EA <path>` | East wall texture (`.xpm`) |
| `F R,G,B`   | Floor color (each channel in `0` to `255`) |
| `C R,G,B`   | Ceiling color (each channel in `0` to `255`) |

Then the 2D grid, where `1` is a wall, `0` is walkable floor, and one of
`N`, `S`, `E`, `W` marks the player spawn and initial facing direction. The
map must be fully closed by walls.

Example:

```
NO ./textures/XPMs/north.xpm
SO ./textures/XPMs/south.xpm
WE ./textures/XPMs/west.xpm
EA ./textures/XPMs/east.xpm

F 220,100,0
C 225,30,0

111111
100101
100001
1100N1
111111
```

## Browser build

The game also builds to WebAssembly with Emscripten. Both builds use the same game sources and the same SDL2 backend in `mlx_sdl/`.

On NixOS:

```bash
nix-shell -p emscripten python3 gnumake --run 'export EM_CACHE=$HOME/.cache/emscripten; make -C web wasm'
nix-shell -p python3 --run 'make -C web serve'
```

Then open http://localhost:8000. The first build takes a few minutes because emcc builds its libraries into `EM_CACHE`.

Pick a map with `?map=<name>`, e.g. `http://localhost:8000/?map=maze`. The default is `pillars`. Available maps are `corridor`, `maze`, `pillars`, `test` and `test_big`. Only lowercase letters and `_` are accepted; anything else falls back to `pillars`. To add a map, drop a `.cub` file in `maps/` and rebuild, since the folder is preloaded into the wasm bundle.

The output is four files in `web/dist/`: `index.html`, `index.js`, `index.wasm` and `index.data`. Serve them from any static host, or embed `index.html` in an `<iframe>`.

In the browser:

- ESC does nothing in the browser. The native ESC handler calls `exit()`, which would stop the page.
- `mlx_get_screen_size` reports 1280x720, so key `6` picks that size.
- Mouse look only works while the cursor is over the canvas.

## Features

- Textured walls (XPM format)
- Floor and ceiling colors from map config
- Smooth movement with delta time
- Mouse look
- Minimap with ray visualization (toggle: `M`, `R`)
- Dynamic resolution switching (keys `1` to `6`)
- Subpixel edge blending (wall antialiasing)
- Collision detection with wall sliding

## Rendering

**Raycasting algorithm:** Supercover Bresenham grid traversal with fixed point arithmetic

**Optimizations:**
- Branchless step selection via arithmetic (`go_x = err < 0`)
- Corner tolerance check prevents rays clipping through diagonal walls
- Integer error accumulator instead of floating point DDA

## Controls

| Key | Action |
|-----|--------|
| `WASD` | Move |
| `←` `→` / Mouse | Look |
| `M` | Toggle minimap |
| `R` | Toggle ray debug |
| `H` | Help menu |
| `1` to `6` | Resolution presets |
| `ESC` | Quit (native only) |

## Resources

- Lode Vandevenne, *Raycasting Tutorial*: https://lodev.org/cgtutor/raycasting.html
- Permadi, *Raycasting Tutorial*: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
- Fabien Sanglard, *Game Engine Black Book: Wolfenstein 3D*: https://fabiensanglard.net/gebbwolf3d/
- miniLibX documentation and examples

AI was used as a learning aid to understand the math behind the raycasting
engine (Bresenham supercover traversal, camera plane projection, fisheye
correction) and the miniLibX image and event API. All project code was written
and reviewed by the authors.

***

Made with [Jujutsu](https://github.com/jj-vcs/jj)
