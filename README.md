# Meduza
Personal Game Engine project by Nick Wagter
The purpose of this project is to learn modern Graphics APIs and about other components that make up a game engine.

This is mainly based on learning the components and optimizing where I can and am capable of doing so, this means that this engine will
be no where near as optimal as a commercial game engine like Unity, Unreal etc.

The focus for this project will be on the windows platform but cmake and git action (CI) is setup to support Linux and MacOS as well.

# What will it contain
This project is in the early stages of development and does not contain a lot yet,
but what is currently planned is the following :

- Rendering
  - 2D Rendering
    - :white_check_mark: Textured Quads
    - Sprite Animator
  - 3D Rendering
    - Geometry
      - :white_check_mark: Cubes
      - :white_check_mark: Spheres
      - Planes
    - Object Loading
      - Obj
      - :white_check_mark: glTF
    - Lights
      - Point Lights
      - Directional Lights
    - Skeletal animations
- Entity Component System
  - :white_check_mark: Components
  - :white_check_mark: Systems
- Input
  - Mouse
  - :white_check_mark: Keyboard
- Physics
  - 2D Phsyics
    - Box2D Collision
    - Circle Collision
  - 3D Physics
    - Box Collision
    - Sphere Collision
  - Physics Bodies


# Graphics APIs :
- OpenGL 3.1
- DirectX 12

# Libraries Used :
- GLAD
- ImGUI

# Project description

Meduza is a personal game engine project, mainly made with C++.
Capable of Rendering 2D and 3D geometry, input events, ECS and basic Physics

3D rendered Duck gltf loader

<p align="center">
  <img src="https://github.com/NWagter/Meduza/blob/master/.github/Images/DuckRendered.png" width="500"/>
</p>
