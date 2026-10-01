# Contributing to CMoss

Thank you for contributing to **CMoss**, the C binding for Moss Framework.

CMoss provides a C-facing API over Moss, while rendering and physics remain primarily implemented in the C++ backend. The C API should therefore stay explicit, stable, and independent of C++ object layouts.

## Before You Start

For public API or ABI changes, open an issue before substantial implementation.

Please search existing issues and pull requests before starting work.

## Development Requirements

- Git
- C99-capable C compiler
- C++17 compiler
- CMake
- A local Moss Framework checkout

## Building

```bash
git clone https://github.com/TxbiG/CMoss.git
cd CMoss

cmake -S . -B build
cmake --build build
```

Run available tests where configured:

```bash
ctest --test-dir build --output-on-failure
```

## Repository Structure

- `include/Moss/` — public C headers
- `src/` — C binding implementation
- `docs/` — documentation
- `.github/workflows/` — CI

## Areas for Contribution

- C API coverage
- Resource handles
- Rendering
- Physics
- Audio
- Input
- Networking
- Platform functionality
- Documentation
- Examples
- Tests
- Build/CI support

## C API Guidelines

Prefer opaque handles and descriptors over exposing native C++ structures.

Public APIs should clearly define:

- Ownership
- Lifetime
- Nullability
- Threading requirements
- Error behaviour
- Resource destruction

Do not expose C++ types, templates, references, STL containers, or object layouts through public C headers.

## ABI Compatibility

CMoss is a C-facing ABI, so be careful when changing:

- Struct layouts
- Enum values
- Function signatures
- Calling conventions
- Integer widths
- Alignment
- Handle representations

Prefer additive changes where possible. If an ABI change is unavoidable, document it clearly.

## Testing

Test the C interface independently from C++ implementation details where practical.

Useful cases include:

- Resource creation/destruction
- Null argument handling
- Invalid handles
- Repeated cleanup
- Struct initialisation
- Error reporting
- Cross-platform compilation

## Documentation

Every new public function should document:

- Purpose
- Parameters
- Return value
- Ownership
- Lifetime
- Errors
- Threading expectations where relevant

## Commit Messages

Recommended prefixes:

```text
feat: add C audio device API
fix: validate null texture handles
docs: document Moss window lifecycle
test: add C handle regression
refactor: simplify C wrapper ownership
build: improve CMake installation
```

## Pull Requests

Include:

- API description
- ABI considerations
- Tests performed
- Compiler/platform information
- Corresponding Moss changes if applicable
- Compatibility notes

If a change mirrors a new Moss C++ API, explain how the C representation maps to the native implementation.

## Licence

CMoss is distributed under the **MIT License**. Contributions should be compatible with the repository's licence and applicable C/Moss/third-party licence requirements.

Thank you for contributing.
