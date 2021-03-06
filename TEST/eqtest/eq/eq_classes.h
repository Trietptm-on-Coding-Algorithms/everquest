#pragma once

#include "eq.h"
#include "eq_constants.h"
#include "eq_macros.h"
#include "eq_messages.h"

namespace EQClass
{
    class CEverQuest;
    class CDisplay;

    class EQPlayerManager;
    class EQPlayer;

    class EQSwitch;

    class CXWndManager;
    class CXWnd;

    class CBazaarWnd;
    class CBazaarConfirmationWnd;
    class CBazaarSearchWnd;
    class CTaskSelectWnd;

    // EQGraphicsDX9.dll
    class CCamera;
    class CRender;
} // namespace EQClass

/* CEverQuest */

class EQClass::CEverQuest
{
public:
    void CEverQuest::InterpretCmd(class EQPlayer* player, const char* text);
    void CEverQuest::dsp_chat(const char* text, int textColor, bool one_1, bool one_2, bool zero_1);
    void CEverQuest::StartCasting(EQMessage::CEverQuest__StartCasting_ptr message);
    void CEverQuest::LMouseUp(int x, int y);
    void CEverQuest::RMouseUp(int x, int y);
};

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CEverQuest::InterpretCmd(class EQPlayer* player, const char* text), EQ_ADDRESS_FUNCTION_CEverQuest__InterpretCmd);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CEverQuest__InterpretCmd)(void* this_ptr, class EQPlayer* player, const char* text);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CEverQuest::dsp_chat(const char* text, int textColor, bool one_1, bool one_2, bool zero_1), EQ_ADDRESS_FUNCTION_CEverQuest__dsp_chat);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CEverQuest__dsp_chat)(void* this_ptr, const char* text, int textColor, bool one_1, bool one_2, bool zero_1);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CEverQuest::StartCasting(EQMessage::CEverQuest__StartCasting_ptr message), EQ_ADDRESS_FUNCTION_CEverQuest__StartCasting);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CEverQuest__StartCasting)(void* this_ptr, EQMessage::CEverQuest__StartCasting_ptr message);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CEverQuest::LMouseUp(int x, int y), EQ_ADDRESS_FUNCTION_CEverQuest__LMouseUp);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CEverQuest::RMouseUp(int x, int y), EQ_ADDRESS_FUNCTION_CEverQuest__RMouseUp);

EQClass::CEverQuest** EQ_CLASS_POINTER_CEverQuest_pptr;
EQClass::CEverQuest* EQ_CLASS_POINTER_CEverQuest;

/* CDisplay */

class EQClass::CDisplay
{
public:
    static int __cdecl CDisplay::WriteTextHD2(const char* text, int x, int y, signed int color);
    uint32_t CDisplay::CreatePlayerActor(uint32_t spawn, int a2, int a3, int a4, int a5, int a6);
    void CDisplay::DeleteActor(uint32_t cactor);
};

EQ_MACRO_FUNCTION_FunctionAtAddress(int __cdecl EQClass::CDisplay::WriteTextHD2(const char* text, int x, int y, signed int color), EQ_ADDRESS_FUNCTION_CDisplay__WriteTextHD2);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CDisplay__WriteTextHD2)(void* this_ptr, const char* text, int x, int y, signed int color);

EQ_MACRO_FUNCTION_FunctionAtAddress(uint32_t EQClass::CDisplay::CreatePlayerActor(uint32_t spawn, int a2, int a3, int a4, int a5, int a6), EQ_ADDRESS_FUNCTION_CDisplay__CreatePlayerActor);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CDisplay__CreatePlayerActor)(void* this_ptr, uint32_t spawn, int a2, int a3, int a4, int a5, int a6);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CDisplay::DeleteActor(uint32_t cactor), EQ_ADDRESS_FUNCTION_CDisplay__DeleteActor);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CDisplay__DeleteActor)(void* this_ptr, uint32_t cactor);

EQClass::CDisplay** EQ_CLASS_POINTER_CDisplay_pptr;
EQClass::CDisplay* EQ_CLASS_POINTER_CDisplay;

/* EQPlayerManager */

class EQClass::EQPlayerManager
{
public:
    uint32_t* EQPlayerManager::GetSpawnByID(uint32_t spawnID);
    uint32_t* EQPlayerManager::GetSpawnByName(const char* spawnName);
};

