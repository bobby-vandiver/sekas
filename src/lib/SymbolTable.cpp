#include "SymbolTable.h"
#include "IllegalArgumentException.h"

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
		throw IllegalArgumentException("Symbol cannot be null!");
}

void SymbolTable::throwIfSymbolAlreadyDefined(Symbol *symbol) const {
	std::string name = symbol->getName();
	if(isSymbolInTable(name)) {
		std::string message = "Symbol [" + name + "] already defined!";
		throw IllegalArgumentException(message);
	}
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