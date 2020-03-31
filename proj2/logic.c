/* Jacqueline Lee, jacquelinelee
 * CS 152, Winter 2020
 * Project 2
 */

#include <stdlib.h>
#include <stdio.h>
#include "logic.h"

game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type) {
    if (run > 1 && (run <= width || run <= height)) {
        game* res = (game*)malloc(sizeof(game));
        if (res == NULL) {
            fprintf(stderr, "new_game: failed to allocate memory\n");
            exit(1);
        }
        res->run = run;
        res->b = board_new(width, height, type);
        res->next = BLACK_NEXT;
        return res;
    } else {
        fprintf(stderr, "new_game: run is out of range\n");
        exit(1);
    }
}

void game_free(game* g) {
    board_free(g->b);
    free(g);
}

int drop_piece(game* g, unsigned int col) {
    int i;
    pos p;
    for (i = g->b->height - 1; i >= 0; i--) {
        p = make_pos(i, col);
        if (board_get(g->b, p) == EMPTY) {
            switch (g->next) {
                case BLACK_NEXT:
                    board_set(g->b, p, BLACK);
                    return 1;
                case WHITE_NEXT:
                    board_set(g->b, p, WHITE);
                    return 1;
                default:
                    fprintf(stderr, "drop_piece: invalid turn\n");
                    exit(1);
            }
        }
    }
    return 0;
}

