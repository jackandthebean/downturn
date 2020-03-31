/* Jacqueline Lee, jacquelinelee
 * CS 152, Winter 2020
 * Project 2
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "board.h"

/* matrix_new: create a new (empty) matrix-type board representation
 * parameter "width": the width for the new matrix-type board representation
 * parameter "height": the height for the new matrix-type board representation
 * output: a pointer to the new matrix-type board representation
 */
cell** matrix_new(unsigned int width, unsigned int height) {
    cell** res = (cell**)malloc(sizeof(cell*) * height);
    if (res == NULL) {
        fprintf(stderr, "matrix_new: failed to allocate memory\n");
        exit(1);
    }
    unsigned int i, j;
    for (i = 0; i < height; i++) {
        res[i] = (cell*)malloc(sizeof(cell) * width);
        if (res[i] == NULL) {
            fprintf(stderr, "matrix_new: failed to allocate memory\n");
            exit(1);
        }
        for (j = 0; j < width; j++) {
            res[i][j] = EMPTY;
        }
    }
    return res;
}

/* matrix_free: free a matrix-type board representation
 * parameter "m": the pointer to the matrix to be freed
 * parameter "width": the width of the matrix
 * parameter "height": the height of the matrix
 * output: void
 */
void matrix_free(cell** m, unsigned int width, unsigned int height) {
    unsigned int i;
    for (i = 0; i < height; i++) {
        free(m[i]);
    }
    free(m);
}

/* bits_new: create a new (empty) bits-type board representation
 * parameter "width": the width for the new bits-type board representation
 * parameter "height": the height for the new bits-type board representation
 * output: a pointer to the new bits-type board representation
 */
unsigned int* bits_new(unsigned int width, unsigned int height) {
    unsigned int alen = ceil(width * height * 2 / 16.0);
    unsigned int* res = (unsigned int*)malloc(sizeof(unsigned int) * alen);
    if (res == NULL) {
        fprintf(stderr, "bits_new: failed to allocate memory\n");
        exit(1);
    }
    unsigned int i;
    for (i = 0; i < alen; i++) {
        res[i] = 0;
    }
    return res;
}

board* board_new(unsigned int width, unsigned int height, enum type type) {
    if (width < 2 || height < 2) {
        fprintf(stderr, "board_new: invalid dimensions\n");
        exit(1);
    }
    board* res = (board*)malloc(sizeof(board));
    if (res == NULL) {
        fprintf(stderr, "board_new: failed to allocate memory\n");
        exit(1);
    }
    res->width = width;
    res->height = height;
    switch (type) {
        case MATRIX:
            res->type = MATRIX;
            res->u.matrix = matrix_new(width, height);
            return res;
        case BITS:
            res->type = BITS;
            res->u.bits = bits_new(width, height);
            return res;
        default:
            fprintf(stderr, "board_new: invalid type\n");
            exit(1);
    }
}

void board_free(board* b) {
    switch (b->type) {
        case MATRIX:
            matrix_free(b->u.matrix, b->width, b->height);
            free(b);
            break;
        case BITS:
            free(b->u.bits);
            free(b);
            break;
        default:
            fprintf(stderr, "board_free: invalid type\n");
            exit(1);
    }
}

/* board_label: return the ASCII decimal for the character with which a given
 *              row or column should be labeled
 * parameter "i": the index of the row or column to be labeled
 * output: the label for the row or column
 */
unsigned char board_label(unsigned int i) {
    if (i < 10) {
        return i + 48;
    } else if (i < 36) {
        return i + 55;
    } else if (i < 62) {
        return i + 61;
    } else {
        return 63;
    }
}

/* print_cell: print a cell to the screen, in the specified format
 * parameter "c": the cell enum to be printed
 * output: void
 */
void print_cell(cell c) {
    switch (c) {
        case EMPTY:
            printf(".");
            break;
        case BLACK:
            printf("*");
            break;
        case WHITE:
            printf("o");
            break;
        default:
            fprintf(stderr, "print_cell: invalid cell\n");
            exit(1);
    }
}

/* bits_to_cell: retrieve the cell at the given position from a bits-type board
 * parameter "bits": the bits-type board
 * parameter "p": the position of inquiry
 * parameter "width": the width of the board
 * output: the cell enum at the given position on the board
 */
cell bits_to_cell(unsigned int* bits, pos p, unsigned int width) {
    unsigned int bit_n = p.r * width + p.c;
    unsigned int i = bit_n / 16, bit_shift = 2 * (bit_n % 16), mask = 0x3;
    switch((bits[i] >> bit_shift) & mask) {
        case 0:
            return EMPTY;
        case 1:
            return BLACK;
        case 2:
            return WHITE;
        default:
            fprintf(stderr, "bits_to_cell: invalid bit\n");
            exit(1);
    }
}

/* cell_to_bits: modify the cell at the given position on a bits-type board
 * parameter "bits": the bits-type board
 * parameter "p": the position of the cell to be modified
 * parameter "width": the width of the board
 * parameter "c": the cell enum to which the position should be modified
 * output: void
 */
void cell_to_bits(unsigned int* bits, pos p, unsigned int width, cell c) {
    unsigned int bit_n = p.r * width + p.c;
    unsigned int i = bit_n / 16, bit_shift = 2 * (bit_n % 16), mask = 0x3;
    mask = ~(mask << bit_shift);
    bits[i] = bits[i] & mask;
    switch (c) {
        case EMPTY:
            break;
        case BLACK:
            bits[i] = bits[i] | (0x1 << bit_shift);
            break;
        case WHITE:
            bits[i] = bits[i] | (0x2 << bit_shift);
            break;
        default:
            fprintf(stderr, "cell_to_bits: invalid cell\n");
            exit(1);
    }
}

void board_show(board* b) {
    unsigned int r, c;
    pos p;
    printf("  ");
    for (c = 0; c < b->width; c++) {
        printf("%c", board_label(c));
    }
    printf("\n\n");
    switch (b->type) {
        case MATRIX:
            for (r = 0; r < b->height; r++) {
                printf("%c ", board_label(r));
                for (c = 0; c < b->width; c++) {
                    print_cell(b->u.matrix[r][c]);
                }
                printf("\n");
            }
            break;
        case BITS:
            for (r = 0; r < b->height; r++) {
                printf("%c ", board_label(r));
                for (c = 0; c < b->width; c++) {
                    p = make_pos(r, c);
                    print_cell(bits_to_cell(b->u.bits, p, b->width));
                }
                printf("\n");
            }
            break;
        default:
            fprintf(stderr, "board_show: invalid type\n");
            exit(1);
    }
}

cell board_get(board* b, pos p) {
    if (p.r < b->height && p.c < b->width) {
        switch (b->type) {
            case MATRIX:
                return b->u.matrix[p.r][p.c];
            case BITS:
                return bits_to_cell(b->u.bits, p, b->width);
            default:
                fprintf(stderr, "board_get: invalid type\n");
                exit(1);
        }
    } else {
        fprintf(stderr, "board_get: position out of range\n");
        exit(1);
    }
}

void board_set(board* b, pos p, cell c) {
    if (p.r < b->height && p.c < b->width) {
        switch (b->type) {
            case MATRIX:
                b->u.matrix[p.r][p.c] = c;
                break;
            case BITS:
                cell_to_bits(b->u.bits, p, b->width, c);
                break;
            default:
                fprintf(stderr, "board_set: invalid type\n");
                exit(1);
        }
    } else {
        fprintf(stderr, "board_set: position out of range\n");
        exit(1);
    }
}
