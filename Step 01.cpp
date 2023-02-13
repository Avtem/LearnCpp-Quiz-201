class Point
{
public:
    int x;
    int y;

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
