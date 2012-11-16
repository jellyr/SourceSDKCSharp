#include "Stdafx.h"
#include "tier0\dbg.h"


void ConColorMsg(class Color const &,char const *,...)
{
}

void CharacterSetBuild(struct characterset_t *,char const *)
{
}

void ConMsg(char const *,...)
{
}

void Error(char const *,...)
{
}

void _AssertValidReadPtr( void* ptr, int count )
{
}

void AssertValidStringPtr(char const *,int)
{
}

void _AssertValidWritePtr(void *,int)
{
}

void _Warning(const char* pMsg, ... )
{
}

int Q_log2(int val)
{
	int answer=0;
	while (val>>=1)
		answer++;
	return answer;
}
