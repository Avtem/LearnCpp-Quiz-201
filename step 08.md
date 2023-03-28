H) Goal: In this step, we'll finish our game. Randomize the initial state of the game board. Also, detect when user wins, so after that we can print a win message and quit the game.

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
