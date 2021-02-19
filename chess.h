#pragma once

/*

Game()
Turn()
DoesMoveGiveExposedCheck()
DoesCaptureGiveExposedCheck()
MoveXWhiteNoCapture()
MoveXBlackNoCapture()
MoveXBlack/WhiteCapture()
IsWhiteCheck?()
IsBlackCheck?()
CastleQueenSideWhite/Back()
CastleKingSideWhite/Black()
Enpassant-White/Black()
canXCapturePiece?(White/Black)()
Draw?()
Mate?()



*/

typedef struct
{
    int i;
    int j;
} kingPos;

typedef struct
{
    int board[8][8];
    int lostPieces[16];
    kingPos whiteKing;
    kingPos blackKing;
    int turn;
} chessBoard;

typedef struct
{
    int i;
    int j;
    int goalI;
    int goalJ;
} movePiece;

void updateBoard(chessBoard*boardStruct,movePiece*mPiece);

int gameWin();

int gameDraw();

int isInCheck();

int validateMovePawn(chessBoard *boardStruct, movePiece *movePiece);

int validateMoveBishop(chessBoard *boardStruct, movePiece *movePiece); 

int validateMoveKing(chessBoard *boardStruct, movePiece *movePiece); 

int validateMoveQueen(chessBoard *boardStruct, movePiece *movePiece); 

int validateMoveRook(chessBoard *boardStruct, movePiece *movePiece); 

int validateMoveKnight(chessBoard *boardStruct, movePiece *movePiece); 