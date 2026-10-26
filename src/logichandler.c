#include "programs/logichandler.h"
#include "../include/mymath.h"

unsigned int MAX_BOARD_SQUARES() {
    int r = 1;
    int i = 0;

    while (i < __CHAR_BIT__) {
        r *= 2;

        i++;
    }

    return r;
}

// PRESETS
BoardSection_Assignmentation ModifyPiece() {
    return (BoardSection_Assignmentation) {
        .OccupiedSpace = 1,
        .HostBearing = 1,
        .Identification = 1,
        .StartingSquare = 1
    };
}

Opportunities_Assignmentation ModifyStatus() {
    return (Opportunities_Assignmentation) {
        .ChainParent = 1,
        .Seen = 1,
        .Real = 1
    };
}

Abilities_Assignmentation ModifyAbilities() {
    return (Abilities_Assignmentation) {
        .Moves = 1,
        .Takes = 1
    };
}

// DEFINITIONS
void DestructPlay(const HostChessBoard* Board) {
    unsigned char Squares = 0;
    while (Squares < 64) {
        Squares++;
        free(Board->Collection[Squares].Opportunes);
    }
    free(Board->Collection);
}

HostChessBoard ConstructPlay() {
    const HostChessBoard Board = {
        .Starting = 1,
        .Play = 1,
        .Collection = (BoardSection*) calloc(64, sizeof(BoardSection)),
    };

    if (Board.Collection != NULL) {
        int SequentialNumerator = 0;

        while (SequentialNumerator < 64) {
            const SquareCount UpdatedSquare = (SquareCount) {.Square = SequentialNumerator, .OffBoard = 0};

            Board.Collection[SequentialNumerator] = (BoardSection) {
                .Space = UpdatedSquare,
                .StartingSquare = UpdatedSquare,
                .Opportunes = (Opportunities*) calloc(64, sizeof(Opportunities)),
                .OccupiedSpace = 0,
                .HostBearing = 0,
                .Identification = 0,
                .MovedSince = 0
            };

            SequentialNumerator++;
        }
    } else {
        printf("Failed to collect board!\n");

        DestructPlay(&Board);
    }

    return Board;
}

void Define_Piece(const HostChessBoard* ProvisionalBoard, const unsigned char ParentSquare) {
    unsigned char Square = 0;

    while (Square < 64) {
        ProvisionalBoard->Collection[Square].Opportunes[ParentSquare] = (Opportunities) {};
        Square++;
    }
}

void ModifyRegionalValues(const HostChessBoard* Board, const unsigned char Square, const BoardSection Region, const BoardSection_Assignmentation Assigning) {
    if (Assigning.Space != 0) {
        Board->Collection[Square].Space = Region.Space;
    }

    if (Assigning.Identification != 0) {
        Board->Collection[Square].Identification = Region.Identification;
    }

    if (Assigning.HostBearing != 0) {
        Board->Collection[Square].HostBearing = Region.HostBearing;
    }

    if (Assigning.OccupiedSpace != 0) {
        Board->Collection[Square].OccupiedSpace = Region.OccupiedSpace;
    }

    if (Assigning.MovedSince != 0) {
        Board->Collection[Square].MovedSince = Region.MovedSince;
    }

    if (Assigning.StartingSquare != 0) {
        Board->Collection[Square].StartingSquare = Region.StartingSquare;
    }
}

void ModifyOpportuneBusiness(const HostChessBoard* Board, const unsigned char Square, const unsigned char ParentSquare, const Opportunities Opportune, const Opportunities_Assignmentation Assigning) {
    if (Assigning.ChainParent != 0) {
        Board->Collection[Square].Opportunes[ParentSquare].ChainParent = Opportune.ChainParent;
    }

    if (Assigning.Predecessor != 0) {
        Board->Collection[Square].Opportunes[ParentSquare].Predecessor = Opportune.Predecessor;
    }

    if (Assigning.Dependee != 0) {
        Board->Collection[Square].Opportunes[ParentSquare].Dependee = Opportune.Dependee;
    }

    if (Assigning.Seen != 0) {
        Board->Collection[Square].Opportunes[ParentSquare].Seen = Opportune.Seen;
    }

    if (Assigning.Real != 0) {
        Board->Collection[Square].Opportunes[ParentSquare].Real = Opportune.Real;
    }
}

