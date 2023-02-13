#include <iostream>

int main()
{
    Point p1{1,2};
    Point p2{3,4};
    const Point pRes{4,6};
    std::cout << std::boolalpha << ((p1 + p2) == pRes) << '\n';
    std::cout << ((p1 - p2) == Point{-2, -2}) << '\n';
    std::cout << (p1 != p2);
}
