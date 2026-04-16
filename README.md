*This project has been created as part of the 42 curriculum by lucpardo, pramos-c.*

# cub3D

A raycaster inspired by Wolfenstein 3D, built with the miniLibX library.

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

Linux (tested on Ubuntu, Fedora, and NixOS), a C compiler, GNU make, and the
X11 development libraries (`libX11`, `libXext`) along with the math library.
miniLibX is cloned and built automatically by the Makefile.

On Fedora, the required development packages can be installed with:

```bash
sudo dnf install libX11-devel libXext-devel mesa-libGL-devel
```

On NixOS, the Makefile runs `.patch_minilibx.sh` to fix up the miniLibX
include paths so they point at the Nix store. It only runs on Nix systems.

### Build

```bash
make         # build cub3D
make clean   # remove object files
make fclean  # remove object files and the executable
make re      # fclean followed by make
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
| `ESC` | Quit |

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