void ModifyAbilityList(Abilities* List, const Abilities Example, const Abilities_Assignmentation Assigning) {
    if (Assigning.Takes != 0) {
        List->Takes = Example.Takes;
    }

    if (Assigning.Moves != 0) {
        List->Moves = Example.Moves;
    }

    if (Assigning.Sabotages != 0) {
        List->Sabotages = Example.Sabotages;
    }
}

// Basics
_Bool EqualOpportunities(const Opportunities A, const Opportunities B) {
    return A.ChainParent.Square == B.ChainParent.Square && A.ChainParent.OffBoard == B.ChainParent.OffBoard && A.Predecessor == B.Predecessor && A.Dependee == B.Dependee && A.Seen == B.Seen && A.Real == B.Real;
}

void FlipTurn(HostChessBoard* BoardPast) {
    BoardPast->Play = BoardPast->Play == 0;
}

// LOADING
void LoadChessBoard(const HostChessBoard* Destination, const HostChessBoard Source) {
    int SequentialNumerator = 0;

    while (SequentialNumerator < 64) {
        Destination->Collection[SequentialNumerator] = Source.Collection[SequentialNumerator];

        SequentialNumerator++;
    }
}

// TRANSLATING
SquareAlignment RobotLanguage(const SquareAlignment HumanLanguage) {
    const int File = HumanLanguage.File - 1;
    const int Rank = HumanLanguage.Rank - 1;

    return (SquareAlignment) {
        .File = (char) File,
        .Rank = (char) Rank
    };
}

SquareCount BoardSquare(const SquareAlignment Location) {
    const int Square = 8 * Location.File + Location.Rank;

    return (SquareCount) {
        .Square = AbsoluteValue_hhu((char) Square),
        .OffBoard = InclusiveOR(Square < 0, Invert(Square < 64))
    };
}

SquareAlignment BoardLocation(const unsigned char Square) {
    int File = 0;
    int Rank = Square;

    while (!(Rank < 8)) {
        File = File + 1;
        Rank = Rank - 8;
    }

    return (SquareAlignment) {
        .File = (char) File,
        .Rank = (char) Rank
    };
}

SquareCount ShiftOver(const unsigned char Square, const signed char UpRanks, const signed char LeftFiles) {
    SquareAlignment Location = BoardLocation(Square);

    const signed int File = Location.File - LeftFiles;
    const signed int Rank = Location.Rank + UpRanks;

    Location.File = ClampValue_hhd((signed char) File, 0, 7);
    Location.Rank = ClampValue_hhd((signed char) Rank, 0, 7);

    const int Calculation = Square - 8 * LeftFiles + UpRanks;
    const SquareCount Index = (SquareCount) {
        .Square = AbsoluteValue_hhu((char) Calculation),
        .OffBoard = InclusiveOR(Location.Rank != Rank, Location.File != File)
    };

    return Index;
}

