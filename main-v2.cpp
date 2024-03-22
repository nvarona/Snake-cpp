// Primera version de template para juegos ....

#include <iostream>
#include <raylib.h>

using namespace std;

// Definicion de variables y constantes para el juego
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Food {

public:
    Vector2 position;
    Texture2D texture;
    Food(){
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);     // Despues de leer la imagen y convertirla en textura, podemos liberrar memoria
        position = GenerateRandomPos();
    }
    ~Food(){
        UnloadTexture(texture);
    }
    void Draw(){
        // DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkGreen);
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }
    Vector2 GenerateRandomPos(){
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }
};

int main(){


    cout << endl;
    cout << "Starting the game..." << endl;

    InitWindow(cellSize * cellCount, cellSize * cellCount, "SNAKE Game + RayLib");
    SetTargetFPS(60);

    Food food = Food();

    // Loop del juego -------------------------------------------------
    while (WindowShouldClose() == false)
    {
        BeginDrawing(); 
        // Dibujando
        ClearBackground(green);
        food.Draw();
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}