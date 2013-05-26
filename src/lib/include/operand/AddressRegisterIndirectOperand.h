#ifndef ADDRESS_REGISTER_INDIRECT_OPERAND_H
#define ADDRESS_REGISTER_INDIRECT_OPERAND_H

#include "Operand.h"
#include <string>

class AddressRegisterIndirectOperand : public Operand {
public:
	static bool isAddressRegisterIndirect(const std::string &operand);

	AddressRegisterIndirectOperand(const std::string &operand);

	virtual ~AddressRegisterIndirectOperand() {}

	virtual unsigned int getExtensionWordCount() const;	
	virtual void setExtensionWordCount(const unsigned int count);

	virtual unsigned short *getExtensionWords() const;
	virtual void setExtensionWords(unsigned short *extensionWords);

	virtual unsigned int getRegisterField() const;
	virtual unsigned int getModeField() const;

private:
	static const unsigned int EXTENSION_WORD_COUNT = 0;
	static const unsigned int MODE_FIELD = 2;

	static const unsigned int REGISTER_NUMBER_POSITION = 2;
	unsigned int registerNumber;

	void throwExceptionIfInvalidOperand(const std::string &operand);
};

#endif