EQ_MACRO_FUNCTION_FunctionAtAddress(uint32_t* EQClass::EQPlayerManager::GetSpawnByID(uint32_t spawnID), EQ_ADDRESS_FUNCTION_EQPlayerManager__GetSpawnByID);
typedef int (__thiscall* EQ_FUNCTION_TYPE_EQPlayerManager__GetSpawnByID)(void* this_ptr, uint32_t spawnID);

EQ_MACRO_FUNCTION_FunctionAtAddress(uint32_t* EQClass::EQPlayerManager::GetSpawnByName(const char* spawnName), EQ_ADDRESS_FUNCTION_EQPlayerManager__GetSpawnByName);
typedef int (__thiscall* EQ_FUNCTION_TYPE_EQPlayerManager__GetSpawnByName)(void* this_ptr, const char* spawnName);

EQClass::EQPlayerManager** EQ_CLASS_POINTER_EQPlayerManager_pptr;
EQClass::EQPlayerManager* EQ_CLASS_POINTER_EQPlayerManager;

/* EQPlayer */

class EQClass::EQPlayer
{
public:
    void EQPlayer::FollowPlayerAI();
    void EQPlayer::ChangeHeight(float height, float a2, float a3, int a4);
    bool EQPlayer::UpdateItemSlot(uint8_t updateItemSlot, const char* itemDefinition, bool b1, bool serverSide, bool b3);
    bool EQPlayer::IsTargetable();
};

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::EQPlayer::FollowPlayerAI(), EQ_ADDRESS_FUNCTION_EQPlayer__FollowPlayerAI);
typedef int (__thiscall* EQ_FUNCTION_TYPE_EQPlayer__FollowPlayerAI)(void* this_ptr);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::EQPlayer::ChangeHeight(float height, float a2, float a3, int a4), EQ_ADDRESS_FUNCTION_EQPlayer__ChangeHeight);
typedef int (__thiscall* EQ_FUNCTION_TYPE_EQPlayer__ChangeHeight)(void* this_ptr, float height, float a2, float a3, int a4);

EQ_MACRO_FUNCTION_FunctionAtAddress(bool EQClass::EQPlayer::UpdateItemSlot(uint8_t updateItemSlot, const char* itemDefinition, bool b1, bool serverSide, bool b3), EQ_ADDRESS_FUNCTION_EQPlayer__UpdateItemSlot);
typedef int (__thiscall* EQ_FUNCTION_TYPE_EQPlayer__UpdateItemSlot)(void* this_ptr, uint8_t updateItemSlot, const char* itemDefinition, bool b1, bool serverSide, bool b3);

EQ_MACRO_FUNCTION_FunctionAtAddress(bool EQClass::EQPlayer::IsTargetable(), EQ_ADDRESS_FUNCTION_EQPlayer__IsTargetable);

/* EQSwitch */

class EQClass::EQSwitch
{
public:
    void EQSwitch::UseSwitch(uint32_t spawnID, uint32_t keyID, uint32_t pickSkill, const void* hitLocation = 0);
    void EQSwitch::ChangeState(uint8_t state, int zero1, int zero2);
};

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::EQSwitch::UseSwitch(uint32_t spawnID, uint32_t keyID, uint32_t pickSkill, const void* hitLocation), EQ_ADDRESS_FUNCTION_EQSwitch__UseSwitch);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::EQSwitch::ChangeState(uint8_t state, int zero1, int zero2), EQ_ADDRESS_FUNCTION_EQSwitch__ChangeState);


/* CXWndManager */

class EQClass::CXWndManager
{
public:
    int CXWndManager::DrawWindows();
};

EQ_MACRO_FUNCTION_FunctionAtAddress(int EQClass::CXWndManager::DrawWindows(), EQ_ADDRESS_FUNCTION_CXWndManager__DrawWindows);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CXWndManager__DrawWindows)(void* this_ptr);

EQClass::CXWndManager** EQ_CLASS_POINTER_CXWndManager_pptr;
EQClass::CXWndManager* EQ_CLASS_POINTER_CXWndManager;

/* CXWnd */

class EQClass::CXWnd
{
public:
    int CXWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown);
    void CXWnd::Activate();
    void CXWnd::Deactivate();
    void CXWnd::BringToTop(bool bRecurse = true);
    bool CXWnd::IsActive();
    bool CXWnd::IsReallyVisible(); // is open
};

