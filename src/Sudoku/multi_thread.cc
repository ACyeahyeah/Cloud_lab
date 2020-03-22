#include<pthread.h>
#include<vector>
#include <stdio.h>
#include <string.h>

#include "sudoku.h"
#include "multi_thread.h"

// int total_solved = 0;
// int total = 0;

// pthread_mutex_t total_m ;
// pthread_mutex_t total_s_m ;

// std::vector<mission> mission_queue ;
// std::vector<pthread_t> thread_queue ;



void make_mission(FILE *fp){
    char puzzle[128] ;
    while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
        total++ ;
        if (strlen(puzzle) >= N) {
            mission tmp ;
            tmp.sovle = false ;
            strcpy(tmp.puzzle, puzzle) ;
            mission_queue.push_back(tmp) ;
        }
    }
}

#if (!MULTI_THREAD)
void* solve_sudoku(void *arg){
    args *tmp_args = (args*)arg ;
    bool (*solve)(char * , int) = tmp_args->solve_name ;
    if (strlen((tmp_args->m)->puzzle) >= N) {
        // ++total;
        if (solve(m.puzzle, tmp_args->which_space)) {
            (tmp_args->m)->sovle = true ;
            ++total_solved;
        }
        else {
            printf("No: %s", (tmp_args->m)->puzzle);
        }
    }
}
#endif

#if (MULTI_THREAD)
void* solve_sudoku(void *arg){
    args *tmp_args = (args*)arg ;
    bool (*solve)(char * , int) = tmp_args->solve_name ;
    if (strlen((tmp_args->m)->puzzle) >= N) {
        // pthread_mutex_lock(&total_m) ;
        // ++total;
        // pthread_mutex_unlock(&total_m) ;
        if (solve((tmp_args->m)->puzzle, tmp_args->which_space)) {
            (tmp_args->m)->sovle = true ;
            pthread_mutex_lock(&total_s_m) ;
            ++total_solved;
            pthread_mutex_unlock(&total_s_m) ;
        }
        else {
            printf("No: %s", (tmp_args->m)->puzzle);
        }
    }
}
#endif