#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "chess.h"


char *pieceNamesPng[] = {"",
                         "images/black_pawn.png",
                         "images/white_pawn.png",
                         "images/black_bishop.png",
                         "images/black_knight.png",
                         "images/black_rook.png",
                         "images/black_queen.png",
                         "images/black_king.png",
                         "images/",
                         "images/",
                         "images/white_rook.png",
                         "images/white_knight.png",
                         "images/white_bishop.png",
                         "images/white_queen.png",
                         "images/white_king.png"};


void drawBoardPieces(sfRenderWindow *window, chessBoard *board) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            if (board->board[i][j]) {

                // draw the pieces!
                sfVector2f mySpritePos = {.x = (j)*128+4, .y = (i)*128+4};
                sfVector2f mySpriteSize = {1.5, 1.5};
                sfImage *img =
                    sfImage_createFromFile(pieceNamesPng[board->board[i][j]]);
            
                sfTexture *imgT = sfTexture_createFromImage(img, NULL);
                sfSprite *boardPiece = sfSprite_create();
                sfBool boo = {1};
                sfSprite_setPosition(boardPiece, mySpritePos);
                sfSprite_setTexture(boardPiece, imgT, NULL);
                sfSprite_setScale(boardPiece,mySpriteSize);
                 sfTexture_setSmooth(imgT,boo);
                sfRenderWindow_drawSprite(window, boardPiece, NULL);
                sfTexture_destroy(imgT);
                sfSprite_destroy(boardPiece);
                sfImage_destroy(img);
            }
        }
    }
}

void draw(sfRenderWindow *window, chessBoard *board) {
    // prints board

    int alt = 0;
    for (int i = 0; i < 8; ++i) {
        alt = i % 2;
        for (int j = 0; j < 8; ++j) {
            sfRectangleShape *myRec = sfRectangleShape_create();
            sfVector2f myRecSize = {.x = 128, .y = 128};
            sfVector2f myRecPos = {(i)*128, (j)*128};
            // printf("%f %f\n",myRecPos.x,myRecPos.y);
            sfRectangleShape_setPosition(myRec, myRecPos);
            sfRectangleShape_setSize(myRec, myRecSize);
            sfColor sfGrey = {2,1,54,150};
            
            if (alt) {
                if (j % 2 == 0) {
                    sfRectangleShape_setFillColor(myRec, sfGrey);
                } else {
                    sfRectangleShape_setFillColor(myRec, sfWhite);
                }
            } else {
                if (j % 2) {
                    sfRectangleShape_setFillColor(myRec, sfGrey);
                } else {
                    sfRectangleShape_setFillColor(myRec, sfWhite);
                }
            }
            sfRenderWindow_drawRectangleShape(window, myRec, NULL);
            sfRectangleShape_destroy(myRec);
        }
    }
    drawBoardPieces(window, board);
}

int main(int argc, char *args[]) {
    
    chessBoard board = {.castleStats = {0,0,0,0},.lastMovePawnTwoUp = 0,.lastPieceMoveCord = {-1,-1},.turn = 0,.board = {{5, 4, 3, 6, 7, 3, 4, 5},
                                    {1, 1, 1, 1, 1, 1, 1, 1},
                                    {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0},
                                    {2, 2, 2, 2, 2, 2, 2, 2},
                                    {10, 11, 12, 13, 14, 12, 11, 10}}};
    //piece to be moved...
    movePiece p = {1, 0, 3, 0};
    


    int firstClick = 0;
    int validMove = 0;
    // create the window
    sfVideoMode vidMode = {.width = 1024, .height = 1024, .bitsPerPixel = 32};

    // contexts
/*     sfContextSettings settings;
    settings.antialiasingLevel = 2;
 */
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

            // user clicks!

            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    
                    if (firstClick == 0) {
                        // see where this click falls on 8x8
                        // this sets the i,j
                        //printf("%d %d\n", (int) (event.mouseButton.x / 128), (int) (event.mouseButton.y / 128));
                        printf("one\n");
                        p.j = (int) (event.mouseButton.x / 128);
                        p.i = (int) (event.mouseButton.y / 128);
                        firstClick = 1;
                    } else {
                        printf("two\n");
                        if (p.i != (int) (event.mouseButton.y / 128) || (int) (event.mouseButton.x / 128) != p.j){
                            p.goalJ = (int) (event.mouseButton.x / 128);
                            p.goalI = (int) (event.mouseButton.y / 128);
                            validMove = 1;
                        }
                        firstClick = 0;
                        // this sets the goal i,j
                    }
                    //printf("%d %d\n", event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        // clear the window with black color
        sfRenderWindow_clear(window, sfWhite);
        if (validMove){
            if (updateBoard(&board, &p)){
                printf("game is over!\n");
                break;
            }
            validMove = 0;
        }
        // draw everything here...
        draw(window, &board);
       
        // end the current frame
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return 0;
}
