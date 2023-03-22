D) Goal: Allow the user to repeatedly input commands by creating namespace `UserInput`. It will help us to process the user input and to slide the puzzle Tiles around in the next step.

These are the 5 commands our game will support (each of which will be input as a single character):
* 'w' - slide tile up
* 'a' - slide tile left
* 's' - slide tile down
* 'd' - slide tile right
* 'q' - quit game

Right now, for commands `w, a, s, d` print `"Valid command: "` and the character the user input. For command `q` print `"\n\nBye!\n\n"` and quit the app

[solution tasks]

Implement the `UserInput` namespace:
* Create a function named `getCommandFromUser()`.  Read in a single character from the user.  If the character is not a valid game command, clear any additional extraneous input, and read in another character from the user.  Repeat until a valid game command is entered.  Return the valid command to the caller.  
* Create as many helper functions as you need.

Update the `main()` function from the prior example, so that it does the following:
* Prints the solved field
* Repeatedly accepts game commands
* If the user inputs `q`, print `"\n\nBye!\n\n"` and quit the app.
* If the user inputs any other valid game command, print `"Valid command: "` and the character the user input.

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

// Increase amount of new lines if your field isn't
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
    Tile m_tiles[SIZE][SIZE] {
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

int main()
{
    Field field{};
    std::cout << field;

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
