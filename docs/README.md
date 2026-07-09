# Moss Framework Documentation

## Table of Contents
1. [Overview](#overview)
2. [Architecture](#architecture)
3. [Getting Started](#getting-started)
4. [Core Systems](#core-systems)
5. [API Reference](#api-reference)

## Overview

Moss Framework is a powerful C Binding for a modern game and application development framework. It provides comprehensive tools for:
- Cross-platform development (Windows, Linux, macOS, iOS, Android)
- 2D and 3D game development
- Real-time rendering with multiple graphics APIs
- Physics simulation and collision detection
- Networking and multiplayer support
- Audio and spatial sound
- UI and user interface components
- VR/XR application development

## Architecture

### Core Systems

**Platform Layer** — Cross-platform abstraction for windows, input, monitors, and system events  
**Rendering System** — Multi-API renderer supporting OpenGL, Vulkan, Metal, and DirectX 12  
**Physics Engine** — Jolt Physics-based rigid body dynamics and collision detection  
**Audio System** — Spatial audio with support for 2D/3D streams and effects  
**Networking** — ENet-based reliable networking for multiplayer games  
**Resource Management** — Asset loading, caching, and lifecycle management  
**Component System** — Reusable 2D and 3D components for game objects  

### External Dependencies
- [Thirdparties Documentation](../External/Thirdparties.md)
- [Licensing Information](../LICENSE)

## Getting Started

Choose your path based on your project:
- **[Your First 2D Game](./2DGame/README.md)** — Learn to create simple 2D games
- **[Your First 3D Game](./3DGame/README.md)** — Build your first 3D application

## Core Systems

### Platform
Cross-platform support for Windows, Linux, macOS, FreeBSD, Android, and iOS.
- [Window Management](./Platform.md#window)
- [Input Handling](./Platform.md#input)
- [Monitor Detection](./Platform.md#monitor)
- [Video Capture](./Platform.md#videocapture)
- [Haptic Feedback](./Platform.md#haptic-feedback)
- [Threading & Processes](./Platform.md#threads)
- [Graphics API Integration](./Platform.md#graphics-api-specific)
- **[Full Documentation →](./Platform.md)**

### Audio System
Spatial audio with channels, effects, and streaming.
- [Audio Channels](./Audio.md#channels)
- [Audio Effects](./Audio.md#effects)
- [2D/3D Audio Streams](./Audio.md#streams)
- [Audio Listeners](./Audio.md#listeners)
- [Speaker & Microphone](./Audio.md#speaker--microphone)
- **[Full Documentation →](./Audio.md)**

### Components
Reusable game object components for 2D and 3D.
- **2D Components**
  - [CPUParticle2D](./Components.md#cpuparticle2d)
  - [GPUParticle2D](./Components.md#gpuparticle2d)
  - [Sprite2D](./Components.md#sprite2d)
  - [Tilemap](./Components.md#tilemap)
- **3D Components**
  - [CPUParticle3D](./Components.md#cpuparticle3d)
  - [GPUParticle3D](./Components.md#gpuparticle3d)
  - [Terrain](./Components.md#terrain)
  - [Decal](./Components.md#decal)
- **[Full Documentation →](./Components.md)**

### Physics
Jolt Physics-based simulation for both 2D and 3D.
- [Collision Detection](./Physics.md#collision-detection)
- [Rigid Body Dynamics](./Physics.md#rigid-bodies)
- [2D Physics](./Physics.md#physics-2d)
- [3D Physics](./Physics.md#physics-3d)
- **[Full Documentation →](./Physics.md)**

### Rendering
Multi-API rendering system with support for modern graphics APIs.
- [Renderer Selection](./Renderer.md#choosing-a-renderer)
- [Textures & Shaders](./Renderer.md#textures)
- [Cameras & Viewports](./Renderer.md#camera-2d--3d)
- [Lighting & Shadows](./Renderer.md#lighting-and-shadows)
- [Post-Processing](./Renderer.md#post-processing)
- **[Full Documentation →](./Renderer.md)**

### UI System
Comprehensive UI components for building user interfaces.
- [Containers](./UI.md#containers)
- [Buttons & Controls](./UI.md#buttons)
- [Text & Labels](./UI.md#text)
- [Menus](./UI.md#menus)
- **[Full Documentation →](./UI.md)**

### Resources
Resource management for assets and configurations.
- [Configuration Files](./Resources.md#config)
- [JSON Format](./Resources.md#json)
- [Curves & Gradients](./Resources.md#curve)
- [Fonts & Textures](./Resources.md#font)
- [Audio Files](./Resources.md#wav)
- **[Full Documentation →](./Resources.md)**

### Data Types & Variants
Core data structures and type system.
- [Integer Types](./Variants.md#signed--unsigned-integers)
- [Vector Types](./Variants.md#vec2) — Vec2, Vec3, Vec4, and their int/unsigned variants
- [Matrix Types](./Variants.md#mat2x2) — Mat2x2 through Mat4x4
- [Color & Geometry](./Variants.md#color) — Color, Rect, AABB, Quaternion
- [Template Collections](./Variants.md#tarray) — TArray, TMap, TSet
- **[Full Documentation →](./Variants.md)**

### Networking
ENet-based reliable networking for multiplayer applications.
- [Client/Server Architecture](./Network.md#overview)
- [Connection Management](./Network.md#creating-hostserver)
- [Packet Handling](./Network.md#creating-packets)
- [Events & Disconnection](./Network.md#events)
- **[Full Documentation →](./Network.md)**

### Extended Reality (XR)
VR/AR development using OpenXR standard.
- [XR Setup](./XR.md#overview)
- [XR Controllers](./XR.md#xrcontrols)
- [Hand Tracking](./XR.md#xrhand)
- [Camera & Character Body](./XR.md#xrcamera)
- **[Full Documentation →](./XR.md)**

### Mathematics
Mathematical utilities and functions.
- [Constants](./Maths.md#macros) — PI, TAU, mathematical constants
- [Random Number Generation](./Maths.md#random-number-generations)
- [Trigonometric Functions](./Maths.md#macros)
- **[Full Documentation →](./Maths.md)**

## API Reference

For detailed API information, see the [CheatSheet](./CheatSheet.md) for quick reference or individual module documentation.

### Quick Links
- **[Function CheatSheet](./CheatSheet.md)** — Quick reference of common functions and macros
- **[Platform Macros](./CheatSheet.md#macros)** — Platform detection macros
- **[Input Keys](./CheatSheet.md#input-keys)** — Keyboard, mouse, and gamepad constants
- **[Math Macros](./CheatSheet.md#maths)** — Mathematical operations and constants

## Contributing

See [CONTRIBUTING.md](./CONTRIBUTING.md) for guidelines on documenting your code and contributing to this documentation.
