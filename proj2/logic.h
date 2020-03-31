/* Jacqueline Lee, jacquelinelee
 * CS 152, Winter 2020
 * Project 2
 */

#ifndef LOGIC_H
#define LOGIC_H

#include "board.h"

/* === Data Definitions === */
enum turn {
    BLACK_NEXT,
    WHITE_NEXT
};
typedef enum turn turn;

enum outcome {
    BLACK_WIN,
    WHITE_WIN,
    DRAW,
    IN_PROGRESS
};
typedef enum outcome outcome;

enum direction {
    CW, CCW
};
typedef enum direction direction;

struct game {
    unsigned int run;
    board* b;
    turn next;
};
typedef struct game game;

/* === Function Declarations === */
/* new_game: create a new game
 * parameter "run": the requisite number of pieces to win the game
 * parameter "width": the width for the board
 * parameter "height": the height for the board
 * parameter "type": the type of the board
 * output: a pointer to the new game
 */
game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type);

/* game_free: free a game
 * parameter "g": the pointer to the game to be freed
 * output: void
 */
void game_free(game* g);

/* drop_piece: drop a piece belonging to the player whose turn it is in the
 *             specified column
 * parameter "g": the pointer to the game
 * parameter "col": the column into which the piece should be dropped
 * output: (pseudo-boolean integer) true if a piece is dropped, false if the
 *         column is already full and no pieces are dropped
 */
int drop_piece(game* g, unsigned int col);

/* twist: rotate the board and simulate the resulting gravitational effects
 * parameter "g": the pointer to the game
 * parameter "d": the direction in which to rotate the board, CW or CCW
 * output: void
 */
void twist(game* g, direction d);

/* game_outcome: return the current state of the game, whether completed or
 *               still in progress
 * parameter "g": the pointer to the game
 * output: an outcome enum, BLACK_WIN or WHITE_WIN if the game is won, DRAW if
 *         the game is tied, or IN_PROGRESS if the game is still in progress
 */
outcome game_outcome(game* g);

#endif /* LOGIC_H */
