#include "chess.h"
#define PawnWhite 2
#define PawnBlack 1
#define rookWhite 10
#define rookBlack 5
#define KnightWhite 11
#define KnightBlack 4
#define QueenWhite 13
#define QueenBlack 6
#define BishopWhite 12
#define BishopBlack 3
#define KingBlack 7
#define KingWhite 14

//won't include kings here
const int whitePieceArr[] = {14,2,10,11,13,12};
const int blackPieceArr[] = {7,1,6,4,5,3};


int colorOfMovingPiece(chessBoard*boardStruct,movePiece*mPiece){
    int type = 1;
    for (int i = 0; i < 6;++i){
        if (boardStruct->board[mPiece->i][mPiece->j] == whitePieceArr[i]){
            type = 0;
            break;
        } 
    }
    return type;
}
//checks to see whether we can take a piece that's diff than our color
// nothing more that checking
int canTakeValid(chessBoard *boardStruct, movePiece *mPiece){

    int type = 1;
    for (int i = 0; i < 6;++i){
        if (boardStruct->board[mPiece->goalI][mPiece->goalJ] == whitePieceArr[i]){
            type = 0;
            break;
        } 
    }
    if (type != boardStruct->turn){
        return 1;
    } else {
        return 0;
    }

}

void fillBoard(chessBoard *boardStruct) {
    /*     {
      {5,4,3,6,7,3,4,5},
      {1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0},
      {2,2,2,2,2,2,2,2},
      {10,11,12,13,14,12,11,10}
  }; */
}

void updateKingPositions(chessBoard *boardStruct, movePiece *mPiece) {
    // find both kings
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (boardStruct->board[i][j] == KingWhite) {
                boardStruct->whiteKing.i = i;
                boardStruct->whiteKing.j = j;
            }
            if (boardStruct->board[i][j] == KingBlack) {
                boardStruct->blackKing.i = i;
                boardStruct->blackKing.j = j;
            }
        }
    }
}

int isJumpingOverPiece(chessBoard *boardStruct, movePiece *mPiece) {
    // get start piece pos
    int i = mPiece->i;
    int j = mPiece->j;

    // determine movement type
    // vertical
    if (abs(mPiece->goalI - i) == 0) {
        if (j < mPiece->goalJ) {
            for (int start = j + 1; start <= mPiece->goalJ; ++start) {
                //
                if (boardStruct->board[i][start]) {
                    if (start ==  mPiece->goalJ && canTakeValid(boardStruct,mPiece)){
                        printf("yes\n");
                        return 0;
                    }
                    return 1;
                }
            }
            return 0;
        } else {
            for (int start = j - 1; start >= mPiece->goalJ; --start) {
                if (boardStruct->board[i][start]) {
                    if (start ==  mPiece->goalJ && canTakeValid(boardStruct,mPiece)){
                        return 0;
                    }
                    return 1;
                }
            }
            return 0;
        }
    }
    // horizontal
    else if (abs(mPiece->goalJ - j) == 0) {
        if (i < mPiece->goalI) {
            for (int start = i + 1; start <= mPiece->goalI; ++start) {
                if (boardStruct->board[start][j]) {
                    if (start ==  mPiece->goalI && canTakeValid(boardStruct,mPiece)){
                        return 0;
                    }
                    return 1;
                }
            }
            return 0;
        } else {
            for (int start = i - 1; start >= mPiece->goalI; --start) {
                if (boardStruct->board[start][j]) {
                    if (start ==  mPiece->goalI && canTakeValid(boardStruct,mPiece)){
                        return 0;
                    }
                    return 1;
                }
            }
            return 0;
        }
    }
    // everything else (diagonals)
    else {
        
        int temp = 0;
        if ((j < mPiece->goalJ) && (i < mPiece->goalI)) {
            temp = i + 1;
            for (int start = j + 1; start <= mPiece->goalJ; ++start) {
                if (boardStruct->board[temp][start]) {
                    if (start ==  mPiece->goalJ && canTakeValid(boardStruct,mPiece)){
                        return 0;
                    }
                    return 1;
                }
                temp += 1;
            }
            return 0;
        } else if ((j < mPiece->goalJ) && (i > mPiece->goalI)) {
            printf("somecorener\n");
            temp = i - 1;
            for (int start = j +1; start <= mPiece->goalJ; ++start) {
                if (boardStruct->board[temp][start]) {
                    if (start ==  mPiece->goalJ && canTakeValid(boardStruct,mPiece)){
                        return 0;
                    }
                    return 1;
                }
                temp -= 1;
            }
            return 0;
        } else if ((j > mPiece->goalJ) && (i < mPiece->goalI)) {
            temp = i + 1;
            for (int start = j - 1; start >= mPiece->goalJ; --start) {
                if (boardStruct->board[temp][start]) {
                    if (start ==  mPiece->goalJ && canTakeValid(boardStruct,mPiece)){
                        return 0;
                    }
                    return 1;
                }
                temp += 1;
            }
            return 0;
        } else {
            temp = i - 1;
            for (int start = j -1; start >= mPiece->goalJ; --start) {
                if (boardStruct->board[temp][start]) {
                    if (start ==  mPiece->goalJ && canTakeValid(boardStruct,mPiece)){
                        return 0;
                    }
                    return 1;
                }
                temp -= 1;
            }
            return 0;
        }
        
    }
}