// LEGAL MOVES
void LOOP_Piece(HostChessBoard* ProvisionalBoard, SquareCount* PredecessorSquare, const BoardSection* Residence, const Abilities Options, const _Bool SkipParent, _Bool Allaround, const _Bool ContinuouslyIterate, const signed char UpRanks, const signed char LeftFiles, const signed char UpRanksIncrementation, const signed char LeftFilesIncrementation) {
    const unsigned char ParentSquare = Residence->Space.Square;
    const SquareCount Index = ShiftOver(ParentSquare, UpRanks, LeftFiles);

    const BoardSection* InspectedSquare = &ProvisionalBoard->Collection[Index.Square];

    Opportunities* Handle = &InspectedSquare->Opportunes[ParentSquare];

    const _Bool StartOut = PredecessorSquare->Square == ParentSquare;
    const _Bool AtPiece = InspectedSquare->Space.Square == Residence->Space.Square;

    if (Residence->Identification == 2 && StartOut == 1) {
        if (DEBUGMODE == 1) printf("\n%hhd %hhd %d %d DEBUG1\n%hhu %hhu %hhu DEBUG2\n", UpRanks, LeftFiles, AtPiece, SkipParent, ParentSquare, PredecessorSquare->Square, Index.Square);
    }

    if (Invert(Index.OffBoard)) {
        if (InvertedAND(AtPiece, SkipParent)) {
            Handle->ChainParent = Residence->Space;

            Handle->Real = InspectedSquare->OccupiedSpace;
            Handle->Seen = 0;
        }

        if (Invert(AtPiece)) {
            Opportunities* Concern = &ProvisionalBoard->Collection[PredecessorSquare->Square].Opportunes[ParentSquare];
            if (PredecessorSquare->Square != ParentSquare && PredecessorSquare->OffBoard == 0) Concern->Dependee = InspectedSquare->Space.Square;
            Handle->Predecessor = PredecessorSquare->Square;

            const _Bool OpposingPiece = InclusiveOR(AND(Invert(InspectedSquare->HostBearing), Residence->HostBearing), AND(InspectedSquare->HostBearing, Invert(Residence->HostBearing)));
            Handle->Seen = AND(InclusiveOR(StartOut, AND(Invert(Concern->Real), Concern->Seen)), InclusiveOR(AND(Invert(Handle->Real), Options.Moves), InclusiveOR(AND(OpposingPiece, Options.Takes), AND(Invert(OpposingPiece), Options.Sabotages))));
            if (Handle->Seen == 1) ProvisionalBoard->LegalMoveCount++;

            if (DEBUGMODE == 1) printf(",%hhu!'%d!", Concern->Dependee, Handle->Seen);
        }
    }

    *PredecessorSquare = Index;

    _Bool ContinuouslyIterateModifiable = ContinuouslyIterate;
    if (InclusiveOR(ContinuouslyIterateModifiable, InclusiveOR(AtPiece, SkipParent))) {
        if (Index.OffBoard) Allaround = 0;
        if (InvertedInclusiveOR(Allaround, AtPiece)) ContinuouslyIterateModifiable = 0;

        const int StillStageRank = UpRanks + UpRanksIncrementation;
        const int StillStageFile = LeftFiles + LeftFilesIncrementation;

        LOOP_Piece(ProvisionalBoard, PredecessorSquare, Residence, Options, 0, Allaround, ContinuouslyIterateModifiable, (char) StillStageRank, (char) StillStageFile, UpRanksIncrementation, LeftFilesIncrementation);
    }
}

void LOOP_PieceQ(QuickDefinition* Settings, _Bool Allaround, const signed char UpRanksIncrementation, const signed char LeftFilesIncrementation) {
    LOOP_Piece(Settings->ProvisionalBoard, Settings->PredecessorSquare, Settings->Residence, *Settings->Options, 1, Allaround, *Settings->ContinuouslyIterate, 0, 0, UpRanksIncrementation, LeftFilesIncrementation);
}

void RecalculateOpportunes(HostChessBoard* ProvisionalBoard, const unsigned char Square) {
    BoardSection Residence = ProvisionalBoard->Collection[Square];

    SquareCount PredecessorSquare = {
        .Square = 0,
        .OffBoard = 0
    };

    Abilities Options = {
        .Takes = 1,
        .Moves = 1,
        .Sabotages = 0
    };
    _Bool CI = 0;

    Define_Piece(ProvisionalBoard, Square);

    QuickDefinition SettingLook = {
        .ProvisionalBoard = ProvisionalBoard,
        .PredecessorSquare = &PredecessorSquare,
        .Residence = &Residence,
        .Options = &Options,
        .ContinuouslyIterate = &CI
    };
    
    QuickDefinition* Settings = &SettingLook;
    
    switch (Residence.Identification) {
        case 1: ; // Pawn (En Passant / Promote)
            Options.Moves = 0;
            LOOP_PieceQ(Settings, 0, Residence.HostBearing == 1 ? 1 : -1, 1); // Left Take
            LOOP_PieceQ(Settings, 0, Residence.HostBearing == 1 ? 1 : -1, -1); // Right Take

            Options.Takes = 0;
            Options.Moves = 1;
            CI = 1;
            LOOP_PieceQ(Settings, 0, Residence.HostBearing == 1 ? 1 : -1, 0); // Move ahead

            break;
        case 2: ; // Knight
            LOOP_PieceQ(Settings, 0, 2, 1);
            LOOP_PieceQ(Settings, 0, 2, -1);
            LOOP_PieceQ(Settings, 0, 1, -2);
            LOOP_PieceQ(Settings, 0, -1, -2);
            LOOP_PieceQ(Settings, 0, -2, -1);
            LOOP_PieceQ(Settings, 0, -2, 1);
            LOOP_PieceQ(Settings, 0, -1, 2);
            LOOP_PieceQ(Settings, 0, 1, 2);

            break;
        case 3: ; // Bishop
            CI = 1;
            LOOP_PieceQ(Settings, 1, 1, 1);
            LOOP_PieceQ(Settings, 1, 1, -1);
            LOOP_PieceQ(Settings, 1, -1, -1);
            LOOP_PieceQ(Settings, 1, -1, 1);

            break;
        case 4: ; // Rook
            CI = 1;
            LOOP_PieceQ(Settings, 1, 1, 0);
            LOOP_PieceQ(Settings, 1, -1, 0);
            LOOP_PieceQ(Settings, 1, 0, 1);
            LOOP_PieceQ(Settings, 1, 0, -1);

            break;
        case 5: ; // Queen
            CI = 1;
            LOOP_PieceQ(Settings, 1, 1, 1);
            LOOP_PieceQ(Settings, 1, 1, 0);
            LOOP_PieceQ(Settings, 1, 1, -1);
            LOOP_PieceQ(Settings, 1, 0, -1);
            LOOP_PieceQ(Settings, 1, -1, -1);
            LOOP_PieceQ(Settings, 1, -1, 0);
            LOOP_PieceQ(Settings, 1, -1, 1);
            LOOP_PieceQ(Settings, 1, 0, 1);

            break;
        case 6: ; // King (Castle w/ Rook)
            LOOP_PieceQ(Settings, 0, 1, 1);
            LOOP_PieceQ(Settings, 0, 1, 0);
            LOOP_PieceQ(Settings, 0, 1, -1);
            LOOP_PieceQ(Settings, 0, 0, -1);
            LOOP_PieceQ(Settings, 0, -1, -1);
            LOOP_PieceQ(Settings, 0, -1, 0);
            LOOP_PieceQ(Settings, 0, -1, 1);
            LOOP_PieceQ(Settings, 0, 0, 1);

            break;
        default: ;
    }
}

