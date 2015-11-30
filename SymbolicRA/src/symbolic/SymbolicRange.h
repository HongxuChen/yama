#ifndef SYMBOLIC_RANGE_H__
#define SYMBOLIC_RANGE_H__

class SymbolicExpr;

class SymbolicRange {
private:
    SymbolicExpr upperBound;
    SymbolicExpr lowerBound;
public:
    // TODO: implement symbolic range 
    // algebra shown in Figure 2
    // plus, minus, multiply, divide, mod,
    // union, and intersect    
    
    SymbolicRange(SymbolicExpr upper, SymbolicExpr lower):
	    upperBound(upper), lowerBound(lower) { }
    
};
#endif
