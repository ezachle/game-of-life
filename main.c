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
#include "life.h"

typedef struct {
    int x;
    int y;
} VectorI;

int main() {
    double move_timer = 0.0;
    double update_interval = 0.5; // measured in seconds
    bool paused = true;
    Camera2D camera;
    Vector2 mouse_pos;
    VectorI cell_pos;
    Grid map;
    Grid new_gen;

    reset_map(map);

#ifdef DEBUG
    int x = neighbor_count(map, 5, 4);
    x = neighbor_count(new_gen, 5, 4);
    printf("%d\n",x);
#endif

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");

    camera.rotation = 0;
    camera.target = (Vector2){WORLD_WIDTH / 2, WORLD_HEIGHT / 2};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.zoom = 1;
    SetTargetFPS(30);

    while(!WindowShouldClose()) {
        if(IsKeyPressed(KEY_SPACE)) paused = !paused;
        if(paused) {
            if(IsKeyPressed(KEY_RIGHT)) update_interval += 0.1;
            if(IsKeyPressed(KEY_LEFT)) update_interval -= 0.1;
            if(IsKeyPressed(KEY_R)) {
                reset_map(map);
                camera.zoom = 1.0f;
                camera.target = (Vector2){WORLD_WIDTH / 2, WORLD_HEIGHT / 2};
                camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            }
            // TODO: Running the mouse over an ALIVE cell will erase it
            //       add a way to discern the two
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                // Gets the mouse position relative to window and converts that
                // into a position relative to the camera(or world)
                mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);

                cell_pos.x = ceil(mouse_pos.x / CELL_SIZE);
                cell_pos.y = ceil(mouse_pos.y / CELL_SIZE);
                map[cell_pos.y][cell_pos.x] = 
                    (map[cell_pos.y][cell_pos.x] == ALIVE) ?
                    DEAD : ALIVE;
#ifdef DEBUG
                printf("col %d row %d status %d %d\n", cell_pos.x, cell_pos.y, map[cell_pos.x][cell_pos.y],__LINE__);
#endif
            }
        }

        if(paused == false) {
            move_timer += GetFrameTime();
            if(move_timer >= update_interval) {
                update_map(map);
                move_timer = 0;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        double wheel = GetMouseWheelMove();
        if(wheel != 0) {
            Vector2 mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), camera);

            camera.offset = GetMousePosition();
            camera.target = mouse_world_pos;

            camera.zoom += wheel * 0.5f;
            if(camera.zoom < 0.75f) camera.zoom = 0.75f;
            if(camera.zoom > 5.0f) camera.zoom = 5.0f;
        }

        if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 delta = GetMouseDelta();
            // Subtract by the delta because of how
            // coordinates work in computer graphics
            camera.target.x -= delta.x / camera.zoom;
            camera.target.y -= delta.y / camera.zoom;
        }

        for(int row = 1; row <= MAX_ROW; row++) {
            for(int col = 1; col <= MAX_COL; col++) {
                if(map[row][col] == ALIVE) {
                    // Draw grid lines
                    Vector2 circle_pos = {
                        (col * CELL_SIZE) - (CELL_SIZE / 2),
                        (row * CELL_SIZE) - (CELL_SIZE / 2)
                    };

                    DrawCircleV(circle_pos, CELL_SIZE * 0.4, WHITE);
                }

            }
        }

        if(camera.zoom >= 0.75f) {
            for(int row = 0; row <= MAX_ROW; row++) {
                DrawLine(0, row * CELL_SIZE, WORLD_WIDTH, row * CELL_SIZE, GRAY);
            }
            for(int col = 0; col <= MAX_COL; col++) {
                DrawLine(col * CELL_SIZE, 0, col * CELL_SIZE, WORLD_HEIGHT, GRAY);
            }
        }

        EndMode2D();

        if(paused) {
            int font_size = SCREEN_WIDTH * .10;
            int width = MeasureText("PAUSED", font_size);
            DrawText("PAUSED", (SCREEN_WIDTH - width) / 2, SCREEN_HEIGHT - font_size, font_size, BLUE);
            char buf[15];
            sprintf(buf, "Speed: %.2f", update_interval);
            width = MeasureText(buf, font_size);
            DrawText(buf, (SCREEN_WIDTH - width) / 2, SCREEN_HEIGHT - (font_size * 2), font_size, BLUE); 
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
