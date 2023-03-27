A) Because this is going to be a bigger program, let's start with a design exercise.

!!!author
If you don't have much experience designing programs up-front, you may find this a bit difficult.  That's expected.  It's less important that you get it right, and more important that you participate and learn.

We will go into more detail on all of these items in subsequent steps, so if you are feeling completely lost, feel free to skip this step.
!!!

Goal: Document the key requirements for this program, and plan how your program will be structured at a high level.  We will do this in two steps.

Step 1: What are the top-level things that your program needs to do?  Here are a few to get you started:

Board things:
* Display the game board
* ...

User things:
* Get commands from user
* ...

[solution]
Board things:
* Display the game board
* Display an individual tile
* Randomize the starting state
* Slide tiles
* Determine if win condition reached

User things:
* Get commands from user
* Handle invalid input
* Allow the user to quit before winning

[/solution]

Step 2: What primary classes or namespaces will you use to implement the items outlined in Step 1?  Also, what will your main() function do?

You can create a diagram, or use two tables like this:
| Primary class/namespace/main | Implements top-level items | Members |
| --- | --- | --- |
| class Board | Display board the game board<br>... | ... |
| function main | Main game logic loop<br>... | ... |

[solution]

| Primary class/Namespace/main | Implements top-level items | Members (type) |
| --- | --- | --- |
| class Board | Display the game board<br>Randomize the starting state<br>Slide tiles<br>Determine if win condition reached | 2d array of Tile |
| class Tile | Display an individual tile | int display number |
| namespace UserInput | Get commands from user<br>Handle invalid input | none |
| function main() | Main game logic loop<br>Allow user to quit before winning | none |

<br/>
Here is some rationale behind the choices above.

* `class Board`: Our game is a 4x4 grid of tiles.  The main purpose of this class is to store and manage the 2-dimensional array of tiles. This class is also responsible for randomizing, moving tiles, displaying the board, and checking whether our board is solved.

* `class Tile`: This class represents a single tile within the game board.  Using a class here allows us to overload the output operator to output a tile in the format we desire.  It also allows us to have well-named member functions that will increase the readability of code related to a single tile.

* `namespace UserInput`: This namespace has functions to get input from the user, to check whether the user input is valid, and to handle invalid input.  Because this doesn't have any state, we don't need a class here.

* `function main()`: This is where our main game loop will be written.  This will handle setup of the game board, coordinate retrieving user input and command processing, and handle exit conditions (when the user wins or enters the quit command).

We also will make use of two helper classes.  The need for these classes may not be obvious at first glance, so don't worry if you didn't come up with anything similar.  Often the need for (or benefit of) helper classes isn't apparent into you get further into the implementation of your program.

[/solution]

Step 3 (extra credit): Can you think of any helper classes or capabilities that will make implementing the above easier or more cohesive?

[solution]

| Helper class/Namespace | What does this help with? | Members (type) | 
| --- | --- | --- |
| class Point | Indexing the game board tiles | int x-axis and y-axis coordinates |
| class Direction | Make working with Directional commands easier and more intuitive  | enum direction |

* `class Point`: Accessing a specific tile in our 2d array of tiles will require 2 indices.  We can think of these as { x-axis, y-axis } index pairs.  This Point class implements such an index pair, to make it easy to pass or return a pair of indices.

* `class Direction`: The user will be entering single-letter (char) commands on the keyboard to slide tiles in cardinal directions (e.g. `'w'`=up, `'a'`=left).  Converting these char commands into a Direction object (representing a cardinal direction) will make our code more intuitive and prevent our code from being littered with char literals (`Direction::left` is more meaningful than `'a'`).

[/solution]

If you had a hard time with this exercise, that's okay.  The goal here was mainly to get you thinking about what you're going to do before you start doing it.

Now, it's time to get implementing!



