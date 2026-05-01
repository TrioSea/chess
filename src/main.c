#include "programs/logichandler.h"

int main() {
    // Initiation

    _Bool terminate = 0;
    const HostChessBoard PlayCopy = ConstructPlay();
    const HostChessBoard* Board = &PlayCopy;

    ChessPiece Piece = {
        .PieceIdentification = 5,
        .HostPiece = 1
    };

    unsigned char* Squares = calloc(2, sizeof(unsigned char));

    Squares[0] = 59;
    Squares[1] = 41;

    PrintSquares(Board, Squares, 1);
    ExchangePiece(Board, Piece, Squares[0]);
    PrintSquares(Board, Squares, 2);
    SlidePiece(Board, Squares);
    PrintSquares(Board, Squares, 3);

    free(Squares);

    // Iterative
    unsigned long int nth_loop = 0;

    while (terminate != 1) {
        // quit == 0
        // Iterative (Connection Handler)

        nth_loop++;

        printf("%lu", nth_loop);

        if (nth_loop == 9) {
            terminate = 1;
        }

        if (terminate == 1) {
            // Termination

            DestructPlay(Board);

            terminate = 1;
        }
    }

    return 0;
}
