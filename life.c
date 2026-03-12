#include <memory.h>
#include "life.h"

void reset_map(Grid map){
    memset(map, 0, sizeof(Grid));
}
void copy_map(Grid map, Grid new_map) {
    memcpy(new_map, map, sizeof(Grid));
}

void set_neighbor(Grid map, int row, int col) {

}

int neighbor_count(Grid map, int row, int col){
    int count = 0;
    int i = 0;
    while(i <= 9) {
        switch(i) {
            case 1:
                if(row - 1 == 0 || col - 1 == 0) break;
                if(map[row-1][col-1] == ALIVE) count++;
                break;
            case 2:
                if(row - 1 == 0) break;
                if(map[row][col-1] == ALIVE) count++;
                break;
            case 3:
                if(row - 1 == 0 || col + 1 > MAX_COL) break;
                if(map[row-1][col+1] == ALIVE) count++;
                break;
            case 4:
                if(col - 1 == 0) break;
                if(map[row][col-1] == ALIVE) count++;
                break;
            case 6:
                if(col + 1 == 0) break;
                if(map[row][col+1] == ALIVE) count++;
                break;
            case 7:
                if(row + 1 > MAX_ROW || col - 1 == 0) break;
                if(map[row+1][col-1] == ALIVE) count++;
                break;
            case 8:
                if(row + 1 > MAX_ROW) break;
                if(map[row+1][col] == ALIVE) count++;
                break;
            case 9:
                if(row + 1 == MAX_ROW || col + 1 > MAX_COL) break;
                if(map[row+1][col+1] == ALIVE) count++;
                break;
            case 5:
            default:
                break;
        }
        i++;
    }

    return count;
}
