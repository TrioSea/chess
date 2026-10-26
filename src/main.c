#include "programs/logichandler.h"

int main() {
    // Initiation

    _Bool Terminate = 0;

    HostChessBoard PlayCopy = ConstructPlay();
    HostChessBoard* Board = &PlayCopy;

    ClassicalSetup(Board);

    unsigned char MoveC = 0;

    AMove* PlayedMoves = calloc(MoveC, sizeof(AMove));
    MoveC = GamePlay(PlayedMoves);

    // Iterative
    unsigned long int Iteration = 1;
    unsigned long int IterationCap = 32;

    while (Terminate != 1) {
        if (Iteration > IterationCap) {
            // Termination

            DestructPlay(Board);

            free(PlayedMoves);

            Terminate = 1;
        } else {
            // Iterative (Connection Handler)

            GameEngage(Iteration, &IterationCap, Board, PlayedMoves, MoveC);
        }

        Iteration++;
    }

    return 0;
}

/*
Lines of a game
Game Direction
Opening
Opening Theory (few moves)
Opening Tactics (few moves)
Middlegame
Endgame

Nc3
    d5
    Nf6
    e6

    c6
    c5
    g6
    Nc6

e4 c5
    Nf3 Sicilian Defense *OG*
        d6
            d4 (very good and good theory)
            Bb5+ Sicilian Defense: Canal Attack *OG* (theory goes really far though because anything works so nothing does)
            Nc3 (higher level)
        e6 Sicilian Defense: French Variation *OG*
            d6
            Nc3
            c3 Alapin Sicilian Defense
        Nc6 Sicilian Defense: Old Sicilian Variation
            Bb5 Sicilian Defense: Nyezhmetdinov-Rossolimo Attack *OG* (high depth does not completely prefer but is good in many ways)
            d4 Sicilian Defense: Open *OG*
            Nc3 Closed Sicilian Defense: Traditional Line (higher level)
            c3 Alapin Sicilian Defense
    Nc3 Closed Sicilian Defense *OG*
    A good rule of thumb for the closed is to always then look for Nf3 then d4
        if they play e5, play Bc4
        if they play Nf6, play e5
        if they play g pawn, play d4
        take anything obvious, main plan of action is with queen, light bishop, knights, and e pawn
        watch for queen check to win c pawn
        d6
            Nge2 Sicilian Defense: Keres Variation (real variation has much worse off theory, d6 is the best move for any level)
            Nf3 Sicilian Defense
            d4 Magnus Sicilian *OG*
        a6 (FIGURE OUT BEST MOVES AFTER)
            Nf3 Sicilian Defense: O'Kelly, Yerevan System (real variation does not have good theory)
            g3
            Be2
            d4
            Nge2
        e6
            Nf3 Sicilian Defense: French Variation (nearly forced based on theory and e6)
            Nge2 Sicilian Defense: Keres Variation
            a3 EXITS THEORY
            d4 EXITS THEORY
        Nc6 Closed Sicilian Defense: Traditional Line *OG*
            Nge2 Closed Sicilian Defense: Chameleon Variation *OG*
            Nf3
            Bb5 (has ideas but should not be glorified
    d4 Sicilian Defense: Smith-Morra Gambit *OG*
        cxd4
            Nf3 Sicilian Defense: Smith-Morra, Morphy Gambit *OG*
            Qxd4
    c3 Alapin Sicilian Defense *OG* (alapin is actually not very good)
        Nf6
            e5
        d5
            exd5
            e5
            Bb5+
        e5
            Nf3
            Bc4
        Nc6
            d4 (preventing Nf6)
            Nf3
            Bb5

    HIGH THEORY
    Nf3 d6 d4 Sicilian Defense
        Nf3 Sicilian Defense: Anti-Qxd4 Move-Order
            Nc3
                cxd4
                    Nxd4 Sicilian Defense: Open Variation
                        a6 Sicilian Defense: Open, Najdorf Variation
                    Qxd4
        cxd4
            Nxd4 Sicilian Defense: Open Variation *OG*
                Nf6
                    Nc3 (a6 is *OG* Sicilian Defense: Open, Najdorf Variation)
                Nc6 Sicilian Defense: Open

*/
