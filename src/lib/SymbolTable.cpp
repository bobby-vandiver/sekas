#include "SymbolTable.h"
#include <stdexcept>

SymbolTable::~SymbolTable() {
	symbolList.clear();
}

bool SymbolTable::isEmpty() const {
	return symbolList.empty();
}

void SymbolTable::insert(Symbol *symbol) {
	throwIfSymbolIsNull(symbol);
	throwIfSymbolAlreadyDefined(symbol);
	insertSymbol(symbol);
}

void SymbolTable::throwIfSymbolIsNull(Symbol *symbol) const {
	if(symbol == NULL)
		throw std::invalid_argument("Symbol cannot be null!");
}

void SymbolTable::throwIfSymbolAlreadyDefined(Symbol *symbol) const {
	if(isSymbolInTable(symbol->getName()))
		throw std::invalid_argument("Symbol already defined!");
}

void SymbolTable::insertSymbol(Symbol *symbol) {
	symbolList.push_back(symbol);
}

bool SymbolTable::isSymbolInTable(std::string name) const {
	Symbol *symbol = findSymbolByNameOrReturnNull(name);
	return symbol != NULL;
}

Symbol *SymbolTable::findByName(std::string name) const {
	return findSymbolByNameOrReturnNull(name);
}

Symbol *SymbolTable::findSymbolByNameOrReturnNull(std::string name) const {
	std::list<Symbol *>::const_iterator symbolIterator;
	for(symbolIterator = symbolList.begin(); symbolIterator != symbolList.end(); symbolIterator++) {
		if((*symbolIterator)->getName() == name)
			return (Symbol *)*symbolIterator;
	}
	return NULL;
}