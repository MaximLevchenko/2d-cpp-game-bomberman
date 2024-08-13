# Classic Bomberman game
![This is an image](/src/assets/README_assets/readme_bomber.png)
# Bomberman Game Project

## Overview

This project is a C++ implementation of a Bomberman-style game, focusing on applying object-oriented programming (OOP) principles. The game features both single-player and multiplayer modes, various enemy types, bonus items, and a dynamic map system.

## Features

- **Single-player and Multiplayer Modes**: Play against AI or another player.
- **Enemy Types**: Different types of enemies with unique behaviors.
- **Bonuses**: Collect bonuses to gain special abilities like increased bomb range, additional bombs, and more.
- **Collision Detection**: Implemented for player interactions, bomb explosions, and enemy movements.
- **Dynamic Map Loading**: Maps are loaded dynamically and can include various objects like obstacles, enemies, and bonuses.
- **Error Handling**: Robust error handling is integrated to manage exceptions and unexpected behavior.


## Dependencies

To build and run this project, you need to have the following dependencies installed on your system:

- **g++**: The GNU C++ compiler, required to compile the C++ source files.
- **make**: A build automation tool that automatically builds executable programs and libraries from source code.
- **SDL2**: The Simple DirectMedia Layer library, used for handling graphics, events, and audio.
- **SDL2_image**: An SDL2 extension library that supports loading images in various formats.
- **SDL2_ttf**: An SDL2 extension library for rendering TrueType fonts.
- **Doxygen**: A documentation generation tool, used to create documentation from annotated source code.

### Installation on Linux

You can install these dependencies on a Debian-based system using `apt`:

```bash
sudo apt-get update
sudo apt-get install g++ make libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev doxygen
```

## Project Structure

The project is organized as follows:

- **dev/**
    - **15x15.map**: Example map file.
    - **15x15_test.map**: Test map file.
    - **highScore.txt**: Stores the high scores.

- **fonts/**: Contains font files used in the game.

- **images/**: Stores images used for textures and sprites.

- **README_assets/**: Contains assets for the README file, such as images and diagrams.

- **Source Files**:
    - **Bomb.cpp / Bomb.h**: Manages bomb placement, explosion timing, and effects.
    - **Bonus.h**: Defines the bonuses that players can collect.
    - **CircleCollision.h**: Manages circular collision detection.
    - **CollisionManager.h**: General collision management for the game.
    - **Enemy.cpp / Enemy.h**: Base class for all enemy types.
    - **EnemyGhost.cpp / EnemyGhost.h**: Inherits from `Enemy`; ghost enemy type that can pass through walls.
    - **EnemyOvapi.cpp / EnemyOvapi.h**: Inherits from `Enemy`; smart enemy with advanced pathfinding.
    - **ErrorHandler.cpp / ErrorHandler.h**: Manages error logging and handling.
    - **Flame.h**: Manages flames created by bomb explosions.
    - **Game.cpp / Game.h**: Core game loop and game state management.
    - **GameObject.h**: Base class for all interactive objects in the game.
    - **KeyboardController.h**: Handles player input via the keyboard.
    - **Map.cpp / Map.h**: Manages game maps, including loading and rendering.
    - **MapObject.h**: Defines objects that are part of the map.
    - **Player.cpp / Player.h**: Manages player actions, movement, and interactions.
    - **RandomNumberGenerator.h**: Utility for generating random numbers.
    - **TextureManager.cpp / TextureManager.h**: Manages loading and rendering of textures.
    - **TransformObject.h**: Handles transformations like scaling, movement, and positioning of objects.
    - **UiLabel.h**: Manages UI elements like labels.
    - **Vector2D.cpp / Vector2D.h**: Handles 2D vector operations for positioning and movement.

- **Doxyfile**: Configuration for generating project documentation using Doxygen.

- **Makefile**: Build script for compiling the project.

## Object-Oriented Design

The project is structured around OOP principles, particularly encapsulation, inheritance, and polymorphism. Here's a detailed overview of the class hierarchy and relationships:

### Class Hierarchy

1. **GameObject** (Base Class)
    - Abstract class serving as the base for all interactive objects in the game.
    - Defines common properties and methods, such as position, scale, and rendering.

2. **Player** (Inherits from `GameObject`)
    - Manages player-specific behavior, such as movement, bomb placement, and interaction with bonuses.

3. **Enemy** (Inherits from `GameObject`)
    - Base class for all enemy types, defining common enemy behavior.
        - **EnemyGhost**: Inherits from `Enemy`; can pass through walls.
        - **EnemyOvapi**: Inherits from `Enemy`; employs advanced pathfinding to navigate the map.

4. **Bomb** (Inherits from `GameObject`)
    - Handles bomb-specific behavior, including explosions and impact.

5. **MapObject** (Inherits from `GameObject`)
    - Represents static objects that are part of the game map.

### Utility Classes

- **TransformObject**: Manages transformations like scaling and positioning, used by both movable and non-movable objects.
- **Vector2D**: Provides vector operations for 2D space, used in positioning and movement calculations.
- **CollisionManager**: Manages collision detection and responses for game objects.
- **TextureManager**: Loads and manages textures used in the game.

### Key OOP Concepts

- **Encapsulation**: Each class manages its own data and behavior, exposing only what is necessary through public interfaces.
- **Inheritance**: Common behaviors are abstracted into base classes (`GameObject`, `Enemy`), allowing derived classes to reuse and extend functionality.
- **Polymorphism**: Objects of different classes (`Player`, `Enemy`, `MapObject`, etc.) can be managed through pointers or references to their base class, enabling flexible and reusable code.

## Compilation and Execution

To compile the project, use the provided `Makefile`. Run the following command in your terminal:

```bash
make
```
This will compile all source files and produce the executable.

To run the game, execute the following command:
```bash
./levchmak
```

### Documentation

Detailed documentation for the project can be generated using Doxygen. To generate the documentation, run:

```bash
doxygen Doxyfile
```
This will create a set of HTML files that document the classes, functions, and overall structure of the code.


## Conclusion

This project showcases the effective use of object-oriented programming principles in the development of a classic game. By structuring the game around a solid class hierarchy, the project remains modular, extensible, and easy to maintain. The use of polymorphism and inheritance allows for flexible management of various game entities, ensuring that the game can be expanded with new features and improvements in the future.