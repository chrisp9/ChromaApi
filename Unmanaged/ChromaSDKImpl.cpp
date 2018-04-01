//! \example ChromaSDKImpl.cpp

#include "stdafx.h"
#include "ChromaSDKImpl.h"

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

using namespace ChromaSDK;
using namespace ChromaSDK::Keyboard;
using namespace ChromaSDK::Keypad;
using namespace ChromaSDK::Mouse;
using namespace ChromaSDK::Mousepad;
using namespace ChromaSDK::Headset;

typedef RZRESULT (*INIT)(void);
typedef RZRESULT (*UNINIT)(void);
typedef RZRESULT (*CREATEEFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEHEADSETEFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEMOUSEPADEFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEMOUSEEFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEKEYPADEFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*SETEFFECT)(RZEFFECTID EffectId);
typedef RZRESULT (*DELETEEFFECT)(RZEFFECTID EffectId);
typedef RZRESULT (*REGISTEREVENTNOTIFICATION)(HWND hWnd);
typedef RZRESULT (*UNREGISTEREVENTNOTIFICATION)(void);
typedef RZRESULT (*QUERYDEVICE)(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

INIT Init = NULL;
UNINIT UnInit = NULL;
CREATEEFFECT CreateEffect = NULL;
CREATEKEYBOARDEFFECT CreateKeyboardEffect = NULL;
CREATEMOUSEEFFECT CreateMouseEffect = NULL;
CREATEHEADSETEFFECT CreateHeadsetEffect = NULL;
CREATEMOUSEPADEFFECT CreateMousepadEffect = NULL;
CREATEKEYPADEFFECT CreateKeypadEffect = NULL;
SETEFFECT SetEffect = NULL;
DELETEEFFECT DeleteEffect = NULL;
QUERYDEVICE QueryDevice = NULL;

DWORD WINAPI Thread_LoadingAnimationOnKeyboard(LPVOID lpParameter)
{
    RZEFFECTID Frame0 = GUID_NULL;
    RZEFFECTID Frame1 = GUID_NULL;
    RZEFFECTID Frame2 = GUID_NULL;
    RZEFFECTID Frame3 = GUID_NULL;
    RZEFFECTID Frame4 = GUID_NULL;
    RZEFFECTID Frame5 = GUID_NULL;
    RZEFFECTID Frame6 = GUID_NULL;

    if(CreateKeyboardEffect)
    {
        // Loading animation
        ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};

        // Create the animation frames if not created
        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, &Frame0);

        for(UINT r=0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
        {
            for(UINT c=0; c<3; c++)
            {
                Effect.Color[r][c] = ORANGE;
            }
        }

        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame1);

        for(UINT r=0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
        {
            for(UINT c=0; c<6; c++)
            {
                Effect.Color[r][c] = ORANGE;
            }
        }

        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame2);

        for(UINT r=0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
        {
            for(UINT c=0; c<9; c++)
            {
                Effect.Color[r][c] = ORANGE;
            }
        }

        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame3);

        for(UINT r=0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
        {
            for(UINT c=0; c<12; c++)
            {
                Effect.Color[r][c] = ORANGE;
            }
        }

        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame4);

        for(UINT r=0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
        {
            for(UINT c=0; c<15; c++)
            {
                Effect.Color[r][c] = ORANGE;
            }
        }

        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame5);

        for(UINT r=0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
        {
            for(UINT c=0; c<18; c++)
            {
                Effect.Color[r][c] = ORANGE;
            }
        }

        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame6);

        // Play the animation
        SetEffect(Frame0);
        Sleep(500);
        SetEffect(Frame1);
        Sleep(100);
        SetEffect(Frame2);
        Sleep(100);
        SetEffect(Frame3);
        Sleep(100);
        SetEffect(Frame4);
        Sleep(100);
        SetEffect(Frame5);
        Sleep(100);
        SetEffect(Frame6);
        Sleep(100);

        ChromaSDK::Keyboard::STATIC_EFFECT_TYPE StaticEffect = {};
        StaticEffect.Color = ORANGE;

        CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &StaticEffect, NULL);
    }

    if(DeleteEffect != NULL)
    {
        DeleteEffect(Frame0);
        DeleteEffect(Frame1);
        DeleteEffect(Frame2);
        DeleteEffect(Frame3);
        DeleteEffect(Frame4);
        DeleteEffect(Frame5);
        DeleteEffect(Frame6);
    }

    return 0;
}

