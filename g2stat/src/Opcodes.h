#pragma once
//SJCLib
#include <SJCLib.h>

namespace SJCPBLib
{
	namespace Daedalus
	{
		enum EOpcode
		{
			OPCODE_ADD, //0
			OPCODE_SUBTRACT, //1
			OPCODE_MULTIPLICATE, //2
			OPCODE_DIVIDE, //3
			OPCODE_MODULO, //4
			OPCODE_BITWISEOR, //5
			OPCODE_BITWISEAND, //6
			OPCODE_LESSTHAN, //7
			OPCODE_GREATERTHAN, //8
			OPCODE_ASSIGN, //9
			OPCODE_LOGICALOR = 11,
			OPCODE_LOGICALAND = 12, //12
			OPCODE_LESSTHANOREQUALTO = 15, //15
			OPCODE_EQUALS, //16
			OPCODE_NOTEQUALS, //17
			OPCODE_GREATERTHANOREQUALTO, //18
			OPCODE_ADDASSIGN, //19
			OPCODE_UNARYMINUS = 31, //31
			OPCODE_NOT, //32
			OPCODE_RETURN = 60, //60
			OPCODE_CALL, //61
			OPCODE_CALLEXTERNAL, //62
			OPCODE_PUSHINT = 64, //64
			OPCODE_PUSHVAR, //65
			OPCODE_PUSHINSTANCE = 67, //67
			OPCODE_ASSIGN_STRING = 70, //70
			OPCODE_ASSIGN_FUNC = 72, //72
			OPCODE_ASSIGN_FLOAT = 73,
			OPCODE_ASSIGN_INSTANCE = 74, //74
			OPCODE_JUMP, //75
			OPCODE_JUMP_IF, //76
			OPCODE_SET_INSTANCE = 80, //80
			OPCODE_PUSH_ARRAY_VAR = 245
		};
	}
}