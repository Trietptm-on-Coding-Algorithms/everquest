#pragma once

bool g_alwaysHotbuttonIsEnabled = false;
unsigned int g_alwaysHotbuttonNumber = 1;
DWORD g_alwaysHotbuttonTimer = 0;
DWORD g_alwaysHotbuttonTimerDelay = 1000;
DWORD g_alwaysHotbuttonTimerDelayInSeconds = 1;

bool g_alwaysHotbuttonSitStandAtManaIsEnabled = false;
DWORD g_alwaysHotbuttonSitAtManaValue = 100;
DWORD g_alwaysHotbuttonStandAtManaValue = 1000;
bool g_alwaysHotbuttonIsSitting = false;

void EQAPP_AlwaysHotbutton_Execute();
void EQAPP_AlwaysHotbutton_Print();
void EQAPP_AlwaysHotbutton_Set(unsigned buttonNumber, DWORD timerDelayInSeconds);

void EQAPP_AlwaysHotbutton_SitStandAtMana_Toggle();
void EQAPP_AlwaysHotbutton_SitStandAtMana_Set(bool bEnabled);
void EQAPP_AlwaysHotbutton_SitStandAtMana_Print();

void EQAPP_AlwaysHotbutton_Execute()
{
    if (g_alwaysHotbuttonIsEnabled == false)
    {
        return;
    }

    if (EQ_HasTimePassed(g_alwaysHotbuttonTimer, g_alwaysHotbuttonTimerDelay) == false)
    {
        return;
    }

    DWORD playerSpawn = EQ_GetPlayerSpawn();
    if (playerSpawn == NULL)
    {
        return;
    }

    int standingState = EQ_ReadMemory<BYTE>(playerSpawn + EQ_OFFSET_SPAWN_INFO_STANDING_STATE);
    if (standingState == EQ_STANDING_STATE_STANDING)
    {
        g_alwaysHotbuttonIsSitting = false;
    }

    if (g_alwaysHotbuttonSitStandAtManaIsEnabled == true)
    {
        DWORD mana = EQ_ReadMemory<DWORD>(playerSpawn + EQ_OFFSET_SPAWN_INFO_MANA);

        if (mana <= g_alwaysHotbuttonSitAtManaValue && mana < g_alwaysHotbuttonStandAtManaValue && g_alwaysHotbuttonIsSitting == false)
        {
            if (g_debugIsEnabled == true)
            {
                std::cout << "AHB Sitting" << std::endl;
            }

            ((EQPlayer*)playerSpawn)->ChangePosition(EQ_STANDING_STATE_SITTING);

            g_alwaysHotbuttonIsSitting = true;
        }

        if (mana >= g_alwaysHotbuttonStandAtManaValue && mana > g_alwaysHotbuttonSitAtManaValue)
        {
            if (g_debugIsEnabled == true)
            {
                std::cout << "AHB Standing" << std::endl;
            }

            ((EQPlayer*)playerSpawn)->ChangePosition(EQ_STANDING_STATE_STANDING);

            g_alwaysHotbuttonIsSitting = false;
        }
    }

    if (g_alwaysHotbuttonSitStandAtManaIsEnabled == true && g_alwaysHotbuttonIsSitting == true)
    {
        return;
    }

    EQ_DoHotButton(g_alwaysHotbuttonNumber);
}

void EQAPP_AlwaysHotbutton_Print()
{
    std::cout << "Always Hotbutton: " << g_alwaysHotbuttonNumber << " (" << g_alwaysHotbuttonTimerDelayInSeconds << " second(s))" << std::endl;
}

void EQAPP_AlwaysHotbutton_Set(unsigned buttonNumber, DWORD timerDelayInSeconds)
{
    if (buttonNumber < EQ_HOTBUTTON_NUMBER_MIN || buttonNumber > EQ_HOTBUTTON_NUMBER_MAX)
    {
        std::stringstream ss;
        ss << "invalid hotbutton number specified: " << buttonNumber;

        EQAPP_PrintErrorMessage(__FUNCTION__, ss.str());
        return;
    }

    g_alwaysHotbuttonNumber = buttonNumber;

    g_alwaysHotbuttonTimerDelay = (DWORD)(timerDelayInSeconds * 1000); // convert seconds to milliseconds

    g_alwaysHotbuttonTimerDelayInSeconds = timerDelayInSeconds;
}

void EQAPP_AlwaysHotbutton_SitStandAtMana_Toggle()
{
    EQ_ToggleBool(g_alwaysHotbuttonSitStandAtManaIsEnabled);

    g_alwaysHotbuttonIsSitting = false;
}

void EQAPP_AlwaysHotbutton_SitStandAtMana_Set(bool bEnabled)
{
    g_alwaysHotbuttonSitStandAtManaIsEnabled = bEnabled;

    g_alwaysHotbuttonIsSitting = false;
}

void EQAPP_AlwaysHotbutton_SitStandAtMana_Print()
{
    std::cout << "Always Hotbutton Sit At Mana Value: " << g_alwaysHotbuttonSitAtManaValue << std::endl;
    std::cout << "Always Hotbutton Stand At Mana Value: " << g_alwaysHotbuttonStandAtManaValue << std::endl;
}
