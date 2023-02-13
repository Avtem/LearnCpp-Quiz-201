#include <vector>   // for std::vector
#include <assert.h> // for debugging purposes
#include <iostream> // input-output
#include <random> // for generating random directions

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// reads a character from the user input
char getCharacter()
{
    char operation{};
    std::cin >> operation;
    ignoreLine(); // remove any extraneous input
    return operation;
}

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
    // so hide it from the public by declaring it “private”.
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

    friend std::ostream& operator<<(std::ostream& stream, const Direction& dir);
};
const std::vector<Point> Direction::m_dirs ={{0,-1}, {0,1}, {-1,0}, {1,0}};
