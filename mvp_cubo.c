// MVP: Mostrar modelos 3D simples usando las 4 caras
// de cada asset "Transparente" (Arbusto, Flores, Granero, Roca)
// Compilar: gcc mvp_cubo.c -o mvp_cubo -lraylib -lopengl32 -lgdi32 -lwinmm

#include "raylib.h"
#include "rlgl.h"

#define FACES 4
#define MODELS 6

// Orden de las caras por modelo: frontal, derecha, trasera, izquierda
static const char *modelFaceFiles[MODELS][FACES] = {
    {// Arbusto
     "assets/Transparente Arbusto_r1_c1_processed_by_imagy.png",
     "assets/Transparente Arbusto_r1_c2_processed_by_imagy.png",
     "assets/Transparente Arbusto_r2_c1_processed_by_imagy.png",
     "assets/Transparente Arbusto_r2_c2_processed_by_imagy.png"},
    {// Granero
     "assets/Transparente Granero.png_r1_c1_processed_by_imagy.png",
     "assets/Transparente Granero.png_r1_c2_processed_by_imagy.png",
     "assets/Transparente Granero.png_r2_c1_processed_by_imagy.png",
     "assets/Transparente Granero.png_r2_c2_processed_by_imagy.png"},
    {// Roca
     "assets/Transparente Roca_r1_c1_processed_by_imagy.png",
     "assets/Transparente Roca_r1_c2_processed_by_imagy.png",
     "assets/Transparente Roca_r2_c1_processed_by_imagy.png",
     "assets/Transparente Roca_r2_c2_processed_by_imagy.png"},
    {// WhatsApp (1)
     "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (1)-fotor-bg-remover-20260106132648_r1_c1_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (1)-fotor-bg-remover-20260106132648_r1_c2_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (1)-fotor-bg-remover-20260106132648_r2_c1_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (1)-fotor-bg-remover-20260106132648_r2_c2_processed_by_imagy.png"},
    {// WhatsApp (3)
     "assets/WhatsApp Image 2026-01-06 at 11.31.03 AM (3)-fotor-bg-remover-20260106132652_r1_c1_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.03 AM (3)-fotor-bg-remover-20260106132652_r1_c2_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.03 AM (3)-fotor-bg-remover-20260106132652_r2_c1_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.03 AM (3)-fotor-bg-remover-20260106132652_r2_c2_processed_by_imagy.png"},
    {// WhatsApp (5)
     "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (5)-fotor-bg-remover-20260106132655_r1_c1_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (5)-fotor-bg-remover-20260106132655_r1_c2_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (5)-fotor-bg-remover-20260106132655_r2_c1_processed_by_imagy.png",
     "assets/WhatsApp Image 2026-01-06 at 11.31.02 AM (5)-fotor-bg-remover-20260106132655_r2_c2_processed_by_imagy.png"}};

typedef struct SpriteModel
{
    Texture2D texture; // atlas 2x2 con las 4 partes del modelo
} SpriteModel;

typedef struct MapEntity
{
    int modelIndex;   // índice en models[]
    Vector3 position; // posición en el mundo
    float size;       // escala del billboard
} MapEntity;

