![radium logo](https://github.com/raging-loon/radium-engine-2.0/tree/main/logo.png "Logo")
# Radium Engine

This is a game engine oriented towards 2D games. In the future I plan on adding 3D support.

## Directory Structure
- `core`
  -   Core engine. Template library, threading, logging, etc
- `scene`
  -   ECS, scene manager, high level components (e.g. Sprite2D)
- `renderer`
  -   Graphics API interface, low-level components (e.g. Texture2D)
- `game`
  -   The game
- `platform`
    - Platform dependent code 
- `unitest`
  -   Unit Tests
## Coding Style
I am using Allman Style bracing.

Everything RTL/Math related is in lower_snake_case.

RTL classes are under the `rtl` namespace, Math classes are under the `rm` namespace, 
everything else is in the `radium` namespace

Classes are UpperCamelCase, class members/functions are lowerCamelCase

Private member variables are preceded with `m_`

Constants and Macros are in SCREAMING_SNAKE_CASE

Please, *please* ensure your IDE/editor is using 4 spaces and NOT tabs.