void updateBoard(chessBoard *boardStruct, movePiece *mPiece) {
    // leap of faith
    // if the piece that we are trying to move exists
    int moveWasValid = 0;
    if (boardStruct->board[mPiece->i][mPiece->j]) {
        switch (boardStruct->board[mPiece->i][mPiece->j]) {
            case 1:
            case 2:
                moveWasValid = validateMovePawn(boardStruct, mPiece);
                break;
            case 3:
            case 12:
                moveWasValid = validateMoveBishop(boardStruct, mPiece);
                break;
            case 4:
            case 11:
                printf("knight time poggers~\n");
                moveWasValid = validateMoveKnight(boardStruct, mPiece);
                break;
            case 5:
            case 10:
                moveWasValid = validateMoveRook(boardStruct, mPiece);
                break;
            case 7:
            case 14:
                moveWasValid = validateMoveKing(boardStruct, mPiece);
                break;
            case 6:
            case 13:
                moveWasValid = validateMoveQueen(boardStruct, mPiece);
                break;
            default:
                break;
        }

        if (moveWasValid && colorOfMovingPiece(boardStruct,mPiece) == boardStruct->turn) {
            int temp = boardStruct->board[mPiece->i][mPiece->j];
            boardStruct->board[mPiece->goalI][mPiece->goalJ] = temp;
            boardStruct->board[mPiece->i][mPiece->j] = 0;

            if (boardStruct->turn == 0)
                boardStruct->turn = 1;
            else
                boardStruct->turn = 0;
        } else {
            printf("oof %d %d\n",colorOfMovingPiece(boardStruct,mPiece) , boardStruct->turn);
        }
        printf("turn: %d\n",boardStruct->turn);

        // printf("Piece in check? %d\n", isInCheck(boardStruct, mPiece,
        // boardStruct->turn));
    }
}

int gameWin(chessBoard *boardStruct, movePiece *mPiece) {
    // there is no valid move left for whichever player and one is in check
    if (isInCheck(boardStruct, mPiece, !boardStruct->turn)) {
        // find all the enemy pieces that might be able to attack/black
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
            }
        }
    }
}

int gameDraw(chessBoard *boardStruct, movePiece *mPiece) {}

