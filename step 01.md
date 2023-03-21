A) Because this is going to be a bigger program, let's start with a design exercise.

Goal: Think about how your program will be structured.  We will do this in two steps.

Step 1: What are the top-level things that your program needs to do? (e.g. display the game board)

[solution]
* Display the game board
* Display an individual tile
* Randomize the starting state
* Handle user input
* Slide tiles
* Determine if user won
* Allow the user to quit

[/solution]

Step 2: What classes or namespaces will you use to implement the items outlined in Step 1?  Also, what will your main() function do?  Think about what helper classes or namespaces that you will need.

You can create a diagram, or use two tables like this:
| Primary class/namespace/main | Implements top-level items | Members | Dependencies | 
| --- | --- | --- | --- |
| class Field | Display board the game board<br>... | ... | ... | 
| function main | Main game logic loop<br>... | ... | ... | 

| Helper class/namespace | What does this help with? | Members | Dependencies | 
| --- | --- | --- | --- |
| ... | ... | ... | ... | 


[solution]
| Class/Namespace/main | Implements top-level items | Members (type) | Dependencies |
| --- | --- | --- | --- |
| class Field | Display the game board<br>Randomize the starting state<br>Slide tiles<br>Determine if user won | 2d array of Tile | Random, Tile, Point, Direction | 
| class Tile | Display an individual tile | int display number | none |
| namespace UserInput | Get user input | none | none | 
| function main() | Main game logic loop<br>allow user to quit | none | Field, UserInput |

| Class/Namespace | What does this help with? | Members (type) | Dependencies |
| --- | --- | --- | --- |
| class Point | Indexing the game board tiles | int x-axis and y-axis coordinates none | none |
| class Direction | Make working with Directional commands easier and more intuitive  | enum direction | none |

// We probably want additional text here explaining these choices

[/solution]
