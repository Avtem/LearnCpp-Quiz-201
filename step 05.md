E) Goal: Implement a helper class that will make it easier for us to handle directional commands.

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
