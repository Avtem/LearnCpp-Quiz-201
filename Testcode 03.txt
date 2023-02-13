#include <numeric> // for std::iota
#include <iostream>

// Code below is solely for testing Tile class.
int main()
{
    // Note: ALL tiles are initially empty
    Tile tiles[16]{0};
    // So we only have to fill tiles from 1 to 15 and leave tile 16 empty
    std::iota(tiles, tiles +15, 1);

    for(int i=0; i < 16; ++i)
    {
        // Print a new line before printing tile 4, 8 and 12
        if(i && (i % 4 == 0))
            std::cout << '\n';
        std::cout << tiles[i];
    }
}