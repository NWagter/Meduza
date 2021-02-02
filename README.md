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
    - Textured Quads
    - Sprite Animator
  - 3D Rendering
    - Geometry
      - Cubes
      - Spheres
      - Planes
    - Object Loading
      - Obj
      - glTF
    - Lights
      - Point Lights
      - Directional Lights
    - Skeletal animations
- Entity Component System
  - Components
  - Systems
- Input
  - Mouse
  - Keyboard
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
