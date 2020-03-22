#include<pthread.h>
#include<vector>
#include <stdio.h>
#include <string.h>



#include "sudoku.h"

int total_solved = 0;
int total = 0;

pthread_mutex_t total_m ;
pthread_mutex_t total_s_m ;



struct mission{
    bool sovle = false ;
    char puzzle[128] ;
    int flag ;
};

struct args{
    bool (*solve_name)(char* , int) ;
    mission *m ;
    int which_space ;
};

// std::vector<mission> mission_queue ; //vector does not support multi threads
std::vector<pthread_t> thread_queue ;
// std::vector<args> args_queue ;
mission mission_queue[1005] ;
args args_queue[1005] ;

//vector version to make missions
// void make_mission(FILE *fp){
//     char puzzle[128] ;
//     while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
//         total++ ;
//         if (strlen(puzzle) >= N) {
//             mission tmp ;
//             tmp.sovle = false ;
//             tmp.flag = total ;
//             strcpy(tmp.puzzle, puzzle) ;
//             mission_queue.push_back(tmp) ;
//         }
//     }
// }

void make_mission(FILE *fp){
    char puzzle[128] ;
    while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
        total++ ;
        if (strlen(puzzle) >= N) {
            strcpy(mission_queue[total-1].puzzle, puzzle) ;
            mission_queue[total-1].sovle = false ;
            mission_queue[total-1].flag = total ;
        }
    }
}

#if (!MULTI_THREAD)
void* solve_sudoku(void *arg){
    args *tmp_args = (args*)arg ;
    bool (*solve)(char * , int) = tmp_args->solve_name ;
    if (strlen((tmp_args->m)->puzzle) >= N) {
        // ++total;
        if (solve((tmp_args->m)->puzzle, tmp_args->which_space)) {
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
    args* tmp_args = (args*)arg ;
    bool (*solve)(char * , int) = tmp_args->solve_name ;
    if (strlen((tmp_args->m)->puzzle) >= N) {
        // pthread_mutex_lock(&total_m) ;
        // ++total;
        // pthread_mutex_unlock(&total_m) ;
        if (solve((tmp_args->m)->puzzle, tmp_args->which_space)) {
            pthread_mutex_lock(&total_s_m) ;
            (tmp_args->m)->sovle = true ;
            // pthread_mutex_lock(&total_s_m) ;
            ++total_solved;
            pthread_mutex_unlock(&total_s_m) ;
        }
        else {
            printf("No: %s", (tmp_args->m)->puzzle);
        }
        // pthread_mutex_unlock(&total_m) ;
    }
}
#endif