void FillOppurtunes(HostChessBoard* MainBoard, const _Bool DoOtherPieces) {
    unsigned char Square = 0;

    while (Square < 64) {
        if (InclusiveOR(InvertedExclusiveOR(MainBoard->Collection[Square].HostBearing, MainBoard->Play), DoOtherPieces)) RecalculateOpportunes(MainBoard, Square);
        Square++;
    }
}

unsigned char ezslidingstuff(const unsigned char File, const unsigned char Rank) {
    return BoardSquare(RobotLanguage((SquareAlignment) {
        .File = SignedSwap_hh(File),
        .Rank = SignedSwap_hh(Rank)
    })).Square;
}

// SLIDING PIEES
void SlidePiece(const HostChessBoard* ProvisionalBoard, const unsigned char SourceSquare, const unsigned char DestinationSquare) {
    ModifyRegionalValues(ProvisionalBoard, DestinationSquare, ProvisionalBoard->Collection[SourceSquare], ModifyPiece());
    ModifyRegionalValues(ProvisionalBoard, SourceSquare, (BoardSection) {}, ModifyPiece());
    ProvisionalBoard->Collection[DestinationSquare].MovedSince = 1;
}

void ezslider(const HostChessBoard* ProvisionalBoard, const AMove Select) {
    SlidePiece(ProvisionalBoard, ezslidingstuff(Select.StartingFile, Select.StartingRank), ezslidingstuff(Select.EndingFile, Select.EndingRank));
}

_Bool CheckIfMovable(const HostChessBoard Board, const AMove Position) {
    return Board.Collection[ezslidingstuff(Position.EndingFile, Position.EndingRank)].Opportunes[ezslidingstuff(Position.StartingFile, Position.StartingRank)].Seen;
}

unsigned char FindPlayKing(const HostChessBoard Board) {
    unsigned char Square = 0;
    unsigned char KingsSquare = 0;

    while (Square < 64) {
        if (Board.Collection[Square].Identification == 6 && ExclusiveOR(Board.Collection[Square].HostBearing == 1, Board.Play == 1) == 0) KingsSquare = Square;

        Square++;
    }

    return KingsSquare;
}

unsigned char SquareByPlay(const HostChessBoard Board, const unsigned char Square) {
    unsigned char SquareHigh = 0;
    unsigned char Attackers = 0;

    while (SquareHigh < 64) {
        if (ExclusiveOR(Board.Collection[SquareHigh].HostBearing, Board.Play) == 1 && Board.Collection[Square].Opportunes[SquareHigh].Seen == 1) Attackers++;

        SquareHigh++;
    }

    return Attackers;
}

