# cub3D
Raycaster built with miniLibX / MLX42

cub3D is a simple 3D raycasting game inspired by classic Wolfenstein-like engines. It uses `libft` for utility functions and `MLX42` (or `miniLibX`) for graphics rendering.

---

## Table of Contents

- Dependencies
- Installation
- Building the Game
- Running the Game
- Troubleshooting
- Supported Platforms

---

## Dependencies

Before building cub3D, make sure the following dependencies are installed on your system.

macOS:

1. Install Xcode Command Line Tools:

`xcode-select --install`

2. Install Homebrew (for MLX42 or GLFW libraries):

`/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`

`brew install glfw glew`

Ubuntu / Linux:

'sudo apt update
sudo apt install build-essential cmake gcc g++ make libx11-dev libxext-dev libbsd-dev libglfw3-dev libglew-dev'

Windows (via WSL2):

1. Install Ubuntu 22.04+ in WSL2.
2. Follow the Linux instructions above.
3. Optionally, install an X server (like VcXsrv) to display the game.

---

## Installation

1. Clone the repository:

`git clone https://github.com/yourusername/cub3D.git`

`cd cub3D`

2. Initialize submodules (if using MLX42 as a submodule):

`git submodule update --init --recursive`

3. Make sure `libft` is present or will be built automatically.

---

## Building the Game

The Makefile handles building `libft`, `MLX42`, and cub3D itself. Run:

`make`

After building, the executable `cub3D` will be created in the project root.

Cleaning build artifacts:

`make clean`
`make fclean`

---

## Running the Game

`./cub3D path/to/your/map.cub`

- Make sure your `.cub` map file follows the expected format.  
- Example maps are included in the `maps/` folder.

---

## Troubleshooting

- libft fails to build: Ensure `gcc` and `make` are installed. On Linux: `sudo apt install build-essential`.
- MLX42 fails to build: Make sure system dependencies are installed (`libx11-dev`, `libxext-dev`, `libbsd-dev`, `libglfw3-dev`, `libglew-dev`).
- `strlcpy` / `strlcat` missing on Linux: Use Linux-compatible versions in `libft`.
- Permission errors: Make sure scripts are executable: `chmod +x ./Makefile`.

---

## Supported Platforms

- macOS (with Xcode CLT and Homebrew libraries)  
- Linux (Ubuntu/Debian recommended)  
- Windows via WSL2 + X server

---

## Notes

- This project uses C11 standards and assumes a POSIX environment.  
- Make sure the Makefile uses tabs for all commands, not spaces.  
- MLX42 is preferred over legacy MiniLibX for cross-platform compatibility.

---

## License

This project is licensed under the [MIT License](LICENSE.txt) - see the LICENSE file for details.
