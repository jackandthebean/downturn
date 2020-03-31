/* Jacqueline Lee, jacquelinelee
 * CS 152, Winter 2020
 * Project 2
 */

#ifndef BOARD_H
#define BOARD_H

#include "pos.h"

/* === Data Definitions === */
enum cell {
    EMPTY,
    BLACK,
    WHITE
};
typedef enum cell cell;

union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};
typedef union board_rep board_rep;

enum type {
    MATRIX, BITS
};

struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};
typedef struct board board;

/* === Function Declarations === */
/* board_new: create a new (empty) board
 * parameter "width": the width for the new board
 * parameter "height": the height for the new board
 * parameter "type": the type of the new board
 * output: a pointer to the new empty board
 */
board* board_new(unsigned int width, unsigned int height, enum type type);

/* board_free: free a board
 * parameter "b": the pointer to the board to be freed
 * output: void
 */
void board_free(board* b);

/* board_show: print a board to the screen, in the specified format
 * parameter "b": the pointer to the board to be printed
 * output: void
 */
void board_show(board* b);

/* board_get: retrieve the cell at the given position on the board
 * parameter "b": the pointer to the board
 * parameter "p": the position of inquiry
 * output: the cell enum at the given position on the board
 */
cell board_get(board* b, pos p);

/* board_set: modify the cell at the given position on the board
 * parameter "b": the pointer to the board
 * parameter "p": the position of the cell to be modified
 * parameter "c": the cell enum to which the position should be modified
 * output: void
 */
void board_set(board* b, pos p, cell c);

#endif /* BOARD_H */
