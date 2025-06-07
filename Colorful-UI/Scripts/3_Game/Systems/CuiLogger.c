class CuiLogger
{
    protected static const string LOG_FILE = "$profile:cui_logger.log";

    static void InitCUILogger()
    {
        FileHandle file = OpenFile(LOG_FILE, FileMode.WRITE);
        if (file != 0)
        {
            FPrintln(file, LOG_FILE);
            FPrintln(file, Timestamp());
            CloseFile(file);
        }
    }

    static void Log(string message)
    {
        FileHandle handle = OpenFile(LOG_FILE, FileMode.APPEND);
        if (handle)
        {
            FPrintln(handle, Timestamp() + " - " + message);
            CloseFile(handle);
        }
    }

    protected static string Timestamp()
    {
        float time = GetGame().GetTime();
        int s = Math.Floor(time / 1000);
        int m = s / 60;
        int h = m / 60;
        m = m % 60;
        s = s % 60;

        return h.ToStringLen(2) + ":" + m.ToStringLen(2) + ":" + s.ToStringLen(2);
    }
}
