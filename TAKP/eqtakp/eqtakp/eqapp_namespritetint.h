#pragma once

bool g_NameSpriteTintIsEnabled = true;

static int g_NameSpriteTintFlash = 0;

void EQAPP_NameSpriteTint_Toggle();
bool EQAPP_NameSpriteTint_HandleEvent_CDisplay__SetNameSpriteTint(void* this_ptr, class EQPlayer* player);

void EQAPP_NameSpriteTint_Toggle()
{
    EQ_ToggleBool(g_NameSpriteTintIsEnabled);
    EQAPP_PrintBool("Name Sprite Tint", g_NameSpriteTintIsEnabled);
}

bool EQAPP_NameSpriteTint_HandleEvent_CDisplay__SetNameSpriteTint(void* this_ptr, class EQPlayer* player)
{
    if (EQ_IsInGame() == false)
    {
        return false;
    }

    EQ::Spawn_ptr spawn = (EQ::Spawn_ptr)player;
    if (spawn == NULL)
    {
        return false;
    }

    if (spawn->Actor == NULL)
    {
        return false;
    }

    if (spawn->Actor->ModelBoneHeadPoint == NULL)
    {
        return false;
    }

    if (spawn->Actor->ModelBoneHeadPoint->StringSprite == NULL)
    {
        return false;
    }

    if (spawn->Actor->ModelBoneHeadPoint->StringSprite->Type != EQ_STRINGSPRITE_TYPE_1)
    {
        return false;
    }

    if (spawn->Actor->ModelBoneHeadPoint->StringSprite->ID == 0xFFFFFFFF)
    {
        return false;
    }

    EQ::ColorRGB color;

    auto playerSpawn = EQ_GetPlayerSpawn();
    if (playerSpawn == NULL)
    {
        return false;
    }

    if ((spawn == playerSpawn) || (spawn->PetOwnerSpawnID == playerSpawn->SpawnID))
    {
        color.R = 255;
        color.G = 128;
        color.B = 0;
        spawn->Actor->ModelBoneHeadPoint->StringSprite->Color = color;
    }

    if (spawn->Type == EQ_SPAWN_TYPE_NPC)
    {
        if (spawn->Class == EQ_CLASS_BANKER)
        {
            color.R = 0;
            color.G = 255;
            color.B = 64;
            spawn->Actor->ModelBoneHeadPoint->StringSprite->Color = color;
        }
        else if (spawn->Class == EQ_CLASS_MERCHANT)
        {
            color.R = 255;
            color.G = 255;
            color.B = 0;
            spawn->Actor->ModelBoneHeadPoint->StringSprite->Color = color;
        }
        else if (spawn->Class >= EQ_CLASS_GUILDMASTER_BEGIN && spawn->Class <= EQ_CLASS_GUILDMASTER_END)
        {
            color.R = 128;
            color.G = 64;
            color.B = 255;
            spawn->Actor->ModelBoneHeadPoint->StringSprite->Color = color;
        }
    }
    else if (spawn->Type == EQ_SPAWN_TYPE_NPC_CORPSE)
    {
        color.R = 128;
        color.G = 128;
        color.B = 128;
        spawn->Actor->ModelBoneHeadPoint->StringSprite->Color = color;
    }
    else if (spawn->Type == EQ_SPAWN_TYPE_PLAYER_CORPSE)
    {
        color.R = 64;
        color.G = 64;
        color.B = 64;
        spawn->Actor->ModelBoneHeadPoint->StringSprite->Color = color;
    }

    auto targetSpawn = EQ_GetTargetSpawn();
    if (targetSpawn == NULL)
    {
        return false;
    }

    if (spawn == targetSpawn)
    {
        uint8_t r = spawn->Actor->ModelBoneHeadPoint->StringSprite->Color.R;
        uint8_t g = spawn->Actor->ModelBoneHeadPoint->StringSprite->Color.G;
        uint8_t b = spawn->Actor->ModelBoneHeadPoint->StringSprite->Color.B;

        uint8_t rr = (int)(g_NameSpriteTintFlash * ((255 - r) * 0.1f)); // / 10
        uint8_t gg = (int)(g_NameSpriteTintFlash * ((255 - g) * 0.1f)); // / 10
        uint8_t bb = (int)(g_NameSpriteTintFlash * ((255 - b) * 0.1f)); // / 10

        uint8_t rrr = 0;

        if (255 - rr >= 0)
        {
            rrr = 255 - rr;
        }

        uint8_t ggg = 255 - gg;

        if (255 - gg < 0)
        {
            ggg = 0;
        }

        uint8_t bbb = 255 - bb;

        if (255 - bb < 0)
        {
            bbb = 0;
        }

        spawn->Actor->ModelBoneHeadPoint->StringSprite->Color.R = rrr;
        spawn->Actor->ModelBoneHeadPoint->StringSprite->Color.G = ggg;
        spawn->Actor->ModelBoneHeadPoint->StringSprite->Color.B = bbb;

        if (g_NameSpriteTintFlash >= 10)
        {
            g_NameSpriteTintFlash = 0;
        }
        else
        {
            g_NameSpriteTintFlash++;
        }
    }

    return true;
}
