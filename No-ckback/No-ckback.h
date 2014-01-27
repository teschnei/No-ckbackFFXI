#include "..\..\SDK\Depends\Common\Extension.h"
#include <stdint.h>

#define RBUFP(p,pos) (((uint8_t*)(p)) + (pos))
#define RBUFB(p,pos) (*(uint8_t*)RBUFP((p),(pos)))
#define RBUFW(p,pos) (*(uint16_t*)RBUFP((p),(pos)))
#define RBUFL(p,pos) (*(uint32_t*)RBUFP((p),(pos)))
#define RBUFF(p,pos) (*(float*)RBUFP((p),(pos)))

#define WBUFP(p,pos) (((uint8_t*)(p)) + (pos))
#define WBUFB(p,pos) (*(uint8_t*)WBUFP((p),(pos)))
#define WBUFW(p,pos) (*(uint16_t*)WBUFP((p),(pos)))
#define WBUFL(p,pos) (*(uint32_t*)WBUFP((p),(pos)))
#define WBUFF(p,pos) (*(float*)WBUFP((p),(pos)))

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
