#include "Stdafx.h"
#include "VGui.h"

CSourceSDKVgui::CSourceSDKVgui()
{
	m_pVGuiSurface = nullptr;
	m_pVGuiInput = nullptr;
	m_pVGui = nullptr;
	m_pVGuiPanel = nullptr;
	m_pVGuiLocalize = nullptr;
	m_pVGuiSchemeManager = nullptr;
	m_pVGuiSystem = nullptr;
}

bool CSourceSDKVgui::Init(CreateInterfaceFn appSystemFactory)
{
	setlocale(LC_CTYPE, "");
	setlocale(LC_TIME, "");
	setlocale(LC_COLLATE, "");
	setlocale(LC_MONETARY, "");
}

void CSourceSDKVgui::Shutdown()
{
	// Make sure anything "marked for deletion"
	//  actually gets deleted before this dll goes away
	vgui::ivgui()->RunFrame();
}



