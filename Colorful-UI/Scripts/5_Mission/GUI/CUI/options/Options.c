modded class OptionsMenu extends UIScriptedMenu
{
	private Widget m_Separator
	private	Widget m_shader
	private Widget m_TopShader;
	private Widget m_BottomShader;
	private Widget m_MenuDivider;
		
	override Widget Init()
	{
		m_Options		= new GameOptions();
		
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets("Colorful-ui/gui/layouts/options/cui.options_menu.layout", null);
		
		layoutRoot.FindAnyWidget("Tabber").GetScript(m_Tabber);
		
		m_Details		= layoutRoot.FindAnyWidget("settings_details");
		m_Version		= TextWidget.Cast(layoutRoot.FindAnyWidget("version"));
		
		m_GameTab		= new OptionsMenuGame(layoutRoot.FindAnyWidget("Tab_0"), m_Details, m_Options, this);
		m_SoundsTab		= new OptionsMenuSounds(layoutRoot.FindAnyWidget("Tab_1"), m_Details, m_Options, this);
		
		m_VideoTab		= new OptionsMenuVideo(layoutRoot.FindAnyWidget("Tab_2"), m_Details, m_Options, this);
		m_ControlsTab	= new OptionsMenuControls(layoutRoot.FindAnyWidget("Tab_3"), m_Details, m_Options, this);

		m_Apply			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("apply"));
		m_Back			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("back"));
		m_Reset			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("reset"));
		m_Defaults		= ButtonWidget.Cast(layoutRoot.FindAnyWidget("defaults"));
		
		m_TopShader 			    = layoutRoot.FindAnyWidget( "TopShader" );
		m_BottomShader 			    = layoutRoot.FindAnyWidget( "BottomShader" );
		m_MenuDivider				= layoutRoot.FindAnyWidget( "MenuDivider" );
		

		m_TopShader.SetColor(colorScheme.TopShader());
		m_BottomShader.SetColor(colorScheme.BottomShader());
		m_MenuDivider.SetColor(colorScheme.Separator());


		m_ModalLock = false;
		m_CanApplyOrReset = false;
		
		string version;
		m_Version.SetText( version );
		
		SetFocus( layoutRoot );
		ToggleFocus();
			
		OnChanged();
		Class.CastTo(m_shader, layoutRoot.FindAnyWidget("Colorful_Shader"));
		// m_shader.SetColor(colorScheme.ShaderColor());

		m_Separator 	= layoutRoot.FindAnyWidget( "colorful_separator" );
		// m_Separator.SetColor(colorScheme.SeparatorColor());
		
		return layoutRoot;
	}

	override void Back()
	{
		if (!g_Game.GetUIManager().IsDialogVisible() && !g_Game.GetUIManager().IsModalVisible())
		{
			if (IsAnyTabChanged())
			{
				EnterScriptedMenu( COLORFUL_CONFIGURE );
				//g_Game.GetUIManager().ShowDialog("#main_menu_configure", "#main_menu_configure_desc", 1337, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
			}
			else
			{
				m_Options.Revert();
				GetGame().EndOptionsVideo();
				GetGame().GetUIManager().Back();
			}
		}
	}
	
}
