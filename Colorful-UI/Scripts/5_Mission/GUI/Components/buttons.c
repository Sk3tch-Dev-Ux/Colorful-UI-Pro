class CUIButtonHandler
{
    private ButtonWidget m_Button;
    private TextWidget   m_TextWidget;
    private ImageWidget  m_ImageWidget;
    private int          m_TextColor;
    private int          m_HoverColor;
    private string       m_ClickAction;
    private Class        m_TargetClass;
    private string       m_CallbackMethod;
    private string       m_ServerIP;
    private int          m_ServerPort;

    // Icon-only support
    private bool         m_IconOnly = false;
    private int          m_IconImageIndex = -1;

    void CUIButtonHandler(ButtonWidget button, TextWidget textWidget, ImageWidget imageWidget,
                          int textColor, int hoverColor, string clickAction = "", Class targetClass = null,
                          string callbackMethod = "", string serverIP = "", int serverPort = 0)
    {
        m_Button         = button;
        m_TextWidget     = textWidget;
        m_ImageWidget    = imageWidget;
        m_TextColor      = textColor;
        m_HoverColor     = hoverColor;
        m_ClickAction    = clickAction;
        m_TargetClass    = targetClass;
        m_CallbackMethod = callbackMethod;
        m_ServerIP       = serverIP;
        m_ServerPort     = serverPort;

        ApplyBaseStyles();
        RegisterEvents();
    }

    void SetIconOnly(bool isIconOnly, int imageIdx = -1)
    {
        m_IconOnly = isIconOnly;
        m_IconImageIndex = imageIdx;
        ApplyBaseStyles();
    }

    private void ApplyBaseStyles()
    {
        if (m_IconOnly)
        {
            if (m_TextWidget) m_TextWidget.Show(false);
            m_Button.SetText("");
            if (m_ImageWidget)
            {
                if (m_IconImageIndex >= 0) m_ImageWidget.SetImage(m_IconImageIndex);
                m_ImageWidget.Show(true);
                m_ImageWidget.SetColor(ARGB(255,255,255,255)); // icon-only default white
            }
            m_Button.SetColor(UIColor.Transparent());
            return;
        }

        if (!m_TextWidget && !m_ImageWidget)
        {
            m_Button.SetTextColor(m_TextColor);
            return;
        }
        if (m_TextWidget)
        {
            m_TextWidget.SetColor(m_TextColor);
        }
        else
        {
            m_Button.SetTextColor(m_TextColor);
        }
        if (m_ImageWidget)
        {
            m_ImageWidget.SetColor(m_HoverColor);
            m_ImageWidget.SetImage(1);
        }
    }

    private void ApplyHoverStyles()
    {
        if (m_IconOnly)
        {
            if (m_ImageWidget) m_ImageWidget.SetColor(m_HoverColor);
            m_Button.SetColor(UIColor.Transparent());
            return;
        }

        if (!m_TextWidget && !m_ImageWidget)
        {
            m_Button.SetColor(m_HoverColor);
            return;
        }
        if (m_TextWidget)
        {
            m_TextWidget.SetColor(m_HoverColor);
        }
        if (m_ImageWidget)
        {
            m_ImageWidget.SetColor(m_HoverColor);
        }
        m_Button.SetColor(UIColor.Transparent());
    }

    private void RegisterEvents()
    {
        auto handler = WidgetEventHandler.GetInstance();
        handler.RegisterOnMouseEnter(m_Button, this, "OnMouseEnter");
        handler.RegisterOnMouseLeave(m_Button, this, "OnMouseLeave");
        handler.RegisterOnClick(m_Button, this, "OnClick");
        handler.RegisterOnFocus(m_Button, this, "OnFocus");
        handler.RegisterOnFocusLost(m_Button, this, "OnFocusLost");
    }

    bool OnMouseEnter(Widget w, int x, int y) { ApplyHoverStyles(); return true; }
    bool OnMouseLeave(Widget w, Widget enterW, int x, int y) { ApplyBaseStyles(); return true; }
    bool OnFocus(Widget w, int x, int y) { ApplyHoverStyles(); return true; }
    bool OnFocusLost(Widget w, int x, int y) { ApplyBaseStyles(); return true; }

    bool OnClick(Widget w, int x, int y, int button)
    {
        if (m_ClickAction)
        {
            GetGame().OpenURL(m_ClickAction);
        }
        else if (m_TargetClass && m_CallbackMethod)
        {
            GetGame().GameScript.CallFunction(m_TargetClass, m_CallbackMethod, null, 0);
        }
        else if (m_ServerIP != "" && m_ServerPort > 0)
        {
            g_Game.ConnectFromServerBrowser(m_ServerIP, m_ServerPort, "");
        }
        return true;
    }
}
