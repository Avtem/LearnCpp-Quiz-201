B) Next, we're going to implement the 4x4 grid of tiles.  We'll call this grid a `Field`.

Create a class called Field, containing a 2-dimensional array of Tile.  Make sure the size of the grid is not a magic number (hint: store it in a constant).

The Field class should have the following functions:
* A member function called `createSolvedField()` that overwrites the value of the Tile objects in the grid to those of a solved grid.
* A default constructor that calls `createSolvedField()`.
* An overloaded `operator<<` that first prints N blank lines, then prints the 4x4 grid of tiles.  The value of N should be defined as a global constant at the top of the program, and defaulted to value 25.

// NOTES: createSolvedField() needs a better description.  N needs a better description.

The following program should run:
```cpp
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
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include "Random.h"

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

    // create field that looks like 1,2,3,4,5,6 ... 14,15,0
    void createSolvedField()
    {
        for (int y = 0, i = 1; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x, ++i)
                m_tiles[y][x] = Tile(i);

        // init empty cell
        m_tiles[SIZE - 1][SIZE - 1] = Tile(0);
    }

private:
    static const int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{};
};

int main()
{
    Field field{};
    std::cout << field;

    return 0;
}
```
[/solution]
