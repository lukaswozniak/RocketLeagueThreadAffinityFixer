#include "throwIf.h"
#include <sstream>

FunctionReturnValueException::FunctionReturnValueException(const char* functionName, const char* result)
	: std::runtime_error((std::stringstream() << functionName << " returned value " << result << "!").str())
{}