DWORD WINAPI Thread_LoadingAnimationOnMousepad(LPVOID lpParameter)
{
    if(CreateMousepadEffect)
    {
        CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, NULL);
        Sleep(500);

        ChromaSDK::Mousepad::CUSTOM_EFFECT_TYPE CustomEffect = {};
        for(UINT i=ChromaSDK::Mousepad::MAX_LEDS-1; i>0; --i)
        {
            CustomEffect.Color[i] = ORANGE;

            CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_CUSTOM, &CustomEffect, NULL);

            Sleep(50);
        }
    }

    return 0;
}

DWORD WINAPI Thread_LoadingAnimationOnMice(LPVOID lpParameter)
{
    if(CreateMouseEffect)
    {
        // This works too!
        // Using old interface.
        //ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE CustomEffect = {};

        //CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM, &CustomEffect, NULL);

        //Sleep(500);

        //for(UINT i=0; i<7; i++)
        //{
        //    CustomEffect.Color[RZLED_SIDE_STRIP7-i] = ORANGE;
        //    CustomEffect.Color[RZLED_SIDE_STRIP14-i] = ORANGE;

        //    if(i == 2)
        //    {
        //        CustomEffect.Color[RZLED_LOGO] = ORANGE;
        //    }
        //    else if(i == 6)
        //    {
        //        CustomEffect.Color[RZLED_SCROLLWHEEL] = ORANGE;
        //    }

        //    CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM, &CustomEffect, NULL);

        //    Sleep(50);
        //}

        // Using the new mice virtual grid
        ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE2 CustomEffect = {};

        CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM2, &CustomEffect, NULL);

        Sleep(500);

        //for(UINT i=0; i<7; i++)
        //{
        //    CustomEffect.Color[HIBYTE(RZLED2_LEFT_SIDE7)-i][0] = ORANGE;
        //    CustomEffect.Color[HIBYTE(RZLED2_RIGHT_SIDE7)-i][6] = ORANGE;

        //    if(i == 0)
        //    {
        //        // For Razer Diamondback bottom LEDs.
        //        CustomEffect.Color[8][LOBYTE(RZLED2_BOTTOM1)] = RED;
        //        CustomEffect.Color[8][LOBYTE(RZLED2_BOTTOM5)] = RED;
        //    }
        //    else if(i == 2)
        //    {
        //        CustomEffect.Color[HIBYTE(RZLED2_LOGO)][LOBYTE(RZLED2_LOGO)] = ORANGE;

        //        // For Razer Diamondback bottom LEDs.
        //        CustomEffect.Color[8][LOBYTE(RZLED2_BOTTOM2)] = RED;
        //        CustomEffect.Color[8][LOBYTE(RZLED2_BOTTOM4)] = RED;
        //    }
        //    else if(i == 4)
        //    {
        //        // For Razer Naga Epic numpad LED.
        //        CustomEffect.Color[HIBYTE(RZLED2_BACKLIGHT)][LOBYTE(RZLED2_BACKLIGHT)] = ORANGE;
        //    }
        //    else if(i == 6)
        //    {
        //        CustomEffect.Color[HIBYTE(RZLED2_SCROLLWHEEL)][LOBYTE(RZLED2_SCROLLWHEEL)] = ORANGE;

        //        // For Razer Diamondback bottom LEDs.
        //        CustomEffect.Color[8][LOBYTE(RZLED2_BOTTOM3)] = RED;
        //    }

        //    CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM2, &CustomEffect, NULL);

        //    Sleep(50);
        //}

        for(INT row=Mouse::MAX_ROW-1; row>=0; row--)
        {
            for(UINT col=0; col<Mouse::MAX_COLUMN; col++)
            {
                CustomEffect.Color[row][col] = ORANGE;
            }

            CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM2, &CustomEffect, NULL);

            Sleep(50);
        }
    }

    return 0;
}

