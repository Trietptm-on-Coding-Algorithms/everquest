#pragma once

namespace EQApp
{
    typedef struct _NetworkStats
    {
        uint8_t ErrorCode;
        uint16_t SpawnID;
        float SpawnDistance;
        char SpawnName[30];
        uint16_t SpawnHPCurrent;
        uint16_t SpawnHPMax;
        uint16_t SpawnManaCurrent;
        uint16_t SpawnManaMax;
        uint8_t SpawnHasPet;
        uint16_t SpawnPetID;
        char SpawnPetName[30];
        uint16_t SpawnPetHPCurrent;
        uint16_t SpawnPetHPMax;
        uint16_t BuffSpellID[EQ_NUM_BUFFS];
        uint16_t BuffTicks[EQ_NUM_BUFFS];
    } NetworkStats, *NetworkStats_ptr;
}

bool g_NetworkStatsIsEnabled = true;

std::vector<std::string> g_NetworkStatsPlayerList;
std::vector<EQApp::NetworkStats> g_NetworkStatsList;

float g_NetworkStatsDrawBarSpawnDistanceMax = 200.0f;

float g_NetworkStatsDrawBarWidth = 64.0f;
float g_NetworkStatsDrawBarHeight = 8.0f;

uint32_t g_NetworkStatsDrawBarBackgroundColorARGB = 0x80000000;
uint32_t g_NetworkStatsDrawBarBorderColorARGB     = 0xFF000000;
uint32_t g_NetworkStatsDrawBarHPColorARGB         = 0x80FF0000;
uint32_t g_NetworkStatsDrawBarManaColorARGB       = 0x800080FF;

uint32_t g_NetworkStatsDrawTextX = 8;
uint32_t g_NetworkStatsDrawTextY = 64;

uint32_t g_NetworkStatsDrawTextBuffsX = 100;
uint32_t g_NetworkStatsDrawTextBuffsY = 300;

uint32_t g_NetworkStatsTimer = 0;
uint32_t g_NetworkStatsTimerDelay = 1000;

void EQAPP_NetworkStats_Load();
void EQAPP_NetworkStats_DrawBar(EQApp::NetworkStats& networkStats, EQ::Spawn_ptr spawn, bool spawnIsPet);
void EQAPP_NetworkStats_DrawBars();
void EQAPP_NetworkStats_DrawText();
void EQAPP_NetworkStats_Execute();
void EQAPP_NetworkStats_Write();
EQApp::NetworkStats EQAPP_NetworkStats_Read(std::string spawnName);

void EQAPP_NetworkStats_Toggle()
{
    EQ_ToggleBool(g_NetworkStatsIsEnabled);
    EQAPP_PrintBool("Network Stats", g_NetworkStatsIsEnabled);
}

void EQAPP_NetworkStats_Load()
{
    std::cout << "Loading Network Stats players..." << std::endl;

    g_NetworkStatsPlayerList.clear();
    g_NetworkStatsPlayerList.reserve(100);

    EQAPP_ReadFileToList("networkstats.txt", g_NetworkStatsPlayerList);
}

