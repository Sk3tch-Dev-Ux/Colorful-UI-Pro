class ANVICaptchaMenu extends UIScriptedMenu {
  private int m_CorrectAnswer;
  protected ImageWidget m_CorrectNumberDigit_0;
  protected ImageWidget m_CorrectNumberDigit_1;
  protected TextWidget m_CaptchaAttemptsText;
  protected EditBoxWidget m_TextAnswerInput;
  protected ButtonWidget m_AnswerSubmit;
  protected TextWidget m_QuitWarning;
  protected ButtonWidget m_QuitButton;
  protected ButtonWidget m_QuitConfirmButton;

  void ANVICaptchaMenu() { g_Game.SetKeyboardHandle(this); }

  void ~ANVICaptchaMenu() { g_Game.SetKeyboardHandle(NULL); }

  override void OnShow() {
    super.OnShow();

    PPEffects.SetBlurMenu(1);
    GetGame().GetInput().ChangeGameFocus(1);
    SetFocus(layoutRoot);
  }

  override void OnHide() {
    super.OnHide();

    PPEffects.SetBlurMenu(0);
    GetGame().GetInput().ResetGameFocus();
  }

  override Widget Init() {
    layoutRoot = GetGame().GetWorkspace().CreateWidgets(
        "Colorful-UI/GUI/layouts/plugins/AntiNvidia/"
        "dialog_anvi_captcha.layout");

    m_CorrectNumberDigit_0 =
        ImageWidget.Cast(layoutRoot.FindAnyWidget("DigitLeft"));
    m_CorrectNumberDigit_1 =
        ImageWidget.Cast(layoutRoot.FindAnyWidget("DigitRight"));
    m_CaptchaAttemptsText =
        TextWidget.Cast(layoutRoot.FindAnyWidget("CaptchaAttempts"));
    m_TextAnswerInput =
        EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AnswerInput"));
    m_AnswerSubmit =
        ButtonWidget.Cast(layoutRoot.FindAnyWidget("AnswerSubmitButton"));

    m_QuitWarning = TextWidget.Cast(layoutRoot.FindAnyWidget("QuitWarning"));
    m_QuitButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("QuitButton"));
    m_QuitConfirmButton =
        ButtonWidget.Cast(layoutRoot.FindAnyWidget("ConfirmQuitButton"));

    return layoutRoot;
  }

  override bool OnClick(Widget w, int x, int y, int button) {
    super.OnClick(w, x, y, button);

    if (w != m_QuitButton) {
      m_QuitConfirmButton.Show(false);
      m_QuitWarning.Show(false);
    }

    switch (w) {
    case m_QuitButton: {
      m_QuitConfirmButton.Show(true);
      m_QuitWarning.Show(true);
      return true;
    }
    case m_QuitConfirmButton: {
      Leave("User clicked Confirm Quit");
      return true;
    }
    case m_AnswerSubmit: {
      string answer = m_TextAnswerInput.GetText();
      if (answer != string.Empty) {
        HandleAnswer(answer.ToInt());
      }
      return true;
    }
    }

    return false;
  }

  override bool OnChange(Widget w, int x, int y, bool finished) {
    super.OnChange(w, x, y, finished);

    if (w == m_TextAnswerInput) {
      string fieldText = m_TextAnswerInput.GetText();
      if (fieldText.Length() > 2) {
        m_TextAnswerInput.SetText(fieldText.Substring(0, 2));
      }
      return true;
    }
    return false;
  }

  private void HandleAnswer(int answer) {
    if (g_Game.m_CaptchaCompleted)
      return;

    bool isCorrect = CheckAnswer(answer);

    if (isCorrect) {
      HandleCorrectAnswer();
    } else {
      HandleIncorrectAnswer();
    }
  }

  private void HandleCorrectAnswer() {
    g_Game.m_CaptchaCompleted = true;

    m_TextAnswerInput.SetColor(COLOR_GREEN);
    m_TextAnswerInput.SetFlags(WidgetFlags.NOFOCUS);
    m_AnswerSubmit.SetColor(COLOR_GREEN);
    m_AnswerSubmit.SetText("JOINING..");
    m_AnswerSubmit.SetFlags(WidgetFlags.DISABLED);
    m_QuitButton.SetFlags(WidgetFlags.DISABLED);

    DayZGame game = DayZGame.Cast(GetGame());
    if (game) {
      GetGame()
          .GetCallQueue(CALL_CATEGORY_SYSTEM)
          .CallLater(game.Connect, 10, false);
    }
  }

  private void HandleIncorrectAnswer() {
    SetAttempts(g_Game.m_CaptchaAttempts - 1);
    if (g_Game.m_CaptchaAttempts > 0) {
      Reset();
    } else {
      Leave("User failed all captcha attempts");
    }
  }

  private void Leave(string reason = "Unknown") { g_Game.RequestExit(0); }

  void Reset() {
    m_TextAnswerInput.SetText("");
    m_CorrectAnswer = DrawNumber();

    SetCorrectAnswer(m_CorrectAnswer);
  }

  private void SetCorrectAnswer(int number) {
    string numberString = number.ToStringLen(2);
    m_CorrectNumberDigit_0.LoadImageFile(
        0, "Colorful-UI/GUI/textures/plugins/AntiNvidia/numbers/" +
               numberString[0] + ".edds");
    m_CorrectNumberDigit_1.LoadImageFile(
        0, "Colorful-UI/GUI/textures/plugins/AntiNvidia/numbers/" +
               numberString[1] + ".edds");
  }

  void SetAttempts(int attempts) {
    g_Game.m_CaptchaAttempts = attempts;
    m_CaptchaAttemptsText.SetText(string.Format("attempts left: %1", attempts));
  }

  private bool CheckAnswer(int answer) { return m_CorrectAnswer == answer; }

  private int DrawNumber(int range = 100) { return Math.RandomInt(0, 100); }
}