#define EQ_VFTABLE_INDEX_CXWnd__WndNotification    0x88
#define EQ_VFTABLE_INDEX_CXWnd__Activate           0x90 // show window
#define EQ_VFTABLE_INDEX_CXWnd__Deactivate         0x94 // hide window

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(int EQClass::CXWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown), EQ_VFTABLE_INDEX_CXWnd__WndNotification);

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(void EQClass::CXWnd::Activate(), EQ_VFTABLE_INDEX_CXWnd__Activate);

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(void EQClass::CXWnd::Deactivate(), EQ_VFTABLE_INDEX_CXWnd__Deactivate);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CXWnd::BringToTop(bool bRecurse), EQ_ADDRESS_FUNCTION_CXWnd__BringToTop);

EQ_MACRO_FUNCTION_FunctionAtAddress(bool EQClass::CXWnd::IsActive(), EQ_ADDRESS_FUNCTION_CXWnd__IsActive);

EQ_MACRO_FUNCTION_FunctionAtAddress(bool EQClass::CXWnd::IsReallyVisible(), EQ_ADDRESS_FUNCTION_CXWnd__IsReallyVisible);

/* CBazaarWnd */

class EQClass::CBazaarWnd
{
public:
    int CBazaarWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown);
};

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(int EQClass::CBazaarWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown), EQ_VFTABLE_INDEX_CXWnd__WndNotification);

EQClass::CBazaarWnd** EQ_CLASS_POINTER_CBazaarWnd_pptr;
EQClass::CBazaarWnd* EQ_CLASS_POINTER_CBazaarWnd;

/* CBazaarConfirmationWnd */

class EQClass::CBazaarConfirmationWnd
{
public:
    int CBazaarConfirmationWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown);
};

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(int EQClass::CBazaarConfirmationWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown), EQ_VFTABLE_INDEX_CXWnd__WndNotification);

EQClass::CBazaarConfirmationWnd** EQ_CLASS_POINTER_CBazaarConfirmationWnd_pptr;
EQClass::CBazaarConfirmationWnd* EQ_CLASS_POINTER_CBazaarConfirmationWnd;

/* CBazaarSearchWnd */

class EQClass::CBazaarSearchWnd
{
public:
    int CBazaarSearchWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown);
    void CBazaarSearchWnd::AddItemToList(char* itemName, uint32_t itemPrice, char* traderName, int a4, int a5, int a6, int a7, int a8, void* a9, int a10, void* a11);
    void CBazaarSearchWnd::doQuery();
    bool CBazaarSearchWnd::BuyItem(int quantity);
};

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(int EQClass::CBazaarSearchWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown), EQ_VFTABLE_INDEX_CXWnd__WndNotification);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CBazaarSearchWnd::AddItemToList(char* itemName, uint32_t itemPrice, char* traderName, int a4, int a5, int a6, int a7, int a8, void* a9, int a10, void* a11), EQ_ADDRESS_FUNCTION_CBazaarSearchWnd__AddItemToList);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CBazaarSearchWnd__AddItemToList)(void* this_ptr, char* itemName, uint32_t itemPrice, char* traderName, int a4, int a5, int a6, int a7, int a8, void* a9, int a10, void* a11);

EQ_MACRO_FUNCTION_FunctionAtAddress(void EQClass::CBazaarSearchWnd::doQuery(), EQ_ADDRESS_FUNCTION_CBazaarSearchWnd__doQuery);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CBazaarSearchWnd__doQuery)(void* this_ptr);

EQ_MACRO_FUNCTION_FunctionAtAddress(bool EQClass::CBazaarSearchWnd::BuyItem(int quantity), EQ_ADDRESS_FUNCTION_CBazaarSearchWnd__BuyItem);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CBazaarSearchWnd__BuyItem)(void* this_ptr, int quantity);

EQClass::CBazaarSearchWnd** EQ_CLASS_POINTER_CBazaarSearchWnd_pptr;
EQClass::CBazaarSearchWnd* EQ_CLASS_POINTER_CBazaarSearchWnd;

/* CTaskSelectWnd */

class EQClass::CTaskSelectWnd
{
public:
    int CTaskSelectWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown);
};

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(int EQClass::CTaskSelectWnd::WndNotification(uint32_t cxwndAddress, uint32_t cxwndMessage, void* unknown), EQ_VFTABLE_INDEX_CXWnd__WndNotification);

