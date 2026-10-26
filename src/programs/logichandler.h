#ifndef CHESS_MAIN_H
#define CHESS_MAIN_H

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#include "../../include/calculator.h"

#define DEBUGMODE 0

enum ChessPieceUsedProperty {
    IDENTIFICATION = 1,
    HOSTBEARING = 2,
    OCCUPIEDSQUARE = 3
};

typedef struct {
    unsigned char Square;
    _Bool OffBoard;
} SquareCount;

typedef struct {
    SquareCount ChainParent; // Index
    unsigned char Predecessor;
    unsigned char Dependee;
    _Bool Seen;
    _Bool Real;
    _Bool Legal;
} Opportunities;

typedef struct {
    _Bool ChainParent;
    _Bool Predecessor;
    _Bool Dependee;
    _Bool Seen;
    _Bool Real;
} Opportunities_Assignmentation;

typedef struct {
    Opportunities* Opportunes; // Only calculate at last steps, not in any set up functions
    SquareCount Space; // Index
    SquareCount StartingSquare;
    unsigned char Identification;
    _Bool HostBearing;
    _Bool OccupiedSpace;
    _Bool MovedSince;
} BoardSection;

typedef struct {
    _Bool Opportunes;
    _Bool Space;
    _Bool StartingSquare;
    _Bool Identification;
    _Bool HostBearing;
    _Bool OccupiedSpace;
    _Bool MovedSince;
} BoardSection_Assignmentation;

typedef struct {
    _Bool Takes;
    _Bool Moves;
    _Bool Sabotages;
} Abilities;

typedef struct {
    _Bool Takes;
    _Bool Moves;
    _Bool Sabotages;
} Abilities_Assignmentation;

typedef struct {
    BoardSection* Collection;
    unsigned char LegalMoveCount;
    _Bool Starting;
    _Bool Play;
    _Bool HostWon;
    _Bool HostDrew;
    _Bool GameEnded;
} HostChessBoard;

typedef struct {
    unsigned char StartingFile;
    unsigned char StartingRank;
    unsigned char EndingFile;
    unsigned char EndingRank;
} AMove;

extern unsigned int MAX_BOARD_SQUARES();
extern BoardSection_Assignmentation ModifyPiece();
extern Opportunities_Assignmentation ModifyStatus();
extern Abilities_Assignmentation ModifyAbilities();

typedef struct {
    signed char File;
    signed char Rank;
} SquareAlignment;

typedef struct {
    HostChessBoard* ProvisionalBoard;
    SquareCount* PredecessorSquare;
    BoardSection* Residence;
    Abilities* Options;
    _Bool* ContinuouslyIterate;
} QuickDefinition;

/*
typedef struct {
    AMove*
} AllMoves;
*/

extern void DestructPlay(const HostChessBoard *Board);
extern HostChessBoard ConstructPlay(); // this most follow whatever i have for board section
extern void Define_Piece(const HostChessBoard* ProvisionalBoard, unsigned char ParentSquare);

extern void ModifyRegionalValues(const HostChessBoard* Board, unsigned char Square, BoardSection Region, BoardSection_Assignmentation Assigning); // this most follow whatever i have for board section
extern void ModifyOpportuneBusiness(const HostChessBoard* Board, unsigned char Square, unsigned char ParentSquare, Opportunities Opportune, Opportunities_Assignmentation Assigning);
extern void ModifyAbilityList(Abilities* List, Abilities Example, Abilities_Assignmentation Assigning);

extern _Bool EqualOpportunities(Opportunities A, Opportunities B);
extern void FlipTurn(HostChessBoard* BoardPast);

extern void LoadChessBoard(const HostChessBoard *Destination, HostChessBoard Source);

extern SquareAlignment RobotLanguage(SquareAlignment HumanLanguage);
extern SquareCount BoardSquare(SquareAlignment Location);
extern SquareAlignment BoardLocation(unsigned char Square);

extern SquareCount ShiftOver(unsigned char Square, signed char UpRanks, signed char LeftFiles);

extern void LOOP_Piece(HostChessBoard* ProvisionalBoard, SquareCount* PredecessorSquare, const BoardSection* Residence, Abilities Options, _Bool SkipParent, _Bool Allaround, _Bool ContinuouslyIterate, signed char UpRanks, signed char LeftFiles, signed char UpRanksIncrementation, signed char LeftFilesIncrementation);
extern void LOOP_PieceQ(QuickDefinition* Settings, _Bool Allaround, signed char UpRanksIncrementation, signed char LeftFilesIncrementation);

extern void RecalculateOpportunes(HostChessBoard* ProvisionalBoard, unsigned char Square);

extern unsigned char ezslidingstuff(unsigned char File, unsigned char Rank);

extern _Bool CheckIfMovable(HostChessBoard Board, AMove Position);
extern _Bool KingAttacked(HostChessBoard Board);
extern void FillOpportunes(HostChessBoard* MainBoard, _Bool DoOtherPieces);

extern void SlidePiece(const HostChessBoard *ProvisionalBoard, unsigned char SourceSquare, unsigned char DestinationSquare);
extern void ezslider(const HostChessBoard* ProvisionalBoard, AMove Select);

extern void PrintSpacer();
extern void PrintBoard(const HostChessBoard* ProvisionalBoard, enum ChessPieceUsedProperty Property, _Bool printthis, unsigned char SelectedFile, unsigned char SelectedRank, _Bool UseLetters);

extern void PlopPiece(const HostChessBoard* Board, unsigned char File, unsigned char Rank, _Bool OccupiedSpace, _Bool HostBearing, unsigned char Identification, SquareCount StartingSquare);

extern HostChessBoard FlippedBoard(const HostChessBoard* RegularBoard);

extern void ClassicalPlopper(const HostChessBoard* Board, unsigned char File, unsigned char Rank, unsigned char Identification);
extern void ClassicalSetup(const HostChessBoard* Board);

extern void GameEngage(unsigned long int Iteration, unsigned long int* IterationCap, HostChessBoard* MainBoard, const AMove* Moves, unsigned char NumberofMoves);
extern unsigned char GamePlay(AMove* PlayedMoves);

#endif // CHESS_MAIN_H