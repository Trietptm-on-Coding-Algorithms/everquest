#pragma once

volatile int g_ConsoleIsLoaded = 0;

bool g_ConsolePrintIsEnabled = true;

std::stringstream g_ConsoleStringStream;
std::streambuf* g_ConsoleStreamBuffer;

void EQAPP_Console_Load();
void EQAPP_Console_Unload();
void EQAPP_Console_Print_Toggle();
void EQAPP_Console_Print();

void EQAPP_Console_Load()
{
    setvbuf(stdout, 0, _IOLBF, 4096);

    // redirect cout to stringstream
    g_ConsoleStreamBuffer = std::cout.rdbuf(g_ConsoleStringStream.rdbuf());

    g_ConsoleIsLoaded = 1;
}

void EQAPP_Console_Unload()
{
    // restore cout
    std::cout.rdbuf(g_ConsoleStreamBuffer);

    g_ConsoleIsLoaded = 0;
}

void EQAPP_Console_Print_Toggle()
{
    EQ_ToggleBool(g_ConsolePrintIsEnabled);
    EQAPP_PrintBool("Console Print", g_ConsolePrintIsEnabled);
}

void EQAPP_Console_Print()
{
    if (g_ConsolePrintIsEnabled == true)
    {
        // print redirected cout to the chat window
        for (std::string text; std::getline(g_ConsoleStringStream, text, '\n');)
        {
            std::stringstream ss;
            ss << "[" << g_EQAppNameEx << "] " << text;

            EQ_PrintTextToChat(ss.str().c_str());
        }
    }

    g_ConsoleStringStream.str(std::string());
    g_ConsoleStringStream.clear();
}
