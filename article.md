## project

Let's implement the classic game [15 Puzzle](https://en.wikipedia.org/wiki/15_puzzle)!

In 15 Puzzle, you begin with a randomized 4x4 grid of tiles.  15 of the tiles have numbers 1 through 15.  One tile is missing.

For example:

```text
     15   1   4
  2   5   9  12
  7   8  11  14
 10  13   6   3
```

In this puzzle, the missing tile is in the upper-left corner.

Each turn of the game, you pick one of the tiles that is adjacent to the missing tile, and slide it into the spot occupied by the missing tile.

The goal of the game is to slide tiles around until they are in numerical order, with the missing tile in the bottom right corner:

```text
  1   2   3   4
  5   6   7   8
  9  10  11  12
 13  14  15   
```

You can play a few rounds [on this site](https://15puzzle.netlify.app/). It will help you to understand how this game works and how it should be implemented.

In our version of the game, each turn the user will enter a single letter command.  There are 5 valid commands:
* w - slide tile up
* a - slide tile left
* s - slide tile down
* d - slide tile right
* q - quit game

Because this is going to be a longer program, we'll develop it in stages.

One more thing: at each step, we'll present two things: a *goal* and *tasks*.  The goal defines the outcome that the step is trying to achieve, along with any additional relevant information.  The tasks provide detail and hints about how to implement the goal.

The tasks will initially be hidden from view, to encourage you to see if you can complete each step using just the goal and sample output or sample program.  If you are unsure how to start, or are feeling stuck, you can unhide the tasks.  They should help get you moving forward.

### step 1

Because this is going to be a bigger program, let's start with a design exercise.

!!!author
If you don't have much experience designing programs up-front, you may find this a bit difficult.  That's expected.  It's less important that you get it right, and more important that you participate and learn.

We will go into more detail on all of these items in subsequent steps, so if you are feeling completely lost, feel free to skip this step.
!!!

Goal: Document the key requirements for this program, and plan how your program will be structured at a high level.  We will do this in three parts.

A) What are the top-level things that your program needs to do?  Here are a few to get you started:

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

B) What primary classes or namespaces will you use to implement the items outlined in Step 1?  Also, what will your main() function do?

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

C) (extra credit) Can you think of any helper classes or capabilities that will make implementing the above easier or more cohesive?

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

### step 2

Goal: Be able to display individual tiles on the screen.

Our game board is a 4x4 grid of tiles that can slide around.  Therefore, it will be useful to have a `Tile` class that represents one of the numbered tiles on our 4x4 grid or the missing tile.  Each tile should be able to:
* Be given a number or be set as the missing tile
* Determine whether it is the missing tile.
* Draw to the console with the appropriate spacing (so the tiles will line up when the board is displayed).  See the sample output below for an example indicating how tiles should be spaced.

[tasks]
Our `Tile` class should have this functionality:
* A default constructor.
* A constructor that lets us create a Tile with a display value.  Because we are not using `0` as a display value, we can use value `0` to identify our missing tile. 
* A `getNum()` access function that returns the value held by the tile.
* An `isEmpty()` member function that returns a bool indicating whether the current tile is the missing tile.
* An overloaded `operator<<` that will display the value held by the tile.

[/tasks]

The following code should compile and produce the output result you can see below the code:
```cpp
int main()
{
    Tile tile1{ 10 };
    Tile tile2{ 8 };
    Tile tile3{ 0 }; // the missing tile
    Tile tile4{ 1 };

    std::cout << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
    std::cout << tile1 << tile2 << tile3 << tile4 << '\n';
    
    std::cout << std::boolalpha << tile1.isEmpty() << ' ' << tile3.isEmpty() << '\n';
    std::cout << "Tile 2 has number: " << tile2.getNum() << "\nTile 4 has number: " << tile4.getNum() << '\n';
    
    return 0;
}
```

Expected output (pay attention to the white spaces):
```text
0123456789ABCDEF
 10   8       1 
false true
Tile 2 has number: 8
Tile 4 has number: 1
```

[solution]

