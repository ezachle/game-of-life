#include "common.h"

typedef enum state { DEAD, ALIVE } State;
typedef State Grid[MAX_ROW + 2][MAX_COL + 2];

void copy_map(Grid map, Grid new_map);
void reset_map(Grid map);
void set_neighbor(Grid map, int row, int col);
int neighbor_count(Grid map, int row, int col);

void draw_map(Grid map);
void draw_neighbor(int row, int col);
