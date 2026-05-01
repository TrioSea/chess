#ifndef CHESS_MAIN_H
#define CHESS_MAIN_H

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <tgmath.h>
#include <stdio.h>

typedef struct {
    unsigned char PieceIdentification;
    _Bool HostPiece;

    /*
    PieceID (0 - 6 standard)
    air
    pawn
    knight
    bishop
    rook
    queen
    king

    Host (true/false)
    true && host white -> white
    false && host black -> white
    true && host black -> black
    false && host white -> black
    */
} ChessPiece;

typedef struct {
    ChessPiece ResidedPiece;
    unsigned char Square;
} BoardSection;

extern int MAX_BOARD_SQUARES();

typedef struct {
    BoardSection *Collection;
    _Bool Starting;
} HostChessBoard;

extern BoardSection* Reader(const HostChessBoard *Board, unsigned char Square);

extern void DestructPlay(const HostChessBoard *Board);
extern HostChessBoard ConstructPlay();

extern void ExchangePiece(const HostChessBoard *ProvisionalBoard, ChessPiece Piece, unsigned char Square);
extern void SlidePiece(const HostChessBoard *ProvisionalBoard, const unsigned char* Squares);

extern void PrintSquares(const HostChessBoard* ProvisionalBoard, const unsigned char* Squares, unsigned char Section);

extern void LoadChessBoard(const HostChessBoard *Destination, HostChessBoard Source);

#endif // CHESS_MAIN_H
