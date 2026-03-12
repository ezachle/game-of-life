/*
 * The rules to the cellular simulation of Game of Life are as follows:
 * 1. Neighbors of a cell are the eight cells that touch it vertically, 
 *    horizontally and diagonally.
 * 2. If a cell is alive but it has no neighboring cells alive or one cell alive.
 *    In the next generation, it will die of loneliness.
 * 3. If a cell is alive and has four or more neighbors surrounding it that are
 *    alive, it will die of overpopulation in the next generation.
 * 4. A living cell with either two or more neighbors alive will remain alive in
 *    the next generation.
 * 5. If a cell is dead, but has three surrounding neighbors that are alive, **no
 *    more or fewer**, it will become alive. 
 * 6. Birth and death will take the same time, so dying cells can give help birth
 *    to another, but cannot prevent the death of others by reducing overpopulation
 *    or kill cells in the previous generation.
 *
 */
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "life.h"

int main() {
    bool paused = true;
    Vector2 mouse_pos;
    Vector2 cell_pos;
    Grid map;
    Grid new_gen;

    reset_map(map);

#ifdef DEBUG
    int x = neighbor_count(map, 5, 4);
    x = neighbor_count(new_gen, 5, 4);
    printf("%d\n",x);
#endif

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");

    while(!WindowShouldClose()) {
        if(IsKeyPressed(KEY_SPACE)) paused = !paused;
        if(paused == true) {
            if(IsKeyPressed(KEY_R)) reset_map(map);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mouse_pos = GetMousePosition();
                cell_pos.x = ceil(mouse_pos.x / CELL_SIZE);
                cell_pos.y = ceil(mouse_pos.y / CELL_SIZE);
                printf("%f %f %d\n", cell_pos.x, cell_pos.y, __LINE__);
                map[(int)cell_pos.x ][(int)cell_pos.y ] = ALIVE;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for(int row = 0; row <= MAX_ROW; row++) {
            for(int col = 0; col <= MAX_COL; col++) {
                if(map[row][col] == ALIVE) {
                    // Draw grid lines
                    Vector2 circle_pos = {
                        (row * CELL_SIZE) - (CELL_SIZE / 2),
                        (col * CELL_SIZE) - (CELL_SIZE / 2)
                    };

                    DrawCircleV(circle_pos, CELL_SIZE * 0.4, WHITE);
                }
                // Draw grid lines
                DrawRectangleLines(row * CELL_SIZE, col * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
            }
        }

        if(paused) {
            int font_size = CELL_SIZE * .3;
            int width = MeasureText("PAUSED", font_size);
            DrawText("PAUSED", (SCREEN_WIDTH/2) - width, (SCREEN_HEIGHT/2) - width, font_size, BLUE);

        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
