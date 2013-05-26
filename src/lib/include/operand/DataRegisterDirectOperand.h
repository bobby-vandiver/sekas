#ifndef DATA_REGISTER_DIRECT_OPERAND_H
#define DATA_REGISTER_DIRECT_OPERAND_H

#include "Operand.h"
#include <string>

class DataRegisterDirectOperand : public Operand {
public:
	static bool isDataRegisterDirect(const std::string &operand);

	DataRegisterDirectOperand(const std::string &operand);

	virtual ~DataRegisterDirectOperand() {}

	virtual unsigned int getExtensionWordCount() const;	
	virtual void setExtensionWordCount(const unsigned int count);

	virtual unsigned short *getExtensionWords() const;
	virtual void setExtensionWords(unsigned short *extensionWords);

	virtual unsigned int getRegisterField() const;
	virtual unsigned int getModeField() const;

private:
	static const unsigned int EXTENSION_WORD_COUNT = 0;
	static const unsigned int MODE_FIELD = 0;

	static const unsigned int REGISTER_NUMBER_POSITION = 1;
	unsigned int registerNumber;

	void throwExceptionIfInvalidOperand(const std::string &operand);
};

#endif