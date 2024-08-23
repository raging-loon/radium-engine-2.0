# Radium Engine

This is an engine I am writing almost completely from scratch.

What will I not be writing?
1. DirectX 11 + the error helper
2. Math
3. Things that the C++ compiler handles (namely `type_traits`)

Other than that, everything here is 100% my own code.

Why? 
1. It will *totally* be fun
1. I enjoy making things from the ground up
1. I want to learn about things like STL, compression algorithms, file formats, etc

What will I be building?
- [ ] Radium Template Library (`rtl`)
- [ ] Radium Math libary (`rm`)
- [ ] A 2D renderer geared towards isometric graphics
- [ ] Component-System akin to Unity's GameObject + MonoBehaviour system
- [ ] Scene Graph
- [ ] Resource Management/Loading/Conditioning
- [ ] UI Library
- [ ] Audio Library (prob. WASAPI/ALSA)
- [ ] Small self-contained VM language

## Directory Structure


## Coding Style
I am using Allman Style bracing.

Everything RTL/Math related is in lower_snake_case.

RTL classes are under the `rtl` namespace, Math classes are under the `rm` namespace, 
everything else is in the `radium` namespace

Classes are UpperCamelCase, class members/functions are lowerCamelCase

Private member variables are preceded with `m_`

Constants and Macros are in SCREAMING_SNAKE_CASE

Please, *please* ensure your IDE/editor is using 4 spaces and NOT tabs.