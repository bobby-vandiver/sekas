#ifndef ADDRESS_REGISTER_DIRECT_OPERAND_H
#define ADDRESS_REGISTER_DIRECT_OPERAND_H

#include "Operand.h"
#include <string>

class AddressRegisterDirectOperand : public Operand {
public:
	static bool isAddressRegisterDirect(const std::string &operand);

	AddressRegisterDirectOperand(const std::string &operand);

	virtual ~AddressRegisterDirectOperand() {}

	virtual unsigned int getExtensionWordCount() const;	
	virtual void setExtensionWordCount(const unsigned int count);

	virtual unsigned short *getExtensionWords() const;
	virtual void setExtensionWords(unsigned short *extensionWords);

	virtual unsigned int getRegisterField() const;
	virtual unsigned int getModeField() const;

private:
	static const unsigned int EXTENSION_WORD_COUNT = 0;
	static const unsigned int MODE_FIELD = 1;

	unsigned int registerNumber;

	void throwExceptionIfInvalidOperand(const std::string &operand);
	unsigned int getRegisterNumber(const std::string &operand);

};

#endif