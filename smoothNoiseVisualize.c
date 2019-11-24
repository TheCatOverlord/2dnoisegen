#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define X 600
#define Y 600
#define FREQ 50

float noiseMap[X][Y];

float Distance(int xPos,int yPos, int xPeak,int yPeak)
{
    return sqrt(pow(xPos - xPeak, 2) +  pow(yPos - yPeak, 2));
}

float GetNoiseValue(int x, int y)
{
    return noiseMap[x][y];
}

int InitNoise(int seed)
{
    printf("[INFO] Generating Noise...\n");
    int peakX[FREQ];
    int peakY[FREQ];
    float largestDistance;
    float tmpDistance;

    // Init random
    srand(seed);
    printf("[INFO] Using %d as seed.\n", seed);

    printf("[INFO] Generating %d peaks...\n", FREQ);
    // Generate high points
    for (int i = 0; i < FREQ; i++)
    {
        peakX[i] = rand() % X;
        peakY[i] = rand() % Y;
    }

    printf("[INFO] Calculating distance values...\n");
    // Calculate distance values from the peaks
    for (int x = 0; x < X; x++)
    {
        for (int y = 0; y < Y; y++)
        {
            noiseMap[x][y] = 10000;
            for (int i = 0; i < FREQ; i++)
            {
                tmpDistance = Distance(x, y, peakX[i], peakY[i]);
                if (tmpDistance < noiseMap[x][y]) { noiseMap[x][y] = tmpDistance; }
            }
            if (noiseMap[x][y] > largestDistance) { largestDistance = noiseMap[x][y]; }
        }
    }

    printf("[INFO] Normalizing noise map...\n");
    // Normalize map 
    for (int x = 0; x < X; x++)
    {
        for (int y = 0; y < Y; y++)
        {
            noiseMap[x][y] = noiseMap[x][y] / largestDistance;
        }
    }
    printf("[INFO] Done...\n");
}

int main(void)
{
    const int screenWidth = X;
    const int screenHeight = Y;

    // Init noise
    InitNoise(87654321);
    InitWindow(screenWidth, screenHeight, "Smooth 2d Noise");

    bool isNoise;
    float threshold = 0.5f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_Q)) isNoise = !isNoise;
        if (IsKeyPressed(KEY_W)) threshold += 0.05f;
        if (IsKeyPressed(KEY_S)) threshold -= 0.05f;

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            if (isNoise)
            {
                for (int x = 0; x < X; x++)
                {
                    for (int y = 0; y < Y; y++)
                    {
                        DrawPixel(x, y, (Color) { 255, 255, 255, GetNoiseValue(x, y) * 255 });
                    }
                }
            } else 
            {
                for (int x = 0; x < X; x++)
                {
                    for (int y = 0; y < Y; y++)
                    {
                        if (GetNoiseValue(x, y) > threshold ) DrawPixel(x, y, (Color) { 255, 255, 255, 255 });
                    }
                }
            }

            DrawText(TextFormat("Threshold: %0.2f", threshold), 20, 20, 15, RED);
            if (isNoise) DrawText("Noise", 20, 40, 15, RED);
            else DrawText("Threshold", 20, 40, 15, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}