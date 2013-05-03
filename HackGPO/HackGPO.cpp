// HackGPO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "Wtypes.h"
#include "InitGuid.h"
#include "gpedit.h"
#include <stdio.h>


int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr = CoInitialize(0);
	hr=S_OK;

	
	IGroupPolicyObject* p = NULL;

	hr = CoCreateInstance(CLSID_GroupPolicyObject, NULL,
		CLSCTX_INPROC_SERVER, IID_IGroupPolicyObject,
		(LPVOID*)&p);

	if (SUCCEEDED(hr))
	{
		DWORD dwSection = GPO_SECTION_USER;
		DWORD dwSection2 = GPO_SECTION_MACHINE;
		HKEY hGPOSectionKey = NULL;
		HKEY hGPOSectionKey2 = NULL;
		HKEY hSettingKey;
		HKEY hSettingKey2;
		LSTATUS rStatus;
		 DWORD dwData;

		hr = 0;
		hr = p->OpenLocalMachineGPO( GPO_OPEN_LOAD_REGISTRY);
		hr = p->GetRegistryKey(dwSection, &hGPOSectionKey);
		hr = p->GetRegistryKey(dwSection2, &hGPOSectionKey2);
		BOOL bCreate = FALSE;
		BOOL bCreate2 = FALSE;
		if( RegOpenKeyEx( hGPOSectionKey, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_WRITE, &hSettingKey) != ERROR_SUCCESS )
		{
			rStatus = RegCreateKeyEx(
				hGPOSectionKey,
				L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,
				KEY_WRITE,
				NULL,
				&hSettingKey,
				NULL );
			bCreate = TRUE;
		}
		DWORD dwType = 0;
		DWORD cbType = sizeof( dwData );

		if( !bCreate )
		{
//rStatus = RegQueryValueEx(hGPOSectionKey,L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\EnableProfileQuota",NULL,&dwType,(BYTE *)(&dwData),&cbType);
			rStatus = RegGetValue(hGPOSectionKey,
				L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"EnableProfileQuota", RRF_RT_ANY, &dwType, (BYTE *)(&dwData), &cbType);
			if( rStatus != ERROR_SUCCESS ) dwData = 0;
			else RegDeleteValue( hSettingKey, L"EnableProfileQuota");
			rStatus = RegSetValueEx(hSettingKey, L"**del.EnableProfileQuota", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));

			rStatus = RegGetValue(hGPOSectionKey,
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"ProfileQuotaMessage", RRF_RT_ANY, &dwType, (BYTE *)(&dwData), &cbType);
			if( rStatus != ERROR_SUCCESS ) dwData = 0;
			else RegDeleteValue( hSettingKey, L"ProfileQuotaMessage");
			rStatus = RegSetValueEx(hSettingKey, L"**del.ProfileQuotaMessage", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));

			rStatus = RegGetValue(hGPOSectionKey,
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"MaxProfileSize", RRF_RT_ANY, &dwType, (BYTE *)(&dwData), &cbType);
			if( rStatus != ERROR_SUCCESS ) dwData = 0;
			else RegDeleteValue( hSettingKey, L"MaxProfileSize");
			rStatus = RegSetValueEx(hSettingKey, L"**del.MaxProfileSize", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));

			rStatus = RegGetValue(hGPOSectionKey,
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"IncludeRegInProQuota", RRF_RT_ANY, &dwType, (BYTE *)(&dwData), &cbType);
			if( rStatus != ERROR_SUCCESS ) dwData = 0;
			else RegDeleteValue( hSettingKey, L"IncludeRegInProQuota");
			rStatus = RegSetValueEx(hSettingKey, L"**del.IncludeRegInProQuota", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));

			rStatus = RegGetValue(hGPOSectionKey,
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"WarnUser", RRF_RT_ANY, &dwType, (BYTE *)(&dwData), &cbType);
			if( rStatus != ERROR_SUCCESS ) dwData = 0;
			else RegDeleteValue( hSettingKey, L"WarnUser");
			rStatus = RegSetValueEx(hSettingKey, L"**del.WarnUser", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));

			rStatus = RegGetValue(hGPOSectionKey,
			L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"WarnUserTimeout", RRF_RT_ANY, &dwType, (BYTE *)(&dwData), &cbType);
			if( rStatus != ERROR_SUCCESS ) dwData = 0;
			else RegDeleteValue( hSettingKey, L"WarnUserTimeout");
			rStatus = RegSetValueEx(hSettingKey, L"**del.WarnUserTimeout", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));
		}
		else

		{
			dwData = 0;
			rStatus = RegSetValueEx(hSettingKey, L"**del.EnableProfileQuota", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));
			rStatus = RegSetValueEx(hSettingKey, L"**del.ProfileQuotaMessage", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));
			rStatus = RegSetValueEx(hSettingKey, L"**del.MaxProfileSize", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));
			rStatus = RegSetValueEx(hSettingKey, L"**del.IncludeRegInProQuota", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));
			rStatus = RegSetValueEx(hSettingKey, L"**del.WarnUser", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));
			rStatus = RegSetValueEx(hSettingKey, L"**del.WarnUserTimeout", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));
		}

		if( RegOpenKeyEx( hGPOSectionKey2, L"Software\\Policies\\Microsoft\\Windows\\System", 0, KEY_WRITE, &hSettingKey2) != ERROR_SUCCESS )
		{
			rStatus = RegCreateKeyEx(
				hGPOSectionKey2,
				L"Software\\Policies\\Microsoft\\Windows\\System",
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,
				KEY_WRITE,
				NULL,
				&hSettingKey2,
				NULL );
			bCreate2 = TRUE;
		}
		if (!bCreate2)
		{
			rStatus = RegGetValue(hGPOSectionKey2,
			L"Software\\Policies\\Microsoft\\Windows\\System", L"DeleteRoamingCache", RRF_RT_ANY, &dwType, (BYTE *)(&dwData), &cbType);
			if( rStatus != ERROR_SUCCESS ) dwData = 0;
			else RegDeleteValue( hSettingKey2, L"DeleteRoamingCache");
			rStatus = RegSetValueEx(hSettingKey2, L"**del.DeleteRoamingCache", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));

		}
		else
		{
				dwData = 0;
			rStatus = RegSetValueEx(hSettingKey2, L"**del.DeleteRoamingCache", NULL, REG_DWORD, (BYTE *)(&dwData), sizeof(DWORD));
		}
		

		rStatus = RegCloseKey(hSettingKey);
		rStatus = RegCloseKey(hSettingKey2);
		GUID RegistryId = REGISTRY_EXTENSION_GUID;

		GUID ThisAdminToolGuid =
		{
			0x0F6B957E,
			0x509E,
			0x11D1,
			{0xA7, 0xCC, 0x00, 0x00, 0xF8, 0x75, 0x71, 0xE3}
		};

		rStatus = RegCloseKey(hGPOSectionKey);
		rStatus = RegCloseKey(hGPOSectionKey2);
		printf("%s \n", rStatus);
		hr = p->Save(
			FALSE,
			TRUE,
			&RegistryId,
			&ThisAdminToolGuid );
				hr = p->Save(
			TRUE,
			TRUE,
			&RegistryId,
			&ThisAdminToolGuid );
		hr = p->Release();
	}

	return hr;
}