DWORD WINAPI Thread_LoadingAnimationOnKeypad(LPVOID lpParameter)
{
    RZDEVICEID DeviceId = GUID_NULL;
    PTSTR szDevice = (PTSTR)lpParameter;
    if(_tcsicmp(szDevice, _T("Orbweaver")) == 0)
    {
        DeviceId = ORBWEAVER_CHROMA;
    }
    else if(_tcsicmp(szDevice, _T("Tartarus")) == 0)
    {
        DeviceId = TARTARUS_CHROMA;
    }

    RZEFFECTID Frame0 = GUID_NULL;
    RZEFFECTID Frame1 = GUID_NULL;
    RZEFFECTID Frame2 = GUID_NULL;
    RZEFFECTID Frame3 = GUID_NULL;
    RZEFFECTID Frame4 = GUID_NULL;
    RZEFFECTID Frame5 = GUID_NULL;

    if(CreateKeypadEffect)
    {
        ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE Effect = {};

        if(DeviceId == ORBWEAVER_CHROMA)    // Create effects for Orbweaver)
        {
            CreateEffect(DeviceId, ChromaSDK::CHROMA_NONE, NULL, &Frame0);

            for(UINT i=0; i<1; i++)
            {
                for(UINT j=0; j<ChromaSDK::Keypad::MAX_ROW; j++)
                {
                    Effect.Color[j][i] = ORANGE;
                }
            }

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame1);

            for(UINT i=0; i<2; i++)
            {
                for(UINT j=0; j<ChromaSDK::Keypad::MAX_ROW; j++)
                {
                    Effect.Color[j][i] = ORANGE;
                }
            }

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame2);

            for(UINT i=0; i<3; i++)
            {
                for(UINT j=0; j<ChromaSDK::Keypad::MAX_ROW; j++)
                {
                    Effect.Color[j][i] = ORANGE;
                }
            }

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame3);

            for(UINT i=0; i<4; i++)
            {
                for(UINT j=0; j<ChromaSDK::Keypad::MAX_ROW; j++)
                {
                    Effect.Color[j][i] = ORANGE;
                }
            }

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame4);

            for(UINT i=0; i<5; i++)
            {
                for(UINT j=0; j<ChromaSDK::Keypad::MAX_ROW; j++)
                {
                    Effect.Color[j][i] = ORANGE;
                }
            }

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame5);
        }
        else if(DeviceId == TARTARUS_CHROMA)    // Create effect for Tartarus
        {
            CreateEffect(DeviceId, ChromaSDK::CHROMA_NONE, NULL, &Frame0);

            Effect.Color[0][0] = RGB((255.0/100.0*0.2),((165.0/100.0)*0.2),00);     // Orange with 20% brightness

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame1);

            Effect.Color[0][0] = RGB((255.0/100.0*0.4),((165.0/100.0)*0.4),00);     // Orange with 40% brightness

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame2);

            Effect.Color[0][0] = RGB((255.0/100.0*0.6),((165.0/100.0)*0.6),00);     // Orange with 60% brightness

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame3);

            Effect.Color[0][0] = RGB((255.0/100.0*0.8),((165.0/100.0)*0.8),00);     // Orange with 80% brightness

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame4);

            Effect.Color[0][0] = ORANGE;                                            // Orange with 100% brightness

            CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame5);
        }

        // Play the animation
        SetEffect(Frame0);
        Sleep(500);
        SetEffect(Frame1);
        Sleep(100);
        SetEffect(Frame2);
        Sleep(100);
        SetEffect(Frame3);
        Sleep(100);
        SetEffect(Frame4);
        Sleep(100);
        SetEffect(Frame5);
    }

    if(DeleteEffect != NULL)
    {
        DeleteEffect(Frame0);
        DeleteEffect(Frame1);
        DeleteEffect(Frame2);
        DeleteEffect(Frame3);
        DeleteEffect(Frame4);
        DeleteEffect(Frame5);
    }

    return 0;
}

