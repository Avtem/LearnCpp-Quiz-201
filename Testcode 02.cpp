#include <iostream>

std::ostream& operator<<(std::ostream& stream, const Direction& dir)
{
    switch(dir.getType())
    {
        case Direction::up:     stream << "up";     break;
        case Direction::down:   stream << "down";   break;
        case Direction::left:   stream << "left";   break;
        case Direction::right:  stream << "right";  break;
        default:
            assert(0 && "This line should never execute");
    }
    
    return stream;
}

int main()
{
    const Direction up {Direction::up};
    Direction right{Direction::right};

    std::cout << std::boolalpha;
    std::cout << (up.getOpposite().getType() == Direction::down) << '\n';
    std::cout << (right.getOpposite().getType() == Direction::left) << '\n';
    std::cout << Direction::isDirection('w') << '\n';
    std::cout << !Direction::isDirection('o') << '\n';
    std::cout << "Press one of these keys WASD:\n";
    Direction userDir {Direction::getDirectionFromUser()};
    std::cout << "Direction received from the user:\n" << userDir << '\n';
    std::cout << "Random direction: " << Direction::getRand() << '\n';
    std::cout << "Random direction: " << Direction::getRand() << '\n';
    std::cout << "Random direction: " << Direction::getRand() << '\n';
    std::cout << "Random direction: " << Direction::getRand() << '\n';
}
