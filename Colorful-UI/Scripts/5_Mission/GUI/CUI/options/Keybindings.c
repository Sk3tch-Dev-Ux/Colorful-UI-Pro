modded class KeybindingsMenu extends UIScriptedMenu
{
	private Widget m_TopShader;
	private Widget m_BottomShader;
	private Widget m_MenuDivider;
    private TextWidget m_ApplyBtn_Label;
		
	override Widget Init()
	{
		Input input = GetGame().GetInput();
		layoutRoot			= GetGame().GetWorkspace().CreateWidgets("Colorful-UI/GUI/layouts/options/cui.keybinding_menu.layout", null);
		
		m_Apply     = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ApplyBtn"));
		m_Back      = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BackBtn"));
		m_Undo      = ButtonWidget.Cast(layoutRoot.FindAnyWidget("UndoBtn"));
		m_Defaults  = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ResetBtn"));
		m_HardReset = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ResetAllBtn"));

		cuiElmnt.proBtnCB(m_Apply,     "Apply",      colorScheme.PrimaryText(), colorScheme.ButtonHover(), this, "Apply");
		cuiElmnt.proBtnCB(m_Back,      "Back",       colorScheme.PrimaryText(), colorScheme.ButtonHover(), this, "Back");
		cuiElmnt.proBtnCB(m_Undo,      "Undo",       colorScheme.PrimaryText(), colorScheme.ButtonHover(), this, "Reset");
		cuiElmnt.proBtnCB(m_Defaults,  "Defaults",   colorScheme.PrimaryText(), colorScheme.ButtonHover(), this, "SetToDefaults");
		cuiElmnt.proBtnCB(m_HardReset, "Hard Reset", colorScheme.PrimaryText(), colorScheme.ButtonHover(), this, "HardReset");

		m_TopShader    = layoutRoot.FindAnyWidget( "TopShader" );
		m_BottomShader = layoutRoot.FindAnyWidget( "BottomShader" );
		m_MenuDivider  = layoutRoot.FindAnyWidget( "MenuDivider" );

		m_TopShader.SetColor(colorScheme.TopShader());
		m_BottomShader.SetColor(colorScheme.BottomShader());
		m_MenuDivider.SetColor(colorScheme.Separator());
		
		layoutRoot.FindAnyWidget("Tabber").GetScript(m_Tabber);		
		
		InitInputSortingMap();
		CreateTabs();
		CreateGroupContainer();
		
		InitPresets(-1, layoutRoot.FindAnyWidget("group_header"), input);
		m_Tabber.m_OnTabSwitch.Insert(UpdateTabContent);
		m_Tabber.SelectTabControl(0);
		m_Tabber.SelectTabPanel(0);
		g_Game.SetKeyboardHandle(this);
		m_Tabber.RefreshTab(true);
		
		return layoutRoot;
	}
	
    static void OnApplyPressed()
    {
        // Logic for applying changes
        Print("button clicked");
    }
}
