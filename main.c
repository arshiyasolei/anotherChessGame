#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "chess.h"

// TODO: Event handling!

void draw(sfRenderWindow *window) {
    // prints board
    // TODO add images of pieces
    int alt = 0;
    for (int i = 0; i < 8; ++i) {
        alt = i % 2;
        for (int j = 0; j < 8; ++j) {
            sfRectangleShape *myRec = sfRectangleShape_create();
            sfVector2f myRecSize = {.x = 64, .y = 64};
            sfVector2f myRecPos = {(i)*64, (j)*64};
            // printf("%f %f\n",myRecPos.x,myRecPos.y);
            sfRectangleShape_setPosition(myRec, myRecPos);
            sfRectangleShape_setSize(myRec, myRecSize);
            if (alt) {
                if (j % 2 == 0) {
                    sfRectangleShape_setFillColor(myRec, sfBlack);
                } else {
                    sfRectangleShape_setFillColor(myRec, sfWhite);
                }
            } else {
                if (j % 2) {
                    sfRectangleShape_setFillColor(myRec, sfBlack);
                } else {
                    sfRectangleShape_setFillColor(myRec, sfWhite);
                }
            }

            sfRenderWindow_drawRectangleShape(window, myRec, NULL);
            sfRectangleShape_destroy(myRec);
        }
    }
}

int main(int argc, char *args[]) {
    chessBoard board = {.board = {{5, 4, 3, 6, 7, 3, 4, 5},
                                  {1, 1, 1, 1, 1, 1, 1, 1},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {2, 2, 2, 2, 2, 2, 2, 2},
                                  {10, 11, 12, 13, 14, 12, 11, 10}}};
    movePiece p = {1, 0, 3, 0};
    updateBoard(&board, &p);
    // create the window
    sfVideoMode vidMode = {.width = 512, .height = 512, .bitsPerPixel = 30};

    sfRenderWindow *window =
        sfRenderWindow_create(vidMode, "ChessEngine", sfDefaultStyle, NULL);
    // run the program as long as the window is open
    while (sfRenderWindow_isOpen(window)) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            // "close requested" event: we close the window
            if (event.type == sfEvtClosed) sfRenderWindow_close(window);
            // user clicks

            // user clicks again (move piece)
        }

        // clear the window with black color
        sfRenderWindow_clear(window, sfWhite);
        // draw everything here...
        draw(window);
        // end the current frame
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}
