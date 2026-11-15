## What is 2048 game?
2048 is a single-player sliding number puzzle. The player slides numbered tiles on a 4x4 grid. When two tiles with the same number touch, they merge into one tile that holds their sum. The goal is to create a tile with the value 2048.

## Rules:
-	The board is a 4x4 grid (16 cells). At the start, two tiles appear, each with the value 2 (or sometimes 4).
-	The player chooses one of four directions: left, right, up or down. Every tile slides as far as it can in that direction.
-	If two tiles with the same value collide, they merge into one tile with double the value (2+2=4, 4+4=8, and so on). The merged value is added to the score.
-	A tile can only merge once per move. For example, a row of 2, 2, 2, 2 becomes 4, 4 after one move, not 8.
-	After every move that actually changes the board, a new tile (2 with 90% chance, 4 with 10% chance) appears in a random empty cell.
-	The player wins when a 2048 tile is created. The game is lost when the board is full and no two neighbouring tiles are equal, so no move is possible.

## Example

Consider the following 4×4 board before moving left:

**Before moving left:**
```
2   0   4   2
2   2   2   2
0   0   4   4
4   0   0   4
```

**After moving left:**
```
2   4   2   0
4   4   0   0
8   0   0   0
8   0   0   0
```

Each row follows three steps:

1. **Shifting:** Empty cells are removed by moving all non-zero tiles towards the left.
2. **Merging:** Adjacent tiles with equal values are combined into one tile with double their value.
3. **Filling:** The remaining empty cells are filled with zeros.

For example, the row `2  2  2  2` becomes `4  4  0  0` after moving left. Each pair merges only once during a move.

## How Game is Implemented in Code:

| **Part of the Code** | **Purpose** |
|---|---|
| `board[4][4]` | Stores the value of every tile. 0 represents an empty cell. |
| `generatetile()` | Collects all empty cells and places a new 2 or 4 in a random one. |
| `shiftleft()` & `moveleft()` | Slides and merges every row to the left and updates the score. |
| `shiftright()` & `moveright()` | Slides and merges every row to the right and updates the score. |
| `shiftup()` & `moveup()` | Slides and merges tiles upwards and updates the score. |
| `shiftdown()` & `movedown()` | Slides and merges tiles downwards and updates the score. |
| Main loop (SFML) | Handles keyboard and mouse events and draws the board, tiles and score. |

## Conclusion:
This project applies core programming fundamentals: arrays, functions, loops, conditions, and structured code. It also shows how to use an external library (SFML) for graphics and how to manage code with GitHub. The result is a playable 2048 game with scoring, restart, win and game-over handling.
