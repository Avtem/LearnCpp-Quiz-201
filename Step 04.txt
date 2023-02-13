void printEmptyLines(int count)
{
    for(int i = 0; i < count; i++)
        std::cout << '\n';
}

class Field
{
public:
    Field()
    {
        createSolvedField();
        randomizeTiles();
        draw(); // draw tiles for the first time
    }

    void draw() const
    {
        // Before drawing always print some empty lines
        // so that only one field appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space. 
        // Increase amount of new lines if your field isn't
        // at the very bottom of the console
        printEmptyLines(25);

        for(int y=0, i=0; y < SIZE; ++y)
        {
            for(int x=0; x < SIZE; ++x, ++i)
                std::cout << m_tiles[y][x];
            std::cout << '\n';
        }
    }

    Point getEmptyTilePos()
    {
        for(int y=0; y < SIZE; ++y)
            for(int x=0; x < SIZE; ++x)
                if(m_tiles[y][x].isEmpty())
                    return {x,y};

        assert(0 && "There is no empty tile in the field!!!");
        return {-1,-1};
    }
    // create field that looks like 1,2,3,4,5,6 ... 14,15,0
    void createSolvedField()
    {
        for(int y = 0, i=1; y < SIZE; ++y)
            for(int x = 0; x < SIZE; ++x, ++i)
                m_tiles[y][x] = Tile(i);

        // init empty cell
        m_tiles[SIZE -1][SIZE -1] = Tile(0);
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
    bool parseUserInput()
    {
        Direction dir = Direction::getDirectionFromUser();
        Point emptyTile{getEmptyTilePos()};
        Point movingTile = getAdjPoint(emptyTile, -dir);
        // we didn't move
        if(emptyTile == movingTile)
            return false;

        swapTiles(movingTile, emptyTile);
        return true;
    }

    bool playerWon() const
    {
        const Tile* currTile = &m_tiles[0][0];
        for(int i=0; i < SIZE * SIZE -1; ++i, ++currTile)
            if(currTile->getNum() != i +1)
                return false;
        return true;
    }

    void randomizeTiles()
    {
        // default way to shuffle tiles
        // which in 50% will generate an unsolvable tile
        //std::shuffle(tempCopy.begin(), tempCopy.end(), std::random_device());

        // just move empty tile randomly 1000 times
        // (just like you would do in real life)
        for(int i=0; i < 1000; ++i)
        {
            Point pt0tile{getEmptyTilePos()};
            Point ptAdj{pt0tile};
            // if random direction lead us to nowhere, try again
            while(pt0tile == ptAdj)
                ptAdj = getAdjPoint(pt0tile, Direction::getRand());

            swapTiles(pt0tile, ptAdj);
        }
    }

private:
    static const int SIZE = 4;
    Tile m_tiles[SIZE][SIZE];
};

int main()
{
    Field field;
    while(!field.playerWon())
    {
        bool userMoved = field.parseUserInput();
        if(userMoved)
            field.draw();
    }

    std::cout << "\n\nYou won!\n\n";
}
