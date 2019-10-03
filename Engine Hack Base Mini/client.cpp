#include "main.h"
#include "drawing.h"
#include "cVars/cvars.h"

local_s g_Local;
player_s g_Player[33];
vector<entity_s> g_Entity;
SCREENINFO g_Screen;
extern HINSTANCE hInst;
static bool Init = false;

#pragma warning(disable:4996)
#pragma warning(disable:4804)
#pragma warning(disable:4552)
#pragma warning(disable:4244)

void HookEngine( void )
{
	memcpy( &g_Engine, (LPVOID)g_pEngine, sizeof( cl_enginefunc_t ) );
}

void HookStudio( void )
{
	memcpy( &g_Studio, (LPVOID)g_pStudio, sizeof( engine_studio_api_t ) );
}

void HUD_Frame(double time);

void InitHack()
{
	g_Screen.iSize = sizeof( SCREENINFO );
	g_Engine.pfnGetScreenInfo( &g_Screen );

	char *HackPrint = "Engine Hack Base Mini By HLREVENGE 2013 (c)";
	g_Engine.Con_Printf( "\n\n\t\t\t\t\t\t\t%s\n\n", HackPrint );

	g_Engine.Con_Printf("g_pClient: 0x%X\n", g_pClient);
	g_Engine.Con_Printf("HUD_Frame: 0x%X\n", HUD_Frame);
	
	// Dll Protection
	HackBase::HideModule(hInst);
	HackBase::HideModuleXta(hInst);
	HackBase::HideModuleFromPEB(hInst);
	HackBase::RemovePeHeader((DWORD)hInst);
	HackBase::DestroyModuleHeader(hInst);	
}

void HUD_Frame( double time )
{
	if( !Init )
	{
		//HookOpenGL();
		//cfunc.Init();
		InitHack();
		Init = true;
	}

	g_Client.HUD_Frame( time );
}

bool bPathFree( float *pflFrom, float *pflTo )
{
	if( !pflFrom || !pflTo ) { return false; }
	pmtrace_t pTrace;
	g_Engine.pEventAPI->EV_SetTraceHull( 2 );
	g_Engine.pEventAPI->EV_PlayerTrace( pflFrom, pflTo, PM_GLASS_IGNORE | PM_STUDIO_BOX, g_Local.iIndex, &pTrace );
	return ( pTrace.fraction == 1.0f );
}

void HUD_Redraw( float time, int intermission )
{
	g_Client.HUD_Redraw( time, intermission );

	cl_entity_s *ent;
	cl_entity_t *pLocal = g_Engine.GetLocalPlayer();
	g_Local.iIndex = pLocal->index;

	// обновление инфы об игроках
	for(int i=1; i<33; i++)
	{
		ent = g_Engine.GetEntityByIndex(i);
		g_Engine.pfnGetPlayerInfo(i,&g_Player[i].Info);
		g_Player[i].bVisible = (bPathFree(g_Local.vEye, Vector(ent->origin[0],ent->origin[1],ent->origin[2])));
		g_Player[i].vOrigin = ent->origin;
	}
}

void HUD_PlayerMove( struct playermove_s *ppmove, int server )
{
	g_Client.HUD_PlayerMove( ppmove, server );

	g_Local.vOrigin = ppmove->origin;
	g_Engine.pEventAPI->EV_LocalPlayerViewheight(g_Local.vEye);
	g_Local.vEye = g_Local.vEye + ppmove->origin;	
}

void HookClient( void )
{
	memcpy( &g_Client, (LPVOID)g_pClient, sizeof( cl_clientfunc_t ) );
	g_pClient->HUD_Frame = HUD_Frame;
	g_pClient->HUD_Redraw = HUD_Redraw;
	g_pClient->HUD_PlayerMove = HUD_PlayerMove;
}