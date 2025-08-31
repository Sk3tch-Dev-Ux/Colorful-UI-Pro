// ============================== cuiElmnt.c ==============================
class cuiElmnt
{
    static ref array<ref CUIButtonHandler> s_Handlers = new array<ref CUIButtonHandler>();

    static void Cleanup()
    {
        for (int i = 0; i < s_Handlers.Count(); i++)
        {
            delete s_Handlers[i];
        }
        s_Handlers.Clear();
    }

    // ----------------------------- Pro Buttons -----------------------------
    static void proBtn(
        ButtonWidget button, string text, int textColor, int hoverColor,
        string clickAction = "", Class targetClass = null, string callbackMethod = "",
        string serverIP = "", int serverPort = 0)
    {
        if (!button) return;

        button.SetText(text);

        TextWidget textWidget = TextWidget.Cast(button.FindAnyWidget(button.GetName() + "_label"));
        if (textWidget)
        {
            textWidget.SetText(text);
            button.SetText("");
        }

        ImageWidget imageWidget = ImageWidget.Cast(button.FindAnyWidget(button.GetName() + "_img"));

        CUIButtonHandler handler = new CUIButtonHandler(
            button, textWidget, imageWidget,
            textColor, hoverColor, clickAction, targetClass, callbackMethod, serverIP, serverPort);

        s_Handlers.Insert(handler);
    }

    // Icon-only variant. Child image must be named "<buttonName>_img".
    static void proIconBtn(
        ButtonWidget button, int iconImageIndex, int iconColor, int hoverColor,
        string clickAction = "", Class targetClass = null, string callbackMethod = "",
        string serverIP = "", int serverPort = 0)
    {
        if (!button) return;

        button.SetText("");

        TextWidget textWidget = TextWidget.Cast(button.FindAnyWidget(button.GetName() + "_label"));
        if (textWidget) textWidget.Show(false);

        ImageWidget imageWidget = ImageWidget.Cast(button.FindAnyWidget(button.GetName() + "_img"));

        CUIButtonHandler handler = new CUIButtonHandler(
            button, textWidget, imageWidget,
            iconColor, hoverColor, clickAction, targetClass, callbackMethod, serverIP, serverPort);

        handler.SetIconOnly(true, iconImageIndex);
        s_Handlers.Insert(handler);
    }

    static void proBtnDC(ButtonWidget button, string text, int textColor, int hoverColor, string serverIP, int serverPort)
    {
        proBtn(button, text, textColor, hoverColor, "", null, "", serverIP, serverPort);
    }

    static void proBtnURL(ButtonWidget button, string text, int textColor, int hoverColor, string clickAction)
    {
        proBtn(button, text, textColor, hoverColor, clickAction, null, "", "", 0);
    }

    static void proBtnCB(ButtonWidget button, string text, int textColor, int hoverColor, Class targetClass, string callbackMethod)
    {
        proBtn(button, text, textColor, hoverColor, "", targetClass, callbackMethod, "", 0);
    }

    // ----------------------------- Pro Dialogs -----------------------------
    // Coming Soon
}