void EQAPP_NetworkStats_DrawBar(EQApp::NetworkStats& networkStats, EQ::Spawn_ptr spawn, bool spawnIsPet)
{
    uint32_t HPCurrent = 0;
    uint32_t HPMax     = 0;

    if (spawnIsPet == false)
    {
        HPCurrent = networkStats.SpawnHPCurrent;
        HPMax     = networkStats.SpawnHPMax;
    }
    else
    {
        HPCurrent = networkStats.SpawnPetHPCurrent;
        HPMax     = networkStats.SpawnPetHPMax;
    }

    float HPPercent = 0;

    if (HPCurrent > 0 && HPMax > 0)
    {
        HPPercent = (float)HPCurrent / (float)HPMax;
    }

    uint32_t manaCurrent = 0;
    uint32_t manaMax     = 0;

    if (spawnIsPet == false)
    {
        manaCurrent = networkStats.SpawnManaCurrent;
        manaMax     = networkStats.SpawnManaMax;
    }
    else
    {
        manaCurrent = 0;
        manaMax     = 0;
    }

    float manaPercent = 0.0f;

    if (manaCurrent > 0 && manaMax > 0)
    {
        manaPercent = (float)manaCurrent / (float)manaMax;
    }

    bool bDrawMana = true;
    if (manaPercent == 0.0f || spawnIsPet == true)
    {
        bDrawMana = false;
    }

    float spawnZOffset = 0.0f;

    if (spawn->StandingState == EQ_STANDING_STATE_STANDING)
    {
        spawnZOffset = spawn->CameraHeightOffset + 1.0f;
    }
    else
    {
        spawnZOffset = (spawn->CameraHeightOffset * 0.5f) + 1.0f;
    }

    EQ::Location spawnBarLocation =
    {
        spawn->Y,
        spawn->X,
        spawn->Z + spawnZOffset
    };

    float screenX = 0;
    float screenY = 0;
    if (EQ_WorldSpaceToScreenSpaceFloat(spawnBarLocation, screenX, screenY) == false)
    {
        return;
    }

    float halfWidth = g_NetworkStatsDrawBarWidth * 0.5f;

    screenX = screenX - halfWidth;

    float HPWidth = g_NetworkStatsDrawBarWidth * HPPercent;
    float manaWidth = g_NetworkStatsDrawBarWidth * manaPercent;

    if (bDrawMana == true)
    {
        float halfHeight = g_NetworkStatsDrawBarHeight * 0.5f;

        // transparent background
        EQ_DrawRectangle(screenX, screenY, g_NetworkStatsDrawBarWidth, g_NetworkStatsDrawBarHeight, g_NetworkStatsDrawBarBackgroundColorARGB, true);

        // red hp
        EQ_DrawRectangle(screenX, screenY, HPWidth, halfHeight, g_NetworkStatsDrawBarHPColorARGB, true);

        // black hp border
        EQ_DrawRectangle(screenX, screenY, g_NetworkStatsDrawBarWidth, halfHeight, g_NetworkStatsDrawBarBorderColorARGB, false);

        // blue mana
        EQ_DrawRectangle(screenX, screenY + halfHeight, manaWidth, halfHeight, g_NetworkStatsDrawBarManaColorARGB, true);

        // black mana border
        EQ_DrawRectangle(screenX, screenY + halfHeight, g_NetworkStatsDrawBarWidth, halfHeight, g_NetworkStatsDrawBarBorderColorARGB, false);
    }
    else
    {
        // transparent background
        EQ_DrawRectangle(screenX, screenY, g_NetworkStatsDrawBarWidth, g_NetworkStatsDrawBarHeight, g_NetworkStatsDrawBarBackgroundColorARGB, true);

        // red hp
        EQ_DrawRectangle(screenX, screenY, HPWidth, g_NetworkStatsDrawBarHeight, g_NetworkStatsDrawBarHPColorARGB, true);

        // black hp border
        EQ_DrawRectangle(screenX, screenY, g_NetworkStatsDrawBarWidth, g_NetworkStatsDrawBarHeight, g_NetworkStatsDrawBarBorderColorARGB, false);
    }
}

void EQAPP_NetworkStats_DrawBars()
{
    if (EQ_IsInGame() == false)
    {
        return;
    }

    for (auto& networkStats : g_NetworkStatsList)
    {
        if (networkStats.SpawnDistance > g_NetworkStatsDrawBarSpawnDistanceMax)
        {
            continue;
        }

        auto spawn = EQ_GetSpawnByID(networkStats.SpawnID);
        if (spawn == NULL)
        {
            continue;
        }

        EQAPP_NetworkStats_DrawBar(networkStats, spawn, false);

        if (networkStats.SpawnHasPet == 1)
        {
            auto spawnPet = EQ_GetSpawnByID(networkStats.SpawnPetID);
            if (spawnPet != NULL)
            {
                EQAPP_NetworkStats_DrawBar(networkStats, spawnPet, true);
            }
        }
    }
}

