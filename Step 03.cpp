#include <string>
#include <iostream>

class Tile
{
public:
    Tile() = default;
    Tile(int number)
        :m_num(number)
    {
    }
    friend std::ostream& operator<<(std::ostream& stream, Tile tile)
    {
        if(tile.m_num > 9)
            stream << " "  << std::to_string(tile.m_num) << " ";
        else if(tile.m_num > 0)
            stream << "  " << std::to_string(tile.m_num) << " ";
        else if(tile.m_num == 0)
            stream << "    ";
        return stream;
    }
    bool isEmpty() const
    {
        return m_num == 0;
    }
    int getNum() const { return m_num; }
private:
    int m_num;
};
