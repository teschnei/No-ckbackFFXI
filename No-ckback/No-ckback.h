#include "..\..\ADK\Ashita.h"
#include <stdint.h>

class Nockback : public PluginBase
{
private:
	IAshitaCore* m_AshitaCore;

public:
	Nockback(){}
	virtual ~Nockback(){}
	bool Initialize(IAshitaCore* ashitaCore, DWORD dwPluginId);

	void Release();

	PluginData GetPluginData();
	
	bool HandleIncomingPacket(unsigned int uiPacketId, unsigned int uiPacketSize, void* lpRawData);
};

//Exports
__declspec(dllexport) double    __stdcall GetInterfaceVersion(void);
__declspec(dllexport) void		__stdcall CreatePluginData(PluginData* lpPluginData);
__declspec(dllexport) IPlugin*	__stdcall CreatePlugin(char* pszText);
