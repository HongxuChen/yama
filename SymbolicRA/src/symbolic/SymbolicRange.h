#ifndef SYMBOLIC_RANGE_H__
#define SYMBOLIC_RANGE_H__

class SymbolicExpr;

class SymbolicRange {
private:
    SymbolicExpr lowerBound;
    SymbolicExpr upperBound;
    SymbolicRange mul(SymbolicExpr * E);
    SymbolicRange div(SymbolicExpr * E);
    SymbolicRange mod(SymbolicExpr * E);
public:
   SymbolicRange(SymbolicExpr lower, SymbolicExpr upper):
	    lowerBound(lower), upperBound(upper) { }

   bool containsZero();

   // TODO: implement symbolic range 
   // algebra shown in Figure 2
   // plus, minus, multiply, divide, mod,
   // union, and intersect    
   SymbolicRange add(SymbolicRange * other);
   SymbolicRange sub(SymbolicRange * other);
   SymbolicRange mul(SymbolicRange * other);
   SymbolicRange div(SymbolicRange * other);
   SymbolicRange mod(SymbolicRange * other);
   SymbolicRange unite(SymbolicRange * other);
   SymbolicRange intersect(SymbolicRange * other);
   
};
#endif
