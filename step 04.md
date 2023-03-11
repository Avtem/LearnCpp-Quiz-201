D) So now we are getting closer to manipulating the field by user! Right now we can accept commands from the user, but characters `'w', 'a', 's', 'd'` are just numbers of `char` type, so let's implement class `Direction` which will help us to process UserInput and any movement in the field.

Implement the class Direction, which has:
* Enum Type with values up, down, left, right and max direction count
* A member field of type `Type` defined above that stores the actual direction
* A constructor which takes one argument of type `Type`
* `operator-` which will return the opposite direction, but as a new Direction object
* In UserInput:: namespace add a function that will convert a character (command) to a Direction object

The following program should run:
```cpp
#include <iostream>
#include <assert.h>

// Your code goes here


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
    std::cout << "Please enter one of the following:\n"
        << "- a valid direction\n"
        << "- an invalid command\n"
        << "- the quit command\n";

    while(true)
    {
        char ch{UserInput::getCommandFromUser()};

        if(ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        std::cout << "You entered direction: "
                  << directionToStr(UserInput::charToDirection(ch)) << '\n';
    }

    return 0;
}
```
and output the following:
```text
Please enter one of the following:
- a valid direction
- an invalid command
- the quit command
f
r
e
d
You entered direction: right
w
You entered direction: up
s
You entered direction: down
a
You entered direction: left
f
q


Bye!


```

[solution]
```cpp
#include <iostream>
#include <numeric>
#include <assert.h>
#include <string_view>

// Increase amount of new lines if your field isn't
// at the very bottom of the console
constexpr int g_consoleLines{25};

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
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 }};
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
    std::cout << "Please enter one of the following:\n"
        << "- a valid direction\n"
        << "- an invalid command\n"
        << "- the quit command\n";

    while(true)
    {
        char ch{UserInput::getCommandFromUser()};

        if(ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        std::cout << "You entered direction: " << 
                directionToStr(UserInput::charToDirection(ch)) << '\n';
    }

    return 0;
}
```
[/solution]
