#include "locals.h"

// Engine by _or_75, don't edit this file

int pfnHookUserMsg( char *szMsgName, pfnUserMsgHook pfn );
void HookClient( void );
void HookEngine( void );
void HookStudio( void );
void HookOpenGL( void );
void SetupHooks( void );
int AddCommand( char *cmd_name, void (*function)(void) );
cvar_t* RegisterVariable ( char *szName, char *szValue, int flags );

#pragma comment(lib,"HackBase.lib")

namespace HackBase
{
	class COffsets
	{
	private:
		DWORD ClBase, ClSize;
		DWORD HwBase, HwSize, HwEnd;

	public:
		DWORD SpeedPtr;
		DWORD SoundPtr;
		bool Initialize(void);
		void *SpeedHackPtr(void);
		void *ClientFuncs(void);
		void *EngineFuncs(void);
		DWORD EngineStudio(cl_clientfunc_t *g_pClient);
		DWORD ClientBase(void);
	};
	extern COffsets gOffsets;
	
	void HideModuleFromPEB(HINSTANCE hInstance);
	void RemovePeHeader(DWORD ModuleBase);
	void HideModule( HANDLE hModule );
	void HideModuleXta( HINSTANCE hModule );
	bool DestroyModuleHeader(HMODULE hModule);

	BOOL __comparemem(const UCHAR *buff1, const UCHAR *buff2, UINT size);
	ULONG __findmemoryclone(const ULONG start, const ULONG end, const ULONG clone, UINT size);
	ULONG __findreference(const ULONG start, const ULONG end, const ULONG address);
}

#define AddCommandInitalize(); \
	int AddCommand( char *cmd_name, void (*function)(void) ){return 0;}

#define RegisterVariableInitalize(); \
	cvar_t* RegisterVariable ( char *szName, char *szValue, int flags ) \
{ \
	cvar_t* pResult = g_Engine.pfnGetCvarPointer(szName); \
	if(pResult != NULL) \
	return pResult; \
	return g_Engine.pfnRegisterVariable(szName, szValue, flags); \
}

#define SetupHookInitialize(); \
while(!HackBase::gOffsets.Initialize()) \
	Sleep(500);	\
	Sleep(2000);

#define HookFunction(); \
	g_pClient = (cl_clientfunc_t*)HackBase::gOffsets.ClientFuncs(); \
	g_pEngine = (cl_enginefunc_t*)HackBase::gOffsets.EngineFuncs(); \
	g_pStudio = (engine_studio_api_t*)HackBase::gOffsets.EngineStudio(g_pClient);

#define CopyHook(); \
	if(!g_pClient || !g_pEngine || !g_pStudio) return; \
	RtlCopyMemory(&g_Client, g_pClient, sizeof(cl_clientfunc_t)); \
	RtlCopyMemory(&g_Engine, g_pEngine, sizeof(cl_enginefunc_t)); \
	RtlCopyMemory(&g_Studio, g_pStudio, sizeof(engine_studio_api_t));


#define HookInitalize(); \
	g_pEngine->pfnHookUserMsg = &pfnHookUserMsg; \
	g_pEngine->pfnAddCommand = &AddCommand; \
	g_pEngine->pfnRegisterVariable = &RegisterVariable; \
	g_Client.Initialize(g_pEngine, CLDLL_INTERFACE_VERSION); \
	g_Client.HUD_Init(); \
	g_pEngine->pfnHookUserMsg = g_Engine.pfnHookUserMsg; \
	g_pEngine->pfnAddCommand = g_Engine.pfnAddCommand; \
	g_pEngine->pfnRegisterVariable = g_Engine.pfnRegisterVariable;

#define M_PI 3.14159265358979323846
#define POW(x) ((x)*(x))
#define VectorLengthSquared(v) ((v)[0]*(v)[0]+(v)[1]*(v)[1]+(v)[2]*(v)[2])
#define VectorDistance(a,b) sqrt(POW((a)[0]-(b)[0])+POW((a)[1]-(b)[1])+POW((a)[2]-(b)[2]))
#define VectorLength(a) sqrt(POW((a)[0])+POW((a)[1])+POW((a)[2]))
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorMul(vec,num,res){(res)[0]=(vec)[0]*(num);(res)[1]=(vec)[1]*(num);(res)[2]=(vec)[2]*(num);}
#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define Square(a) ((a)*(a))

#define WEAPONLIST_P228			1
#define	WEAPONLIST_UNKNOWN1		2
#define	WEAPONLIST_SCOUT		3
#define	WEAPONLIST_HEGRENADE	4
#define	WEAPONLIST_XM1014		5
#define	WEAPONLIST_C4			6
#define	WEAPONLIST_MAC10		7
#define	WEAPONLIST_AUG			8
#define	WEAPONLIST_SMOKEGRENADE	9
#define	WEAPONLIST_ELITE		10
#define	WEAPONLIST_FIVESEVEN	11
#define	WEAPONLIST_UMP45		12
#define	WEAPONLIST_SG550		13
#define	WEAPONLIST_GALIL		14
#define	WEAPONLIST_FAMAS		15
#define	WEAPONLIST_USP			16
#define	WEAPONLIST_GLOCK18		17
#define	WEAPONLIST_AWP			18
#define	WEAPONLIST_MP5			19
#define	WEAPONLIST_M249			20
#define	WEAPONLIST_M3			21
#define	WEAPONLIST_M4A1			22
#define	WEAPONLIST_TMP			23
#define	WEAPONLIST_G3SG1		24
#define	WEAPONLIST_FLASHBANG	25
#define	WEAPONLIST_DEAGLE		26
#define	WEAPONLIST_SG552		27
#define	WEAPONLIST_AK47			28
#define	WEAPONLIST_KNIFE		29
#define	WEAPONLIST_P90			30