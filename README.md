# Sorting-Visualization

Sorting algorithm visualizer written in C with OpenGL

The graphics are done with OpenGL. After the menu creation, an array is randomly generated and sorted, then played back at the desired speed that was set\
Audible tones are also generated and played through the speakers using `libasound2`

## Installation
You need the OpenGL dev packages and the ALSA dev packages\
`sudo apt-get install freeglut3-dev`\
`sudo apt-get install libasound2-dev`

Afterwards clone and make
```
git clone git@github.com:Codyne/Sorting-Visualization.git
cd Sorting-Visualization/
make
./sortvis
```

## Options

`Sorting Algorithm`: Currently can choose between a handful of sorting algorithms: bubble, selection, insertion, quick, merge, heap, radix, and cocktail.\
`Array Size`: Size of array to be sorted. The arrays contain values equally distributed between `0 - (n-1)` and placed at random indexes.\
`Speed`: How fast to play the sorting animation. Higher is faster.
