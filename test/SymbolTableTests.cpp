#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SymbolTable.h"
#include "IllegalArgumentException.h"

TEST(SymbolTableTests, IsEmptyReturnsTrueWhenNoSymbolsInTable) {
	SymbolTable symbolTable = SymbolTable();
	EXPECT_TRUE(symbolTable.isEmpty());
}

TEST(SymbolTableTests, IsEmptyReturnsFalseForNonEmptyTable) {
	SymbolTable symbolTable = SymbolTable();
	Symbol *symbol = new Symbol("foo", 1234);
	ASSERT_TRUE(symbol != NULL);

	symbolTable.insert(symbol);
	EXPECT_FALSE(symbolTable.isEmpty());
	delete symbol;
}

TEST(SymbolTableTests, FindByNameReturnsNullWhenSymbolNotFound) {
	SymbolTable symbolTable = SymbolTable();
	Symbol *symbol = symbolTable.findByName("foo");
	EXPECT_EQ(NULL, symbol);
	delete symbol;
}

TEST(SymbolTableTests, FindByNameReturnsSymbolWithOneSymbolInTable) {
	SymbolTable symbolTable = SymbolTable();
	Symbol *symbol = new Symbol("foo", 1234);
	ASSERT_TRUE(symbol != NULL);

	symbolTable.insert(symbol);
	Symbol *result = symbolTable.findByName("foo");
	EXPECT_EQ(symbol, result);
	delete symbol;
}

TEST(SymbolTableTests, FindByNameReturnsSymbolWithMultipleSymbolsInTable) {
	SymbolTable symbolTable = SymbolTable();
	
	Symbol *symbol1 = new Symbol("foo", 1234);
	Symbol *symbol2 = new Symbol("bar", 567890);

	ASSERT_TRUE(symbol1 != NULL);
	ASSERT_TRUE(symbol2 != NULL);

	symbolTable.insert(symbol1);
	symbolTable.insert(symbol2);

	Symbol *result = symbolTable.findByName("bar");
	EXPECT_EQ(symbol2, result);

	delete symbol1;
	delete symbol2;
}

TEST(SymbolTableTests, InsertNullThrowsException) {
	SymbolTable symbolTable = SymbolTable();
	EXPECT_THROW(symbolTable.insert(NULL), IllegalArgumentException);
}

TEST(SymbolTableTests, InsertDuplicateSymbolThrowsException) {
	SymbolTable symbolTable = SymbolTable();

	Symbol *symbol1 = new Symbol("foo", 1234);
	Symbol *symbol2 = new Symbol("foo", 1234);

	ASSERT_TRUE(symbol1 != NULL);
	ASSERT_TRUE(symbol2 != NULL);

	symbolTable.insert(symbol1);
	EXPECT_THROW(symbolTable.insert(symbol2), IllegalArgumentException);

	delete symbol1;
	delete symbol2;
}

class MockSymbol : public Symbol {
	public:
		MockSymbol() : Symbol("mockSymbol") {}
		MOCK_METHOD0(Die, void());
		~MockSymbol() { Die(); }
};

TEST(SymbolTableTests, DestructorDeletesAllSymbols) {
	SymbolTable *symbolTable = new SymbolTable();
	ASSERT_TRUE(symbolTable != NULL);

	MockSymbol *mockSymbol = new MockSymbol;
	EXPECT_CALL(*mockSymbol, Die());

	symbolTable->insert(mockSymbol);

	delete symbolTable;
	delete mockSymbol;
}