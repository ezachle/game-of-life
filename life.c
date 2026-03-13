#include <memory.h>
#include "life.h"

void reset_map(Grid map){
    memset(map, 0, sizeof(Grid));
}
void copy_map(Grid map, Grid new_map) {
    memcpy(new_map, map, sizeof(Grid));
}

int neighbor_count(Grid map, int row, int col){
    int count = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0) continue;
            if(map[row+i][col+j] == ALIVE) count++;
        }
    }
    return count;
}

void update_map(Grid map) {
    Grid next_gen = {0};
    for(int r = 1; r <= MAX_ROW; r++) {
        for(int c = 1; c <= MAX_ROW; c++) {
            int n_count = neighbor_count(map, r, c);
            if(map[r][c] == ALIVE) {
                // Rule 4
                next_gen[r][c] = (n_count == 2 || n_count == 3) ?
                    ALIVE : DEAD;
            } else {
                // Rule 5
                if(n_count == 3) next_gen[r][c] = ALIVE;
            }
        }
    }

    memcpy(map, next_gen, sizeof(Grid));
}
