#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <list>
#include <string>

#include "Symbol.h"

class SymbolTable {

public:
	SymbolTable() {}
	~SymbolTable();

	bool isEmpty() const;
	void insert(Symbol *symbol);
	Symbol *findByName(std::string name) const;

private:
	std::list<Symbol *> symbolList;

	void throwIfSymbolIsNull(Symbol *symbol) const;
	void throwIfSymbolAlreadyDefined(Symbol *symbol) const;

	void insertSymbol(Symbol *symbol);
	bool isSymbolInTable(std::string name) const;

	Symbol *findSymbolByNameOrReturnNull(std::string name) const;
};

#endif