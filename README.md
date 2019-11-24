# 2dnoisegen
My take on a smooth 2d noise generator

## Compiling noise
```gcc noise.c -o noise -lm```
## Compiling visualizer
```gcc smoothNoiseVisualize.c -o visualize -lm -raylib```

## Running the noise program
```./noise [seed]```\
Replace [seed] with a seed

## Running the visualizer
```./visualize```
