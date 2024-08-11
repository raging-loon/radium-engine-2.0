# Radium Engine

This is an engine I am writing almost completely from scratch.

What will I not be writing?
1. The Operating system
2. The graphics API (DX11)
3. Unit testing framework (GTEST)
	* I will be using GLM here to ensure the correctness of my math library
4. Parts of the STL that are handled by the compiler. e.g. `std::__is_trivially_copiable`

Other than that, everything here is 100% my own code.

Why? 
1. It will *totally* be fun
1. I enjoy making things from the ground up
1. I want to learn about things like STL, compression algorithms, file formats, etc

What will I be building?
- [ ] Radium Template Library (`rtl`)
- [ ] Radium Math libary (`rm`)
- [ ] 