D) Goal: In this step, we'll allow the user to repeatedly input game commands, handle invalid input, and implement the quit game command.

These are the 5 commands our game will support (each of which will be input as a single character):
* 'w' - slide tile up
* 'a' - slide tile left
* 's' - slide tile down
* 'd' - slide tile right
* 'q' - quit game

When the user runs the game, the following should occur:
* The (solved) board should be printed to the console.
* The program should repeatedly get valid game commands from the user.  If the user enters an invalid command or extraneous input, ignore it.

For each valid game command:
* Print `"Valid command: "` and the character the user input.
* If the command is the quit command, also print `"\n\nBye!\n\n"` and then quit the app.

Because our user input routines do not need to maintain any state, implement them inside a namespace named 'UserInput`.

[tasks]
Implement the `UserInput` namespace:
* Create a function named `getCommandFromUser()`.  Read in a single character from the user.  If the character is not a valid game command, clear any additional extraneous input, and read in another character from the user.  Repeat until a valid game command is entered.  Return the valid command to the caller.  
* Create as many helper functions as you need.

In main():
* Implement an infinite loop.  Inside the loop, fetch a valid game command, and then handle the commands per the above requirements.

[/solution]

The output of the program should match the following:

```text

























  1   2   3   4
  5   6   7   8
  9  10  11  12
 13  14  15
w
Valid command: w
a
Valid command: a
s
Valid command: s
d
Valid command: d
f
g
h
Valid command: q


Bye!


```

[solution]
```cpp
#include <iostream>
#include <numeric>

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

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

    while (true)
    {
        char ch{ UserInput::getCommandFromUser() };

        // If we reach the line below, "ch" will ALWAYS be a correct command!
        std::cout << "Valid command: " << ch << '\n';
        
        // Handle non-direction commands
        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }
    }

    return 0;
}
```
[/solution]
