# Sorting-Visualization

Sorting algorithm visualizer written in C with OpenGL

## Installation
You need the OpenGL dev packages\
`sudo apt-get install freeglut3-dev`

Afterwards clone and make
```
git clone git@github.com:Codyne/Sorting-Visualization.git
cd Sorting-Visualization/
make
```

## Options

`Sorting Algorithm`: Currently can choose between 4 sorting algorithms: bubble, quick, merge, and heap.\
`Array Size`: Array size can be any number >= 3. The arrays are randomly generated with values 0 to n.\
`Swaps Per Second`: How fast to play the sorting animation. Must be 1 or more. Use higher numbers to speed up visualizer.
