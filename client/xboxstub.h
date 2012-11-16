#pragma once

#include "tier0\platform.h"
typedef unsigned long       DWORD_t;

typedef struct _XUSER_DATA
{
	BYTE                                type;

	union
	{
		int                            nData;     // XUSER_DATA_TYPE_INT32
		int64                        i64Data;   // XUSER_DATA_TYPE_INT64
		double                          dblData;   // XUSER_DATA_TYPE_DOUBLE
		struct                                     // XUSER_DATA_TYPE_UNICODE
		{
			uint                       cbData;    // Includes null-terminator
			char *                      pwszData;
		} string;
		float                           fData;     // XUSER_DATA_TYPE_FLOAT
		struct                                     // XUSER_DATA_TYPE_BINARY
		{
			uint                       cbData;
			char *                       pbData;
		} binary;
	};
} XUSER_DATA, *PXUSER_DATA;

typedef struct _XUSER_PROPERTY
{
	DWORD_t                               dwPropertyId;
	XUSER_DATA                          value;
} XUSER_PROPERTY, *PXUSER_PROPERTY;

typedef struct _XUSER_CONTEXT
{
	DWORD_t                               dwContextId;
	DWORD_t                               dwValue;
} XUSER_CONTEXT, *PXUSER_CONTEXT;