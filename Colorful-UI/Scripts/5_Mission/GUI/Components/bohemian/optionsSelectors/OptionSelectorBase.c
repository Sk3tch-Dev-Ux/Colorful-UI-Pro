// modded class OptionSelectorBase extends ScriptedWidgetEventHandler
// {	
// 	override bool OnMouseEnter(Widget w, int x, int y)
// 	{
// 		if (!IsFocusable(w))
// 			return true;

// 		if (m_ParentClass)
// 		{
// 			m_ParentClass.OnFocus(m_Root.GetParent(), -1, m_SelectorType);
// 		}

// 		UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();

// 		if (menu && menu.IsInherited(CharacterCreationMenu))
// 		{
// 			menu.OnFocus(m_Root.GetParent(), -1, m_SelectorType);
// 			menu.OnMouseEnter(m_Root.GetParent().GetParent(), x, y);
// 		}

// 		ColorHighlightConsole(w);
// 		if (m_ParentClass)
// 		{
// 			m_ParentClass.OnFocus(m_Root.GetParent(), -1, m_SelectorType);
// 		}

// 		return true;
// 	}

// 	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
// 	{
// 		if (m_ParentClass)
// 		{
// 			m_ParentClass.OnFocus(null, x, y);
// 		}

// 		UIScriptedMenu menu = GetGame().GetUIManager().GetMenu();

// 		if (menu && menu.IsInherited(CharacterCreationMenu))
// 		{
// 			menu.OnFocus(null, x, y);
// 			menu.OnMouseLeave(m_Root.GetParent().GetParent(), enterW, x, y);
// 		}

// 		ColorNormalConsole(w);
// 		if (m_ParentClass)
// 		{
// 			m_ParentClass.OnFocusLost(w, x, y);
// 		}

// 		return true;
// 	}

// 	override bool OnFocus(Widget w, int x, int y)
// 	{
// 		if (IsFocusable(w))
// 		{
// 			ColorHighlightConsole(w);
// 			if (m_ParentClass)
// 			{
// 				m_ParentClass.OnFocus(m_Root.GetParent(), -1, m_SelectorType);
// 			}
// 			return true;
// 		}
// 		return false;
// 	}

// 	override bool OnFocusLost(Widget w, int x, int y)
// 	{
// 		ColorNormalConsole(w);
// 		if (m_ParentClass)
// 		{
// 			m_ParentClass.OnFocusLost(w, x, y);
// 		}
// 		return true;
// 	}

// 	void Focus()
// 	{
// 		SetFocus(m_Parent);
// 	}

// 	void Enable()
// 	{
// 		m_Enabled = true;
// 		m_Parent.ClearFlags(WidgetFlags.IGNOREPOINTER);
// 		ColorNormal(m_Parent);
// 	}

// 	void Disable()
// 	{
// 		m_Enabled = false;
// 		m_Parent.SetFlags(WidgetFlags.IGNOREPOINTER);
// 		ColorDisabled(m_Parent);
// 	}

// 	void ColorHighlight(Widget w)
// 	{
// 		if (!w)
// 			return;

// 		ButtonSetColor(w, colorScheme.OptionBGHover());
// 	}

// 	void ColorNormal(Widget w)
// 	{
// 		if (!w)
// 			return;

// 		int color_pnl = UIColor.Transparent();
// 		int color_lbl = ARGB(255, 255, 255, 255); // White text

// 		ButtonSetColor(w, color_pnl);

// 		Widget title_label = w.FindAnyWidget(w.GetName() + "_label");
// 		Widget option_label = w.FindAnyWidget("option_label");

// 		if (title_label)
// 		{
// 			title_label.SetColor(color_lbl);
// 		}

// 		if (option_label)
// 		{
// 			option_label.SetColor(color_lbl);
// 		}
// 	}

// 	void ColorDisabled(Widget w)
// 	{
// 		if (!w)
// 			return;

// 		int color_pnl = UIColor.Transparent();
// 		int color_lbl = colorScheme.DisabledText();

// 		ButtonSetColor(w, color_pnl);

// 		Widget title_label = w.FindAnyWidget(w.GetName() + "_label");
// 		Widget option_label = w.FindAnyWidget("option_label");

// 		if (title_label)
// 		{
// 			title_label.SetColor(color_lbl);
// 		}

// 		if (option_label)
// 		{
// 			option_label.SetColor(color_lbl);
// 		}		
// 	}

// 	void ButtonSetColor(Widget w, int color)
// 	{
// 		Widget option = w.FindAnyWidget(w.GetName() + "_image");

// 		if (option)
// 		{
// 			option.SetColor(color);
// 		}
// 	}

// 	void ColorHighlightConsole(Widget w)
// 	{
// 		if (!w)
// 			return;

// 		int color_pnl = colorScheme.OptionBGHover(); // Background hover color
// 		int color_lbl = ARGB(255, 255, 255, 0); // Yellow text

// 		ButtonSetColorConsole(w, color_pnl);
// 		ButtonSetAlphaAnimConsole(null);
// 		ButtonSetTextColorConsole(w, color_lbl);
// 	}

// 	void ColorNormalConsole(Widget w)
// 	{
// 		if (!w)
// 			return;

// 		int color_pnl = UIColor.Transparent();
// 		int color_lbl = ARGB(255, 255, 255, 255); // White text

// 		ButtonSetColorConsole(w, color_pnl);
// 		ButtonSetAlphaAnimConsole(null);
// 		ButtonSetTextColorConsole(w, color_lbl);
// 	}

// 	void ColorDisabledConsole(Widget w)
// 	{
// 		if (!w)
// 			return;

// 		int color_pnl = UIColor.Transparent();
// 		int color_lbl = colorScheme.DisabledText();

// 		ButtonSetColorConsole(w, color_pnl);
// 		ButtonSetAlphaAnimConsole(null);
// 		ButtonSetTextColorConsole(w, color_lbl);
// 	}

// 	void ButtonSetColorConsole(Widget w, int color)
// 	{
// 		w.SetColor(color);
// 	}

// 	void ButtonSetAlphaAnimConsole(Widget w)
// 	{
// 		if (!w)
// 			return;

// 		Widget panel = w.FindAnyWidget(w.GetName() + "_panel");

// 		if (panel)
// 		{
// 			//m_Root.SetWidgetAnimAlpha(panel);
// 		}
// 	}

// 	void ButtonSetTextColorConsole(Widget w, int color)
// 	{
// 		if (!w)
// 			return;

// 		TextWidget label = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_label"));
// 		TextWidget text = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_text"));
// 		TextWidget text2 = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_text_1"));

// 		if (label)
// 		{
// 			label.SetColor(color);
// 		}

// 		if (text)
// 		{
// 			text.SetColor(color);
// 		}

// 		if (text2)
// 		{
// 			text2.SetColor(color);
// 		}
// 	}
// }