```cpp
#include <iostream>

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if (tile.m_num > 9) // if two digit number
            stream << " " << tile.m_num << " ";
        else if (tile.m_num > 0) // if one digit number
            stream << "  " << tile.m_num << " ";
        else if (tile.m_num == 0) // if empty spot
            stream << "    ";
        return stream;
    }
    
    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num{};
};

int main()
{
    Tile tile1{ 10 };
    Tile tile2{ 8 };
    Tile tile3{ 0 }; // the missing tile
    Tile tile4{ 1 };

    std::cout << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
    std::cout << tile1 << tile2 << tile3 << tile4 << '\n';

    std::cout << std::boolalpha << tile1.isEmpty() << ' ' << tile3.isEmpty() << '\n';
    std::cout << "Tile 2 has number: " << tile2.getNum() << "\nTile 4 has number: " << tile4.getNum() << '\n';

    return 0;
}
```
[/solution]

### step 3

Goal: Create a solved board (4x4 grid of tiles) and display it on the screen.

Define a `Board` class that will represent 4x4 grid of tiles. A newly created `Board` object should be in the solved state.  To display the board, first print `g_consoleLines` (defined in code snippet below) empty lines and then print the board itself.  Doing so will ensure that any prior output is pushed out of view so that only the current board is visible on the console.

