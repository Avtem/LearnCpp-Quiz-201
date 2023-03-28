G) Goal: Add the ability for players to slide the tiles on the board.

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

Implement this by adding a member function `moveTile(Direction)` to the class `Board`.  Add this to your game loop from step E.  If the user successfully slides a tile, the game should redraw the updated board.

[tasks]

Implement the following member functions in our `Board` class:
* A function which returns a bool indicating whether a given Point is valid (within our Board).
* A function that finds and returns the position of empty tile as a `Point`.  We could just keep track of where the empty tile is, but that introduces a class invariant, and finding the empty tile whenever we need it isn't that expensive.
* A function that will swap two tiles given their Point indices.
* A `moveTile(Direction dir)` function that will try to move a tile in a given direction and will return `true` if it succeeds.  This function should implement the procedure outlined above.

Modify the `main()` from step E so that `moveTile()` is called if a directional command is entered.  If the move was successful, redraw the board.

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
