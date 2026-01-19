*This project has been created as part of the 42 curriculum by ekibar, azorlutu.*

## Description

**cub3D** is a 3D graphical representation project inspired by the legendary Wolfenstein 3D, considered the first FPS (First Person Shooter) in video game history. This project implements a ray-casting engine using the miniLibX graphics library to create a dynamic first-person view inside a maze.

The project explores fundamental computer graphics concepts and demonstrates how mathematical principles can be transformed into elegant algorithms for real-time 3D rendering. Through this implementation, we learned to create a pseudo-3D perspective from a 2D map, handle texture mapping, manage user input events, and apply trigonometric functions for realistic graphics rendering.

**Key Learning Objectives:**
- Understanding and implementing the raycasting algorithm for 3D perspective rendering
- Texture mapping techniques with directional wall textures
- Event-driven programming and game loop architecture
- Mathematical transformations using rotation matrices and vector operations
- Memory management and resource cleanup in C
- Map parsing and validation using flood fill algorithms

## Instructions

### Prerequisites

- **Operating System:** Linux
- **Compiler:** GCC with C99 standard support
- **Required Libraries:**
  - libft
  - miniLibX (MiniLibX-Linux)
  - X11 libraries (libXext, libX11)
  - Math library (libm)

### Compilation

Clone the repository and compile the project:

```bash
git clone git@vogsphere.42istanbul.com.tr:vogsphere/intra-uuid-9631a608-a1f2-4dc5-ab57-f14123c41e8e-7175891-azorlutu.git cub3D
cd cub3D
make
```

The compilation will:
- Build the custom libft library
- Compile all source files with `-Wall -Wextra -Werror` flags
- Link with miniLibX and required system libraries
- Generate the `cub3D` executable

**Makefile Rules:**
- `make` or `make all` - Compile the entire project
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Recompile the project from scratch

### Usage

Run the program with a valid `.cub` scene description file:

```bash
./cub3D maps/valid/subject_map.cub
```

**Controls:**

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit program |

**Window Events:**
- Clicking the red cross on the window frame will close the window and exit the program cleanly

### Map File Format

A `.cub` file must contain texture paths, floor/ceiling colors, and a map grid:

**Texture Identifiers:**
```
NO ./path_to_the_north_texture.xpm
SO ./path_to_the_south_texture.xpm
WE ./path_to_the_west_texture.xpm
EA ./path_to_the_east_texture.xpm
```

**Color Identifiers (RGB format, 0-255):**
```
F 220,100,0
C 225,30,0
```

