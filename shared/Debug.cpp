#include "Stdafx.h"

typedef char tchar;


/* Various types of spew messages */
// I'm sure you're asking yourself why SPEW_ instead of DBG_ ?
// It's because DBG_ is used all over the place in windows.h
// For example, DBG_CONTINUE is defined. Feh.
enum SpewType_t
{
	SPEW_MESSAGE = 0,
	SPEW_WARNING,
	SPEW_ASSERT,
	SPEW_ERROR,
	SPEW_LOG,

	SPEW_TYPE_COUNT
};

enum SpewRetval_t
{
	SPEW_DEBUGGER = 0,
	SPEW_CONTINUE,
	SPEW_ABORT
};

void _SpewInfo(SpewType_t type, const tchar* pFile, int line)
{

}

SpewRetval_t _SpewMessage(const tchar* pMsg, ...)
{
	return SPEW_ABORT;
}

bool ShouldUseNewAssertDialog()
{
	return true;
}

bool DoNewAssertDialog(const tchar *pFile, int line, const tchar *pExpression)
{
	return true;
}

void _ExitOnFatalAssert(const tchar* pFile, int line)
{

}