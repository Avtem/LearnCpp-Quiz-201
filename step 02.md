B) Goal: First we will start by showing individual tiles on the screen.

Every tile in our program will be an object of a class that we will call `Tile`. Each `Tile` will represent either one of the numbered tiles on our 4x4 grid, or the missing tile. This class should be able to do three things: store the number it represents, being able to tell whether the tile is a missing tile and draw the tile on the screen with appropriate spacing, so that following tile won't stick to the previous one.

[tasks]
Our `Tile` class should have this functionality:
* A default constructor.
* A constructor that lets us create a Tile with a display value.  Because we are not using `0` as a display value, we can use value `0` to identify our missing tile. 
* A `getNum()` access function that returns the value held by the tile.
* An `isEmpty()` member function that returns a bool indicating whether the current tile is the missing tile.
* An overloaded `operator<<` that will display the value held by the tile.

[/tasks]

The following code should compile and produce the output result you can see below the code:
```cpp
int main()
{
    Tile tile1{ 10 };
    Tile tile2{ 8 };
    Tile tile3{ 0 }; // the missing tile
    Tile tile4{ 1 };

    std::cout << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
    std::cout << tile1 << tile2 << tile3 << tile4 << '\n';
    
    std::cout << std::boolalpha << tile1.isEmpty() << ' ' << tile3.isEmpty() << '\n';
    std::cout << "Tile 2 has number: " << tile2.getNum() << "\nTile 4 has number: " << tile4.getNum() << '\n';
    
    return 0;
}
```

Expected output (pay attention to the white spaces):
```text
0123456789ABCDEF
 10   8       1 
false true
Tile 2 has number: 8
Tile 4 has number: 1
```

[solution]

```cpp
#include <iostream>

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

int main()
{
    Tile tile1{ 10 };
    Tile tile2{ 8 };
    Tile tile3{ 0 }; // the missing tile
    Tile tile4{ 1 };

    std::cout << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
    std::cout << tile1 << tile2 << tile3 << tile4 << '\n';

    std::cout << std::boolalpha << tile1.isEmpty() << ' ' << tile3.isEmpty() << '\n';
    std::cout << "Tile 2 has number: " << tile2.getNum() << "\nTile 4 has number: " << tile4.getNum() << '\n';

    return 0;
}
```
[/solution]
