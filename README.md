# Prism

C++ entity metadata extraction tool

![status](https://badgen.net/static/status/dev/yellow)
![status](https://badgen.net/static/c++/23/green)

<img src="assets/logo.svg" alt="logo">

## Prerequisites

- CMake
- C++ compiler with C++23 support
- Doxygen and dot (only for generating docs)

## Features

- Entities
  - [ ] Classes
  - [ ] Class templates
  - [ ] Enumerations
  - [ ] Functions
  - [ ] Function templates
  - [ ] Type aliases
  - [ ] Type alias templates
  - [ ] Attributes (annotated)
- Build systems
  - [ ] CMake
  - [ ] MSBuild
- Source types
  - [ ] Regular
  - [ ] Modules

## Build

To build Prism, go to the project's root directory and execute the following commands:

```shell
cmake -S . -B build
cmake --build build --target Prism --parallel
```

## Documentation

To generate docs, go to the project's root directory and execute the following command:

```shell
doxygen docs/Doxyfile
```

The generated documentation will be placed in the [following](docs/out) directory.

## Author

Oleg E. Vorobiov <isnullxbh@gmail.com>

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE) for more information.