// check if the king is in check if a move is played
HostChessBoard* GhostMove(const HostChessBoard OriginalBoard, const AMove Movement) {
    HostChessBoard PlayCopy = ConstructPlay();
    HostChessBoard* Board = &PlayCopy;

    LoadChessBoard(Board, OriginalBoard);

    ezslider(Board, Movement);

    return Board;
}

// compile all legal moves based on king attacked function
_Bool ALegalMove(const HostChessBoard Board, const AMove Movement) {
    _Bool Decision = 0;

    if (CheckIfMovable(Board, Movement) == 1) {
        HostChessBoard PlayCopy = {
            .Starting = 1,
            .Play = 1,
            .Collection = (BoardSection*) calloc(64, sizeof(BoardSection)),
        };

        HostChessBoard* GhostBoard = &PlayCopy;

        memcpy(PlayCopy.Collection, Board.Collection, sizeof(&PlayCopy.Collection));
        ezslider(GhostBoard, Movement);

        unsigned char KingsSquare = 0;

        unsigned char SequentialNumerator = 0;

        while (SequentialNumerator < 64) {
            if (Board.Collection[SequentialNumerator].Identification == 6 && ExclusiveOR(Board.Collection[SequentialNumerator].HostBearing, Board.Play) == 0) KingsSquare = SequentialNumerator;

            SequentialNumerator++;
        }

        SequentialNumerator = 0;

        unsigned char Attackers = 0;

        while (SequentialNumerator < 64) {
            if (ExclusiveOR(GhostBoard->Collection[SequentialNumerator].HostBearing, GhostBoard->Play) == 1 && GhostBoard->Collection[KingsSquare].Opportunes[SequentialNumerator].Seen == 1) Attackers++;

            SequentialNumerator++;
        }

        Decision = Attackers == 0;

        SequentialNumerator = 0;

        while (SequentialNumerator < 64) {
            free(GhostBoard->Collection[SequentialNumerator + 1].Opportunes);

            SequentialNumerator++;
        }

        free(GhostBoard->Collection);
    }

    return Decision;
}

// LETTER TRANSLATIONS
char NumberLetterTranslation(const char Case, const _Bool NumericalOut, const _Bool UseNumber) {
    char LetterTranslation;
    if (UseNumber == 0 && NumericalOut == 1) {
        LetterTranslation = 0;
        if (Case == 'A') LetterTranslation = 1;
        if (Case == 'B') LetterTranslation = 2;
        if (Case == 'C') LetterTranslation = 3;
        if (Case == 'D') LetterTranslation = 4;
        if (Case == 'E') LetterTranslation = 5;
        if (Case == 'F') LetterTranslation = 6;
        if (Case == 'G') LetterTranslation = 7;
        if (Case == 'H') LetterTranslation = 8;
        return LetterTranslation;
    }
    if (UseNumber == 1 && NumericalOut == 0) {
        LetterTranslation = ' ';
        if (Case == 1) LetterTranslation = 'A';
        if (Case == 2) LetterTranslation = 'B';
        if (Case == 3) LetterTranslation = 'C';
        if (Case == 4) LetterTranslation = 'D';
        if (Case == 5) LetterTranslation = 'E';
        if (Case == 6) LetterTranslation = 'F';
        if (Case == 7) LetterTranslation = 'G';
        if (Case == 8) LetterTranslation = 'H';
        return LetterTranslation;
    }
    return Case;
}

char PieceToLetterTranslation(const unsigned char Piece, const unsigned char File) {
    char LetterTranslation;
    LetterTranslation = ' ';
    if (Piece == 1) LetterTranslation = NumberLetterTranslation(SignedSwap_hh(File), 0, 1);
    if (Piece == 2) LetterTranslation = 'N';
    if (Piece == 3) LetterTranslation = 'B';
    if (Piece == 4) LetterTranslation = 'R';
    if (Piece == 5) LetterTranslation = 'Q';
    if (Piece == 6) LetterTranslation = 'K';
    return LetterTranslation;
}

// PRINTING OUT
void PrintSpacer() {
    printf(". ---------------------------------\n");
}