Why initiate the board in the solved state?  When you buy a physical version of these puzzles, the puzzles typically start in the solved state -- you have to manually mix them up (by sliding tiles around) before trying to solve them.  We will mimic that process in our program (we'll do the mixing up in a future step).

[tasks]
The `Board` class should have the following functionality:
* A `constexpr` symbolic constant, set to the size of the grid (you can assume the grid is square).
* A two-dimentional array of `Tile` objects, which will hold our 16 numbers.  These should start in the solved state.
* A default constructor.
* An overloaded `operator<<` which will print N blank lines (where N = the value of `g_consoleLines`) and then draw the board to the console.
[/tasks]

The following program should run:
```cpp
// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

// Your code goes here

int main()
{
    Board board{};
    std::cout << board;

    return 0;
}
```

and output the following:
```text

























  1   2   3   4
  5   6   7   8
  9  10  11  12
 13  14  15
```

[solution]
```cpp
#include <iostream>

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if (tile.m_num > 9) // if two digit number
            stream << " " << tile.m_num << " ";
        else if (tile.m_num > 0) // if one digit number
            stream << "  " << tile.m_num << " ";
        else if (tile.m_num == 0) // if empty spot
            stream << "    ";
        return stream;
    }
    
    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num{};
};

class Board
{
public:

    Board() = default;

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Board &board)
    {
        // Before drawing always print some empty lines
        // so that only one board appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        printEmptyLines(g_consoleLines);

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

private:
    static constexpr int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

int main()
{
    Board board{};
    std::cout << board;

    return 0;
}
```
[/solution]

### step 4

Goal: In this step, we'll allow the user to repeatedly input game commands, handle invalid input, and implement the quit game command.

These are the 5 commands our game will support (each of which will be input as a single character):
* 'w' - slide tile up
* 'a' - slide tile left
* 's' - slide tile down
* 'd' - slide tile right
* 'q' - quit game

When the user runs the game, the following should occur:
* The (solved) board should be printed to the console.
* The program should repeatedly get valid game commands from the user.  If the user enters an invalid command or extraneous input, ignore it.

For each valid game command:
* Print `"Valid command: "` and the character the user input.
* If the command is the quit command, also print `"\n\nBye!\n\n"` and then quit the app.

Because our user input routines do not need to maintain any state, implement them inside a namespace named `UserInput`.

[tasks]
Implement the `UserInput` namespace:
* Create a function named `getCommandFromUser()`.  Read in a single character from the user.  If the character is not a valid game command, clear any additional extraneous input, and read in another character from the user.  Repeat until a valid game command is entered.  Return the valid command to the caller.  
* Create as many helper functions as you need.

In main():
* Implement an infinite loop.  Inside the loop, fetch a valid game command, and then handle the commands per the above requirements.

[/solution]

The output of the program should match the following:

```text

























  1   2   3   4
  5   6   7   8
  9  10  11  12
 13  14  15
w
Valid command: w
a
Valid command: a
s
Valid command: s
d
Valid command: d
f
g
h
Valid command: q


Bye!


```

[solution]
```cpp
#include <iostream>
#include <numeric>

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input
        return operation;
    }

    char getCommandFromUser()
    {
        char ch{};
        while (!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

};

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if (tile.m_num > 9) // if two digit number
            stream << " " << tile.m_num << " ";
        else if (tile.m_num > 0) // if one digit number
            stream << "  " << tile.m_num << " ";
        else if (tile.m_num == 0) // if empty spot
            stream << "    ";
        return stream;
    }
    
    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num{};
};

class Board
{
public:

    Board() = default;

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Board &board)
    {
        // Before drawing always print some empty lines
        // so that only one board appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        printEmptyLines(g_consoleLines);

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

private:
    static constexpr int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

int main()
{
    Board board{};
    std::cout << board;

    while (true)
    {
        char ch{ UserInput::getCommandFromUser() };

        // If we reach the line below, "ch" will ALWAYS be a correct command!
        std::cout << "Valid command: " << ch << '\n';
        
        // Handle non-direction commands
        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }
    }

    return 0;
}
```
[/solution]

### step 5

Goal: Implement a helper class that will make it easier for us to handle directional commands.

After implementing the prior step, we can accept commands from the user (as characters 'w', 'a', 's', 'd', and 'q').  These characters are essentially magic numbers in our code.  While it's fine to handle these commands in our `UserInput` namespace and function `main()`, we don't want to propagate them throughout our whole program.  For example, the `Board` class should have no knowledge of what 's' means.

Implement a helper class named `Direction`, which will allow us to create objects that represent the cardinal directions (up, left, down, or right).  `operator-` should return the opposite direction, and `operator<<` should print the direction to the console.  We will also need a member function that will return a Direction object containing a random direction. Lastly, add a function to namespace `UserInput` that converts a directional game command ('w', 'a', 's', or 'd') to a Direction object.

The more we can use `Direction` instead of directional game commands, the easier our code will be to read and understand.

[tasks]
Implement the class `Direction`, which has:
* A public nested enum named `Type` with enumerators `up`, `down`, `left`, `right`, and `max_directions`.
* A private member that stores the actual direction.
* A single argument constructor which allows us to initialize a `Direction` with a `Type` initializer.
* An overloaded `operator-`, which takes a Direction and returns the opposite Direction.
* An overloaded `operator<<`, which outputs the Direction name to the console.
* A static function that returns a Direction with a randomized `Type`.  You can use the `Random::get()` function from the ["Random.h"](https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/#RandomH) header to generate a random number.

Also, in the `UserInput` namespace, add the following:
* A function that will convert a directional game command (character) to a Direction object.

[/tasks]

Finally, modify the program you wrote in the prior step so that the output matches the following:

```text

























  1   2   3   4
  5   6   7   8
  9  10  11  12
 13  14  15
Generating random direction... up
Generating random direction... down
Generating random direction... up
Generating random direction... left

Enter a command: w
You entered direction: up
a
You entered direction: left
s
You entered direction: down
d
You entered direction: right
q


Bye!


```

[solution]
```cpp
#include <cassert>
#include <iostream>
#include <numeric>
#include "Random.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        max_directions,
    };

    Direction(Type type)
        :m_type(type)
    {
    }

    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch (m_type)
        {
        case up:    return Direction{ down };
        case down:  return Direction{ up };
        case left:  return Direction{ right };
        case right: return Direction{ left };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
    }

    friend std::ostream& operator<<(std::ostream& stream, Direction dir)
    {
        switch (dir.getType())
        {
        case Direction::up:     return (stream << "up");
        case Direction::down:   return (stream << "down");
        case Direction::left:   return (stream << "left");
        case Direction::right:  return (stream << "right");
        default:                return (stream << "unknown direction");
        }
    }
    
    static Direction getRandomDirection()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
        return Direction{ random };
    }

private:
    Type m_type{};
};


namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input
        return operation;
    }

    char getCommandFromUser()
    {
        char ch{};
        while (!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w': return Direction{ Direction::up };
        case 's': return Direction{ Direction::down };
        case 'a': return Direction{ Direction::left };
        case 'd': return Direction{ Direction::right };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
};

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if (tile.m_num > 9) // if two digit number
            stream << " " << tile.m_num << " ";
        else if (tile.m_num > 0) // if one digit number
            stream << "  " << tile.m_num << " ";
        else if (tile.m_num == 0) // if empty spot
            stream << "    ";
        return stream;
    }
    
    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num{};
};

class Board
{
public:

    Board() = default;

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Board &board)
    {
        // Before drawing always print some empty lines
        // so that only one board appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        printEmptyLines(g_consoleLines);

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

private:
    static constexpr int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

int main()
{
    Board board{};
    std::cout << board;

    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << "\n\n";

    std::cout << "Enter a command: ";
    while (true)
    {
        char ch{ UserInput::getCommandFromUser() };

        // Handle non-direction commands
        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        // Handle direction commands
        Direction dir{ UserInput::charToDirection(ch) };

        std::cout << "You entered direction: " << dir << '\n';
    }

    return 0;
}
```
[/solution]

### step 6

Goal: Implement a helper class that will make it easier for us to index the tiles in our game board.

Our game board is a 4x4 grid of `Tile`, which we store in two-dimensional array member `m_tiles` of the `Board` class.  We will access a given tile using its {x, y} coordinates.  For example, the top left tile has coordinate {0, 0}.  The tile to the right of that has coordinate {1, 0} (x becomes 1, y stays 0).  The tile one down from that has coordinate {1, 1}.

Since we'll be working with coordinates a lot, create a helper class named `Point` that stores an {x, y} pair of coordinates.  We should be able to compare two Point objects for equality and inequality.  Also implement a member function named `getAdjacentPoint` that takes a Direction object as a parameter and returns the Point in that direction.  For example, `Point{1, 1}.getAdjacentPoint(Direction::right)` == `Point{2, 1}`.

[tasks]
Implement a struct named `Point`.  This should contain:
* Two public data members to store the x-axis and y-axis coordinates.
* An overloaded `operator==` and `operator!=` to compare two sets of coordinates.
* A const member function `Point getAdjacentPoint(Direction)` that returns the Point in the direction of the Direction parameter.  We do not need to do any validity checking here.

We're using a struct instead of a class here because Point is simple bundle of data that would benefit little from being encapsulated.
[/tasks]

Save your `main()` function from the prior step, as you'll need it again in the next step.

The following code should run and print `true` for every test-case:

```cpp
// Your code goes here

// Note: save your main() from the prior step, as you'll need it again in the next step
int main()
{
    std::cout << std::boolalpha;
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::up)    == Point{ 1, 0 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::down)  == Point{ 1, 2 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::left)  == Point{ 0, 1 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::right) == Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 1, 2 }) << '\n';
    std::cout << !(Point{ 1, 1 } != Point{ 1, 1 }) << '\n';

    return 0;
}
```

[solution]
```cpp
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include "Random.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        max_directions,
    };

    Direction(Type type)
        :m_type(type)
    {
    }

    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch (m_type)
        {
        case up:    return Direction{ down };
        case down:  return Direction{ up };
        case left:  return Direction{ right };
        case right: return Direction{ left };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
    }

    friend std::ostream& operator<<(std::ostream& stream, Direction dir)
    {
        switch (dir.getType())
        {
        case Direction::up:     return (stream << "up");
        case Direction::down:   return (stream << "down");
        case Direction::left:   return (stream << "left");
        case Direction::right:  return (stream << "right");
        default:                return (stream << "unknown direction");
        }
    }

    static Direction getRandomDirection()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
        return Direction{ random };
    }

private:
    Type m_type{};
};

struct Point
{
    int x{};
    int y{};

    friend bool operator==(Point p1, Point p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

    friend bool operator!=(Point p1, Point p2)
    {
        return !(p1 == p2);
    }

    Point getAdjacentPoint(Direction dir) const
    {
        switch (dir.getType())
        {
        case Direction::up:     return Point{ x,     y - 1 };
        case Direction::down:   return Point{ x,     y + 1 };
        case Direction::left:   return Point{ x - 1, y };
        case Direction::right:  return Point{ x + 1, y };
        }

        return *this;
    }
};

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input
        return operation;
    }

    char getCommandFromUser()
    {
        char ch{};
        while (!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w': return Direction{ Direction::up };
        case 's': return Direction{ Direction::down };
        case 'a': return Direction{ Direction::left };
        case 'd': return Direction{ Direction::right };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
};

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if (tile.m_num > 9) // if two digit number
            stream << " " << tile.m_num << " ";
        else if (tile.m_num > 0) // if one digit number
            stream << "  " << tile.m_num << " ";
        else if (tile.m_num == 0) // if empty spot
            stream << "    ";
        return stream;
    }
    
    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num{};
};

class Board
{
public:

    Board() = default;

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Board &board)
    {
        // Before drawing always print some empty lines
        // so that only one board appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        printEmptyLines(g_consoleLines);

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

private:
    static constexpr int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::up)    == Point{ 1, 0 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::down)  == Point{ 1, 2 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::left)  == Point{ 0, 1 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::right) == Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 1, 2 }) << '\n';
    std::cout << !(Point{ 1, 1 } != Point{ 1, 1 }) << '\n';

    return 0;
}
```
[/solution]

### step 7

Goal: Add the ability for players to slide the tiles on the board.

First, we should take a closer look at how sliding tiles actually works:

Given a puzzle state that looks like this:

```text
     15   1   4
  2   5   9  12
  7   8  11  14
 10  13   6   3
```

When the user enters 'w' on the keyboard, the only tile that can go up is tile `2`.

After moving the tile, the board looks like this:

```text
  2  15   1   4
      5   9  12
  7   8  11  14
 10  13   6   3
```

So, essentially what happened is we swapped the empty tile with tile `2`.

Let's generalize this procedure.  When the user enters a directional command, we need to:
* Locate the empty tile.
* From the empty tile, find the adjacent tile that is in the direction opposite of the direction the user entered.
* If the adjacent tile is valid (it's not off the grid), swap the empty tile and adjacent tile.
* If the adjacent tile is not valid, do nothing.

Implement this by adding a member function `moveTile(Direction)` to the class `Board`.  Add this to your game loop from step 5.  If the user successfully slides a tile, the game should redraw the updated board.

[tasks]

Implement the following member functions in our `Board` class:
* A function which returns a bool indicating whether a given Point is valid (within our Board).
* A function that finds and returns the position of empty tile as a `Point`.  We could just keep track of where the empty tile is, but that introduces a class invariant, and finding the empty tile whenever we need it isn't that expensive.
* A function that will swap two tiles given their Point indices.
* A `moveTile(Direction dir)` function that will try to move a tile in a given direction and will return `true` if it succeeds.  This function should implement the procedure outlined above.

Modify the `main()` from step 5 so that `moveTile()` is called if a directional command is entered.  If the move was successful, redraw the board.

[/tasks]

[solution]

```cpp
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include "Random.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        max_directions,
    };

    Direction(Type type)
        :m_type(type)
    {
    }

    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch (m_type)
        {
        case up:    return Direction{ down };
        case down:  return Direction{ up };
        case left:  return Direction{ right };
        case right: return Direction{ left };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
    }

    friend std::ostream& operator<<(std::ostream& stream, Direction dir)
    {
        switch (dir.getType())
        {
        case Direction::up:     return (stream << "up");
        case Direction::down:   return (stream << "down");
        case Direction::left:   return (stream << "left");
        case Direction::right:  return (stream << "right");
        default:                return (stream << "unknown direction");
        }
    }

    static Direction getRandomDirection()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
        return Direction{ random };
    }

private:
    Type m_type{};
};

struct Point
{
    int x{};
    int y{};

    friend bool operator==(Point p1, Point p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

    friend bool operator!=(Point p1, Point p2)
    {
        return !(p1 == p2);
    }

    Point getAdjacentPoint(Direction dir) const
    {
        switch (dir.getType())
        {
        case Direction::up:     return Point{ x,     y - 1 };
        case Direction::down:   return Point{ x,     y + 1 };
        case Direction::left:   return Point{ x - 1, y };
        case Direction::right:  return Point{ x + 1, y };
        }

        return *this;
    }
};

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input
        return operation;
    }

    char getCommandFromUser()
    {
        char ch{};
        while (!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w': return Direction{ Direction::up };
        case 's': return Direction{ Direction::down };
        case 'a': return Direction{ Direction::left };
        case 'd': return Direction{ Direction::right };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
};

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if (tile.m_num > 9) // if two digit number
            stream << " " << tile.m_num << " ";
        else if (tile.m_num > 0) // if one digit number
            stream << "  " << tile.m_num << " ";
        else if (tile.m_num == 0) // if empty spot
            stream << "    ";
        return stream;
    }
    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num{};
};

class Board
{
public:

    Board() = default;

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Board& board)
    {
        // Before drawing always print some empty lines
        // so that only one board  appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        printEmptyLines(g_consoleLines);

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

    Point getEmptyTilePos() const
    {
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                if (m_tiles[y][x].isEmpty())
                    return { x,y };

        assert(0 && "There is no empty tile in the board!!!");
        return { -1,-1 };
    }

    static bool isValidTilePos(Point pt)
    {
        return (pt.x >= 0 && pt.x < SIZE)
            && (pt.y >= 0 && pt.y < SIZE);
    }

    void swapTiles(Point pt1, Point pt2)
    {
        std::swap(m_tiles[pt1.y][pt1.x], m_tiles[pt2.y][pt2.x]);
    }

    // returns true if user moved successfully
    bool moveTile(Direction dir)
    {
        Point emptyTile{ getEmptyTilePos() };
        Point adj{ emptyTile.getAdjacentPoint(-dir) };

        if (!isValidTilePos(adj))
            return false;

        swapTiles(adj, emptyTile);
        return true;
    }

private:
    static const int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

int main()
{
    Board board{};
    std::cout << board;

    std::cout << "Enter a command: ";
    while (true)
    {
        char ch{ UserInput::getCommandFromUser() };

        // Handle non-direction commands
        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        // Handle direction commands
        Direction dir{ UserInput::charToDirection(ch) };

        bool userMoved { board.moveTile(dir) };
        if (userMoved)
            std::cout << board;
    }

    return 0;
}
```

[/solution]

### step 8

Goal: In this step, we'll finish our game. Randomize the initial state of the game board. Also, detect when user wins, so after that we can print a win message and quit the game.

We need to be careful about *how* we randomize our puzzle, because not every puzzle is solvable.  For example, there is no way to solve this puzzle:

```text
  1   2   3   4 
  5   6   7   8
  9  10  11  12
 13  15  14
```

If we just blindly randomize the numbers in the puzzle, there is a chance that we will generate such an unsolvable puzzle.  With a physical version of the puzzle, we'd randomize the puzzle by sliding tiles in random directions until the tiles were sufficiently mixed.  The solution for such a randomized puzzle is to slide each tile in the opposite direction that it was slid to randomize it in the first place.  Thus, randomizing puzzles this way always generates a solvable puzzle.

We can have our program randomize the board in the same way.

Once the user has solved the puzzle, the program should print `"\n\nYou won!\n\n"` and then exit normally.

[tasks]
* Add a `randomize()` member function to the `Board` class which randomizes the tiles in the game board.  Pick a random direction and if the adjacent point is valid, then slide a tile in that direction.  Doing this 1000 times should be sufficient to mix up the board.
* Implement operator== in `Board` class which will compare if tiles of two given boards are identical.
* Add `playerWon()` member function to the `Board` class that will return true if the current game board is solved.  You can use the `operator==` you implemented to compare the current game board against a solved game board.  Remember that `Board` objects start in the solved state, so if you need a solved game board, just value initialize a `Board` object!
* Update your main() function to integrate randomize() and playerWon().

[/tasks]

Here is the full solution for our 15 puzzle game:

[solution]

```cpp
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include "Random.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        max_directions,
    };

    Direction(Type type)
        :m_type(type)
    {
    }
    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch (m_type)
        {
        case up:    return Direction{ down };
        case down:  return Direction{ up };
        case left:  return Direction{ right };
        case right: return Direction{ left };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
    }

    friend std::ostream& operator<<(std::ostream& stream, Direction dir)
    {
        switch (dir.getType())
        {
        case Direction::up:     return (stream << "up");
        case Direction::down:   return (stream << "down");
        case Direction::left:   return (stream << "left");
        case Direction::right:  return (stream << "right");
        default:                return (stream << "unknown direction");
        }
    }

    static Direction getRandomDirection()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::max_directions - 1)) };
        return Direction{ random };
    }

private:
    Type m_type{};

};

struct Point
{
    int x{};
    int y{};

    friend bool operator==(Point p1, Point p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

    friend bool operator!=(Point p1, Point p2)
    {
        return !(p1 == p2);
    }

    Point getAdjacentPoint(Direction dir) const
    {
        switch (dir.getType())
        {
        case Direction::up:     return Point{ x,     y - 1 };
        case Direction::down:   return Point{ x,     y + 1 };
        case Direction::left:   return Point{ x - 1, y };
        case Direction::right:  return Point{ x + 1, y };
        }

        return *this;
    }
};

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input
        return operation;
    }

    char getCommandFromUser()
    {
        char ch{};
        while (!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w': return Direction{ Direction::up };
        case 's': return Direction{ Direction::down };
        case 'a': return Direction{ Direction::left };
        case 'd': return Direction{ Direction::right };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
};

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if (tile.m_num > 9) // if two digit number
            stream << " " << tile.m_num << " ";
        else if (tile.m_num > 0) // if one digit number
            stream << "  " << tile.m_num << " ";
        else if (tile.m_num == 0) // if empty spot
            stream << "    ";
        return stream;
    }
    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num{};
};

class Board
{
public:

    Board() = default;

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Board& board)
    {
        // Before drawing always print some empty lines
        // so that only one board appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        printEmptyLines(g_consoleLines);

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

    Point getEmptyTilePos() const
    {
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                if (m_tiles[y][x].isEmpty())
                    return { x,y };

        assert(0 && "There is no empty tile in the board!!!");
        return { -1,-1 };
    }

    static bool isValidTilePos(Point pt)
    {
        return (pt.x >= 0 && pt.x < SIZE)
            && (pt.y >= 0 && pt.y < SIZE);
    }

    void swapTiles(Point pt1, Point pt2)
    {
        std::swap(m_tiles[pt1.y][pt1.x], m_tiles[pt2.y][pt2.x]);
    }

    // Compare two boards to see if they are equal
    friend bool operator==(const Board& f1, const Board& f2)
    {
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                if (f1.m_tiles[y][x].getNum() != f2.m_tiles[y][x].getNum())
                    return false;

        return true;
    }

    // returns true if user moved successfully
    bool moveTile(Direction dir)
    {
        Point emptyTile{ getEmptyTilePos() };
        Point adj{ emptyTile.getAdjacentPoint(-dir) };

        if (!isValidTilePos(adj))
            return false;

        swapTiles(adj, emptyTile);
        return true;
    }

    bool playerWon() const
    {
        static Board s_solved{};  // generate a solved board
        return s_solved == *this; // player wins if current board == solved board
    }

    void randomize()
    {
        // just move empty tile randomly 1000 times
        // (just like you would do in real life)
        for (int i = 0; i < 1000; ++i)
        {
            Point pt0tile{ getEmptyTilePos() };
            Point ptAdj{};
            do
            {
                ptAdj = pt0tile.getAdjacentPoint(Direction::getRandomDirection());
            } while (!isValidTilePos(ptAdj));

            swapTiles(pt0tile, ptAdj);
        }
    }

private:
    static const int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

int main()
{
    Board board{};
    board.randomize();
    std::cout << board;

    while (!board.playerWon())
    {
        char ch{ UserInput::getCommandFromUser() };

        // Handle non-direction commands
        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        // Handle direction commands
        Direction dir{ UserInput::charToDirection(ch) };

        bool userMoved { board.moveTile(dir) };
        if (userMoved)
            std::cout << board;
    }

    std::cout << "\n\nYou won!\n\n";
    return 0;
}
```
[/solution]

[link prevnext]
