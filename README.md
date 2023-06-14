# pokeclash

pokemon tower defense game using sfml

## Build Setup

Before you start with the setup, make sure that you have a C++ compiler that supports C++20, OpenGL, and SFML installed on your machine.

1. **Clone the repository**

```bash
git clone https://github.com/token03/pokeclash.git
```

2. **Navigate to your project directory**

```bash
cd pokeclash
```

3. **Setup external libraries**

```bash
mkdir build external
cd external
git clone https://github.com/zeux/pugixml.git
git clone https://github.com/ocornut/imgui.git
git clone https://github.com/eliasdaler/imgui-sfml.git
cd ..
```

4. **Configure the project with CMake**

```bash
cd build
cmake ..
```

5. **Build the project**

```bash
make
```

this should create an executeable you can run within the build directory

## Credit

This project uses the following projects:

- [PMDCollab](https://github.com/PMDCollab/SpriteCollab) for sprites
- [SFML](https://github.com/SFML/SFML) for rendering
- [Dear Imgui](https://github.com/ocornut/imgui) for gui
- [pugixml](https://github.com/zeux/pugixml) for xml parsing

```

```