int isInCheck(chessBoard *boardStruct, movePiece *mPiece, int whiteBlack) {
    // find both kings
    updateKingPositions(boardStruct, mPiece);
    // check king vertical
    int KINGI = boardStruct->whiteKing.i;
    int KINGJ = boardStruct->whiteKing.j;
    int ROOK = rookBlack;
    int QUEEN = QueenBlack;
    int BISHOP = BishopBlack;
    int KNIGHT = KnightBlack;
    int PAWN = PawnBlack;
    if (whiteBlack) {
        KINGI = boardStruct->blackKing.i;
        KINGJ = boardStruct->blackKing.j;
        QUEEN = QueenWhite;
        ROOK = rookWhite;
        BISHOP = BishopWhite;
        KNIGHT = KnightWhite;
        PAWN = PawnWhite;
    }
    for (int i = KINGI + 1; i < 8; ++i) {
        if (boardStruct->board[i][KINGJ]) {
            if (boardStruct->board[i][KINGJ] == QUEEN ||
                boardStruct->board[i][KINGJ] == ROOK) {
                return 1;
            } else {
                break;
            }
        }
    }

    // reverse vertical
    for (int i = KINGI - 1; i >= 0; --i) {
        if (boardStruct->board[i][KINGJ]) {
            if (boardStruct->board[i][KINGJ] == QUEEN ||
                boardStruct->board[i][KINGJ] == ROOK) {
                return 2;
            } else {
                break;
            }
        }
    }

    // check king horizontal
    for (int i = KINGJ + 1; i < 8; ++i) {
        if (boardStruct->board[KINGI][i]) {
            if (boardStruct->board[KINGI][i] == QUEEN ||
                boardStruct->board[KINGI][i] == ROOK) {
                return 3;
            } else {
                break;
            }
        }
    }
    // reverse horizontal
    for (int i = KINGJ - 1; i >= 0; --i) {
        if (boardStruct->board[KINGI][i]) {
            if (boardStruct->board[KINGI][i] == QUEEN ||
                boardStruct->board[KINGI][i] == ROOK) {
                return 4;
            } else {
                break;
            }
        }
    }

    // diagonal TODO
    // up left/ down right
    // considers pawns too!
    int temp = KINGJ + 1;
    for (int i = KINGI + 1; i < 8; ++i) {
        if (temp >= 8) break;
        if (boardStruct->board[i][temp]) {
            if (boardStruct->board[i][temp] == BISHOP ||
                boardStruct->board[i][temp] == QUEEN ||
                boardStruct->board[i][temp] == PAWN) {
                if (whiteBlack) {
                    if (boardStruct->board[i][temp] == PAWN && KINGI + 1 != i)
                        break;
                    return 5;
                } else {
                    if (boardStruct->board[i][temp] != PAWN) return 5;
                }
            } else {
                break;
            }
        }
        ++temp;
    }

    temp = KINGJ - 1;
    for (int i = KINGI - 1; i >= 0; --i) {
        if (temp < 0) break;
        if (boardStruct->board[i][temp]) {
            if (boardStruct->board[i][temp] == BISHOP ||
                boardStruct->board[i][temp] == QUEEN ||
                boardStruct->board[i][temp] == PAWN) {
                if (!whiteBlack) {
                    if (boardStruct->board[i][temp] == PAWN && KINGI - 1 != i)
                        break;
                    return 6;
                } else {
                    if (boardStruct->board[i][temp] != PAWN) return 6;
                }
            } else {
                break;
            }
        }
        --temp;
    }
    // up right/ down left
    temp = KINGJ - 1;
    for (int i = KINGI + 1; i < 8; ++i) {
        if (temp < 0) break;
        if (boardStruct->board[i][temp]) {
            if (boardStruct->board[i][temp] == BISHOP ||
                boardStruct->board[i][temp] == QUEEN ||
                boardStruct->board[i][temp] == PAWN) {
                if (whiteBlack) {
                    if (boardStruct->board[i][temp] == PAWN && KINGI + 1 != i)
                        break;
                    return 7;
                } else {
                    if (boardStruct->board[i][temp] != PAWN) return 7;
                }
            } else {
                break;
            }
        }
        --temp;
    }

    temp = KINGJ + 1;
    for (int i = KINGI - 1; i >= 0; --i) {
        if (temp >= 8) break;
        if (boardStruct->board[i][temp]) {
            if (boardStruct->board[i][temp] == BISHOP ||
                boardStruct->board[i][temp] == QUEEN ||
                boardStruct->board[i][temp] == PAWN) {
                if (!whiteBlack) {
                    if (boardStruct->board[i][temp] == PAWN && KINGI - 1 != i)
                        break;
                    return 8;
                } else {
                    if (boardStruct->board[i][temp] != PAWN) return 8;
                }
            } else {
                break;
            }
        }
        ++temp;
    }

    // knights! TODO bounds checking
    // 2 up, one left/right
    if (KINGI + 2 < 8) {
        if (KINGJ + 1 < 8) {
            if (boardStruct->board[KINGI + 2][KINGJ + 1] == KNIGHT) return 9;
        }
        if (KINGJ - 1 >= 0) {
            if (boardStruct->board[KINGI + 2][KINGJ - 1] == KNIGHT) return 10;
        }
    }
    // 2 down, one left/right
    if (KINGI - 2 >= 0) {
        if (KINGJ + 1 < 8) {
            if (boardStruct->board[KINGI - 2][KINGJ + 1] == KNIGHT) return 11;
        }
        if (KINGJ - 1 >= 0) {
            if (boardStruct->board[KINGI - 2][KINGJ - 1] == KNIGHT) return 12;
        }
    }
    // 2 right ,one up/down
    if (KINGJ + 2 < 8) {
        if (KINGI + 1 < 8) {
            if (boardStruct->board[KINGI + 1][KINGJ + 2] == KNIGHT) return 13;
        }
        if (KINGI - 1 >= 0) {
            if (boardStruct->board[KINGI - 1][KINGJ + 2] == KNIGHT) return 14;
        }
    }
    // 2 left, one up/down
    if (KINGJ - 2 >= 0) {
        if (KINGI + 1 < 8) {
            if (boardStruct->board[KINGI + 1][KINGJ - 2] == KNIGHT) return 15;
        }
        if (KINGI - 1 >= 0) {
            if (boardStruct->board[KINGI - 1][KINGJ - 2] == KNIGHT) return 16;
        }
    }

    return 0;
}

