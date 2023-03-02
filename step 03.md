// implement class Direction and the following members...
// implement namespace UserInput which will contain the following functionality...

#include <iostream>
#include <array>
#include <random>
#include <assert.h>

// DEPENDENCIES:
// ... code from Step 01

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
        static const std::array<Point, 4> dirs{{ {0,-1}, {0,1}, {-1,0}, {1,0} }};
        return dirs[m_type];
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

    static Direction getRandomDirection()
    {
        static std::mt19937 mt(std::random_device{}());
        return Direction(Type(mt() % Type::max_directions));
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