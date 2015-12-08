#include "SymbolicRange.h"
SymbolicRange SymbolicRange::add(SymbolicRange * other) {
    SymbolicExpr upper = 
	    (this->upperBound).add(other->upperBound);
    SymbolicExpr lower = 
            (this->lowerBound).add(other->lowerBound);
    return SymbolicRange(lower, upper);
}

SymbolicRange SymbolicRange::sub(SymbolicRange * other) {
    SymbolicExpr upper = 
	    (this->upperBound).sub(other->lowerBound);
    SymbolicExpr lower = 
	    (this->lowerBound).sub(other->upperBound);
    return SymbolicRange(lower, upper);
}

SymbolicRange SymbolicRange::mul(SymbolicExpr * E) {
    SymbolicRange range1 = SymbolicRange(
		    (this->lowerBound).mul(E),
		    (this->upperBound).mul(E));
    SymbolicRange range2 = SymbolicRange(
		    (this->upperBound).mul(E),
		    (this->lowerBound).mul(E));
    return range1.unite(range2);
}

SymbolicRange SymbolicRange::mul(SymbolicRange * other) {
    SymbolicRange range1= this->mul(other->lowerBound);	
    SymbolicRange range2= this->mul(other->upperBound);	
    return range1.unite(range2);
}

SymbolicRange SymbolicRange::div(SymbolicExpr * E) {
}

SymbolicRange SymbolicRange::div(SymbolicRange * other) {
    if (other->containsZero()) {
        return SymbolicRange(
		    *(BottomSymbol.getInstance()), 
	            *(TopSymbol.getInstance()));
    } else {
	SymbolicRange range1 = this->div(other->lowerBound);
	SymbolicRange range2 = this->div(other->upperBound);
	return range1.unite(range2);
    }
}

SymbolicRange SymbolicRange::mod(SymbolicExpr * E) {
	
}

SymbolicRange SymbolicRange::mod(SymbolicRange * other) {
}

SymbolicRange SymbolicRange::unite(SymbolicRange * other) {
}

SymbolicRange SymbolicRange::intersect(SymbolicRange * other) {
}
