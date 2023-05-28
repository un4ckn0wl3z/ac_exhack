#include <locale>
#include <codecvt>
#include "Common.hpp"
#include <conio.h>

void init_player_data(IN std::shared_ptr<PLAYER> player);
BOOL init_player_dynamic_address(IN HANDLE hProcess, IN PVOID modulebase_address, IN OUT std::shared_ptr<PLAYER> player);

int main()
{
	system("title AC_HACK.exe");

	DWORD dwExitCode = 0;
	PVOID modulebase_address = NULL;
	std::shared_ptr<PLAYER> player = std::make_shared<PLAYER>();
	DWORD process_id = NULL;
	const wchar_t* process_name = L"ac_client.exe";

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string process_name_utf8 = converter.to_bytes(process_name);

	init_player_data(player);

	// Get game process ID
	if (!GetProcId(process_name, &process_id))
	{
		std::cout << "[!] GetProcId failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return 0;
	}
	std::cout << "[+] Found " << process_name_utf8 << "'s ID: " << process_id << std::endl;


	// Get ac_client.exe base address
	if (!GetModuleBaseAddress(process_id, process_name, &modulebase_address))
	{
		std::cout << "[!] GetModuleBaseAddress failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "[+] Found " << process_name_utf8 << "'s Module base address: " << modulebase_address << std::endl;


	// Get process handle
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
	if (hProcess == NULL)
	{
		std::cout << "[!] OpenProcess failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return 0;
	}

	if (init_player_dynamic_address(hProcess, modulebase_address, player) != TRUE)
	{
		std::cout << "[!] Cannot init_player_dynamic_address: " << GetLastError() << std::endl;
		system("pause");
		return 0;
	}

	// -----------------------------------------------------------------------------------------

	while (GetExitCodeProcess(hProcess, &dwExitCode) && dwExitCode == STILL_ACTIVE)
	{
		std::cout << "########### AssaultCube 1.3.0.2 EXTERNAL HACK by un4ckn0wl3z" << std::endl;
		std::cout << "[+] " << process_name_utf8 << " still active!" << std::endl << std::endl;
		std::cout << "[+] (F1) HEALTH: " << ((player->health->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F2) ARMOR: " << ((player->armor->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F3) GRENADE: " << ((player->grenade->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F4) RIFLE AMMO: " << ((player->rifle_ammo->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F5) RIFLE MAG: " << ((player->rifle_mag->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F6) PISTAL AMMO: " << ((player->pistal_ammo->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F7) PISTAL MAG: " << ((player->pistal_mag->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F8) SNIPER AMMO: " << ((player->sniper_ammo->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F9) SNIPER MAG: " << ((player->sniper_mag->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (F10) SHOTGUN AMMO: " << ((player->shotgun_ammo->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (NUM_0) SHOTGUN MAG: " << ((player->shotgun_mag->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (NUM_1) RAPID FIRE: " << ((player->rapid_fire->toggle) ? "ON" : "OFF") << std::endl;
		std::cout << "[+] (NUM_2) NO RECOIL: " << ((player->no_recoil->toggle) ? "ON" : "OFF") << std::endl;


		// INIT HOTKEYS
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			player->health->toggle = !player->health->toggle;
		}

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			player->armor->toggle = !player->armor->toggle;
		}

		if (GetAsyncKeyState(VK_F3) & 1)
		{
			player->grenade->toggle = !player->grenade->toggle;
		}

		if (GetAsyncKeyState(VK_F4) & 1)
		{
			player->rifle_ammo->toggle = !player->rifle_ammo->toggle;
		}

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			player->rifle_mag->toggle = !player->rifle_mag->toggle;
		}

		if (GetAsyncKeyState(VK_F6) & 1)
		{
			player->pistal_ammo->toggle = !player->pistal_ammo->toggle;
		}

		if (GetAsyncKeyState(VK_F7) & 1)
		{
			player->pistal_mag->toggle = !player->pistal_mag->toggle;
		}

		if (GetAsyncKeyState(VK_F8) & 1)
		{
			player->sniper_ammo->toggle = !player->sniper_ammo->toggle;
		}

		if (GetAsyncKeyState(VK_F9) & 1)
		{
			player->sniper_mag->toggle = !player->sniper_mag->toggle;
		}

		if (GetAsyncKeyState(VK_F10) & 1)
		{
			player->shotgun_ammo->toggle = !player->shotgun_ammo->toggle;
		}

		if (GetAsyncKeyState(VK_NUMPAD0) & 1)
		{
			player->shotgun_mag->toggle = !player->shotgun_mag->toggle;
		}

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			player->rapid_fire->toggle = !player->rapid_fire->toggle;
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			player->no_recoil->toggle = !player->no_recoil->toggle;
		}

		if (player->health->toggle)
		{
			player->health->value = 1337;

			if ((WriteMem(hProcess, player->health)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->health failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		if (player->armor->toggle)
		{
			player->armor->value = 1337;

			if ((WriteMem(hProcess, player->armor)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->armor failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		if (player->grenade->toggle)
		{
			player->grenade->value = 1337;

			if ((WriteMem(hProcess, player->grenade)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->grenade failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		if (player->rifle_ammo->toggle)
		{
			player->rifle_ammo->value = 1337;

			if ((WriteMem(hProcess, player->rifle_ammo)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->rifle_ammo failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		if (player->rifle_mag->toggle)
		{
			player->rifle_mag->value = 1337;

			if ((WriteMem(hProcess, player->rifle_mag)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->rifle_mag failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		if (player->pistal_ammo->toggle)
		{
			player->pistal_ammo->value = 1337;

			if ((WriteMem(hProcess, player->pistal_ammo)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->pistal_ammo failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		if (player->pistal_mag->toggle)
		{
			player->pistal_mag->value = 1337;

			if ((WriteMem(hProcess, player->pistal_mag)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->pistal_mag failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}


		if (player->sniper_ammo->toggle)
		{
			player->sniper_ammo->value = 1337;

			if ((WriteMem(hProcess, player->sniper_ammo)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->sniper_ammo failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}


		if (player->sniper_mag->toggle)
		{
			player->sniper_mag->value = 1337;

			if ((WriteMem(hProcess, player->sniper_mag)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->sniper_mag failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}


		if (player->shotgun_ammo->toggle)
		{
			player->shotgun_ammo->value = 1337;

			if ((WriteMem(hProcess, player->shotgun_ammo)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->shotgun_ammo failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}


		if (player->shotgun_mag->toggle)
		{
			player->shotgun_mag->value = 1337;

			if ((WriteMem(hProcess, player->shotgun_mag)) == FALSE)
			{
				std::cout << "[!] WriteProcessMemory player->shotgun_mag failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		if (player->rapid_fire->toggle)
		{

			if ((NopEx(hProcess, (PBYTE)player->rapid_fire->address,2)) == FALSE)
			{
				std::cout << "[!] NopEx player->rapid_fire failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}
		else {
			if ((PatchMemEx(hProcess, (PBYTE)player->rapid_fire->address,(PBYTE)"\x89\x08", 2)) == FALSE)
			{
				std::cout << "[!] PatchMemEx player->rapid_fire failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		if (player->no_recoil->toggle)
		{

			if ((NopEx(hProcess, (PBYTE)player->no_recoil->address, 5)) == FALSE)
			{
				std::cout << "[!] NopEx player->no_recoil failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}
		else {
			if ((PatchMemEx(hProcess, (PBYTE)player->no_recoil->address, (PBYTE)"\xF3\x0F\x11\x50\x40", 5)) == FALSE)
			{
				std::cout << "[!] PatchMemEx player->no_recoil failed with error code: " << GetLastError() << std::endl;
				system("pause");
				return 0;
			};
		}

		Sleep(16);
		system("cls");
	}


	std::cout << "[!] " << process_name_utf8 << " lost in translation" << std::endl;
	CloseHandle(hProcess);

	system("pause");
	return 0;
}


void init_player_data(IN std::shared_ptr<PLAYER> player)
{
	// ----------------- LOCAL PLAYER SETUP
	player->local_player = std::make_shared<PLAYER_DATA>();

	// ----------------- LOCAL RAPID FIRE SETUP
	player->rapid_fire = std::make_shared<PLAYER_DATA>();

	// ----------------- no_recoil SETUP
	player->no_recoil = std::make_shared<PLAYER_DATA>();

	// ----------------- health SETUP
	player->health = std::make_shared<PLAYER_DATA>();
	player->health->offsets = std::make_shared<std::vector<PVOID>>();
	player->health->offsets->push_back(reinterpret_cast<PVOID>(0xEC));

	// ----------------- armor SETUP
	player->armor = std::make_shared<PLAYER_DATA>();
	player->armor->offsets = std::make_shared<std::vector<PVOID>>();
	player->armor->offsets->push_back(reinterpret_cast<PVOID>(0xF0));

	// ----------------- grenade SETUP
	player->grenade = std::make_shared<PLAYER_DATA>();
	player->grenade->offsets = std::make_shared<std::vector<PVOID>>();
	player->grenade->offsets->push_back(reinterpret_cast<PVOID>(0x144));

	// ----------------- rifle_ammo SETUP
	player->rifle_ammo = std::make_shared<PLAYER_DATA>();
	player->rifle_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->rifle_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x140));

	// ----------------- rifle_mag SETUP
	player->rifle_mag = std::make_shared<PLAYER_DATA>();
	player->rifle_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->rifle_mag->offsets->push_back(reinterpret_cast<PVOID>(0x11C));

	// ----------------- pistal_ammo SETUP
	player->pistal_ammo = std::make_shared<PLAYER_DATA>();
	player->pistal_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->pistal_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x12C));

	// ----------------- pistal_mag SETUP
	player->pistal_mag = std::make_shared<PLAYER_DATA>();
	player->pistal_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->pistal_mag->offsets->push_back(reinterpret_cast<PVOID>(0x108));

	// ----------------- sniper_ammo SETUP
	player->sniper_ammo = std::make_shared<PLAYER_DATA>();
	player->sniper_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->sniper_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x13C));

	// ----------------- sniper_mag SETUP
	player->sniper_mag = std::make_shared<PLAYER_DATA>();
	player->sniper_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->sniper_mag->offsets->push_back(reinterpret_cast<PVOID>(0x118));

	// ----------------- shotgun_ammo SETUP
	player->shotgun_ammo = std::make_shared<PLAYER_DATA>();
	player->shotgun_ammo->offsets = std::make_shared<std::vector<PVOID>>();
	player->shotgun_ammo->offsets->push_back(reinterpret_cast<PVOID>(0x134));

	// ----------------- shotgun_mag SETUP
	player->shotgun_mag = std::make_shared<PLAYER_DATA>();
	player->shotgun_mag->offsets = std::make_shared<std::vector<PVOID>>();
	player->shotgun_mag->offsets->push_back(reinterpret_cast<PVOID>(0x110));
}


BOOL init_player_dynamic_address(IN HANDLE hProcess, IN PVOID modulebase_address, IN OUT std::shared_ptr<PLAYER> player)
{

	// Get dynamic local player address
	player->local_player->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0x0017E0A8);
	std::cout << "[+] Dynamic LocalPlayer address: " << player->local_player->address << std::endl;

	// Get dynamic rapid_fire address
	player->rapid_fire->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0xC73EA);
	std::cout << "[+] Dynamic rapid_fire address: " << player->rapid_fire->address << std::endl;

	// Get dynamic rapid_fire address
	player->no_recoil->address = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(modulebase_address) + 0xC8E52);
	std::cout << "[+] Dynamic no_recoil address: " << player->no_recoil->address << std::endl;

	// Find dynamic health address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->health->offsets, &player->health->address))
	{
		std::cout << "[!] FindDMAAddy with health failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}

	// Find dynamic armor address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->armor->offsets, &player->armor->address))
	{
		std::cout << "[!] FindDMAAddy with armor failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}

	// Find dynamic grenade address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->grenade->offsets, &player->grenade->address))
	{
		std::cout << "[!] FindDMAAddy with grenade failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}

	// Find dynamic rifle_ammo address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->rifle_ammo->offsets, &player->rifle_ammo->address))
	{
		std::cout << "[!] FindDMAAddy with rifle_ammo failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}


	// Find dynamic rifle_mag address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->rifle_mag->offsets, &player->rifle_mag->address))
	{
		std::cout << "[!] FindDMAAddy with rifle_mag failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}

	// Find dynamic pistal_ammo address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->pistal_ammo->offsets, &player->pistal_ammo->address))
	{
		std::cout << "[!] FindDMAAddy with pistal_ammo failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}

	// Find dynamic pistal_mag address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->pistal_mag->offsets, &player->pistal_mag->address))
	{
		std::cout << "[!] FindDMAAddy with pistal_mag failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}

	// Find dynamic sniper_ammo address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->sniper_ammo->offsets, &player->sniper_ammo->address))
	{
		std::cout << "[!] FindDMAAddy with sniper_ammo failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}


	// Find dynamic sniper_mag address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->sniper_mag->offsets, &player->sniper_mag->address))
	{
		std::cout << "[!] FindDMAAddy with sniper_mag failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}

	// Find dynamic shotgun_ammo address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->shotgun_ammo->offsets, &player->shotgun_ammo->address))
	{
		std::cout << "[!] FindDMAAddy with shotgun_ammo failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}


	// Find dynamic shotgun_mag address
	if (!FindDMAAddy(hProcess, player->local_player->address, *player->shotgun_mag->offsets, &player->shotgun_mag->address))
	{
		std::cout << "[!] FindDMAAddy with shotgun_mag failed with error code: " << GetLastError() << std::endl;
		system("pause");
		return FALSE;
	}

	return TRUE;
}