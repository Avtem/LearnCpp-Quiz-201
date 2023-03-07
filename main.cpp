#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include "Random.h"

// Increase amount of new lines if your field isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

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

class Field
{
public:

    Field()
    {
        createSolvedField();
    }

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Field &field)
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

    Point getEmptyTilePos()
    {
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                if (m_tiles[y][x].isEmpty())
                    return { x,y };

        assert(0 && "There is no empty tile in the field!!!");
        return { -1,-1 };
    }

    // create field that looks like 1,2,3,4,5,6 ... 14,15,0
    void createSolvedField()
    {
        for (int y = 0, i = 1; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x, ++i)
                m_tiles[y][x] = Tile(i);

        // init empty cell
        m_tiles[SIZE - 1][SIZE - 1] = Tile(0);
    }

    static bool isValidTilePos(Point pt)
    {
        return (pt.x >= 0 && pt.x < SIZE)
            && (pt.y >= 0 && pt.y < SIZE);
    }

    // if adj. point is invalid, it returns the origin
    Point getAdjPoint(const Point& origin, Direction dir)
    {
        Point copy = origin + Point(dir);

        if (isValidTilePos(copy))
            return copy;

        // that adj tile is not valid, so return the origin point
        return origin;
    }

    void swapTiles(Point pt1, Point pt2)
    {
        std::swap(m_tiles[pt1.y][pt1.x], m_tiles[pt2.y][pt2.x]);
    }

    // Compare two fields to see if they are equal
    friend bool operator==(const Field& f1, const Field& f2)
    {
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                if (f1.m_tiles[y][x].getNum() != f2.m_tiles[y][x].getNum())
                    return false;

        return true;
    }

    // returns true if user moved successfully
    bool moveTiles(Direction dir)
    {
        Point emptyTile{ getEmptyTilePos() };
        Point movingTile = getAdjPoint(emptyTile, -dir);
        // we didn't move
        if (emptyTile == movingTile)
            return false;

        swapTiles(movingTile, emptyTile);
        return true;
    }

    bool playerWon() const
    {
        static Field s_solved{};  // generate a solved field
        return s_solved == *this; // player wins if current field == solved field
    }

    void randomize()
    {
        // just move empty tile randomly 1000 times
        // (just like you would do in real life)
        for (int i = 0; i < 1000; ++i)
        {
            Point pt0tile{ getEmptyTilePos() };
            Point ptAdj{ pt0tile };
            // if random direction lead us to nowhere, try again
            while (pt0tile == ptAdj)
                ptAdj = getAdjPoint(pt0tile, Direction::getRandomDirection());

            swapTiles(pt0tile, ptAdj);
        }
    }

private:
    static const int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{};
};

int main()
{
    Field field{};
    field.randomize();
    std::cout << field;

    while (!field.playerWon())
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

        bool userMoved = field.moveTiles(dir);
        if (userMoved)
            std::cout << field;
    }

    std::cout << "\n\nYou won!\n\n";
    return 0;
}
