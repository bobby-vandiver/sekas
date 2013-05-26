#ifndef ADDRESS_REGISTER_INDIRECT_DISPLACEMENT_OPERAND_H
#define ADDRESS_REGISTER_INDIRECT_DISPLACEMENT_OPERAND_H

#include "Operand.h"
#include <string>

class AddressRegisterIndirectDisplacementOperand : public Operand {
public:
	static bool isAddressRegisterIndirectDisplacement(const std::string &operand);

	AddressRegisterIndirectDisplacementOperand(const std::string &operand);

	virtual ~AddressRegisterIndirectDisplacementOperand() {}

	virtual unsigned int getExtensionWordCount() const;	
	virtual void setExtensionWordCount(const unsigned int count);

	virtual unsigned short *getExtensionWords() const;
	virtual void setExtensionWords(unsigned short *extensionWords);

	virtual unsigned int getRegisterField() const;
	virtual unsigned int getModeField() const;

private:
	static const unsigned int EXTENSION_WORD_COUNT = 1;
	static const unsigned int MODE_FIELD = 5;
	static const unsigned long MAX_DISPLACEMENT = 0xffff;

	std::string operand;

	unsigned int registerNumber;
	unsigned short *extensionWords;

	void throwExceptionIfInvalidOperand() const;
	unsigned int getRegisterNumberPosition() const;

	unsigned short *getExtensionWordsForDisplacement() const;

	static bool isUsingStandardDisplacementNotation(const std::string &operand);
	static bool isValidAddressRegisterIndirectWithStandardDisplacementNotation(const std::string &operand);

	static bool isUsingPrefixDisplacementNotation(const std::string &operand);
	static bool isValidAddressRegisterIndirectWithPrefixDisplacementNotation(const std::string &operand);

	static const std::string getPrefixDisplacement(const std::string &operand);
	static const std::string getStandardDisplacement(const std::string &operand);
};

#endif