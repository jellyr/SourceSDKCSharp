#pragma once

#include "ivguicenterprint.h"


class CSourceSDKCenterPrint : public ICenterPrint
{
public:
	void SetTextColor( int r, int g, int b, int a ) override;
	void Print( char *text ) override;
	void Print( wchar_t *text ) override;
	void ColorPrint( int r, int g, int b, int a, char *text ) override;
	void ColorPrint( int r, int g, int b, int a, wchar_t *text ) override;
	void Clear() override;
};