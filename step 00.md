### quiz 4

Let's implement the classic game [15 Puzzle](https://en.wikipedia.org/wiki/15_puzzle)!

In 15 Puzzle, you begin with a randomized 4x4 grid of tiles.  15 of the tiles have numbers 1 through 15.  One tile is missing.

For example:

```text
     15   1   4
  2   5   9  12
  7   8  11  14
 10  13   6   3
```

In this puzzle, the missing tile is in the upper-left corner.

Each turn of the game, you pick one of the tiles that is adjacent to the missing tile, and slide it into the spot occupied by the missing tile.

The goal of the game is to slide tiles around until they are in numerical order, with the missing tile in the bottom right corner:

```text
  1   2   3   4
  5   6   7   8
  9  10  11  12
 13  14  15   
```

Because this is going to be a longer program, we'll develop it in stages.
