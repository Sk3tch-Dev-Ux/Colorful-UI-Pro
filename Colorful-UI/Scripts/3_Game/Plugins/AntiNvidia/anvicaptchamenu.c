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

  void ANVICaptchaMenu() {}

  void ~ANVICaptchaMenu() {}

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
    string p1 = "Colorful-UI/GUI/layouts/plugins/AntiNvidia/";
    string p2 = "dialog_anvi_captcha.layout";
    layoutRoot = GetGame().GetWorkspace().CreateWidgets(p1 + p2);

    Widget w;
    w = layoutRoot.FindAnyWidget("DigitLeft");
    m_CorrectNumberDigit_0 = ImageWidget.Cast(w);
    w = layoutRoot.FindAnyWidget("DigitRight");
    m_CorrectNumberDigit_1 = ImageWidget.Cast(w);
    w = layoutRoot.FindAnyWidget("CaptchaAttempts");
    m_CaptchaAttemptsText = TextWidget.Cast(w);
    w = layoutRoot.FindAnyWidget("AnswerInput");
    m_TextAnswerInput = EditBoxWidget.Cast(w);
    w = layoutRoot.FindAnyWidget("AnswerSubmitButton");
    m_AnswerSubmit = ButtonWidget.Cast(w);
    w = layoutRoot.FindAnyWidget("QuitWarning");
    m_QuitWarning = TextWidget.Cast(w);
    w = layoutRoot.FindAnyWidget("QuitButton");
    m_QuitButton = ButtonWidget.Cast(w);
    w = layoutRoot.FindAnyWidget("ConfirmQuitButton");
    m_QuitConfirmButton = ButtonWidget.Cast(w);
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
      Leave();
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
    DayZGame game = DayZGame.Cast(GetGame());
    if (game && game.m_CaptchaCompleted)
      return;
    bool isCorrect = CheckAnswer(answer);
    if (isCorrect) {
      HandleCorrectAnswer();
    } else {
      HandleIncorrectAnswer();
    }
  }

  private void HandleCorrectAnswer() {
    DayZGame game = DayZGame.Cast(GetGame());
    if (game) {
      game.m_CaptchaCompleted = true;
      m_TextAnswerInput.SetColor(COLOR_GREEN);
      m_TextAnswerInput.SetFlags(WidgetFlags.NOFOCUS);
      m_AnswerSubmit.SetColor(COLOR_GREEN);
      m_AnswerSubmit.SetText("JOINING..");
      m_AnswerSubmit.SetFlags(WidgetFlags.DISABLED);
      m_QuitButton.SetFlags(WidgetFlags.DISABLED);
      ScriptCallQueue queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
      if (queue)
        queue.CallLater(game.Connect, 10, false);
    }
  }

  private void HandleIncorrectAnswer() {
    DayZGame game = DayZGame.Cast(GetGame());
    if (game) {
      SetAttempts(game.m_CaptchaAttempts - 1);
      if (game.m_CaptchaAttempts > 0) {
        Reset();
      } else {
        Leave();
      }
    }
  }

  private void Leave() { GetGame().RequestExit(0); }

  void Reset() {
    m_TextAnswerInput.SetText("");
    m_CorrectAnswer = DrawNumber(100);
    SetCorrectAnswer(m_CorrectAnswer);
  }

  private void SetCorrectAnswer(int number) {
    string numberString = number.ToStringLen(2);
    string prefix = "Colorful-UI/GUI/textures/plugins/AntiNvidia/numbers/";
    m_CorrectNumberDigit_0.LoadImageFile(0, prefix + numberString[0] + ".edds");
    m_CorrectNumberDigit_1.LoadImageFile(0, prefix + numberString[1] + ".edds");
  }

  void SetAttempts(int attempts) {
    DayZGame game = DayZGame.Cast(GetGame());
    if (game)
      game.m_CaptchaAttempts = attempts;
    m_CaptchaAttemptsText.SetText(string.Format("attempts left: %1", attempts));
  }

  private bool CheckAnswer(int answer) { return m_CorrectAnswer == answer; }

  private int DrawNumber(int range = 100) { return Math.RandomInt(0, 100); }
}