EQClass::CTaskSelectWnd** EQ_CLASS_POINTER_CTaskSelectWnd_pptr;
EQClass::CTaskSelectWnd* EQ_CLASS_POINTER_CTaskSelectWnd;

/* CCamera */

class EQClass::CCamera
{
public:
    int CCamera::SetCameraLocation(EQ::Location& location, bool canSetLocation);
    bool CCamera::WorldSpaceToScreenSpace(EQ::Location& location, float& screenX, float& screenY);
};

#define EQ_VFTABLE_INDEX_CCamera__SetCameraLocation          0x38
#define EQ_VFTABLE_INDEX_CCamera__WorldSpaceToScreenSpace    0x74

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(int EQClass::CCamera::SetCameraLocation(EQ::Location& location, bool canSetLocation), EQ_VFTABLE_INDEX_CCamera__SetCameraLocation);
typedef int (__thiscall* EQ_FUNCTION_TYPE_CCamera__SetCameraLocation)(void* this_ptr, EQ::Location& location, bool canSetLocation);

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(bool EQClass::CCamera::WorldSpaceToScreenSpace(EQ::Location& location, float& screenX, float& screenY), EQ_VFTABLE_INDEX_CCamera__WorldSpaceToScreenSpace);

// calculated at run time
EQClass::CCamera** EQ_CLASS_POINTER_CCamera_pptr;
EQClass::CCamera* EQ_CLASS_POINTER_CCamera;

/* CRender */

class EQClass::CRender
{
public:
    bool CRender::DrawLine(EQ::Point& pointBegin, EQ::Point& pointEnd, uint32_t colorARGB);
    bool CRender::DrawWrappedText(uint32_t fontStyle, const char* text, EQ::CXRect& cxrect1, EQ::CXRect& cxrect2, uint32_t colorARGB, uint16_t flags, int startX);
    bool CRender::DrawColoredRectangle(EQ::Rectangle& rectangle, uint32_t colorARGB);
    void CRender::TakeScreenshot(const char* filename);
};

#define EQ_VFTABLE_INDEX_CRender__ResetDevice             0x64    // "ResetDevice() failed!"
#define EQ_VFTABLE_INDEX_CRender__DrawLine                0x88
#define EQ_VFTABLE_INDEX_CRender__DrawWrappedText         0x94
#define EQ_VFTABLE_INDEX_CRender__DrawColoredRectangle    0xA0
#define EQ_VFTABLE_INDEX_CRender__TakeScreenshot          0xC4

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(bool EQClass::CRender::DrawLine(EQ::Point& pointBegin, EQ::Point& pointEnd, uint32_t colorARGB), EQ_VFTABLE_INDEX_CRender__DrawLine);

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(bool EQClass::CRender::DrawWrappedText(uint32_t fontStyle, const char* text, EQ::CXRect& cxrect1, EQ::CXRect& cxrect2, uint32_t colorARGB, uint16_t flags, int startX), EQ_VFTABLE_INDEX_CRender__DrawWrappedText);

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(bool EQClass::CRender::DrawColoredRectangle(EQ::Rectangle& rectangle, uint32_t colorARGB), EQ_VFTABLE_INDEX_CRender__DrawColoredRectangle);

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(void EQClass::CRender::TakeScreenshot(const char* filename), EQ_VFTABLE_INDEX_CRender__TakeScreenshot);

EQClass::CRender** EQ_CLASS_POINTER_CRender_pptr;
EQClass::CRender* EQ_CLASS_POINTER_CRender;

/**************************************************/

class CCollisionCallbackForActors1
{
public:
    uint32_t CCollisionCallbackForActors1::Call_0x20();
    uint32_t CCollisionCallbackForActors1::Call_0x30();
};

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(uint32_t CCollisionCallbackForActors1::Call_0x20(), 0x20);
EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(uint32_t CCollisionCallbackForActors1::Call_0x30(), 0x30);

class CCollisionCallbackForActors2
{
public:
    uint32_t CCollisionCallbackForActors2::Call_0x0C();
};

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(uint32_t CCollisionCallbackForActors2::Call_0x0C(), 0x0C);

class CCollisionCallbackForActors3
{
public:
    uint32_t CCollisionCallbackForActors3::Call_0x44();
};

EQ_MACRO_FUNCTION_FunctionAtVirtualAddress(uint32_t CCollisionCallbackForActors3::Call_0x44(), 0x44);
