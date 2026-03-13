#include <raylib.h>

//#define DEBUG

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH  800

#define MAX_ROW 10
#define MAX_COL MAX_ROW
#define CELL_SIZE (int)(SCREEN_HEIGHT / MAX_ROW)

typedef enum state { DEAD, ALIVE } State;
typedef State Grid[MAX_ROW + 2][MAX_COL + 2];

void copy_map(Grid map, Grid new_map);
void reset_map(Grid map);
int neighbor_count(Grid map, int row, int col);
void update_map(Grid map);
