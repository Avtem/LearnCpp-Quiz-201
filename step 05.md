```cpp
// Finish implementing class Field, so that we can randomize and process UserInput...

// DEPENDENCIES:
// ... code from Step 01
// ... code from Step 02
// ... code from Step 03
// ... code from Step 04

// Part II of Field class:
// class Field
// { ...
    Point getEmptyTilePos()
    {
        for(int y = 0; y < SIZE; ++y)
            for(int x = 0; x < SIZE; ++x)
                if(m_tiles[y][x].isEmpty())
                    return {x,y};

        assert(0 && "There is no empty tile in the field!!!");
        return {-1,-1};
    }



    static bool isValidTilePos(Point pt)
    {
        return (pt.x >= 0 && pt.x < SIZE)
            && (pt.y >= 0 && pt.y < SIZE);
    }

    // if adj. point is invalid, it returns the origin
    Point getAdjPoint(const Point& origin, Direction dir)
    {
        Point copy = origin + Point(dir);

        if(isValidTilePos(copy))
            return copy;

        // that adj tile is not valid, so return the origin point
        return origin;
    }

    void swapTiles(Point pt1, Point pt2)
    {
        std::swap(m_tiles[pt1.y][pt1.x], m_tiles[pt2.y][pt2.x]);
    }



    // returns true if user moved successfully
    bool moveTiles(Direction dir)
    {
        Point emptyTile{getEmptyTilePos()};
        Point movingTile = getAdjPoint(emptyTile, -dir);
        // we didn't move
        if(emptyTile == movingTile)
            return false;

        swapTiles(movingTile, emptyTile);
        return true;
    }


    void randomize()
    {
        // just move empty tile randomly 1000 times
        // (just like you would do in real life)
        for(int i = 0; i < 1000; ++i)
        {
            Point pt0tile{getEmptyTilePos()};
            Point ptAdj{pt0tile};
            // if random direction lead us to nowhere, try again
            while(pt0tile == ptAdj)
                ptAdj = getAdjPoint(pt0tile, Direction::getRandomDirection());

            swapTiles(pt0tile, ptAdj);
        }
    }
    ```
    
