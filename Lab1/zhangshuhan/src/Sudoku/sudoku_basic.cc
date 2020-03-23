#include <assert.h>
#include <stdio.h>

#include <algorithm>

#include "sudoku.h"


struct sudoku_basic
{
  /* data */
  int board[N];
  int spaces[N];
  int nspaces;
  // int (*chess)[COL] = (int (*)[COL])board;

  void find_spaces()
  {
    nspaces = 0;
    for (int cell = 0; cell < N; ++cell) {
      if (board[cell] == 0)
        spaces[nspaces++] = cell;
    }
  }

  void input(const char in[N])
  {
    for (int cell = 0; cell < N; ++cell) {
      board[cell] = in[cell] - '0';
      assert(0 <= board[cell] && board[cell] <= NUM);
    }
    find_spaces();
  }
  
  void get_result(char * puzzle)
  {
    for (int cell = 0; cell < N; ++cell) {
      puzzle[cell] = board[cell] + '0';
      assert('0' <= puzzle[cell] && puzzle[cell] <= '9');
    }
  }

  bool available(int guess, int cell)
  {
    for (int i = 0; i < NEIGHBOR; ++i) {
      int neighbor = neighbors[cell][i];
      if (board[neighbor] == guess) {
        return false;
      }
    }
    return true;
  }

  bool solve_sudoku_basic(int which_space)
  {
    if (which_space >= nspaces) {
      return true;
    }

    // find_min_arity(which_space);
    int cell = spaces[which_space];

    for (int guess = 1; guess <= NUM; ++guess) {
      if (available(guess, cell)) {
        // hold
        assert(board[cell] == 0);
        board[cell] = guess;

        // try
        if (solve_sudoku_basic(which_space+1)) {
          return true;
        }

        // unhold
        assert(board[cell] == guess);
        board[cell] = 0;
      }
    }
    return false;
  }
};

bool solve_sudoku_basic(char * puzzle, int which_space){
  sudoku_basic basic ;
  basic.input(puzzle) ;
  bool a = basic.solve_sudoku_basic(which_space);
  if (!solved(basic.board) && a == true)
    assert(0);
  if (a == true){
    basic.get_result(puzzle) ;
#if DEBUG_RES
    printf("%s", puzzle) ;
#endif 
  }
  return a ;
}

