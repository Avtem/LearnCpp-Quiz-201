The first class we are going to implement will be `Tile` class. Think about Tile objects as Tiles in a real game - they contain a number that they represent, they are visible to you (so we need to be able to print a Tile on the screen) and there is a lack of Tile - an empty spot in a real game, but in our program, we will still make it a Tile object that represents number `0`.

To summarize - you have to implement `class Tile` with this functionality:
* Holding information about the number it represents
* For our convenience let's add isEmpty() method which will return `true` if the tile is empty
* Draw it to the screen using std::ostream<< operator overloading (Make sure you add some spacing around your numbers so that they don't stick together)

The following code should compile and produce the output result you can see below the code:
```cpp
int main()
{
    Tile tile1 {10};
    Tile tile2 {8};
    Tile tile3 {0}; // an empty tile
    Tile tile4 {1};

    std::cout << tile1 << tile2 << tile3 << tile4;
}
```

Expected output (pay attention to the white spaces):
```text
 10   8       1 
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
```
[/solution]
