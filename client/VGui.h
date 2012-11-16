#pragma once


#include <vgui/IScheme.h>
#include <vgui/ISurface.h>
#include <vgui/ISystem.h>
#include <vgui/IVGui.h>
#include <vgui/IPanel.h>


class CSourceSDKVgui
{
public:
	CSourceSDKVgui();

	void Init();


	vgui::IInput *input()
	{
		return m_pVGuiInput;
	}

	vgui::ISchemeManager *scheme()
	{
		return m_pVGuiSchemeManager;
	}

	vgui::ISurface *surface()
	{
		return m_pVGuiSurface;
	}
 
	vgui::ISystem *system()
	{
		return m_pVGuiSystem;
	}

	vgui::IVGui *ivgui()
	{
		return m_pVGui;
	}

	vgui::IPanel *ipanel()
	{
		return m_pVGuiPanel;
	}

private:
	vgui::ISurface *m_pVGuiSurface;
	vgui::IInput *m_pVGuiInput;
	vgui::IVGui *m_pVGui;
	vgui::IPanel *m_pVGuiPanel;
	vgui::ILocalize *m_pVGuiLocalize;
	vgui::ISchemeManager *m_pVGuiSchemeManager;
	vgui::ISystem *m_pVGuiSystem;
};