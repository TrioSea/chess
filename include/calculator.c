#include "calculator.h"
// #include "mymath.h"

_Bool Inequality(const _Bool* X, const _Bool Check) {
    if (*X != Check) return 1; // Invert your check parameter for an equality, 1 is meant to be to run a function inside an if
    return 0; // alongside definition of 1, function same to *X ? !Check : Check
}

_Bool Invert(const _Bool N) {
    return Inequality(&N, 1);

    /*
    if (*X != 0) return 0;
    return 1;
    */
}

_Bool InvertedAND(const _Bool A, const _Bool B) {
    _Bool* Through = 0;

    *Through = Invert(A);
    if (*Through) return *Through;

    *Through = Invert(B);
    if (*Through) return *Through;

    return Invert(1);

    /*
    if (A != 1) return 1;
    if (B != 1) return 1;

    return 0;
    */
}

_Bool AND(const _Bool A, const _Bool B) {
    return Invert(InvertedAND(A, B));

    /*
    if (A != 1) return 0;
    if (B != 1) return 0;

    return 1;
    */
}

_Bool InvertedInclusiveOR(const _Bool A, const _Bool B) {
    return Invert(InvertedAND(Invert(A), Invert(B)));

    /*
    if (A != 0) return 0;
    if (B != 0) return 0;

    return 1;
    */
}

_Bool InclusiveOR(const _Bool A, const _Bool B) {
    return InvertedAND(Invert(A), Invert(B));

    /*
    if (A != 0) return 1;
    if (B != 0) return 1;

    return 0;
    */
}

_Bool InvertedExclusiveOR(const _Bool A, const _Bool B) {
    return InvertedAND(InvertedAND(Invert(A), Invert(B)), InvertedAND(A, B));

    /*
    _Bool V;

    V = 0;
    if (A != 0) V = 1;
    if (B != 0) V = 1;
    if (V != 1) return 1;

    V = 0;
    if (A != 1) V = 1;
    if (B != 1) V = 1;
    if (V != 1) return 1;

    return 0;
    */
}

_Bool ExclusiveOR(const _Bool A, const _Bool B) {
    return Invert(InvertedAND(InvertedAND(Invert(A), Invert(B)), InvertedAND(A, B)));

    /*
    _Bool V;

    V = 0;
    if (A != 0) V = 1;
    if (B != 0) V = 1;
    if (V != 1) return 0;

    V = 0;
    if (A != 1) V = 1;
    if (B != 1) V = 1;
    if (V != 1) return 0;

    return 1;
    */
}

unsigned char AbsoluteValue_hhu(const signed char X) {
    if (X < 0) return (unsigned char) -X;
    if (X > 0) return (unsigned char) X;
    
    return 0;
}

signed char SignedSwap_hh(const unsigned char X) {
    return (signed char) X;
}

signed char ClampValue_hhd(const signed char X, const signed char Minimum, const signed char Maximum) {
    if (X < Minimum) return Minimum;
    if (X > Maximum) return Maximum;

    return X;
}

/*
void Finish() {
    int RepeatSquare = 0;
    const unsigned char Copies = 2;

    unsigned char KingsSquare = 0;
    unsigned char Attackers = 0;

    while (floor((double) RepeatSquare / Copies) < 64) {
        const unsigned char Section = floor((double) RepeatSquare / 64);
        const unsigned char SequentialNumerator = RepeatSquare - 64 * Section;

        if (Section == 0) {
            ;

            if (SequentialNumerator + 1 == 64) {
                ;
            }
        } else if (Section == 1) {
            ;

            if (SequentialNumerator + 1 == 64) {
                ;
            }
        }

        RepeatSquare++;
    }
}
*/