// Primera version de template para juegos ....

#include <iostream>
#include <raylib.h>

using namespace std;

int main(){
    // Definicion de variables y constantes para el juego
    const int screenWidth = 800;
    const int screenHeight = 600;
    int ball_x = 100;
    int ball_y = 100;
    int ball_speed_x = 5;
    int ball_speed_y = 5;
    int ball_radius = 15;
    cout << "Starting the game..." << endl;

    InitWindow(screenWidth, screenHeight, "My first RAY_LIB Program for SNAKE");
    SetTargetFPS(60);

    // Loop del juego
    while (WindowShouldClose() == false)
    {
        BeginDrawing(); 
        // Dibujando
        ClearBackground(BLACK);
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        if(ball_x+ball_radius >= screenWidth || ball_y+ball_radius <= 0){
            ball_speed_x *= -1;
        }
        if(ball_y + ball_radius >= screenHeight  || ball_y - ball_radius <= 0) {
            ball_speed_y *= -1;
        }

        DrawCircle(ball_x,ball_y,ball_radius, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}