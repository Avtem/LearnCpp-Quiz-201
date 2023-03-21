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

<br></br>
Let's talk about **why** we chose such approach to implement this game.

*Class Field* - if you look at real-game puzzle, it is a very distinct 4x4 board of tiles that are the same size. The main purpose of this class is to store a 2-dimentional array of Tiles that will allow us to easily get and set our tiles. This class is also responsible for randomizing, moving and displaying all our tiles and checking whether our field (board) is solved.

*Class Tile* - it also makes sense to create a class that would represent a single tile. We can display a single tile to the screen and also check the number it holds.

*Namespace UserInput* - functions in this namespace help us to get a valid input from the user without worrying about getting input that does not make sense for our program (like numbers or words).

*Function main()* - this is the place where we write the code at the top abstract level like: create a field, randomize it and ask for input until user wins or exists.

*Class Point and Direction* - purpose of these two can be not obvious for the first glance, but from our experience we found out that making a class for Direction greatly improves readability of our code. Class Point is useful because our game is a grid of tiles, which we often refer to by x-y coordinates like: {0,0} - top left tile, {1,0} - next tile to the right, etc. In conjunction with Direction class we can easily retrieve adjacent tiles which makes our code very easy to read and modify.

Do not worry if you could not understand why we decided to implement those particular classes/namespaces. Seing what should be a class and what should not comes inevitably with a practice.
Now let's code!

[/solution]
