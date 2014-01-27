#include "No-ckback.h"
#include "DSP-Utils.h"

#include <windows.h>
#include <stdio.h>

//do not delete this. Ashita will clean it up.
ExtensionInterfaceData* ModuleData;

int __stdcall Nockback::Load(IAshitaCore* mAshitaCore, DWORD ExtensionID)
{
    m_AshitaCore = mAshitaCore;
    
    return 1;
}

void __stdcall Nockback::Unload()
{
}

ExtensionInterfaceData __stdcall Nockback::GetExtensionData()
{
    return *ModuleData;
}
    
bool __stdcall Nockback::HandleIncomingPacket(unsigned int uiSize, void* pData)
{
	uint16_t packetType = RBUFW(pData, 0) & 0x01FF;

	if (packetType == 0x28)
	{
		IDataTools* dataTools = m_AshitaCore->GetDataModule()->GetDataTools();

		uint8_t actionType = (uint8_t)(dataTools->unpackBitsBE((unsigned char*)pData, 82, 4));

		if (actionType == 11)
		{
			uint8_t targetNum = RBUFB(pData, 0x09);
			uint16_t startBit = 150;
			for (int i = 0; i < targetNum; i++)
			{
				dataTools->packBitsBE((unsigned char*)pData, 0, startBit + 60, 3);
				if (dataTools->unpackBitsBE((unsigned char*)pData, startBit + 121, 1) & 0x1)
				{
					startBit += 37;
				}
				if (dataTools->unpackBitsBE((unsigned char*)pData, startBit + 122, 1) & 0x1)
				{
					startBit += 34;
				}
				startBit += 123;
			}
		}
	}
    return false;
}


__declspec( dllexport ) void __stdcall CreateExtensionData( ExtensionInterfaceData* Data )
{
    ModuleData = Data;
    ModuleData->ExtensionVersion        =        1.00;
    ModuleData->InterfaceVersion        =        INTERFACEVERSION;
    ModuleData->RequiresValadation      =        false;
    ModuleData->AutoloadConfiguration   =        false;
    ModuleData->AutoloadLanguage        =        false;

    strncpy_s( ModuleData->Name, "No-ckback", 256 );
    strncpy_s( ModuleData->Author, "kjLotus", 256 );
}

__declspec( dllexport ) IExtension* __stdcall CreateExtension( char* pszText )
{
	return (IExtension*)new Nockback();
}
