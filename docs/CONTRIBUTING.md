# Contributing to Moss Documentation

Thank you for helping improve the Moss Framework documentation! This guide will help you contribute effectively.

## Documentation Structure

### Main Files
- **README.md** — Main documentation index and architecture overview
- **CheatSheet.md** — Quick reference for APIs and macros
- **CONTRIBUTING.md** — This file

### Module Documentation
- **Platform.md** — Window, input, monitors, system integration
- **Audio.md** — Audio system, channels, effects, listeners
- **Renderer.md** — Rendering, graphics APIs, cameras, lighting
- **Physics.md** — Physics engine, collision detection
- **Components.md** — 2D and 3D game object components
- **UI.md** — User interface components and widgets
- **Resources.md** — Asset management and file formats
- **Variants.md** — Data types and core type system
- **Network.md** — Networking, ENet, multiplayer
- **Maths.md** — Mathematical functions and utilities
- **XR.md** — Virtual and augmented reality

### Guides
- **2DGame/** — Tutorial for creating 2D games
- **3DGame/** — Tutorial for creating 3D applications
- **img/** — Images and diagrams

## Documentation Format

### Standard Section Structure

```markdown
# Topic Name

## Overview
[Explain what this system does and why it matters]

## Macros
```c
[C/C++ code examples]
```

## Enums
```c
[Enumeration definitions]
```

## Structs
```c
[Structure definitions]
```

## Functions
```c
[Function signatures]
```

## Examples
[Practical code examples showing real usage]
```c
[Complete working examples]
```
```

### Markdown Best Practices

1. **Headings** — Use `#` for main topics, `##` for sections, `###` for subsections
2. **Code Blocks** — Use ` ```c ` for C code, ` ```cpp ` for C++
3. **Links** — Use relative links: `[text](./FileName.md#anchor)`
4. **Emphasis** — Use `**bold**` for important terms, `` `code` `` for inline code
5. **Lists** — Use `-` for unordered, numbers for ordered
6. **Tables** — Document API parameters in clear markdown tables

### Example Documentation Entry

```markdown
## Audio Listeners

### AudioListener2D
Positional audio listener for 2D space. Affects how 3D audio is heard.

```c
void Moss_SetAudioListener2(float x, float y);
struct Moss_AudioListener2 Moss_GetAudioListener2(void);
```

**Parameters:**
| Parameter | Type | Description |
| --- | --- | --- |
| x | float | X position in world space |
| y | float | Y position in world space |

**Example:**
```c
// Set listener to follow player
Moss_SetAudioListener2(player.x, player.y);
```
```

## Common Issues to Fix

### Broken Links
- Links should point to valid files or sections
- Use `[text](#anchor)` for internal links
- Use `[text](./FileName.md#anchor)` for cross-file links

### Incomplete Sections
- Sections with `[Add Text here]` need completion
- Empty code blocks should be filled or replaced with "Not yet documented"
- Placeholder examples should be replaced with real examples

### Typos & Formatting
- "Exmaple" → "Example"
- "Suorted" → "Supported"
- "Aroach" → "Approach"
- Inconsistent backticks or code formatting

### Platform & API Support
- Keep platform support tables up to date
- Document graphics API-specific features clearly
- Note version requirements or dependencies

## Contribution Workflow

### Before You Start
1. Check existing documentation to avoid duplication
2. Review the module structure to pick the right file
3. Look at similar sections for consistency

### Making Changes
1. Edit the appropriate `.md` file
2. Follow the section structure above
3. Include working code examples
4. Test all links before submitting

### Checklist
- [ ] Section follows standard structure
- [ ] All links are valid and relative
- [ ] Code examples are accurate and complete
- [ ] Typos are corrected
- [ ] Consistent formatting throughout
- [ ] Platform/API support documented
- [ ] README.md links updated if needed

## Tips for Good Documentation

1. **Be Clear** — Explain what something does, not just how
2. **Show Examples** — Working code is worth 1000 words
3. **Be Consistent** — Match existing documentation style
4. **Be Complete** — Cover common use cases and edge cases
5. **Be Current** — Update docs when APIs change

## Questions?

If you need clarification on anything, open an issue or check existing documentation for patterns.

Thank you for improving Moss documentation! 🎉
