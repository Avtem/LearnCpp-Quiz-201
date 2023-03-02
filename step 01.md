```cpp
// implement class Point and the following members...

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
        return {x + other.x, y + other.y};
    }
    Point operator-(Point other) const
    {
        return {x - other.x, y - other.y};
    }
};
```