void EQAPP_NetworkStats_DrawText()
{
    if (EQ_IsInGame() == false)
    {
        return;
    }

    auto playerSpawn = EQ_GetPlayerSpawn();
    if (playerSpawn == NULL)
    {
        return;
    }

    std::stringstream drawText;

    for (auto& networkStats : g_NetworkStatsList)
    {
        ////if (networkStats.SpawnID == playerSpawn->SpawnID)
        ////{
            ////continue;
        ////}

        drawText << "Name: " << networkStats.SpawnName << "\n";
        drawText << "HP: " << networkStats.SpawnHPCurrent << " / " << networkStats.SpawnHPMax << "\n";

        if (networkStats.SpawnManaMax > 0)
        {
            drawText << "Mana: " << networkStats.SpawnManaCurrent << " / " << networkStats.SpawnManaMax << "\n";
        }

        if (networkStats.SpawnHasPet == 1)
        {
            drawText << "\n";
            drawText << "Pet Name: " << networkStats.SpawnPetName << "\n";
            drawText << "Pet HP: " << networkStats.SpawnPetHPCurrent << " / " << networkStats.SpawnPetHPMax << "\n";
        }

        drawText << "\n";
    }

    EQ_DrawText(drawText.str().c_str(), g_NetworkStatsDrawTextX, g_NetworkStatsDrawTextY, EQ_COLOR_ARGB_WHITE);

    uint32_t drawTextBuffsX = g_NetworkStatsDrawTextBuffsX;
    uint32_t drawTextBuffsY = g_NetworkStatsDrawTextBuffsY;

    for (auto& networkStats : g_NetworkStatsList)
    {
        if (networkStats.SpawnID == playerSpawn->SpawnID)
        {
            continue;
        }

        bool hasBuffs = false;

        for (size_t i = 0; i < EQ_NUM_BUFFS; i++)
        {
            if (networkStats.BuffSpellID[i] > 0 && networkStats.BuffSpellID[i] < EQ_NUM_SPELLS)
            {
                hasBuffs = true;
                break;
            }
        }

        if (hasBuffs == false)
        {
            continue;
        }

        std::stringstream drawTextBuffs;

        drawTextBuffs << networkStats.SpawnName << "\n";
        
        for (size_t i = 0; i < EQ_NUM_BUFFS; i++)
        {
            if (networkStats.BuffSpellID[i] > 0 && networkStats.BuffSpellID[i] < EQ_NUM_SPELLS)
            {
                auto spell = EQ_GetSpellByID(networkStats.BuffSpellID[i]);
                if (spell == NULL)
                {
                    continue;
                }

                drawTextBuffs << i + 1 << ": " << spell->Name << "\n";
            }
        }

        drawTextBuffs << "\n";

        EQ_DrawTextEx(drawTextBuffs.str().c_str(), drawTextBuffsX, drawTextBuffsY, EQ_COLOR_ARGB_WHITE, EQ_ADDRESS_POINTER_FONT_ARIAL12);

        drawTextBuffsX += 150;
    }
}

void EQAPP_NetworkStats_Execute()
{
    if (EQ_IsInGame() == false)
    {
        return;
    }

    if (EQ_HasTimePassed(g_NetworkStatsTimer, g_NetworkStatsTimerDelay) == false)
    {
        return;
    }

    auto playerSpawn = EQ_GetPlayerSpawn();
    if (playerSpawn == NULL)
    {
        return;
    }

    EQAPP_NetworkStats_Write();

    g_NetworkStatsList.clear();
    g_NetworkStatsList.reserve(10);

    for (auto& spawnName : g_NetworkStatsPlayerList)
    {
        auto spawn = EQ_GetSpawnByName(spawnName);
        if (spawn == NULL)
        {
            continue;
        }

        EQApp::NetworkStats networkStats = EQAPP_NetworkStats_Read(spawnName);

        float spawnDistance = EQ_CalculateDistance(spawn->X, spawn->Y, playerSpawn->X, playerSpawn->Y);
        networkStats.SpawnDistance = spawnDistance;

        if (networkStats.ErrorCode == 0)
        {
            g_NetworkStatsList.push_back(networkStats);
        }
    }
}