void PrintBoard(const HostChessBoard* ProvisionalBoard, const enum ChessPieceUsedProperty Property, const _Bool printthis, const unsigned char SelectedFile, const unsigned char SelectedRank, const _Bool UseLetters) {
    char Rank = 8;

    while (Rank > 0) {
        PrintSpacer();
        printf("%hhu |", Rank);

        char File = 1;

        while (!(File > 8)) {
            const BoardSection Residence = ProvisionalBoard->Collection[ezslidingstuff(File, Rank)];
            printf(" ");

            if (printthis == 1) {
                if (Residence.OccupiedSpace == 1) {
                    switch (Property) {
                        case IDENTIFICATION:
                            const char StarterSquare = BoardLocation((char) Residence.StartingSquare.Square).File + 1;

                            if (UseLetters == 0) printf("%hhd", Residence.Identification);
                            if (UseLetters == 1) printf("%c", PieceToLetterTranslation(Residence.Identification, StarterSquare));

                            break;
                        case HOSTBEARING:
                            printf("%d", Residence.HostBearing);

                            break;
                        case OCCUPIEDSQUARE:
                            printf("%d", Residence.OccupiedSpace);

                            break;
                        default: ;
                    }
                } else {
                    printf(" ");
                }
            }
            if (printthis == 0) {
                const unsigned char Selection = ezslidingstuff(SelectedFile, SelectedRank);
                const Opportunities T = Residence.Opportunes[Selection]; // using normal stuff

                if (EqualOpportunities(T, (Opportunities) {}) == 0) {
                    printf("%d", T.Seen);
                } else if (Selection == Residence.Space.Square) {
                    printf("X");
                } else {
                    printf(" ");
                }
            }

            printf(" |");

            File++;
        }

        if (Rank == 1) {
            printf("\n");
            PrintSpacer();
        } else {
            printf("\n");
        }

        Rank--;
    }

    printf(". . a . b . c . d . e . f . g . h .\n\n");
}

// PLACING PIECES
void PlopPiece(const HostChessBoard* Board, const unsigned char File, const unsigned char Rank, const _Bool OccupiedSpace, const _Bool HostBearing, const unsigned char Identification, const SquareCount StartingSquare) {
    const BoardSection Section = (BoardSection) {
        .OccupiedSpace = OccupiedSpace,
        .HostBearing = HostBearing,
        .Identification = Identification,
        .StartingSquare = StartingSquare
    };

    ModifyRegionalValues(Board, ezslidingstuff(File, Rank), (BoardSection) Section, ModifyPiece());
}

// FLIPPING BOARD
HostChessBoard FlippedBoard(const HostChessBoard* RegularBoard) {
    const HostChessBoard SetFlipped = ConstructPlay();

    unsigned char Square = 0;

    while (Square < 64) {
        const SquareAlignment LCCC = BoardLocation(Square);

        const BoardSection Source = RegularBoard->Collection[1 + 8 * LCCC.File * 2 - Square];

        ModifyRegionalValues(&SetFlipped, Square, Source, ModifyPiece());

        Square++;
    }

    return SetFlipped;
}

void ClassicalPlopper(const HostChessBoard* Board, const unsigned char File, const unsigned char Rank, const unsigned char Identification) {
    PlopPiece(Board, File, Rank, 1, 2 * Rank < 9, Identification, Board->Collection[ezslidingstuff(File, Rank)].StartingSquare);

    /*
    const unsigned char Square = ezslidingstuff(File, Rank);

    Board->Collection[Square].Identification = Identification;
    Board->Collection[Square].HostBearing = 2 * Rank < 9;
    Board->Collection[Square].OccupiedSpace = 1;
    */

    /*
    MainBoard->Collection[s].Identification = i;
    MainBoard->Collection[s].HostBearing = b;
    MainBoard->Collection[s].OccupiedSpace = 1;
    */
}

