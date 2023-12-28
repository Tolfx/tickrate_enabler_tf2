// test
#include "hls2dk-tf2/public/eiface.h"
#include "metamod-source/core/sourcehook/sourcehook_impl.h"
class TickrateEnabler : public IServerPluginCallbacks
{
public:
	TickrateEnabler(){};
	~TickrateEnabler(){};

	// IServerPluginCallbacks methods
	virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);
	virtual void Unload(void);
	virtual void Pause(void){};
	virtual void UnPause(void){};
	virtual const char *GetPluginDescription(void);
	virtual void LevelInit(char const *pMapName){};
	virtual void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax){};
	virtual void GameFrame(bool simulating){};
	virtual void LevelShutdown(void){};
	virtual void ClientActive(edict_t *pEntity){};
	virtual void ClientFullyConnect(edict_t *pEntity){};
	virtual void ClientDisconnect(edict_t *pEntity){};
	virtual void ClientPutInServer(edict_t *pEntity, char const *playername){};
	virtual void SetCommandClient(int index){};
	virtual void ClientSettingsChanged(edict_t *pEdict){};
	virtual PLUGIN_RESULT ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen) { return PLUGIN_CONTINUE; };
	virtual PLUGIN_RESULT ClientCommand(edict_t *pEntity, const CCommand &args) { return PLUGIN_CONTINUE; };
	virtual PLUGIN_RESULT NetworkIDValidated(const char *pszUserName, const char *pszNetworkID) { return PLUGIN_CONTINUE; };
	virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue){};

	// added with version 3 of the interface.
	virtual void OnEdictAllocated(edict_t *edict){};
	virtual void OnEdictFreed(const edict_t *edict){};

	// added with version 4 of the interface.
	virtual bool BNetworkCryptKeyCheckRequired(uint32 unFromIP, uint16 usFromPort, uint32 unAccountIdProvidedByClient, bool bClientWantsToUseCryptKey) { return false; };
	virtual bool BNetworkCryptKeyValidate(uint32 unFromIP, uint16 usFromPort, uint32 unAccountIdProvidedByClient, int nEncryptionKeyIndexFromClient, int numEncryptedBytesFromClient, byte *pbEncryptedBufferFromClient, byte *pbPlainTextKeyForNetchan) { return false; };
};
// No idea why this is required for linux.
ICvar *g_pCVar = NULL;

TickrateEnabler g_EmptyServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(TickrateEnabler, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_EmptyServerPlugin);

// SourceHook Embedding
SourceHook::Impl::CSourceHookImpl g_SourceHook;
SourceHook::ISourceHook *g_SHPtr = &g_SourceHook;
int g_PLID = 0;

SH_DECL_HOOK0(IServerGameDLL, GetTickInterval, const, 0, float);

IServerGameDLL *gamedll = NULL;

float GetTickInterval()
{
	float tickinterval = 0.01f;
	RETURN_META_VALUE(MRES_SUPERCEDE, tickinterval);
}

const char *TickrateEnabler::GetPluginDescription(void)
{
	return "TickrateEnabler for TF2";
}

bool TickrateEnabler::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	gamedll = (IServerGameDLL *)gameServerFactory("ServerGameDLL012", NULL);
	if (!gamedll)
	{
		Warning("Failed to get a pointer on ServerGameDLL.\n");
		return false;
	}

	SH_ADD_HOOK(IServerGameDLL, GetTickInterval, gamedll, SH_STATIC(GetTickInterval), false);

	return true;
}

void TickrateEnabler::Unload(void)
{
	SH_REMOVE_HOOK(IServerGameDLL, GetTickInterval, gamedll, SH_STATIC(GetTickInterval), false);
}