void twist(game* g, direction d) {
    turn n = g->next;
    board *b = g->b, *twisted_b = board_new(b->height, b->width, b->type);
    g->b = twisted_b;
    int r, c;
    pos p;
    switch (d) {
        case CW:
            for (r = b->height - 1; r >= 0; r--) {
                for (c = b->width - 1; c >= 0; c--) {
                    p = make_pos(r, c);
                    switch (board_get(b, p)) {
                        case BLACK:
                            g->next = BLACK_NEXT;
                            drop_piece(g, b->height - 1 - r);
                            break;
                        case WHITE:
                            g->next = WHITE_NEXT;
                            drop_piece(g, b->height - 1 - r);
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
        case CCW:
            for (r = 0; r < b->height; r++) {
                for (c = 0; c < b->width; c++) {
                    p = make_pos(r, c);
                    switch (board_get(b, p)) {
                        case BLACK:
                            g->next = BLACK_NEXT;
                            drop_piece(g, r);
                            break;
                        case WHITE:
                            g->next = WHITE_NEXT;
                            drop_piece(g, r);
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
        default:
            fprintf(stderr, "twist: invalid direction\n");
            exit(1);
    }
    g->next = n;
    board_free(b);
}

/* horizontal_outcome: given a game, check for a rightward horizontal run (win)
 *                     from the given position
 * parameter "g": the pointer to the game
 * parameter "p": the position from which to check for a horizontal run
 * parameter "b_wins": an out parameter that is incremented by one for every
 *                     black horizontal run detected
 * parameter "w_wins": an out parameter that is incremented by one for every
 *                     white horizontal run detected
 * output: (pseudo-boolean integer) true if a horizontal run is detected, false
 *         if a horizontal run is not detected
 */
int horizontal_outcome(game* g, pos p, unsigned int* b_wins,
                       unsigned int* w_wins) {
    unsigned int i;
    cell first = board_get(g->b, p);
    for (i = p.c; i < p.c + g->run; i++) {
        if (i == g->b->width || board_get(g->b, make_pos(p.r, i)) != first) {
            return 0;
        }
    }
    switch (first) {
        case BLACK:
            (*b_wins)++;
            return 1;
        case WHITE:
            (*w_wins)++;
            return 1;
        default:
            fprintf(stderr, "horizontal_outcome: invalid cell\n");
            exit(1);
    }
}

/* vertical_outcome: given a game, check for a downward vertical run (win) from
 *                   the given position
 * parameter "g": the pointer to the game
 * parameter "p": the position from which to check for a vertical run
 * parameter "b_wins": an out parameter that is incremented by one for every
 *                     black vertical run detected
 * parameter "w_wins": an out parameter that is incremented by one for every
 *                     white vertical run detected
 * output: (pseudo-boolean integer) true if a vertical run is detected, false if
 *         a vertical run is not detected
 */
int vertical_outcome(game* g, pos p, unsigned int* b_wins,
                     unsigned int* w_wins) {
    unsigned int i;
    cell first = board_get(g->b, p);
    for (i = p.r; i < p.r + g->run; i++) {
        if (i == g->b->height || board_get(g->b, make_pos(i, p.c)) != first) {
            return 0;
        }
    }
    switch (first) {
        case BLACK:
            (*b_wins)++;
            return 1;
        case WHITE:
            (*w_wins)++;
            return 1;
        default:
            fprintf(stderr, "vertical_outcome: invalid cell\n");
            exit(1);
    }
}

/* up_right_outcome: given a game, check for an up and rightward diagonal run
 *                   (win) from the given position
 * parameter "g": the pointer to the game
 * parameter "p": the position from which to check for a diagonal run
 * parameter "b_wins": an out parameter that is incremented by one for every
 *                     black diagonal run detected
 * parameter "w_wins": an out parameter that is incremented by one for every
 *                     white diagonal run detected
 * output: (pseudo-boolean integer) true if a diagonal run is detected, false if
 *         a diagonal run is not detected
 */
int up_right_outcome(game* g, pos p, unsigned int* b_wins,
                    unsigned int* w_wins) {
    unsigned int i, up_shift = 0;
    cell first = board_get(g->b, p);
    for (i = p.c; i < p.c + g->run; i++) {
        if (i == g->b->width || up_shift > p.r ||
            board_get(g->b, make_pos(p.r - up_shift, i)) != first) {
            return 0;
        }
        up_shift++;
    }
    switch (first) {
        case BLACK:
            (*b_wins)++;
            return 1;
        case WHITE:
            (*w_wins)++;
            return 1;
        default:
            fprintf(stderr, "up_right_outcome: invalid cell\n");
            exit(1);
    }
}

/* down_right_outcome: given a game, check for a down and rightward diagonal run
 *                     (win) from the given position
 * parameter "g": the pointer to the game
 * parameter "p": the position from which to check for a diagonal run
 * parameter "b_wins": an out parameter that is incremented by one for every
 *                     black diagonal run detected
 * parameter "w_wins": an out parameter that is incremented by one for every
 *                     white diagonal run detected
 * output: (pseudo-boolean integer) true if a diagonal run is detected, false if
 *         a diagonal run is not detected
 */
int down_right_outcome(game* g, pos p, unsigned int* b_wins,
                      unsigned int* w_wins) {
    unsigned int i, down_shift = 0;
    cell first = board_get(g->b, p);
    for (i = p.c; i < p.c + g->run; i++) {
        if (i == g->b->width || p.r + down_shift == g->b->height ||
            board_get(g->b, make_pos(p.r + down_shift, i)) != first) {
            return 0;
        }
        down_shift++;
    }
    switch (first) {
        case BLACK:
            (*b_wins)++;
            return 1;
        case WHITE:
            (*w_wins)++;
            return 1;
        default:
            fprintf(stderr, "down_right_outcome: invalid cell\n");
            exit(1);
    }
}

outcome game_outcome(game* g) {
    unsigned int r, c, b_wins = 0, w_wins = 0, empties = 0;
    pos p;
    for (r = 0; r < g->b->height; r++) {
        for (c = 0; c < g->b->width; c++) {
            p = make_pos(r, c);
            if (board_get(g->b, p) != EMPTY) {
                horizontal_outcome(g, p, &b_wins, &w_wins);
                vertical_outcome(g, p, &b_wins, &w_wins);
                up_right_outcome(g, p, &b_wins, &w_wins);
                down_right_outcome(g, p, &b_wins, &w_wins);
            } else {
                empties++;
            }
        }
    }
    if (b_wins && w_wins) {
        return DRAW;
    } else if (b_wins) {
        return BLACK_WIN;
    } else if (w_wins) {
        return WHITE_WIN;
    } else if (empties) {
        return IN_PROGRESS;
    } else {
        return DRAW;
    }
}
