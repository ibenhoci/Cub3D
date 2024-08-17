# Cub3D

This project is an implementation of a raycasting algorithm using the 42 graphics library minilibx, it is a very basic maze exploration program based on the Wolfenstein 3D game, more will be added to the game at a later date.

## Description

Taking input that consists of predefinite symbols that represent a map, this program will parse the map and then proceed to render the map with a 3D view using raycasting methods, the input will also contain other information: the ceiling and floor colors alongside four wall textures that will be drawn onto the screen to improve the visual result. The user will be able to navigate through the maze and explore it within its boundaries, wall collision is also implemented.
Future changes will include random spawning enemies, doors, attacking function, health bar system making it closer to the original Wolfenstein 3D game.

## Requirements

- Basic requirements:
	--- This project relies on the minilibx graphics library, it will need to be installed in order to run the program.
	--- Input file with .cub extension, this file will contain a closed map, alongside the path to the wall textures and the colors of the ceiling and the floor.

- Input requirements:
	--- The first rows of input will contain paths to the desired textures, you will need four textures in total, following this format:
		```
			NO /path/to/your/north_wall/texture
			SO /path/to/your/south_wall/texture
			EA /path/to/your/east_wall/texture
			WE /path/to/your/west_wall/texture
		```
	--- The next piece of information needed will be the desired color for the ceiling and floor following this format:
		```
			F 255,255,255
			C 0,0,0
		```
	--- The map must be composed of only the following characters: 0 for empty space, 1 for wall, N,S,W or E for the player's starting position and direction in which he will be facing. 
	--- The map must be surrounded by walls and must not contain spaces inside the wall.
	--- Spaces can be used to offset certain areas of the map but they need to be outside the walls.
	--- Map example:
		```
			111111
			  100011
			100000001
			11111111
		```
## Usage

- Clone the repository:
	```
		git clone https://github.com/ibenhoci/Cub3D
	```
- Build the project:
	```
		make
	```
	Running make for the first time will also download the minilibx library which is necesary for rendering the graphics of the project
- Run the project:
	```
		./cub3d map.cub
	```
- Last step: Enjoy!