void EQAPP_NetworkStats_Write()
{
    if (EQ_IsInGame() == false)
    {
        return;
    }

    auto playerSpawn = EQ_GetPlayerSpawn();
    if (playerSpawn == NULL)
    {
        return;
    }

    if (playerSpawn->Type != EQ_SPAWN_TYPE_PLAYER)
    {
        return;
    }

    std::string spawnName = EQ_GetSpawnName(playerSpawn);
    if (spawnName.size() == 0)
    {
        return;
    }

    std::stringstream filePath;
    filePath << g_EQAppName << "/networkstats/" << spawnName << ".txt";

    std::string filePathStr = filePath.str();

    std::fstream file;
    file.open(filePathStr.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
    if (file.is_open() == false)
    {
        std::stringstream ss;
        ss << "failed to open file: " << filePathStr;

        EQAPP_PrintErrorMessage(__FUNCTION__, ss.str());
        return;
    }

    EQApp::NetworkStats networkStats;
    networkStats.ErrorCode   = 0;
    networkStats.SpawnDistance = 0.0f;
    networkStats.SpawnHasPet = 0;

    networkStats.SpawnID = playerSpawn->SpawnID;

    strncpy_s(networkStats.SpawnName, sizeof(networkStats.SpawnName), spawnName.c_str(), sizeof(networkStats.SpawnName));

    networkStats.SpawnHPCurrent   = playerSpawn->HPCurrent;
    networkStats.SpawnHPMax       = playerSpawn->HPMax;
    networkStats.SpawnManaCurrent = playerSpawn->Character->Mana;
    networkStats.SpawnManaMax     = EQ_CLASS_POINTER_PlayerCharacter->Max_Mana();

    auto playerPetSpawn = EQ_GetPlayerPetSpawn();
    if (playerPetSpawn != NULL)
    {
        std::string spawnPetName = EQ_GetSpawnName(playerPetSpawn);
        if (spawnPetName.size() != 0)
        {
            networkStats.SpawnHasPet = 1;

            networkStats.SpawnPetID = playerPetSpawn->SpawnID;

            strncpy_s(networkStats.SpawnPetName, sizeof(networkStats.SpawnPetName), spawnPetName.c_str(), sizeof(networkStats.SpawnPetName));

            networkStats.SpawnPetHPCurrent = playerPetSpawn->HPCurrent;
            networkStats.SpawnPetHPMax     = playerPetSpawn->HPMax;
        }
    }

    for (size_t i = 0; i < EQ_NUM_BUFFS; i++)
    {
        networkStats.BuffSpellID[i] = playerSpawn->Character->Buff[i].SpellID;
        networkStats.BuffTicks[i] = playerSpawn->Character->Buff[i].Ticks;
    }

    file.seekg(0, std::fstream::beg);
    file.write((char*)&networkStats, sizeof(networkStats));
    file.close();
}

EQApp::NetworkStats EQAPP_NetworkStats_Read(std::string spawnName)
{
    EQApp::NetworkStats networkStats;
    networkStats.ErrorCode   = 1;
    networkStats.SpawnDistance = 0.0f;
    networkStats.SpawnHasPet = 0;

    for (size_t i = 0; i < EQ_NUM_BUFFS; i++)
    {
        networkStats.BuffSpellID[i] = 0;
        networkStats.BuffTicks[i] = 0;
    }

    if (spawnName.size() == 0)
    {
        return networkStats;
    }

    std::stringstream filePath;
    filePath << g_EQAppName << "/networkstats/" << spawnName << ".txt";

    std::string filePathStr = filePath.str();

    std::fstream file;
    file.open(filePathStr.c_str(), std::fstream::in | std::fstream::binary);
    if (file.is_open() == false)
    {
        return networkStats;
    }

    file.read((char*)&networkStats, sizeof(networkStats));
    file.close();

    return networkStats;
}
