#ifndef ATOMIC_SYMBOL_H__
#define ATOMIC_SYMBOL_H__

#include "SymbolicExpr.h"

class AtomicSymbol : public SymbolicExpr {

};

class TopSymbol : public AtomicSymbol {
public:
    static SymbolicExpr * getInstance();
};

class BottomSymbol : public AtomicSymbol {
public:
    static SymbolicExpr * getInstance();
};

#endif
