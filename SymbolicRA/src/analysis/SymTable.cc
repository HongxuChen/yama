#include "SymTable.h"

// define static field
SymTable * SymTable::instance = 0;

SymTable * SymTable::getInstance() {
    if (!instance) {
	instance = new SymTable;
    }
    return instance;
}

SymTable::SymTable() {
    table = new map<Variable*, SymbolicRange*>;
}

SymTable::~SymTable() {
    delete table;
}

void SymTable::putRange(Variable* V, SymbolicRange *R) {
    (*table)[V] = R;
}

SymbolicRange * SymTable::getRange(Variable* V) {
    return (*table)[V];
}

bool SymTable::isInTable(Variable * V) {
    if (table->count(V)) {
	return true;
    } else {
	return false;
    }
}
