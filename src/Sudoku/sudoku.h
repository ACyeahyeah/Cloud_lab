#ifndef SUDOKU_H
#define SUDOKU_H

const bool DEBUG_MODE = false;
enum { ROW=9, COL=9, N = 81, NEIGHBOR = 20 };
const int NUM = 9;

extern int neighbors[N][NEIGHBOR];
// extern int board[N];
// extern int spaces[N];
// extern int nspaces;
// extern int (*chess)[COL];
// int (*chess)[COL];

void init_neighbors();
void input(const char in[N]);
void init_cache();

bool available(int guess, int cell);

bool solve_sudoku_basic(const char puzzle[N], int which_space);
bool solve_sudoku_min_arity(const char puzzle[N], int which_space);
bool solve_sudoku_min_arity_cache(const char puzzle[N], int which_space);
bool solve_sudoku_dancing_links(const char puzzle[N], int unused);
bool solved(int board[N]);
#endif
