#include <iostream>
#include <vector>
#include <assert.h>
#include <numeric>
#include <random>
#include <string>


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

class Point
{
public:
    int x;
    int y;

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
        return {x + other.x, y + other.y};
    }
    Point operator-(Point other) const
    {
        return {x - other.x, y - other.y};
    }
};

class Direction
{
public:
    enum DirectionType
    {
        up,
        down,
        left,
        right,
        COUNT,
    };

    Direction(DirectionType type)
        :m_type(type)
    {
    }

    DirectionType getType() const
    {
        return m_type;
    }

    static bool isDirection(char character)
    {
        return character == 'w'
            || character == 'a'
            || character == 's'
            || character == 'd';
    }

    operator Point() const
    {
        return m_dirs[m_type];
    }
    Direction operator-() const
    {
        return getOpposite();
    }
    Direction getOpposite() const
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

    static Direction getDirectionFromUser()
    {
        char dir{'0'};
        while(!isDirection(dir))
            dir = getCharacter();

        return charToDirection(dir);
    }

    static Direction getRand()
    {
        static std::mt19937 mt(std::random_device{}());
        return Direction(DirectionType(mt() % DirectionType::COUNT));
    }

private:
///////////////// member variables:
    DirectionType m_type;
    // vector that represents up, down, left, right as Points
    static const std::vector<Point> m_dirs;

    // this function is used only within this class,
    // so hide it from the public.
    static Direction charToDirection(char character)
    {
        switch(character)
        {
            case 'w': return Direction{up};
            case 's': return Direction{down};
            case 'a': return Direction{left};
            case 'd': return Direction{right};
        }
        assert(0 && "Unsupported direction was passed!");
        return Direction{up};
    }
};

const std::vector<Point>Direction::m_dirs = {{0,-1}, {0,1}, {-1,0}, {1,0}};

class Tile
{
public:
    Tile() = default;
    Tile(int number)
        :m_num(number)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if(tile.m_num > 9)
            stream << " "  << std::to_string(tile.m_num) << " ";
        else if(tile.m_num > 0)
            stream << "  " << std::to_string(tile.m_num) << " ";
        else if(tile.m_num == 0)
            stream << "    ";
        return stream;
    }
    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }
private:
    int m_num;
};



void printEmptyLines(int count)
{
    for(int i = 0; i < count; i++)
        std::cout << '\n';
}

class Field
{
public:
    Field()
    {
        createSolvedField();
        randomizeTiles();
        draw(); // draw tiles for the first time
    }

    void draw() const
    {
        // Before drawing always print some empty lines
        // so that only one field appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        // Increase amount of new lines if your field isn't
        // at the very bottom of the console
        printEmptyLines(25);

        for(int y=0, i=0; y < SIZE; ++y)
        {
            for(int x=0; x < SIZE; ++x, ++i)
                std::cout << m_tiles[y][x];
            std::cout << '\n';
        }
    }

    Point getEmptyTilePos()
    {
        for(int y=0; y < SIZE; ++y)
            for(int x=0; x < SIZE; ++x)
                if(m_tiles[y][x].isEmpty())
                    return {x,y};

        assert(0 && "There is no empty tile in the field!!!");
        return {-1,-1};
    }
    // create field that looks like 1,2,3,4,5,6 ... 14,15,0
    void createSolvedField()
    {
        for(int y = 0, i=1; y < SIZE; ++y)
            for(int x = 0; x < SIZE; ++x, ++i)
                m_tiles[y][x] = Tile(i);

        // init empty cell
        m_tiles[SIZE -1][SIZE -1] = Tile(0);
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

        if(isValidTilePos(copy))
            return copy;
        // that adj tile is not valid, so return the origin point
        return origin;
    }

    void swapTiles(Point pt1, Point pt2)
    {
        std::swap(m_tiles[pt1.y][pt1.x], m_tiles[pt2.y][pt2.x]);
    }

    // returns true if user moved successfully
    bool parseUserInput()
    {
        Direction dir = Direction::getDirectionFromUser();
        Point emptyTile{getEmptyTilePos()};
        Point movingTile = getAdjPoint(emptyTile, -dir);
        // we didn't move
        if(emptyTile == movingTile)
            return false;

        swapTiles(movingTile, emptyTile);
        return true;
    }

    bool playerWon() const
    {
        const Tile* currTile = &m_tiles[0][0];
        for(int i=0; i < SIZE * SIZE -1; ++i, ++currTile)
            if(currTile->getNum() != i +1)
                return false;
        return true;
    }

    void randomizeTiles()
    {
        // default way to shuffle tiles
        // which in 50% will generate an unsolvable tile
        //std::shuffle(tempCopy.begin(), tempCopy.end(), std::random_device());

        // just move empty tile randomly 1000 times
        // (just like you would do in real life)
        for(int i=0; i < 1000; ++i)
        {
            Point pt0tile{getEmptyTilePos()};
            Point ptAdj{pt0tile};
            // if random direction lead us to nowhere, try again
            while(pt0tile == ptAdj)
                ptAdj = getAdjPoint(pt0tile, Direction::getRand());

            swapTiles(pt0tile, ptAdj);
        }
    }

private:
    static const int SIZE = 4;
    Tile m_tiles[SIZE][SIZE];
};

int main()
{
    Field field;
    while(!field.playerWon())
    {
        bool userMoved = field.parseUserInput();
        if(userMoved)
            field.draw();
    }

    std::cout << "\n\nYou won!\n\n";
}
