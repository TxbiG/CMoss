[![Build](https://github.com/TxbiG/CMoss/actions/workflows/build.yml/badge.svg)](https://github.com/TxbiG/CMoss/actions/workflows/build.yml)
# CMoss
CMoss is the [Moss Framework](https://github.com/TxbiG/Moss) written in C.
## Documentation

Comprehensive documentation is available in the [`docs/`](./docs) directory:

* Architecture overview
* Rendering system design
* Physics system design
* Audio pipeline
* Input system
* Networking model
* Platform backend architecture
* Performance guidelines

- [API cheatsheet](docs/Cheatsheet.md)
- [API Reference](docs/API_Reference.md)
- [Roadmap](docs/README.md#roadmap)

## Required CPU features
- x86/x64
  - Minimum: SSE2.
  - Optional compile targets: SSE4.1, SSE4.2, AVX, AVX2, or AVX512.
- ARM32/ARM64 
  - NEON and FP16. 
  - ARM32 can be built without any special CPU extensions.
- Other Architectures
  - RISC-V64/LoongArch64/PowerPC64LE support

## Compiling
- CMake 3.20 or newer.
- C 99

## Repository Structure
```text
.
|-- assets/       Resources like shaders and textures
|-- docs/         Documentation and developer guides
|-- examples/     Example projects
|-- external/     Third-party dependencies
|-- include/      Public framework headers
|-- src/          Framework source code
|-- performance/  Benchmarks and profiling tools
|-- tests/        Unit and smoke tests
```

## License
The project is distributed under the [MIT license](/LICENSE).