struct _ActiveKeysData
{
    UINT numKeys;
    UINT Key[20];
    COLORREF Color;
} ActiveKeysData;

DWORD WINAPI Thread_AnimateActiveKeysOnKeyboard(LPVOID lpParameter)
{
    Keyboard::CUSTOM_KEY_EFFECT_TYPE Effect = {};

    // Fill up the key effects.
    for(UINT i=0; i<ActiveKeysData.numKeys; i++)
    {
        COLORREF Color = 0x01000000 | ActiveKeysData.Color;

        switch(ActiveKeysData.Key[i])
        {
        case 0x41: Effect.Key[HIBYTE(RZKEY_A)][LOBYTE(RZKEY_A)] = Color; break;
        case 0x42: Effect.Key[HIBYTE(RZKEY_B)][LOBYTE(RZKEY_B)] = Color; break;
        case 0x43: Effect.Key[HIBYTE(RZKEY_C)][LOBYTE(RZKEY_C)] = Color; break;
        case 0x44: Effect.Key[HIBYTE(RZKEY_D)][LOBYTE(RZKEY_D)] = Color; break;
        case 0x45: Effect.Key[HIBYTE(RZKEY_E)][LOBYTE(RZKEY_E)] = Color; break;
        case 0x46: Effect.Key[HIBYTE(RZKEY_F)][LOBYTE(RZKEY_F)] = Color; break;
        case 0x47: Effect.Key[HIBYTE(RZKEY_G)][LOBYTE(RZKEY_G)] = Color; break;
        case 0x48: Effect.Key[HIBYTE(RZKEY_H)][LOBYTE(RZKEY_H)] = Color; break;
        case 0x49: Effect.Key[HIBYTE(RZKEY_I)][LOBYTE(RZKEY_I)] = Color; break;
        case 0x4A: Effect.Key[HIBYTE(RZKEY_J)][LOBYTE(RZKEY_J)] = Color; break;
        case 0x4B: Effect.Key[HIBYTE(RZKEY_K)][LOBYTE(RZKEY_K)] = Color; break;
        case 0x4C: Effect.Key[HIBYTE(RZKEY_L)][LOBYTE(RZKEY_L)] = Color; break;
        case 0x4D: Effect.Key[HIBYTE(RZKEY_M)][LOBYTE(RZKEY_M)] = Color; break;
        case 0x4E: Effect.Key[HIBYTE(RZKEY_N)][LOBYTE(RZKEY_N)] = Color; break;
        case 0x4F: Effect.Key[HIBYTE(RZKEY_O)][LOBYTE(RZKEY_O)] = Color; break;
        case 0x50: Effect.Key[HIBYTE(RZKEY_P)][LOBYTE(RZKEY_P)] = Color; break;
        case 0x51: Effect.Key[HIBYTE(RZKEY_Q)][LOBYTE(RZKEY_Q)] = Color; break;
        case 0x52: Effect.Key[HIBYTE(RZKEY_R)][LOBYTE(RZKEY_R)] = Color; break;
        case 0x53: Effect.Key[HIBYTE(RZKEY_S)][LOBYTE(RZKEY_S)] = Color; break;
        case 0x54: Effect.Key[HIBYTE(RZKEY_T)][LOBYTE(RZKEY_T)] = Color; break;
        case 0x55: Effect.Key[HIBYTE(RZKEY_U)][LOBYTE(RZKEY_U)] = Color; break;
        case 0x56: Effect.Key[HIBYTE(RZKEY_V)][LOBYTE(RZKEY_V)] = Color; break;
        case 0x57: Effect.Key[HIBYTE(RZKEY_W)][LOBYTE(RZKEY_W)] = Color; break;
        case 0x58: Effect.Key[HIBYTE(RZKEY_X)][LOBYTE(RZKEY_X)] = Color; break;
        case 0x59: Effect.Key[HIBYTE(RZKEY_Y)][LOBYTE(RZKEY_Y)] = Color; break;
        case 0x5A: Effect.Key[HIBYTE(RZKEY_Z)][LOBYTE(RZKEY_Z)] = Color; break;
        case VK_LCONTROL: Effect.Key[HIBYTE(RZKEY_LCTRL)][LOBYTE(RZKEY_LCTRL)] = Color; break;
        case VK_LSHIFT: Effect.Key[HIBYTE(RZKEY_LSHIFT)][LOBYTE(RZKEY_LSHIFT)] = Color; break;
        case VK_SPACE: Effect.Key[HIBYTE(RZKEY_SPACE)][LOBYTE(RZKEY_SPACE)] = Color; break;
        case VK_ESCAPE: Effect.Key[HIBYTE(RZKEY_ESC)][LOBYTE(RZKEY_ESC)] = Color; break;
        case VK_RETURN: Effect.Key[HIBYTE(RZKEY_ENTER)][LOBYTE(RZKEY_ENTER)] = Color; break;
        case VK_UP: Effect.Key[HIBYTE(RZKEY_UP)][LOBYTE(RZKEY_UP)] = Color; break;
        case VK_DOWN: Effect.Key[HIBYTE(RZKEY_DOWN)][LOBYTE(RZKEY_DOWN)] = Color; break;
        case VK_LEFT: Effect.Key[HIBYTE(RZKEY_LEFT)][LOBYTE(RZKEY_LEFT)] = Color; break;
        case VK_RIGHT: Effect.Key[HIBYTE(RZKEY_RIGHT)][LOBYTE(RZKEY_RIGHT)] = Color; break;
        }
    }

    CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM_KEY, &Effect, NULL);

    Sleep(50);

    // Create a waterfall effect
    for(int i=0; i<Keyboard::MAX_ROW+3; i++)
    {
        ZeroMemory(Effect.Color, sizeof(Effect.Color));

        for(int row=0; row<Keyboard::MAX_ROW; row++)
        {
            for(int col=0; col<Keyboard::MAX_COLUMN; col++)
            {
                if((i == row) && (i < Keyboard::MAX_ROW))
                {
                    Effect.Color[row][col] = RGB(GetRValue(ORANGE),
                                                 GetGValue(ORANGE),
                                                 GetBValue(ORANGE));
                }

                if((i-1) == row)
                {
                    Effect.Color[row][col] = RGB(0.3 * GetRValue(ORANGE),
                                                 0.3 * GetGValue(ORANGE),
                                                 0.3 * GetBValue(ORANGE));
                }

                if((i-2) == row)
                {
                    Effect.Color[row][col] = RGB(0.1 * GetRValue(ORANGE),
                                                 0.1 * GetGValue(ORANGE),
                                                 0.1 * GetBValue(ORANGE));
                }
            }
        }

        CreateKeyboardEffect(Keyboard::CHROMA_CUSTOM_KEY, &Effect, NULL);

        Sleep(50);
    }

    return 0;
}