int Pinned(chessBoard *boardStruct, movePiece *mPiece) {
    // there's some diagonal on pawn or vertical/horizontal
    // for white
    int orgI = mPiece->i;
    int orgJ = mPiece->j;
    int orgPiece = boardStruct->board[mPiece->i][mPiece->j];
    int temp = boardStruct->board[mPiece->goalI][mPiece->goalJ];

    boardStruct->board[orgI][orgJ] = 0;
    boardStruct->board[mPiece->goalI][mPiece->goalJ] = orgPiece;

    if (isInCheck(boardStruct, mPiece, boardStruct->turn)) {
        boardStruct->board[orgI][orgJ] = orgPiece;
        boardStruct->board[mPiece->goalI][mPiece->goalJ] = temp;
        return 1;
    }
    boardStruct->board[orgI][orgJ] = orgPiece;
    boardStruct->board[mPiece->goalI][mPiece->goalJ] = temp;
    return 0;
}

int RemovesChecks(chessBoard *boardStruct, movePiece *mPiece) {
    return !Pinned(boardStruct, mPiece);
}

int validateMovePawn(chessBoard *boardStruct, movePiece *mPiece) {
    int i = mPiece->i;
    int j = mPiece->j;
    int TYPEPAWN = boardStruct->board[i][j];
    int flag = 1;
    if (TYPEPAWN != PawnBlack) {
        flag = -1;
    }
    // part one of validity
    if (((mPiece->goalI - i) == flag) || ((mPiece->goalI - i) == flag * 2)) {
        if (isInCheck(boardStruct, mPiece, boardStruct->turn) &&
            RemovesChecks(boardStruct, mPiece)) {
                if (boardStruct->board[mPiece->goalI][mPiece->goalJ]  && !canTakeValid(boardStruct,mPiece)){
                return 0;
            }
            return 1;
        } else if (RemovesChecks(boardStruct, mPiece)) {
            if (boardStruct->board[mPiece->goalI][mPiece->goalJ]  && !canTakeValid(boardStruct,mPiece)){
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

int validateMoveBishop(chessBoard *boardStruct, movePiece *mPiece) {
    int i = mPiece->i;
    int j = mPiece->j;
    // part one of validity
    if ((abs(mPiece->goalI - i) == abs(mPiece->goalJ - j))) {
        if (isInCheck(boardStruct, mPiece, boardStruct->turn) &&
            RemovesChecks(boardStruct, mPiece) &&
            !isJumpingOverPiece(boardStruct, mPiece)) {
            return 1;
        } else if (RemovesChecks(boardStruct, mPiece) &&
            !isJumpingOverPiece(boardStruct, mPiece)) {
            return 1;
        }
    }
    return 0;
}

int validateMoveKing(chessBoard *boardStruct, movePiece *mPiece) {
    
    updateKingPositions(boardStruct,mPiece);

    int kingColor = colorOfMovingPiece(boardStruct,mPiece);


    int i = mPiece->i;
    int j = mPiece->j;
    // part one of validity
    // call castling function
    if ((abs(mPiece->goalI - i) >= 0 && abs(mPiece->goalI - i) <= 1) &&
        (abs(mPiece->goalJ - j) >= 0 && abs(mPiece->goalJ - j) <= 1)) {
            // King can't go right by another king!
            for (int x = -1; x < 2;++x){
                for (int y = -1; y < 2;++y){
                    if (!(x == 0 && y == 0) && mPiece->goalI+x >= 0 && mPiece->goalI+x < 8 && mPiece->goalJ+y >= 0 && mPiece->goalJ+y < 8){
                        int tempVal = boardStruct->board[mPiece->goalI+x][mPiece->goalJ+y];
                        if (tempVal == KingBlack && kingColor == 0){
                            return 0;
                        } else if (tempVal == KingWhite && kingColor == 1) {
                            return 0;
                        }
                    }
                }
            }

        if (isInCheck(boardStruct, mPiece, boardStruct->turn) &&
            RemovesChecks(boardStruct, mPiece)) {
            if (boardStruct->board[mPiece->goalI][mPiece->goalJ]  && !canTakeValid(boardStruct,mPiece)){
                return 0;
            }
            return 1;
        } else if (RemovesChecks(boardStruct, mPiece)) {
            if (boardStruct->board[mPiece->goalI][mPiece->goalJ]  && !canTakeValid(boardStruct,mPiece)){
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

int validateMoveQueen(chessBoard *boardStruct, movePiece *mPiece) {
    int i = mPiece->i;
    int j = mPiece->j;
    // part one of validity
    printf("Queentest\n");
    if ((abs(mPiece->goalI - i) == 0) || (abs(mPiece->goalJ - j) == 0) ||
        (abs(mPiece->goalI - i) == abs(mPiece->goalJ - j))) {
        if (isInCheck(boardStruct, mPiece, boardStruct->turn) &&
            RemovesChecks(boardStruct, mPiece) &&
            !isJumpingOverPiece(boardStruct, mPiece) ) {
            return 1;
        } else if (RemovesChecks(boardStruct, mPiece) &&
            !isJumpingOverPiece(boardStruct, mPiece)) {
            return 1;
        }
    }
    return 0;
}

int validateMoveRook(chessBoard *boardStruct, movePiece *mPiece) {
    // make sure goali , goalj reaches the first blocking piece
    int i = mPiece->i;
    int j = mPiece->j;
    // part one of validity

    printf("rook jumping? %d %d\n", !isJumpingOverPiece(boardStruct, mPiece),
           RemovesChecks(boardStruct, mPiece));
    if ((abs(mPiece->goalI - i) == 0) || (abs(mPiece->goalJ - j) == 0)) {
        if (isInCheck(boardStruct, mPiece, boardStruct->turn) &&
            RemovesChecks(boardStruct, mPiece) &&
            !isJumpingOverPiece(boardStruct, mPiece)) {
            return 1;
        } else if (!isInCheck(boardStruct, mPiece, boardStruct->turn) &&
                   RemovesChecks(boardStruct, mPiece) &&
                   !isJumpingOverPiece(boardStruct, mPiece)) {
            return 1;
        }
    }
    return 0;
}

int validateMoveKnight(chessBoard *boardStruct, movePiece *mPiece) {
    int i = mPiece->i;
    int j = mPiece->j;
    // part one of validity
    if ((abs(mPiece->goalI - i) == 2 && abs(mPiece->goalJ - j) == 1) ||
        (abs(mPiece->goalI - i) == 1 && abs(mPiece->goalJ - j) == 2)) {
        if (isInCheck(boardStruct, mPiece, boardStruct->turn) &&
            RemovesChecks(boardStruct, mPiece)) {
                            if (boardStruct->board[mPiece->goalI][mPiece->goalJ]  && !canTakeValid(boardStruct,mPiece)){
                return 0;
            }
            return 1;
        } else if (RemovesChecks(boardStruct, mPiece)) {
            if (boardStruct->board[mPiece->goalI][mPiece->goalJ]  && !canTakeValid(boardStruct,mPiece)){
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

int castleKingSide(chessBoard *boardStruct, movePiece *mPiece) {}

int hasKingMoved() {}

int hasRookMoved() {}

int castleQueenSide(chessBoard *boardStruct, movePiece *mPiece) {
    // king has not moved
    // king is not in check
    // no pieces between king and rook
    // rook has not moved
    // king won't get checked DURING the castiling!
    if (boardStruct->board[mPiece->i][mPiece->j] == KingWhite) {
        if (!isInCheck(boardStruct, mPiece, 0)

        ) {
        }
    } else {
    }
}
/*

    if (isInCheckWhite(boardStruct, mPiece) &&
        !whitePinned(boardStruct, mPiece) &&
        whiteRemovesChecks(boardStruct, mPiece)) {
        if (boardStruct->board[mPiece->i][mPiece->j] == PawnBlack) {
            boardStruct->board[mPiece->goalI][mPiece->goalJ] = PawnBlack;
        } else {
            boardStruct->board[mPiece->goalI][mPiece->goalJ] = PawnWhite;
        }
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        return 1;
    } else if (!isInCheckWhite(boardStruct, mPiece) &&
               !whitePinned(boardStruct, mPiece)) {
        if (boardStruct->board[mPiece->i][mPiece->j] == PawnBlack) {
            boardStruct->board[mPiece->goalI][mPiece->goalJ] = PawnBlack;
        } else {
            boardStruct->board[mPiece->goalI][mPiece->goalJ] = PawnWhite;
        }
        boardStruct->board[mPiece->i][mPiece->j] = 0;
        return 1;
    }

*/

/*
    switch (boardStruct->board[mPiece->i][mPiece->j]) {
        case 1:
        case 2:
            validateMovePawn(boardStruct, mPiece);
            break;
        case 3:
        case 12:
            validateMoveBishop(boardStruct, mPiece);
            break;
        case 4:
        case 11:
            validateMoveKnight(boardStruct, mPiece);
            break;
        case 5:
        case 10:
            validateMoveRook(boardStruct, mPiece);
            break;
        case 6:
        case 13:
            validateMoveKing(boardStruct, mPiece);
            break;
        case 7:
        case 14:
            validateMoveQueen(boardStruct, mPiece);
            break;
        default:
            break;
    }

    */