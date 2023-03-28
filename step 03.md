C) Goal: Create a solved board (4x4 grid of tiles) and display it on the screen.

Define a `Board` class that will represent 4x4 grid of tiles. A newly created `Board` object should be in the solved state.  To display the board, first print `g_consoleLines` (defined in code snippet below) empty lines and then print the board itself.  Doing so will ensure that any prior output is pushed out of view so that only the current board is visible on the console.

Why initiate the board in the solved state?  When you buy a physical version of these puzzles, the puzzles typically start in the solved state -- you have to manually mix them up (by sliding tiles around) before trying to solve them.  We will mimic that process in our program (we'll do the mixing up in a future step).

[tasks]
The `Board` class should have the following functionality:
* A `constexpr` symbolic constant, set to the size of the grid (you can assume the grid is square).
* A two-dimentional array of `Tile` objects, which will hold our 16 numbers.  These should start in the solved state.
* A default constructor.
* An overloaded `operator<<` which will print N blank lines (where N = the value of `g_consoleLines`) and then draw the board to the console.
[/tasks]

The following program should run:
```cpp
// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

// Your code goes here

int main()
{
    Board board{};
    std::cout << board;

    return 0;
}
```

and output the following:
```text

























  1   2   3   4
  5   6   7   8
  9  10  11  12
 13  14  15
```

[solution]
```cpp
#include <iostream>

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

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

    return 0;
}
```
[/solution]
