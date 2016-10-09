#pragma once

bool g_replaceRacesIsEnabled = true;
DWORD g_replaceRacesTimer = 0;
DWORD g_replaceRacesTimerDelay = 1000;

void EQAPP_ReplaceRaces_Execute();

void EQAPP_ReplaceRaces_Execute()
{
    if (g_replaceRacesIsEnabled == false)
    {
        return;
    }

    if (EQ_HasTimePassed(g_replaceRacesTimer, g_replaceRacesTimerDelay) == false)
    {
        return;
    }

    DWORD playerSpawn = EQ_GetPlayerSpawn();

    DWORD spawn = EQ_GetFirstSpawn();
    while (spawn)
    {
        int spawnGender = EQ_ReadMemory<BYTE>(playerSpawn + EQ_OFFSET_SPAWN_INFO_GENDER);

        int spawnRace = EQ_ReadMemory<DWORD>(playerSpawn + EQ_OFFSET_SPAWN_INFO_RACE);

        if (spawnRace == EQ_RACE_INVISIBLE_MAN)
        {
            EQ_SetSpawnForm(spawn, EQ_RACE_HUMAN, spawnGender);
        }
        else if (spawnRace == EQ_RACE_SKELETON)
        {
            EQ_SetSpawnForm(spawn, EQ_RACE_SKELETON2, spawnGender);
        }

        if (spawn == playerSpawn)
        {
            if (spawnRace == EQ_RACE_CHOKADAI)
            {
                EQ_SetSpawnForm(spawn, EQ_RACE_HUMAN, spawnGender);
            }
        }

        spawn = EQ_GetNextSpawn(spawn); // next
    }
}

