#pragma once

#include <stdexcept>

class FunctionReturnValueException : public std::runtime_error
{
public:
	FunctionReturnValueException(const char* functionName, const char* result);
};

template <typename T>
inline T throwIfNull(T result, const char* functionName)
{
	if (result == NULL)
	{
		throw FunctionReturnValueException(functionName, "NULL");
	}
	return result;
}

template <typename T>
inline T throwIfNotNull(T result, const char* functionName)
{
	if (result != NULL)
	{
		throw FunctionReturnValueException(functionName, "Not NULL");
	}
	return result;
}

template <typename T>
inline T throwIfFalse(T result, const char* functionName)
{
	if (!result)
	{
		throw FunctionReturnValueException(functionName, "false");
	}
	return result;
}

template <typename T>
inline T throwIfMinusOne(T result, const char* functionName)
{
	if (result == -1)
	{
		throw FunctionReturnValueException(functionName, "-1");
	}
	return result;
}
