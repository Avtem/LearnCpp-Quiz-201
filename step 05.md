E) Our game board is a 4x4 grid of `Tile`, which we store in two-dimensional array member `m_tiles` of the `Field` class.  We will access a given tile using its {x, y} coordinates.  For example, the top left tile has coordinate {0, 0}.  The tile to the right of that has coordinate {1, 0} (x becomes 1, y stays 0).  The tile one down from that has coordinate {1, 1}.

Since we'll be working with coordinates a lot, let's create an object to help us manage coordinates as {x, y} pairs of values.

Implement a class type named `Point`.  This should contain:
* Two members to store the x-axis and y-axis coordinates.
* An overloaded `operator==` and `operator!=` to compare two sets of coordinates.
* Implement operator+(Point, Direction).  This will allow us to take a `Point` and add a `Direction` to it, in order to get the `Point` in that direction.  For example, `Point{1, 1}` + `Direction{Direction::right}` == `Point{2, 1}`

The following code should run and print “true” for every test-case:

```cpp
// Your code goes here

int main()
{
    std::cout << std::boolalpha;
    std::cout << (Point{ 1, 1 } + Direction{ Direction::up }     == Point{ 1, 0 }) << '\n';
    std::cout << (Point{ 1, 1 } + Direction{ Direction::down }   == Point{ 1, 2 }) << '\n';
    std::cout << (Point{ 1, 1 } + Direction{ Direction::left }   == Point{ 0, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } + Direction{ Direction::right }  == Point{ 2, 1 }) << '\n';
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

// Increase amount of new lines if your field isn't
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

    explicit Direction(Type type)
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

    friend Point operator+(Point p, Direction d)
    {
        switch (d.getType())
        {
        case Direction::up:     return Point{ p.x,      p.y - 1 };
        case Direction::down:   return Point{ p.x,      p.y + 1 };
        case Direction::left:   return Point{ p.x - 1,  p.y };
        case Direction::right:  return Point{ p.x + 1,  p.y };
        }

        return p;
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

class Field
{
public:

    Field() = default;

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Field& field)
    {
        // Before drawing always print some empty lines
        // so that only one field appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        printEmptyLines(g_consoleLines);

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
                stream << field.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
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
    std::cout << std::boolalpha;
    std::cout << (Point{ 1, 1 } + Direction{ Direction::up }     == Point{ 1, 0 }) << '\n';
    std::cout << (Point{ 1, 1 } + Direction{ Direction::down }   == Point{ 1, 2 }) << '\n';
    std::cout << (Point{ 1, 1 } + Direction{ Direction::left }   == Point{ 0, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } + Direction{ Direction::right }  == Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 1, 2 }) << '\n';
    std::cout << !(Point{ 1, 1 } != Point{ 1, 1 }) << '\n';

    return 0;
}
```
[/solution]
