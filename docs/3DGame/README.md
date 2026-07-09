# Your First 3D Game

This guide will help you create your first 3D application with Moss Framework.

## Project Setup

Before starting, ensure you have:
- Moss Framework installed and linked
- C/C++ compiler supporting C11 or later
- A graphics API (OpenGL, Vulkan, Metal, or DirectX 12)

## Step 1: Create a 3D Window and Renderer

```c
#include <Moss.h>

int main() {
    // Initialize Moss
    if (!Moss_Init()) {
        return 1;
    }

    // Create window
    Moss_Window* window = Moss_CreateWindow("My 3D Game");
    if (!window) {
        Moss_Terminate();
        return 1;
    }

    // Create renderer (automatically selects best graphics API)
    Moss_Renderer* renderer = Moss_CreateRenderer(*window);
    if (!renderer) {
        Moss_TerminateWindow(window);
        Moss_Terminate();
        return 1;
    }

    // Main loop
    while (!Moss_ShouldWindowClose(window)) {
        Moss_PollEvents();

        Moss_RendererBeginFrame(*renderer);
        // Rendering code here
        Moss_PresentRenderer(*renderer);
    }

    // Cleanup
    Moss_TerminateRenderer(renderer);
    Moss_TerminateWindow(window);
    Moss_Terminate();
    return 0;
}
```

## Step 2: Set Up a 3D Camera

```c
// Create camera
Moss_Camera3D camera;
camera.position = (Vec3){0.0f, 5.0f, 10.0f};
camera.target = (Vec3){0.0f, 0.0f, 0.0f};
camera.up = (Vec3){0.0f, 1.0f, 0.0f};
camera.fov = 45.0f;
camera.near = 0.1f;
camera.far = 1000.0f;

// Set camera before rendering
Moss_SetCamera3D(&camera);
```

## Step 3: Load and Create 3D Objects

```c
// Load a model from file
Moss_Model* model = Moss_CreateModel("assets/model.obj");

// Create mesh data
Moss_MeshData mesh_data = {
    .vertex_count = 3,
    .vertices = {
        {0.0f, 0.5f, 0.0f},   // Top
        {-0.5f, -0.5f, 0.0f}, // Left
        {0.5f, -0.5f, 0.0f}   // Right
    }
};

// Create mesh from data
Moss_Mesh* mesh = Moss_CreateMesh(&mesh_data);
```

## Step 4: Add Lighting

```c
// Create directional light
Moss_Light light;
light.type = LIGHT_DIRECTIONAL;
light.direction = (Vec3){1.0f, -1.0f, -1.0f};
light.color = (Vec3){1.0f, 1.0f, 1.0f};
light.intensity = 1.0f;

// Add light to renderer
Moss_AddLight(renderer, &light);
```

## Step 5: Implement Camera Control

```c
void UpdateCamera(Moss_Camera3D* camera, float delta_time) {
    float speed = 5.0f;  // units per second
    
    // Keyboard controls
    if (Moss_IsKeyPressed(KEY_W)) {
        camera->position.z -= speed * delta_time;
    }
    if (Moss_IsKeyPressed(KEY_S)) {
        camera->position.z += speed * delta_time;
    }
    if (Moss_IsKeyPressed(KEY_A)) {
        camera->position.x -= speed * delta_time;
    }
    if (Moss_IsKeyPressed(KEY_D)) {
        camera->position.x += speed * delta_time;
    }
    
    // Mouse look
    if (Moss_IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        float dx, dy;
        Moss_GetMousePosition(&dx, &dy);
        // Apply to camera rotation (implement based on your needs)
    }
}
```

## Step 6: Main Game Loop

```c
float delta_time = 0.016f;  // ~60 FPS
float rotation = 0.0f;

while (!Moss_ShouldWindowClose(window)) {
    Moss_PollEvents();

    // Update
    UpdateCamera(&camera, delta_time);
    rotation += 45.0f * delta_time;  // Spin model

    // Render
    Moss_RendererBeginFrame(*renderer);
    Moss_SetCamera3D(&camera);

    // Draw mesh with rotation
    Moss_Mat4x4 transform = Moss_RotateY(rotation);
    Moss_DrawMesh(*renderer, mesh, &transform);

    Moss_PresentRenderer(*renderer);
}
```

## Step 7: Add Physics (Optional)

```c
// Create a physics body for the object
Moss_RigidBody3D* body = Moss_CreateRigidBody3D(
    camera->position.x, 
    camera->position.y, 
    camera->position.z
);

// Set mass and properties
Moss_SetRigidBody3DMass(body, 1.0f);
Moss_SetRigidBody3DBounciness(body, 0.5f);

// In update loop
Moss_Update3DPhysics(delta_time);
Moss_GetRigidBody3DPosition(body, &camera->position.x, &camera->position.y, &camera->position.z);
```

## Next Steps

- Learn about [3D Components](../Components.md) for advanced objects
- Add [Physics Simulation](../Physics.md) for realistic movement
- Implement [Lighting and Shadows](../Renderer.md#lighting-and-shadows)
- Create [3D Audio](../Audio.md) for spatial sound
- Add [UI Overlays](../UI.md) for HUD and menus

For detailed API reference, see:
- [Renderer Documentation](../Renderer.md)
- [Platform Input Documentation](../Platform.md)
- [Physics Documentation](../Physics.md)
