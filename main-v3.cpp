// Tercera version del template para el Juego Snake ....

#include <iostream>
#include <raylib.h>
#include <deque>

using namespace std;

// Definicion de variables y constantes para el juego
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Snake {

public:
    deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    void Draw(){
        for(unsigned int i = 0; i < body.size(); i++){
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * (float)cellSize, y * (float)cellSize, (float)cellSize, (float)cellSize};
            //DrawRectangle(x*cellSize, y*cellSize, cellSize, cellSize, darkGreen);
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
};

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
    Snake snake = Snake();

    // Loop del juego -------------------------------------------------
    while (WindowShouldClose() == false)
    {
        BeginDrawing(); 
        // Dibujando
        ClearBackground(green);
        food.Draw();
        snake.Draw();
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}