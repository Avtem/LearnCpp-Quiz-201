A) Goal: The first class we are going to implement will be `Tile` class.  Each `Tile` will represent either one of the numbered tiles on our 4x4 grid, or the missing tile.  Each tile will store a single value, representing the value it displays.  So that tiles are aligned properly when printed in a grid, each tile will print 4 characters: one or two spaces, the display value, and then another space.

[solution tasks]
Our `Tile` class should have this functionality:
* A default constructor.
* A constructor that lets us create a Tile with a display value.  Because we are not using `0` as a display value, we can use value `0` to identify our missing tile. 
* A `getNum()` access function that returns the value held by the tile.
* An `isEmpty()` member function that returns a bool indicating whether the current tile is the missing tile.
* An overloaded `operator<<` that will display the value held by the tile.
[/solution]

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