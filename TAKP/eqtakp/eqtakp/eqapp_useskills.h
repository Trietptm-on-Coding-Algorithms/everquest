#pragma once

bool g_useSkillsIsEnabled = true;

bool g_useSkillsSenseHeadingIsEnabled = false;
bool g_useSkillsForageIsEnabled = true;
bool g_useSkillsTauntIsEnabled = true;
bool g_useSkillsKickIsEnabled = true;
bool g_useSkillsBashIsEnabled = false;
bool g_useSkillsSlamIsEnabled = false;
bool g_useSkillsDisarmIsEnabled = true;
bool g_useSkillsBackstabIsEnabled = false;

uint32_t g_useSkillsTimer = 0;
uint32_t g_useSkillsTimerDelay = 1000;

void EQAPP_UseSkills_Toggle();
void EQAPP_UseSkills_Execute();

void EQAPP_UseSkills_Toggle()
{
    EQ_ToggleBool(g_useSkillsIsEnabled);
    EQAPP_PrintBool("Use Skills", g_useSkillsIsEnabled);
}

void EQAPP_UseSkills_Toggle_SenseHeading()
{
    EQ_ToggleBool(g_useSkillsSenseHeadingIsEnabled);
    EQAPP_PrintBool("Use Skills (SenseHeading): ", g_useSkillsSenseHeadingIsEnabled);
}

void EQAPP_UseSkills_Toggle_Forage()
{
    EQ_ToggleBool(g_useSkillsForageIsEnabled);
    EQAPP_PrintBool("Use Skills (Forage): ", g_useSkillsForageIsEnabled);
}

void EQAPP_UseSkills_Toggle_Taunt()
{
    EQ_ToggleBool(g_useSkillsTauntIsEnabled);
    EQAPP_PrintBool("Use Skills (Taunt): ", g_useSkillsTauntIsEnabled);
}

void EQAPP_UseSkills_Toggle_Kick()
{
    EQ_ToggleBool(g_useSkillsKickIsEnabled);
    EQAPP_PrintBool("Use Skills (Kick): ", g_useSkillsKickIsEnabled);

    if (g_useSkillsKickIsEnabled == true)
    {
        g_useSkillsBashIsEnabled = false;
        g_useSkillsSlamIsEnabled = false;
    }
}

void EQAPP_UseSkills_Toggle_Bash()
{
    EQ_ToggleBool(g_useSkillsBashIsEnabled);
    EQAPP_PrintBool("Use Skills (Bash): ", g_useSkillsBashIsEnabled);

    if (g_useSkillsBashIsEnabled == true)
    {
        g_useSkillsKickIsEnabled = false;
        g_useSkillsSlamIsEnabled = false;
    }
}

void EQAPP_UseSkills_Toggle_Slam()
{
    EQ_ToggleBool(g_useSkillsSlamIsEnabled);
    EQAPP_PrintBool("Use Skills (Slam): ", g_useSkillsSlamIsEnabled);

    if (g_useSkillsSlamIsEnabled == true)
    {
        g_useSkillsKickIsEnabled = false;
        g_useSkillsBashIsEnabled = false;
    }
}

void EQAPP_UseSkills_Toggle_Disarm()
{
    EQ_ToggleBool(g_useSkillsDisarmIsEnabled);
    EQAPP_PrintBool("Use Skills (Disarm): ", g_useSkillsDisarmIsEnabled);
}

void EQAPP_UseSkills_Toggle_Backstab()
{
    EQ_ToggleBool(g_useSkillsBackstabIsEnabled);
    EQAPP_PrintBool("Use Skills (Backstab): ", g_useSkillsBackstabIsEnabled);
}

void EQAPP_UseSkills_Execute()
{
    if (EQ_HasTimePassed(g_useSkillsTimer, g_useSkillsTimerDelay) == false)
    {
        return;
    }

    auto playerSpawn = EQ_GetPlayerSpawn();
    if (playerSpawn == NULL)
    {
        return;
    }

    if (playerSpawn->IsAwayFromKeyboard == 1)
    {
        if (g_useSkillsSenseHeadingIsEnabled == true)
        {
            EQ_UseSkill(EQ_SKILL_SENSE_HEADING, NULL);
        }

        if (EQ_IsAutoAttackEnabled() == false && playerSpawn->StandingState == EQ_STANDING_STATE_STANDING)
        {
            if (g_useSkillsForageIsEnabled == true)
            {
                EQ_UseSkill(EQ_SKILL_FORAGE, NULL);

                if (playerSpawn->Character->CursorItem != NULL)
                {
                    EQ_AutoInventory(playerSpawn->Character, &playerSpawn->Character->CursorItem, 0);
                }
            }
        }
    }

    if (EQ_IsAutoAttackEnabled() == true)
    {
        auto targetSpawn = EQ_GetTargetSpawn();
        if (targetSpawn != NULL && targetSpawn != playerSpawn)
        {
            float targetSpawnDistance = EQ_CalculateDistance(playerSpawn->X, playerSpawn->Y, targetSpawn->X, targetSpawn->Y);

            float targetSpawnMeleeDistance = EQ_get_melee_range((EQClass::EQPlayer*)playerSpawn, (EQClass::EQPlayer*)targetSpawn);

            if (targetSpawnDistance <= targetSpawnMeleeDistance)
            {
                if (g_useSkillsKickIsEnabled == true)
                {
                    EQ_UseSkill(EQ_SKILL_KICK, (EQClass::EQPlayer*)targetSpawn);
                }

                if (g_useSkillsBashIsEnabled == true)
                {
                    EQ_UseSkill(EQ_SKILL_BASH, (EQClass::EQPlayer*)targetSpawn);
                }

                if (g_useSkillsDisarmIsEnabled == true)
                {

                    EQ_UseSkill(EQ_SKILL_DISARM, (EQClass::EQPlayer*)targetSpawn);
                }

                if (playerSpawn->Class == EQ_CLASS_WARRIOR || playerSpawn->Class == EQ_CLASS_PALADIN || playerSpawn->Class == EQ_CLASS_SHADOWKNIGHT)
                {
                    if (g_useSkillsTauntIsEnabled == true)
                    {
                        EQ_UseSkill(EQ_SKILL_TAUNT, (EQClass::EQPlayer*)targetSpawn);
                    }

                    if (playerSpawn->Race == EQ_RACE_BARBARIAN || playerSpawn->Race == EQ_RACE_OGRE || playerSpawn->Race == EQ_RACE_TROLL)
                    {
                        if (g_useSkillsSlamIsEnabled == true)
                        {
                            EQ_UseSkill(EQ_SKILL_SLAM, (EQClass::EQPlayer*)targetSpawn);
                        }
                    }
                }

                if (playerSpawn->Class == EQ_CLASS_ROGUE)
                {
                    if (g_useSkillsBackstabIsEnabled == true)
                    {
                        EQ_UseSkill(EQ_SKILL_BACKSTAB, (EQClass::EQPlayer*)targetSpawn);
                    }
                }
            }
        }
    }
}

