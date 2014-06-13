#include "No-ckback.h"
#include "DSP-Utils.h"

#include <windows.h>
#include <stdio.h>

//do not delete this. Ashita will clean it up.
PluginData* ModuleData;

bool Nockback::Initialize(IAshitaCore* ashitaCore, DWORD dwPluginId)
{
	m_AshitaCore = ashitaCore;
    
    return true;
}

void Nockback::Release()
{
}

PluginData Nockback::GetPluginData()
{
    return *ModuleData;
}
    
bool Nockback::HandleIncomingPacket(unsigned int uiPacketId, unsigned int uiPacketSize, void* lpRawData)
{
	if (uiPacketId == 0x28)
	{
		uint8_t actionType = (uint8_t)(unpackBitsBE((unsigned char*)lpRawData, 82, 4));

		if (actionType == 11)
		{
			uint8_t targetNum = RBUFB(lpRawData, 0x09);
			uint16_t startBit = 150;
			for (int i = 0; i < targetNum; i++)
			{
				packBitsBE((unsigned char*)lpRawData, 0, startBit + 60, 3);
				if (unpackBitsBE((unsigned char*)lpRawData, startBit + 121, 1) & 0x1)
				{
					startBit += 37;
				}
				if (unpackBitsBE((unsigned char*)lpRawData, startBit + 122, 1) & 0x1)
				{
					startBit += 34;
				}
				startBit += 123;
			}
		}
	}
    return false;
}

__declspec(dllexport) double __stdcall GetInterfaceVersion(void)
{
	return ASHITA_INTERFACE_VERSION;
}

__declspec(dllexport) void __stdcall CreatePluginData( PluginData* Data )
{
    ModuleData = Data;
    ModuleData->PluginVersion       =        1.04;
	ModuleData->InterfaceVersion	= ASHITA_INTERFACE_VERSION;
	ModuleData->Priority = 0;

    strncpy_s( ModuleData->Name, "No-ckback", 256 );
    strncpy_s( ModuleData->Author, "kjLotus", 256 );
}

__declspec(dllexport) IPlugin* __stdcall CreatePlugin( char* pszText )
{
	return (IPlugin*)new Nockback();
}
