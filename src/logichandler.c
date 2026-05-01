#include "programs/logichandler.h"

int MAX_BOARD_SQUARES() {
    int r = 1;
    for (int i = 0; i < __CHAR_BIT__; i++) {
        r *= 2;
    }
    return r;
}

BoardSection* Reader(const HostChessBoard* Board, const unsigned char Square) {
    return &Board->Collection[Square];
}

void DestructPlay(const HostChessBoard* Board) {
    free(Board->Collection);
}

HostChessBoard ConstructPlay() {
    const HostChessBoard Board = {
        .Starting = 1,
        .Collection = (BoardSection*) calloc(MAX_BOARD_SQUARES(), sizeof(BoardSection)),
    };

    if (Board.Collection != NULL) {
        int SequentialNumerator = 0;

        while (SequentialNumerator < MAX_BOARD_SQUARES()) {
            BoardSection* Location = Reader(&Board, SequentialNumerator);

            Location->Square = SequentialNumerator;
            Location->ResidedPiece = (ChessPiece) { 0 };

            SequentialNumerator++;
        }
    } else {
        printf("Failed to collect board!\n");

        DestructPlay(&Board);
    }

    return Board;
}

void ExchangePiece(const HostChessBoard* ProvisionalBoard, const ChessPiece Piece, const unsigned char Square) {
    Reader(ProvisionalBoard, Square)->ResidedPiece = Piece;
}

void SlidePiece(const HostChessBoard* ProvisionalBoard, const unsigned char* Squares) {
    ExchangePiece(ProvisionalBoard, Reader(ProvisionalBoard, Squares[0])->ResidedPiece, Squares[1]);
    ExchangePiece(ProvisionalBoard, (ChessPiece) { 0 }, Squares[0]);
}

void PrintSquares(const HostChessBoard* ProvisionalBoard, const unsigned char* Squares, const unsigned char Section) {
    printf("%hhu0: %hhu\n", Section, Reader(ProvisionalBoard, Squares[0])->ResidedPiece.PieceIdentification);
    printf("%hhu1: %hhu\n\n", Section, Reader(ProvisionalBoard, Squares[1])->ResidedPiece.PieceIdentification);
}

void LoadChessBoard(const HostChessBoard* Destination, const HostChessBoard Source) {
    for (int SequentialNumerator = 0; SequentialNumerator < MAX_BOARD_SQUARES(); SequentialNumerator++) {
        ExchangePiece(Destination, Reader(&Source, SequentialNumerator)->ResidedPiece, SequentialNumerator);
    }
}