/* Jacqueline Lee, jacquelinelee
 * CS 152, Winter 2020
 * Project 2
 */

#ifndef POS_H
#define POS_H

/* === Data Definitions === */
struct pos {
    unsigned int r, c;
};
typedef struct pos pos;

/* === Function Declarations === */
/* make_pos: make new pos struct (representation of location on the board)
 * parameter "r": the row number for the location
 * parameter "c": the column number for the location
 * output: a pos struct with row = r and column = c
 */
pos make_pos(unsigned int r, unsigned int c);

#endif /* POS_H */
