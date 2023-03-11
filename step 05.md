E) Our game board is a 4x4 grid of tiles, which we store in a two-dimensional array `m_tiles`.  We will access a given tile using it's {y, x} coordinates ([row-oriented data](https://upload.wikimedia.org/wikipedia/commons/thumb/4/4d/Row_and_column_major_order.svg/800px-Row_and_column_major_order.svg.png)).  For example, the top left tile has coordinate {0, 0}.  The tile to the right of that has coordinate {0, 1} (y stays 0, and x becomes 1).

Since we'll be working with coordinates a lot, let's create an object to help us manage coordinates as {x, y} pairs of values.

Implement a class type named `Point`.  This should contain:
* Two public members to store the x-axis and y-axis coordinates.
* Overloaded operator== and operator!= to compare two sets of coordinates
* Overloaded binary operator+ and binary operator- to add/subtract two sets of coordinates

Now we can also implement a conversion operator in class `Direction` which will convert a direction (up, down, left, right) to a `Point` object that would represent the same thing but in a good known cartesian coordinate system (notice, in computer programming Y axis is often reversed -- Y coordinate increases when you go **down** and decreases when you go **up**): up = {0, -1}, left = {-1, 0}, etc.

The following code should run and print “true” for every test-case:

```cpp
// Your code goes here

int main()
{
    // Code to test our Point struct
    Point p1{ 1,2 };
    Point p2{ 3,4 };
    const Point p3{ 4,6 };
    
    // Don't forget to test Direction::operator Point() !
    const Direction direction {Direction::up};
    const Point pointUp{ 0,-1 };
    const Point pointLeft{ -1,0 };

    std::cout << std::boolalpha << ((p1 + p2) == p3) << '\n';
    std::cout << ((p1 - p2) == Point{ -2, -2 }) << '\n';
    std::cout << (p1 != p2) << '\n';
    std::cout << (static_cast<Point>(direction) == pointUp) << '\n';
    std::cout << (static_cast<Point>(direction) != pointLeft) << '\n';
    
    return 0;
}
```

[solution]
```cpp
#include <iostream>
#include <numeric>
#include <array>
#include <assert.h>
#include <string_view>

// Increase amount of new lines if your field isn't
// at the very bottom of the console
constexpr int g_consoleLines{25};


// Struct Point must be at top because other classes depend on it
struct Point
{
    int x{};
    int y{};

    bool operator==(Point other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(Point other) const
    {
        return !(*this == other);
    }
    Point operator+(Point other) const
    {
        return { x + other.x, y + other.y };
    }
    Point operator-(Point other) const
    {
        return { x - other.x, y - other.y };
    }
};

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

    explicit operator Point() const
    {
        static const std::array<Point, 4> dirs{ { {0,-1}, {0,1}, {-1,0}, {1,0} } };
        return dirs[m_type];
    }

    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch(m_type)
        {
            case up:    return Direction{down};
            case down:  return Direction{up};
            case left:  return Direction{right};
            case right: return Direction{left};
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{up};
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
        while(!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch(ch)
        {
            case 'w': return Direction{Direction::up};
            case 's': return Direction{Direction::down};
            case 'a': return Direction{Direction::left};
            case 'd': return Direction{Direction::right};
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{Direction::up};
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
        if(tile.m_num > 9) // if two digit number
            stream << " " << tile.m_num << " ";
        else if(tile.m_num > 0) // if one digit number
            stream << "  " << tile.m_num << " ";
        else if(tile.m_num == 0) // if empty spot
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
        for(int i = 0; i < count; ++i)
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

        for(int y = 0; y < SIZE; ++y)
        {
            for(int x = 0; x < SIZE; ++x)
                stream << field.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

private:
    static const int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{
        Tile {  1 }, Tile {  2 }, Tile {  3 }, Tile {  4 },
        Tile {  5 }, Tile {  6 }, Tile {  7 }, Tile {  8 },
        Tile {  9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile {  0 } };
};

// Note: this function is for single use. You can delete it after testing your code
std::string_view directionToStr(Direction dir)
{
    switch(dir.getType())
    {
        case Direction::up:     return "up";
        case Direction::down:   return "down";
        case Direction::left:   return "left";
        case Direction::right:  return "right";
    }
    assert(0 && "Unsupported direction was passed!");
    return "?";
}

int main()
{
    // Code to test our Point struct
    Point p1{ 1,2 };
    Point p2{ 3,4 };
    const Point p3{ 4,6 };
    
    // Don't forget to test Direction::operator Point() !
    const Direction direction {Direction::up};
    const Point pointUp{ 0,-1 };
    const Point pointLeft{ -1,0 };

    std::cout << std::boolalpha << ((p1 + p2) == p3) << '\n';
    std::cout << ((p1 - p2) == Point{ -2, -2 }) << '\n';
    std::cout << (p1 != p2) << '\n';
    std::cout << (static_cast<Point>(direction) == pointUp) << '\n';
    std::cout << (static_cast<Point>(direction) != pointLeft) << '\n';
    
    return 0;
}
```
[/solution]
