#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>

typedef struct _PLAYER_DATA {

	PVOID address;
	DWORD value;
	std::shared_ptr<std::vector<PVOID>> offsets;
	bool toggle = false;

} PLAYER_DATA, * PPLAYER_DATA;

typedef struct _PLAYER
{
	std::shared_ptr<PLAYER_DATA> local_player;
	std::shared_ptr<PLAYER_DATA> health;
	std::shared_ptr<PLAYER_DATA> rifle_ammo;
	std::shared_ptr<PLAYER_DATA> rifle_mag;
	std::shared_ptr<PLAYER_DATA> pistal_ammo;
	std::shared_ptr<PLAYER_DATA> pistal_mag;
	std::shared_ptr<PLAYER_DATA> armor;
	std::shared_ptr<PLAYER_DATA> grenade;

} PLAYER, * PPLAYER;


BOOL GetProcId(IN const wchar_t* process_name, OUT DWORD* pprocess_id);
BOOL ReadMem(IN HANDLE hProcess, IN std::shared_ptr<PLAYER_DATA> player_data);
BOOL WriteMem(IN HANDLE hProcess, IN std::shared_ptr<PLAYER_DATA> player_data);
BOOL GetModuleBaseAddress(IN DWORD process_id, IN const wchar_t* module_name, OUT PVOID* pbaseAddress);
BOOL FindDMAAddy(IN HANDLE hProcess, IN PVOID init_ptr, IN std::vector<PVOID> offsets, OUT PVOID* pbaseAddress);
