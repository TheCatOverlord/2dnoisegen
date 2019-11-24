#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define X 10
#define Y 10
#define FREQ 20


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

int main (int argc, char** argv)
{
    if (argc > 1)
        InitNoise(atoi(argv[1]));
    else InitNoise(12345678);

    for (int x = 0; x < X; x++)
    {
        for (int y = 0; y < Y; y++)
        {
            printf("%0.2f, ", GetNoiseValue(x, y));
        }
        printf("\n");
    }
    
}