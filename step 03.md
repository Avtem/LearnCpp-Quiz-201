C) Next, we're going to implement the 4x4 grid of tiles that represents the puzzle.  By the end of this step, we'll be able to print our puzzle to the console.

Create a class called `Field` that contains a 4x4 array of `Tile`.  Store the size of the grid in a (constexpr) symbolic constant, to avoid magic numbers, and in case we want to change the size later.

When you buy a physical version of these puzzles, the puzzles typically start in the solved state -- you have to manually mix them up (by sliding tiles around) before trying to solve them.  Being able to generate solved field will also help us to easily check whether player won or not. So let's initialize our Field to the solved puzzle state.  We'll mix up the tiles in in a later step.

The Field class should have the following functions:
* A default constructor
* An overloaded `operator<<` which will simply draw our field to the screen. First, it prints N blank lines (thus creating an illusion that field always stays at the bottom of the console), then prints the 4x4 grid of tiles.  Use `g_consoleLines` for the value of N (see sample code below for the definition of `g_consoleLines`).

The following program should run:
```cpp
// Increase amount of new lines if your field isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

// Your code goes here

int main()
{
    Field field{};
    std::cout << field;

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

// Increase amount of new lines if your field isn't
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

class Field
{
public:

    Field() = default;

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
    Field field{};
    std::cout << field;

    return 0;
}
```
[/solution]