**Map Grid (must be last, surrounded by walls):**
```
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**Map Characters:**
- `0` - Empty space (walkable)
- `1` - Wall
- `N` - Player start position facing North
- `S` - Player start position facing South
- `E` - Player start position facing East
- `W` - Player start position facing West
- ` ` (space) - Void (outside map boundaries)

**Map Rules:**
- The map must be closed/surrounded by walls
- There must be exactly one player spawn point
- Spaces are valid and represent areas outside the playable map
- Each type of element can be separated by one or more empty lines
- Elements can be in any order, but the map must always be last

**Error Handling:**

If any misconfiguration is encountered, the program will exit with "Error" followed by an explicit error message:
- Invalid file format or missing .cub extension
- Missing or duplicate texture paths
- Invalid RGB color values (must be 0-255)
- Invalid map characters
- Open map (not surrounded by walls)
- Missing or multiple player spawn points

## Project Structure

```
cub-42repo/
├── includes/
│   └── cub3d.h              # Main header with structures and function prototypes
├── srcs/
│   ├── main.c               # Program entry point and initialization
│   ├── engine/              # Rendering engine
│   │   ├── raycast_init.c   # Ray initialization and camera calculations
│   │   ├── raycast_dda.c    # DDA algorithm for wall detection
│   │   ├── raycast_project.c # Wall projection and height calculation
│   │   ├── raycast_draw.c   # World rendering and pixel drawing
│   │   ├── render.c         # Main render loop
│   │   ├── textures.c       # Texture loading and sampling
│   │   └── window.c         # Window management and image handling
│   ├── hooks/               # Event handling
│   │   ├── hooks.c          # Key press/release event handlers
│   │   ├── hooks_helpers.c  # Input processing utilities
│   │   ├── move_player.c    # Player movement with collision detection
│   │   ├── rotate_player.c  # Camera rotation using rotation matrices
│   │   └── setup_player_vectors.c # Initial direction vector setup
│   ├── parser/              # Map parsing system
│   │   ├── parser.c         # Main parsing logic and file reading
│   │   ├── parser_utils.c   # String processing utilities
│   │   ├── parse_color.c    # RGB color parsing and validation
│   │   ├── parse_color_utils.c # Color conversion helpers
│   │   ├── parse_textures.c # Texture path parsing and validation
│   │   ├── handle_map_line.c # Map line processing
│   │   ├── finalize_map.c   # Map grid finalization
│   │   ├── flood_fill.c     # Flood fill algorithm for map validation
│   │   ├── duplicate_grid.c # Grid copying for validation
│   │   └── gnl/             # get_next_line implementation
│   └── utils/               # Utility modules
│       ├── init_game.c      # Game initialization
│       ├── error.c          # Error handling and safe exit
│       └── memory.c         # Memory management and cleanup
├── lib/
│   ├── libft/               # Custom C standard library
│   └── minilibx-linux/      # MiniLibX graphics library
├── maps/
│   ├── valid/               # Valid test maps
│   │   ├── subject_map.cub
│   │   ├── square_map.cub
│   │   ├── cheese_maze.cub
│   │   └── ...
│   └── invalid/             # Invalid maps for error testing
│       ├── player_none.cub
│       ├── wall_hole_*.cub
│       └── ...
├── textures/
│   └── basic/               # XPM texture files
│       ├── north.xpm
│       ├── south.xpm
│       ├── east.xpm
│       └── west.xpm
├── Makefile
└── README.md
```

## Algorithm Overview

### Raycasting Technique

Raycasting is a rendering technique that creates a pseudo-3D perspective from a 2D map. For each vertical stripe on the screen, a ray is cast from the player's position, and the algorithm calculates where it intersects with a wall.

**Core Algorithm Steps:**

1. **Ray Generation:** For each screen column (x = 0 to screen width), calculate the ray direction based on the player's viewing direction and camera plane.

2. **DDA (Digital Differential Analyzer):** Step through the map grid efficiently to find the first wall intersection. The algorithm alternates between horizontal and vertical grid lines, always choosing the shortest distance.

3. **Distance Calculation:** Calculate the perpendicular distance to the wall to avoid the fish-eye effect (distortion at screen edges).

4. **Wall Height Projection:** Compute the wall height based on the distance - closer walls appear taller, creating the illusion of depth.

5. **Texture Mapping:** Determine which texture to use (North, South, East, or West) and map it onto the wall stripe by calculating texture coordinates.

6. **Rendering:** Draw the textured wall stripe to the screen buffer, along with floor and ceiling colors.

**Mathematical Foundation:**

The ray direction is calculated using:
```
ray_dir = dir + plane * camera_x
```
where `camera_x` ranges from -1 (left edge) to +1 (right edge), `dir` is the player's viewing direction, and `plane` is the camera plane vector that determines the field of view.

The perpendicular wall distance prevents fish-eye distortion:
```
perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x  (for X-side hits)
perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y  (for Y-side hits)
```

**Player Movement:**

Movement uses vector mathematics. Forward/backward movement adds/subtracts the direction vector scaled by movement speed. Strafing uses the perpendicular vector (90-degree rotation of the direction vector).

Camera rotation applies a 2D rotation matrix:
```
x' = x * cos(θ) - y * sin(θ)
y' = x * sin(θ) + y * cos(θ)
```
This rotates both the direction vector and camera plane vector by angle θ.

### Flood Fill Map Validation

To verify that the map is properly enclosed by walls, we use a flood fill algorithm starting from the player's position:

1. Create a copy of the map grid
2. Starting from the player position, recursively visit all connected walkable cells
3. Mark visited cells to avoid infinite recursion
4. If we encounter a space character or reach map boundaries, the map is open (invalid)
5. If we successfully fill all reachable areas without errors, the map is valid

This ensures players cannot walk outside the defined playable area.

## Resources

### Documentation & Tutorials

- **Lode's Raycasting Tutorial** - [https://lodev.org/cgtutor/raycasting.html](https://lodev.org/cgtutor/raycasting.html)  
  Comprehensive guide to raycasting with detailed mathematical explanations and code examples. This was the primary reference for understanding the core algorithm.

- **MiniLibX Documentation** - [https://harm-smits.github.io/42docs/libs/minilibx](https://harm-smits.github.io/42docs/libs/minilibx)  
  Documentation for the miniLibX graphics library used in 42 projects.

- **Wolfenstein 3D Source Code** - [https://github.com/id-Software/wolf3d](https://github.com/id-Software/wolf3d)  
  Original source code by id Software, providing insights into classic FPS game architecture.

- **Super Fast Ray Casting in Tiled Worlds using DDA** - [https://www.youtube.com/watch?v=NbSee-XM7WA&t=1420s](https://www.youtube.com/watch?v=NbSee-XM7WA&t=1420s)  
  In this video I look at how the "traditional OLC" method of raycasting in various videos is in fact terrible, and look at the more intelligent DDA algorithm which can significantly (orders of magnitude) be more effective at determining ray length in tile or voxel based worlds.

### Mathematical Concepts

- **Vector Operations:** Addition, subtraction, dot product, and normalization
- **Trigonometry:** Sin, cos, and tan functions for rotation and angle calculations
- **DDA Algorithm:** Digital line drawing algorithm adapted for grid traversal
- **2D Rotation Matrix:** Mathematical transformation for camera rotation
- **Perpendicular Distance:** Projection onto view direction to prevent distortion

### AI Usage

AI tools (Claude, ChatGPT, GitHub Copilot) were used in this project for the following purposes:

**Code Understanding and Learning:**
- Clarifying complex raycasting mathematical formulas and their practical applications
- Understanding the DDA algorithm and how it efficiently traverses grid cells
- Explaining the concept of perpendicular distance vs Euclidean distance
- Learning about 2D rotation matrices and their implementation in C

**Debugging Assistance:**
- Identifying logical errors in wall detection and texture coordinate calculations
- Troubleshooting segmentation faults in map parsing
- Resolving issues with texture mirroring and orientation
- Finding memory leaks and implementing proper cleanup

**Documentation and Comments:**
- Generating detailed code comments explaining algorithm steps
- Creating this README structure and technical explanations
- Formatting mathematical formulas in readable markdown

**Resource Discovery:**
- Finding relevant tutorials and documentation on raycasting
- Locating mathematical reference materials for vector operations
- Discovering best practices for game loop implementation

**Important Note:** All AI-generated code suggestions were thoroughly reviewed, tested, and understood before integration into the project. We ensured full comprehension of every algorithm and implementation detail. The core raycasting engine, DDA algorithm, player movement system, and map parsing logic were developed through manual coding, peer collaboration, and iterative testing. AI served as a learning aid and debugging assistant, not as a primary code generator.

**Map Validation Logic (Flood Fill)**

Our map parser employs a **Flood Fill algorithm** initiated from the player's starting position to validate map closure. 

*   **Reachability Check:** The algorithm verifies that the **playable area** is strictly enclosed by walls. It recursively checks all accessible tiles reachable by the player.

*   **Isolated Areas:** Please note that **unreachable areas** (isolated "islands" of empty space completely surrounded by walls that the player cannot access) are intentionally **not validated**. Since these areas are mathematically invisible to the raycasting engine and inaccessible during gameplay, ignoring them optimizes the parsing process without affecting stability.

We made extensive use of peer learning sessions where we explained our code to each other, which helped identify gaps in understanding that AI tools alone could not address. The project requirements demanded deep understanding for successful peer evaluation, which motivated us to truly comprehend every aspect of the implementation.

---

**Project completed as part of the 42 Istanbul curriculum**

**Authors:**
- Emine Kibar (ekibar)
- Ahmet Tayyip Zorlutuna (azorlutu)
