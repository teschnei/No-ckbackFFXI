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
