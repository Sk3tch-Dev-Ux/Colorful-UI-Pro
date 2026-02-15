modded class OptionSelectorSliderSetup extends OptionSelectorBase
{
	override void ColorHighlight(Widget w)
	{
		if (!w)
			return;

		// Use Brand Color for slider on hover
		if (m_Slider)
		{
			SetFocus(m_Slider);
			m_Slider.SetColor(colorScheme.OptionSliderColors());
		}

		// Custom ColorHighlight logic (replaces super.ColorHighlight)
		int color_pnl = colorScheme.OptionBGHover();
		int color_lbl = colorScheme.OptionSelectionText();

		ButtonSetColor(w, color_pnl);
		ButtonSetTextColorRecursive(w, color_lbl);
		ButtonSetIconColor(w, colorScheme.OptionIconHover());
	}

	override void ColorNormal(Widget w)
	{
		if (!w)
			return;

		if (m_Slider)
		{
			m_Slider.SetColor(colorScheme.PrimaryText());
		}

		// Custom ColorNormal logic (replaces super.ColorNormal)
		int color_pnl = UIColor.Transparent();
		int color_lbl = colorScheme.PrimaryText();

		ButtonSetColor(w, color_pnl);
		ButtonSetTextColorRecursive(w, color_lbl);
		ButtonSetIconColor(w, colorScheme.OptionIconNormal());
	}

	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (m_ParentClass)
		{
			OnFocus(w, x, y);
			m_ParentClass.OnFocus(m_Root.GetParent(), -1, m_SelectorType);

			#ifdef PLATFORM_WINDOWS
			m_ParentClass.OnMouseEnter(m_Root.GetParent().GetParent(), x, y);
			// Use Brand Color for slider on enter
			m_Slider.SetColor(colorScheme.OptionSliderColors());
			#endif
		}
		
		ColorHighlight(w); // Ensure our overridden ColorHighlight is called
		return true;
	}

	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (m_ParentClass)
		{
			#ifdef PLATFORM_WINDOWS
			m_ParentClass.OnMouseLeave(m_Root.GetParent().GetParent(), enterW, x, y);
			m_Slider.SetColor(colorScheme.PrimaryText());
			#endif

			OnFocusLost(w, x, y);
			SetFocus(null);
		}
		
		ColorNormal(w); // Ensure our overridden ColorNormal is called
		return true;
	}
	
	// Helper for recursive coloring
	void ButtonSetTextColorRecursive(Widget w, int color)
	{
		if (!w)
			return;

		Widget child = w.GetChildren();
		while (child)
		{
			if (child.IsInherited(TextWidget))
			{
				child.SetColor(color);
			}
			else
			{
				ButtonSetTextColorRecursive(child, color);
			}
			
			child = child.GetSibling();
		}
	}
}
