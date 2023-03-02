// implement class Field and the following members... so that we can createSolvedField(), detect whether playerWon() and draw() the field to the screen.

#include <iostream>

// DEPENDENCIES:
// ... code from Step 02

class Field
{
public:

    Field()
    {
        createSolvedField();
    }

    // create field that looks like 1,2,3,4,5,6 ... 14,15,0
    void createSolvedField()
    {
        for(int y = 0, i = 1; y < SIZE; ++y)
            for(int x = 0; x < SIZE; ++x, ++i)
                m_tiles[y][x] = Tile(i);

        // init empty cell
        m_tiles[SIZE - 1][SIZE - 1] = Tile(0);
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

        for(int y = 0; y < SIZE; ++y)
        {
            for(int x = 0; x < SIZE; ++x)
                std::cout << m_tiles[y][x];
            std::cout << '\n';
        }
    }

    // Compare two fields to see if they are equal
    friend bool operator==(const Field& f1, const Field& f2)
    {
        for(int y = 0; y < SIZE; ++y)
            for(int x = 0; x < SIZE; ++x)
                if(f1.m_tiles[y][x].getNum() != f2.m_tiles[y][x].getNum())
                    return false;

        return true;
    }

    bool playerWon() const
    {
        static Field s_solved{};  // generate a solved field
        return s_solved == *this; // player wins if current field == solved field
    }

private:
    void printEmptyLines(int count) const
    {
        for(int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    static const int SIZE = 4;
    Tile m_tiles[SIZE][SIZE]{};
};