typedef struct CharacterEntity
{
    Texture2D *texture; // textura del personaje
    Vector3 position;   // posición en el mundo
    float size;         // escala del billboard
} CharacterEntity;

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "MVP Isometrico - Modelos Transparente");

    SpriteModel models[MODELS];

    // Construir un atlas 2x2 por modelo (rearma la imagen original)
    for (int m = 0; m < MODELS; m++)
    {
        // Cargar las 4 partes
        Image img00 = LoadImage(modelFaceFiles[m][0]); // r1_c1
        Image img10 = LoadImage(modelFaceFiles[m][1]); // r1_c2
        Image img01 = LoadImage(modelFaceFiles[m][2]); // r2_c1
        Image img11 = LoadImage(modelFaceFiles[m][3]); // r2_c2

        int w = img00.width;
        int h = img00.height;
        Image atlas = GenImageColor(w * 2, h * 2, BLANK);

        // Copiar cada tile a su posición en la grilla 2x2
        Rectangle src = (Rectangle){0, 0, (float)w, (float)h};
        ImageDraw(&atlas, img00, src, (Rectangle){0, 0, (float)w, (float)h}, WHITE);
        ImageDraw(&atlas, img10, src, (Rectangle){(float)w, 0, (float)w, (float)h}, WHITE);
        ImageDraw(&atlas, img01, src, (Rectangle){0, (float)h, (float)w, (float)h}, WHITE);
        ImageDraw(&atlas, img11, src, (Rectangle){(float)w, (float)h, (float)w, (float)h}, WHITE);

        models[m].texture = LoadTextureFromImage(atlas);

        UnloadImage(img00);
        UnloadImage(img10);
        UnloadImage(img01);
        UnloadImage(img11);
        UnloadImage(atlas);
    }

    // Cargar solo los 4 sprites que me enviaste al principio (colocar en assets/)
    Texture2D knightTex = LoadTexture("assets/knight.png");
    Texture2D farmerTex = LoadTexture("assets/farmer.png");
    Texture2D archerTex = LoadTexture("assets/archer.png");
    Texture2D merchantTex = LoadTexture("assets/merchant.png");

    Camera camera = {0};
    camera.position = (Vector3){13.0f, 11.0f, 13.0f}; // vista isométrica para ver todo el mapa
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Definir un pequeño mapa con varias instancias de cada modelo
    // 0: Arbusto, 1: Granero, 2: Roca, 3-5: Modelos WhatsApp
    MapEntity entities[] = {
        // Granero principal en el centro
        {1, {0.0f, 0.0f, 0.0f}, 3.5f},

        // Arbustos repartidos alrededor del granero
        {0, {-4.0f, 0.0f, 2.0f}, 3.0f},
        {0, {1.0f, 0.0f, 3.0f}, 3.0f},
        {0, {-3.0f, 0.0f, -3.0f}, 3.0f},

        // Rocas en distintos puntos del mapa
        {2, {5.0f, 0.0f, 1.0f}, 3.0f},
        {2, {8.0f, 0.0f, -2.0f}, 3.0f},
        {2, {2.0f, 0.0f, -4.0f}, 3.0f},
        {2, {7.0f, 0.0f, 4.0f}, 3.0f},

        // Modelos WhatsApp como estructura/campos mas alejados
        {3, {-2.0f, 0.0f, 6.0f}, 3.0f},
        {4, {1.0f, 0.0f, 7.0f}, 3.0f},
        {5, {4.0f, 0.0f, 6.0f}, 3.0f}};
    const int entityCount = sizeof(entities) / sizeof(entities[0]);

    // Personajes colocados en el grid (posiciones elegidas para no solaparse con entidades existentes)
    CharacterEntity characters[] = {
        {&knightTex, {-6.0f, 0.0f, 0.0f}, 2.5f},  // nuevo - lado izquierdo
        {&farmerTex, {6.0f, 0.0f, 0.5f}, 2.5f},   // nuevo - lado derecho
        {&archerTex, {0.0f, 0.0f, -6.0f}, 2.5f},  // nuevo - al fondo
        {&merchantTex, {7.0f, 0.0f, -3.5f}, 2.5f} // nuevo - esquina derecha-atrás
    };
    const int characterCount = sizeof(characters) / sizeof(characters[0]);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        BeginMode3D(camera);
        // Ajuste de espaciado para evitar solapamientos
        const float spacing = 1.8f; // multiplica posiciones para separar entidades
        DrawGrid(20, spacing);

        // Dibujar el mapa usando las entidades (posiciones escaladas por spacing)
        for (int i = 0; i < entityCount; i++)
        {
            MapEntity e = entities[i];
            Vector3 pos = {e.position.x * spacing, e.position.y, e.position.z * spacing};
            DrawBillboard(camera, models[e.modelIndex].texture, pos, e.size, WHITE);
        }

        // Dibujar personajes (posiciones escaladas por spacing)
        for (int i = 0; i < characterCount; i++)
        {
            CharacterEntity c = characters[i];
            Vector3 pos = {c.position.x * spacing, c.position.y, c.position.z * spacing};
            DrawBillboard(camera, *c.texture, pos, c.size, WHITE);
        }

        EndMode3D();

        DrawText("MVP - Mapa isometrico armado con los assets actuales", 20, 20, 20, DARKGRAY);
        DrawText("Sprites usados como entidades del mapa (granero, arbustos, rocas, campos, unidades)", 20, 45, 18, GRAY);

        EndDrawing();
    }

    for (int m = 0; m < MODELS; m++)
    {
        UnloadTexture(models[m].texture);
    }

    UnloadTexture(knightTex);
    UnloadTexture(farmerTex);
    UnloadTexture(archerTex);
    UnloadTexture(merchantTex);

    CloseWindow();
    return 0;
}