void ClassicalSetup(const HostChessBoard* Board) {
    /*
    ClassicalPlopper(Board, 5, 1, 6);
    ClassicalPlopper(Board, 4, 1, 5);
    ClassicalPlopper(Board, 1, 1, 4);
    ClassicalPlopper(Board, 8, 1, 4);
    ClassicalPlopper(Board, 3, 1, 3);
    ClassicalPlopper(Board, 6, 1, 3);
    ClassicalPlopper(Board, 2, 1, 2);
    ClassicalPlopper(Board, 7, 1, 2);
    ClassicalPlopper(Board, 5, 8, 6);
    ClassicalPlopper(Board, 4, 8, 5);
    ClassicalPlopper(Board, 1, 8, 4);
    ClassicalPlopper(Board, 8, 8, 4);
    ClassicalPlopper(Board, 3, 8, 3);
    ClassicalPlopper(Board, 6, 8, 3);
    ClassicalPlopper(Board, 2, 8, 2);
    ClassicalPlopper(Board, 7, 8, 2);
    ClassicalPlopper(Board, 1, 2, 1);
    ClassicalPlopper(Board, 2, 2, 1);
    ClassicalPlopper(Board, 3, 2, 1);
    ClassicalPlopper(Board, 4, 2, 1);
    ClassicalPlopper(Board, 5, 2, 1);
    ClassicalPlopper(Board, 6, 2, 1);
    ClassicalPlopper(Board, 7, 2, 1);
    ClassicalPlopper(Board, 8, 2, 1);
    ClassicalPlopper(Board, 1, 7, 1);
    ClassicalPlopper(Board, 2, 7, 1);
    ClassicalPlopper(Board, 3, 7, 1);
    ClassicalPlopper(Board, 4, 7, 1);
    ClassicalPlopper(Board, 5, 7, 1);
    ClassicalPlopper(Board, 6, 7, 1);
    ClassicalPlopper(Board, 7, 7, 1);
    ClassicalPlopper(Board, 8, 7, 1);
    */

    /**/
    // custom legal move generated scenario
    unsigned char Square = 0;

    Square = ezslidingstuff(5, 3);
    Board->Collection[Square].Identification = 6;
    Board->Collection[Square].HostBearing = 1;
    Board->Collection[Square].OccupiedSpace = 1;

    Square = ezslidingstuff(2, 8);
    Board->Collection[Square].Identification = 6;
    Board->Collection[Square].HostBearing = 0;
    Board->Collection[Square].OccupiedSpace = 1;

    Square = ezslidingstuff(5, 4);
    Board->Collection[Square].Identification = 4;
    Board->Collection[Square].HostBearing = 1;
    Board->Collection[Square].OccupiedSpace = 1;

    Square = ezslidingstuff(6, 4);
    Board->Collection[Square].Identification = 5;
    Board->Collection[Square].HostBearing = 0;
    Board->Collection[Square].OccupiedSpace = 1;
    /**/

    /*
    // FOR DEBUGGING
    const unsigned char Square = ezslidingstuff(5, 4);

    Board->Collection[Square].Identification = 1;
    Board->Collection[Square].HostBearing = 0;
    Board->Collection[Square].OccupiedSpace = 1;
    */
}

// MAIN FUNCTIONS
void MakeMoves(const HostChessBoard* MainBoard, const AMove* Moves, const unsigned char NumberofMoves) {
    unsigned char MoveNumber = 0;

    while (MoveNumber < NumberofMoves) {
        ezslider(MainBoard, Moves[MoveNumber]);
        MoveNumber++;
    }
}

AMove* ALegalBoard(const HostChessBoard MainBoard) {
    unsigned int NumberofMoves = 0;

    AMove* LegalMoveList = calloc(NumberofMoves, sizeof(AMove));
    AMove* RevisedList = calloc(NumberofMoves, sizeof(AMove));

    unsigned char StartingSquare = 0;

    while (StartingSquare < 64) {
        const SquareAlignment StartingLocation = BoardLocation(StartingSquare);

        unsigned char EndingSquare = 0;

        while (EndingSquare < 64) {
            const SquareAlignment EndingLocation = BoardLocation(EndingSquare);
            const AMove SpotlitMove = (AMove) {StartingLocation.File, StartingLocation.Rank, EndingLocation.File, EndingLocation.Rank};

            if (ALegalMove(MainBoard, SpotlitMove) == 1) {
                NumberofMoves++;
                AMove* InnerScopeList = calloc(NumberofMoves, sizeof(AMove));

                unsigned int Moves = 1;

                while (Moves < NumberofMoves) {
                    

                    Moves++;
                }
            }

            EndingSquare++;
        }

        StartingSquare++;
    }

    free(LegalMoveList);
    return RevisedList;
}

void GameEngage(const unsigned long int Iteration, unsigned long int* IterationCap, HostChessBoard* MainBoard, const AMove* Moves, const unsigned char NumberofMoves) {
    MakeMoves(MainBoard, Moves, NumberofMoves);

    FillOppurtunes(MainBoard, 1);

    PrintBoard(MainBoard, IDENTIFICATION, 1, 1, 1, 1);

    *IterationCap = Iteration;
}

unsigned char GamePlay(AMove* PlayedMoves) {
    // PlayedMoves[movenum] = (AMove) {sf, sr, ef, er};

    return 0; // number of moves
}