CChromaSDKImpl::CChromaSDKImpl():m_ChromaSDKModule(NULL)
{
}

CChromaSDKImpl::~CChromaSDKImpl()
{
}

BOOL CChromaSDKImpl::Initialize()
{
    if(m_ChromaSDKModule == NULL)
    {
        m_ChromaSDKModule = LoadLibrary(CHROMASDKDLL);
        if(m_ChromaSDKModule == NULL)
        {
            ASSERT(GetLastError() == ERROR_SUCCESS);
            return FALSE;
        }
    }

    if(Init == NULL)
    {
        RZRESULT Result = RZRESULT_INVALID;
        Init = (INIT)GetProcAddress(m_ChromaSDKModule, "Init");
        if(Init)
        {
            Result = Init();
            if(Result == RZRESULT_SUCCESS)
            {
                CreateEffect = (CREATEEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateEffect");
                CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateKeyboardEffect");
                CreateMouseEffect = (CREATEMOUSEEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateMouseEffect");
                CreateHeadsetEffect = (CREATEHEADSETEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateHeadsetEffect");
                CreateMousepadEffect = (CREATEMOUSEPADEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateMousepadEffect");
                CreateKeypadEffect = (CREATEKEYPADEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateKeypadEffect");
                SetEffect = (SETEFFECT)GetProcAddress(m_ChromaSDKModule, "SetEffect");
                DeleteEffect = (DELETEEFFECT)GetProcAddress(m_ChromaSDKModule, "DeleteEffect");
                QueryDevice = (QUERYDEVICE)GetProcAddress(m_ChromaSDKModule, "QueryDevice");

                if(CreateEffect &&
                    CreateKeyboardEffect &&
                    CreateMouseEffect &&
                    CreateHeadsetEffect &&
                    CreateMousepadEffect &&
                    CreateKeypadEffect &&
                    SetEffect &&
                    DeleteEffect &&
                    QueryDevice)
                {
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

BOOL CChromaSDKImpl::UnInitialize()
{
    if(m_ChromaSDKModule != NULL)
    {
        RZRESULT Result = RZRESULT_INVALID;
        UNINIT UnInit = (UNINIT)GetProcAddress(m_ChromaSDKModule, "UnInit");
        if(UnInit)
        {
            Result = UnInit();
            ASSERT(Result == RZRESULT_SUCCESS);
        }

        FreeLibrary(m_ChromaSDKModule);
        m_ChromaSDKModule = NULL;

        return TRUE;
    }

    return FALSE;
}

void CChromaSDKImpl::PlayLoadingAnimation(UINT DeviceType)
{
    HANDLE hWorkerThread = NULL;
    switch(DeviceType)
    {
    case 1: 
        hWorkerThread = CreateThread(NULL, 0, Thread_LoadingAnimationOnKeyboard, this, 0, NULL);
        CloseHandle(hWorkerThread);
        break;
    }
}

void CChromaSDKImpl::ResetEffects(UINT DeviceType)
{
    switch(DeviceType)
    {
    case 0:
        if(CreateKeyboardEffect)
        {
            CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, NULL);
        }

        if(CreateMousepadEffect)
        {
            CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, NULL);
        }

        if(CreateMouseEffect)
        {
            //CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, NULL, NULL);
            // Use custom effect command is faster because some of the mice has fade-to-black effect.
            ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE2 None = {};
            CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM2, &None, NULL);
        }

        if(CreateHeadsetEffect)
        {
            CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_NONE, NULL, NULL);
        }

        if(CreateKeypadEffect)
        {
            CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_NONE, NULL, NULL);
        }
        break;
    case 1:
        if(CreateKeyboardEffect)
        {
            CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, NULL);
        }
        break;
    case 2:
        if(CreateMousepadEffect)
        {
            CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, NULL);
        }
        break;
    case 3:
        if(CreateMouseEffect)
        {
            //CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, NULL, NULL);
            // Use custom effect command is faster because some of the mice has fade-to-black effect.
            ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE2 None = {};
            CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM2, &None, NULL);
        }
        break;
    case 4:
        if(CreateHeadsetEffect)
        {
            CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_NONE, NULL, NULL);
        }
        break;
    case 5:
        if(CreateKeypadEffect)
        {
            CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_NONE, NULL, NULL);
        }
        break;
    }
}

BOOL CChromaSDKImpl::IsDeviceConnected(RZDEVICEID DeviceId)
{
    if(QueryDevice != NULL)
    {
        ChromaSDK::DEVICE_INFO_TYPE DeviceInfo = {};
        RZRESULT Result = QueryDevice(DeviceId, DeviceInfo);

        ASSERT(Result == RZRESULT_SUCCESS);

        return DeviceInfo.Connected;
    }

    return FALSE;
}

