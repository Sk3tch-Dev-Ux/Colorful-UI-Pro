// // This class customizes the color and focus behavior of the slider options in the UI.
// modded class OptionSelectorSliderSetup extends OptionSelectorBase
// {
// 	// Called when the mouse hovers over the slider (Highlight State)
// 	override void ColorHighlight(Widget w)
// 	{
// 		// Safety check: exit if the widget is null
// 		if (!w)
// 			return;

// 		// If the slider widget exists
// 		if (m_Slider)
// 		{
// 			// Set focus to the slider widget
// 			SetFocus(m_Slider);

// 			// Change the slider color to the primary text color (this is currently how you're styling the hover)
// 			m_Slider.SetColor(colorScheme.OptionBGHover());
			
// 		}

// 		// Also call the base class highlight method to apply the normal highlight logic
// 		super.ColorHighlight(w);
// 	}

// 	// Called when the slider should return to its normal (non-hovered) color
// 	override void ColorNormal(Widget w)
// 	{
// 		// Safety check: exit if the widget is null
// 		if (!w)
// 			return;

// 		// If the slider widget exists
// 		if (m_Slider)
// 		{
// 			// Set the slider color back to the scheme's OptionSliderColors (the base/normal slider color)
// 			m_Slider.SetColor(colorScheme.OptionSliderColors());
// 		}

// 		// Also call the base class normal color method to apply the default reset logic
// 		super.ColorNormal(w);
// 	}

// 	// Called when the mouse enters (hovers over) the slider widget
// 	override bool OnMouseEnter(Widget w, int x, int y)
// 	{
// 		// If a parent class is defined to handle additional events
// 		if (m_ParentClass)
// 		{
// 			// Trigger the focus logic
// 			OnFocus(w, x, y);

// 			// Notify the parent that this option is now focused
// 			m_ParentClass.OnFocus(m_Root.GetParent(), -1, m_SelectorType);

// 			#ifdef PLATFORM_WINDOWS
// 			// On Windows, also call the parent's OnMouseEnter for full event propagation
// 			m_ParentClass.OnMouseEnter(m_Root.GetParent().GetParent(), x, y);

// 			// Set the slider color to the scheme's normal slider color when the mouse enters
// 			m_Slider.SetColor(colorScheme.OptionSliderColors());
// 			#endif
// 		}

// 		// Always return true to confirm the event was handled
// 		return true;
// 	}

// 	// Called when the mouse leaves the slider widget
// 	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
// 	{
// 		// If a parent class is defined to handle additional events
// 		if (m_ParentClass)
// 		{
// 			#ifdef PLATFORM_WINDOWS
// 			// On Windows, call the parent's OnMouseLeave for full event propagation
// 			m_ParentClass.OnMouseLeave(m_Root.GetParent().GetParent(), enterW, x, y);

// 			// Set the slider color back to the primary text color when the mouse leaves
// 			m_Slider.SetColor(colorScheme.PrimaryText());
// 			#endif

// 			// Trigger the focus lost logic
// 			OnFocusLost(w, x, y);

// 			// Clear focus from this widget
// 			SetFocus(null);
// 		}

// 		// Always return true to confirm the event was handled
// 		return true;
// 	}
// }
