#include "..\..\SDK\Depends\Common\Extension.h"
#include <stdint.h>

class Nockback : public ExtensionBase
{
private:
	IAshitaCore* m_AshitaCore;
	Entity* player;

public:
	Nockback()
	{}
	~Nockback()
	{}
	int __stdcall Load(IAshitaCore* mAshitaCore, DWORD ExtensionID);

	void __stdcall Unload();

	ExtensionInterfaceData __stdcall GetExtensionData();
	
	bool __stdcall HandleIncomingPacket(unsigned int uiSize, void* pData);
};

//Exports
__declspec( dllexport ) void __stdcall CreateExtensionData( ExtensionInterfaceData* lpExtensionData );
__declspec( dllexport ) IExtension* __stdcall CreateExtension( char* pszText );
