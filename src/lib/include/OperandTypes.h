#ifndef OPERAND_TYPES_H
#define OPERAND_TYPES_H

namespace OperandTypes {
	const std::string DataRegisterDirect = "data direct";
	const std::string AddressRegisterDirect = "address direct";
	const std::string AddressRegisterIndirect = "address indirect";
	const std::string AddressRegisterIndirectPostIncrement = "address indirect post increment";
	const std::string AddressRegisterIndirectPreDecrement = "address indirect pre decrement";
	const std::string AddressRegisterIndirectDisplacement = "address indirect displacement";
	const std::string InvalidOperand = "invalid";
}

#endif