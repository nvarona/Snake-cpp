// Cuarta version del template para el Juego Snake ....

#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

// Definicion de variables y constantes para el juego
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
double lastUpdateTime = 0;      // Seguimiento de la hora en la que se produjo la ultima actualización

bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake {

public:
    deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    Vector2 direction = {1,0};
    void Draw(){
        for(unsigned int i = 0; i < body.size(); i++){
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * (float)cellSize, y * (float)cellSize, (float)cellSize, (float)cellSize};
            //DrawRectangle(x*cellSize, y*cellSize, cellSize, cellSize, darkGreen);
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
    void Update(){
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
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

class Game {
public:
    Snake snake = Snake();
    Food food = Food();

    void Draw(){
        food.Draw();
        snake.Draw();
    }
    void Update(){
        snake.Update();
    }
};

int main(){
    // Comenzamos el programa ------------------------------------------
    cout << endl;
    cout << "Starting the game..." << endl;

    InitWindow(cellSize * cellCount, cellSize * cellCount, "SNAKE Game + RayLib");
    SetTargetFPS(60);

   Game game = Game();

    // Loop del juego -------------------------------------------------
    while (WindowShouldClose() == false)
    {
        BeginDrawing(); 
        
        if (eventTriggered(0.2)){
            game.Update();    
        }
        // control de teclas pulsadas por el usuario y reacionar 
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1){
            game.snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1){
            game.snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1){
            game.snake.direction = {-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT && game.snake.direction.x != -1)){
            game.snake.direction = {1, 0};
        }
        
        // Dibujando la serpiente en su nueva posición --------------
        ClearBackground(green);
        game.Draw();
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}