// Implement main() which will handle all game logic.

// DEPENDENCIES:
// ... code from Step 01
// ... code from Step 02
// ... code from Step 03
// ... code from Step 04
// ... code from Step 05

#include <iostream>

int main()
{
    Field field{};
    field.randomize();
    field.draw();

    while(!field.playerWon())
    {
        char ch{UserInput::getCommandFromUser()};

        // Handle non-direction commands
        if(ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        // Handle direction commands
        Direction dir{UserInput::charToDirection(ch)};

        bool userMoved = field.moveTiles(dir);
        if(userMoved)
            field.draw();
    }

    std::cout << "\n\nYou won!\n\n";
    return 0;
}