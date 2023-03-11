E) Our game board is a 4x4 grid of tiles, which we store in a two-dimensional array `m_tiles`.  We will access a given tile using it's {x, y} coordinates.  For example, the top left tile has coordinate {0, 0}.  The tile to the right of that has coordinate {1, 0}.

Since we'll be working with coordinates a lot, let's create an object to help us manage coordinates as {x, y} pairs of values.

Implement a class type named `Point`.  This should contain:
* Two public members to store the x-axis and y-axis coordinates.
* Overloaded operator== and operator!= to compare two sets of coordinates
* Overloaded binary operator+ and binary operator- to add/subtract two sets of coordinates

The following code should run and print “true” for every test-case:

```cpp
#include <iostream>

int main()
{
        Point p1{ 1,2 };
        Point p2{ 3,4 };
        const Point p3{ 4,6 };
        std::cout << std::boolalpha << ((p1 + p2) == p3) << '\n';
        std::cout << ((p1 - p2) == Point{ -2, -2 }) << '\n';
        std::cout << (p1 != p2);

        return 0;
}
```

[solution]
```cpp
#include <iostream>

struct Point
{
    int x{};
    int y{};

    bool operator==(Point other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(Point other) const
    {
        return !(*this == other);
    }
    Point operator+(Point other) const
    {
        return { x + other.x, y + other.y };
    }
    Point operator-(Point other) const
    {
        return { x - other.x, y - other.y };
    }
};

int main()
{
        Point p1{ 1,2 };
        Point p2{ 3,4 };
        const Point p3{ 4,6 };
        std::cout << std::boolalpha << ((p1 + p2) == p3) << '\n';
        std::cout << ((p1 - p2) == Point{ -2, -2 }) << '\n';
        std::cout << (p1 != p2);

        return 0;
}
```
[/solution]
