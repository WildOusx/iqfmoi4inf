// MVP de visualización de modelos 3D (imágenes) con raylib
// Para compilar: gcc mvp_raylib.c -o mvp_raylib -lraylib -lopengl32 -lgdi32 -lwinmm
#include "raylib.h"

#define NUM_IMAGES 10

const char *imageFiles[NUM_IMAGES] = {
    "assets/WhatsApp Image 2026-01-06 at 11.31.01 AM.jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (1).jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (2).jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (3).jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (4).jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM.jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.03 AM (1).jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.03 AM (2).jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.03 AM (3).jpeg",
    "assets/WhatsApp Image 2026-01-06 at 11.31.03 AM (4).jpeg"};

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "MVP Modelos 3D - Vista Previa");

    Texture2D textures[NUM_IMAGES];
    for (int i = 0; i < NUM_IMAGES; i++)
    {
        Image img = LoadImage(imageFiles[i]);
        textures[i] = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    int current = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_RIGHT))
            current = (current + 1) % NUM_IMAGES;
        if (IsKeyPressed(KEY_LEFT))
            current = (current - 1 + NUM_IMAGES) % NUM_IMAGES;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Usa <- y -> para cambiar de modelo", 20, 20, 24, DARKGRAY);
        DrawTexturePro(
            textures[current],
            (Rectangle){0, 0, (float)textures[current].width, (float)textures[current].height},
            (Rectangle){screenWidth / 2 - 400, screenHeight / 2 - 300, 800, 600},
            (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    for (int i = 0; i < NUM_IMAGES; i++)
        UnloadTexture(textures[i]);
    CloseWindow();
    return 0;
}
