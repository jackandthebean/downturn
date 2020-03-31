/* Jacqueline Lee, jacquelinelee
 * CS 152, Winter 2020
 * Project 2
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pos.h"
#include "board.h"
#include "logic.h"

/* prompt: print current player's turn to screen
 * parameter "t": the current player's turn
 * output: void
 */
void prompt(turn t) {
    if (t == BLACK_NEXT) {
        printf("Black: ");
    } else {
        printf("White: ");
    }
}

/* label_to_column: convert column label to column number
 * parameter "c": the column label
 * output: the column number
 */
unsigned int label_to_column(char c) {
    if (c >= '0' && c <= '9') {
        return c - 48;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 55;
    } else if (c >= 'a' && c <= 'z') {
        return c - 61;
    } else {
        fprintf(stderr, "label_to_column: label out of range\n");
        exit(1);
    }
}

/* change_turn: change player turn
 * parameter "g": the pointer to the game
 * output: void
 */
void change_turn(game* g) {
    if (g->next == BLACK_NEXT) {
        g->next = WHITE_NEXT;
    } else {
        g->next = BLACK_NEXT;
    }
}

/* print_result: print final game outcome to screen
 * parameter "o": the game outcome
 * output: void
 */
void print_result(outcome o) {
    if (o == BLACK_WIN) {
        printf("Black wins!");
    } else if (o == WHITE_WIN) {
        printf("White wins!");
    } else if (o == DRAW) {
        printf("Draw!");
    } else {
        fprintf(stderr, "print_result: game not over yet\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    unsigned int i, width, height, run, type, dimensions = 0, types = 0;
    /* parse command-line arguments */
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-w")) {
            dimensions++;
            width = atoi(argv[i + 1]);
        } else if (!strcmp(argv[i], "-h")) {
            dimensions++;
            height = atoi(argv[i + 1]);
        } else if (!strcmp(argv[i], "-r")) {
            dimensions++;
            run = atoi(argv[i + 1]);
        } else if (!strcmp(argv[i], "-m")) {
            types++;
            type = 0;
        } else if (!strcmp(argv[i], "-b")) {
            types++;
            type = 1;
        }
    }
    /* check that command-line arguments are valid */
    if (dimensions != 3 || types != 1 || width > 62 || height > 62) {
        fprintf(stderr, "\nMust specify width, height, run, and board type.\n");
        exit(1);
    }
    /* create new game with specified board type */
    game* g;
    if (type) {
        g = new_game(run, width, height, BITS);
    } else {
        g = new_game(run, width, height, MATRIX);
    }
    char play;
    unsigned int c;
    pos p;
    printf("\n");
    /* game loop that alternates between turns */
    while (game_outcome(g) == IN_PROGRESS) {
        board_show(g->b);
        printf("\n");
        /* loop that is only broken if the player's move is valid */
        while (1) {
            prompt(g->next);
            scanf("%c%*c", &play);
            if (play == '<') {
                twist(g, CCW);
                break;
            } else if (play == '>') {
                twist(g, CW);
                break;
            } else if ((play >= '0' && play <= '9') ||
                       (play >= 'A' && play <= 'Z') ||
                       (play >= 'a' && play <= 'z')) {
                c = label_to_column(play);
                if (c < g->b->width) {
                    p = make_pos(0, c);
                    if (board_get(g->b, p) == EMPTY) {
                        drop_piece(g, c);
                        break;
                    } else {
                        printf("\nColumn is full. Try another one.\n\n");
                    }
                } else {
                    printf("\nColumn is out of range. Try again.\n\n");
                }
            } else {
                printf("\nNot a valid play. Try again.\n\n");
            }
        }
        printf("\n");
        change_turn(g);
    }
    /* print final board state and game outcome */
    board_show(g->b);
    printf("\n");
    print_result(game_outcome(g));
    printf("\n\n");
}
