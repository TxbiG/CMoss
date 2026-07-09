# Your First 2D Game

This guide will walk you through creating a simple 2D game using Moss Framework.

## Project Setup

Before starting, ensure you have:
- Moss Framework installed and linked
- C/C++ compiler supporting C11 or later
- A code editor or IDE of your choice

## Step 1: Create the Window

```c
#include <Moss.h>

int main() {
    // Initialize Moss
    if (!Moss_Init()) {
        return 1;
    }

    // Create window
    Moss_Window* window = Moss_CreateWindow("My 2D Game");
    if (!window) {
        Moss_Terminate();
        return 1;
    }

    // Create renderer
    Moss_Renderer* renderer = Moss_CreateRenderer(*window);
    if (!renderer) {
        Moss_TerminateWindow(window);
        Moss_Terminate();
        return 1;
    }

    // Main game loop
    while (!Moss_ShouldWindowClose(window)) {
        Moss_PollEvents();

        // Begin frame
        Moss_RendererBeginFrame(*renderer);

        // Render here
        // ...

        // Present frame
        Moss_PresentRenderer(*renderer);
    }

    // Cleanup
    Moss_TerminateRenderer(renderer);
    Moss_TerminateWindow(window);
    Moss_Terminate();
    return 0;
}
```

## Step 2: Add a Sprite

```c
// Load a texture
Moss_Texture* player_texture = Moss_CreateTexture("assets/player.png");

// Create a 2D sprite
Moss_Sprite2D sprite;
sprite.texture = player_texture;
sprite.position = (Vec2){400.0f, 300.0f};
sprite.scale = (Vec2){1.0f, 1.0f};
```

## Step 3: Handle Input

```c
void HandlePlayerInput(Moss_Sprite2D* player, float delta_time) {
    Vec2 velocity = {0, 0};
    float speed = 200.0f;  // pixels per second

    // Keyboard input
    if (Moss_IsKeyPressed(KEY_W)) velocity.y -= speed * delta_time;
    if (Moss_IsKeyPressed(KEY_S)) velocity.y += speed * delta_time;
    if (Moss_IsKeyPressed(KEY_A)) velocity.x -= speed * delta_time;
    if (Moss_IsKeyPressed(KEY_D)) velocity.x += speed * delta_time;

    // Update position
    player->position.x += velocity.x;
    player->position.y += velocity.y;
}
```

## Step 4: Update and Render

```c
while (!Moss_ShouldWindowClose(window)) {
    Moss_PollEvents();

    // Update
    float delta_time = 0.016f;  // ~60 FPS
    HandlePlayerInput(&player, delta_time);

    // Render
    Moss_RendererBeginFrame(*renderer);
    
    // Draw sprite
    Moss_DrawSprite2D(*renderer, player);
    
    Moss_PresentRenderer(*renderer);
}
```

## Next Steps

- Learn about [Physics](../Physics.md) for collision detection
- Add [Audio](../Audio.md) for sound effects
- Create [UI](../UI.md) for menus and HUD
- Check [Components](../Components.md) for advanced features

For more details, see the [full Platform documentation](../Platform.md).
