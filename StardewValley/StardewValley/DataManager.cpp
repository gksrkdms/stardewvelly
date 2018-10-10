#include "stdafx.h"
#include "DataManager.h"



HRESULT DataManager::init()
{
	return S_OK;
}

void DataManager::release()
{
}

void DataManager::txtSave(const char * saveFileName, vector<string> vecStr)
{
	char str[128];// = { 'h', 'e', 'l', 'l', 'o' };
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vecStr), 126);

	// ���� ���� (���� txt ������ ���������)
	HANDLE hFile;
	hFile = CreateFile(saveFileName,	// ���̺��� ���� ��� / �����̸�
		GENERIC_WRITE,			// ���� ��� ����
		0,						// ���� ���� ��� ���� (0) : ���� ����
								// FILE_SHARE_DELETE : ���� ���� ��û�� ����
		NULL,					// ���� ���� �ɼ�
		CREATE_ALWAYS,			// CREATE_ALWAYS : ���ο� ���� ����, ������ �̸��� ������ ������ �����
								// CREATE_NEW : ���ο� ���� ����
								// OPEN_EXISTING : ������ �����ϸ� ����, ������ �����ڵ� ����
		FILE_ATTRIBUTE_NORMAL,	// FILE_ATTRIBUTE_NORMAL : �ٸ� �Ӽ��� ����
								// FILE_ATTRIBUTE_READONLY : �б� ���� ����
								// FILE_ATTRIBUTE_HIDDEN : ���� ���� ����
		NULL);

	// ���Ͽ� ������ ����
	WriteFile(hFile, str, 128, &write, NULL);

	// �� �� ���� �ڵ��� ����
	CloseHandle(hFile);
}

// string�� ���ҷ� ���� vector => �ϳ��� ���ڿ�
char * DataManager::vectorArrayCombine(vector<string> vecArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vecArray.size(); i++)
	{
		strncat_s(str, 128, vecArray[i].c_str(), 126);
		if (i + 1 < vecArray.size())
			strcat_s(str, ",");
	}

	return str;
}

vector<string> DataManager::txtLoad(const char * loadFileName)
{
	char str[128];
	DWORD read;

	HANDLE hFile;
	hFile = CreateFile(loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(hFile, str, 128, &read, NULL);

	CloseHandle(hFile);

	return charArraySeparation(str);
}

// �ϳ��� ���ڿ� => string�� ���ҷ� ���� vector
vector<string> DataManager::charArraySeparation(char charArray[])
{
	vector<string> vecStr;
	const char* separator = ",";
	char* token;
	char* temp;

	token = strtok_s(charArray, separator, &temp);
	vecStr.push_back(token);

	while ((token = strtok_s(NULL, separator, &temp)) != NULL)
	{
		vecStr.push_back(token);
	}

	return vecStr;
}


void DataManager::saveMap(LPCSTR szfileName, tagTile* tile, int x, int y)
{
	//char szFilter[] = "MapSave (*.map) | All File(*.*)|*,*||";

	DWORD write;
	HANDLE hFile;
	hFile = CreateFile(szfileName,	// ���̺��� ���� ��� / �����̸�
		GENERIC_WRITE,			// ���� ��� ����
		0,						// ���� ���� ��� ���� (0) : ���� ����
								// FILE_SHARE_DELETE : ���� ���� ��û�� ����
		NULL,					// ���� ���� �ɼ�
		CREATE_ALWAYS,			// CREATE_ALWAYS : ���ο� ���� ����, ������ �̸��� ������ ������ �����
								// CREATE_NEW : ���ο� ���� ����
								// OPEN_EXISTING : ������ �����ϸ� ����, ������ �����ڵ� ����
		FILE_ATTRIBUTE_NORMAL,	// FILE_ATTRIBUTE_NORMAL : �ٸ� �Ӽ��� ����
								// FILE_ATTRIBUTE_READONLY : �б� ���� ����
								// FILE_ATTRIBUTE_HIDDEN : ���� ���� ����
		NULL);

	// ���Ͽ� ������ ����
	WriteFile(hFile, tile, sizeof(tagTile) *x *y, &write, NULL);

	// �� �� ���� �ڵ��� ����
	CloseHandle(hFile);
}

void DataManager::saveFile(tagTile tile, int x, int y)
{
	//OPENFILENAME ofn;
	//ZeroMemory(&ofn, sizeof(OPENFILENAME));
	//ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner = g_hWnd;
	//ofn.lpstrFilter = _T("MAP Files(*.map)\0*.map\0All Files (*.*)\0*.*\0");
	//ofn.lpstrFile = szFileName;
	//ofn.nMaxFile = nFileNameMaxLen;
	//ofn.lpstrDefExt = "map";
	////ofn.nFilterIndex = 1;
	////ofn.lpstrFileTitle = szFileName;
	////ofn.nMaxFileTitle = 0;
	////ofn.lpstrInitialDir = NULL;
	//ofn.Flags = OFN_OVERWRITEPROMPT;
	//GetSaveFileName(&ofn);

	////if (0 != GetOpenFileName(&OFN))
	////{
	////}

	//saveMap(szFileName, tile, x, y);
	////MessageBox(g_hWnd, TEXT("dd"), TEXT("ddkkk"), MB_OK);
}

void DataManager::loadFile(HWND hwnd, tagTile tile, int x, int y)
{
	//memset(&OFN, 0, sizeof(OPENFILENAME));
	//OFN.lStructSize = sizeof(OPENFILENAME);
	//OFN.hwndOwner = hwnd;
	//OFN.lpstrFilter = "Map Files(*.map)\0*.map\0All Files (*.*)\0*.*\0";
	//OFN.lpstrFile = szFileName;
	//OFN.nMaxFile = nFileNameMaxLen;

	//if (0 != GetOpenFileName(&OFN))
	//{
	//	SetWindowText(hEditFileToBeOpened, OFN.lpstrFile);
	//	loadMap(OFN.lpstrFile, tile,x,y);
	//}
}

void DataManager::loadMap(LPCSTR szfileName, tagTile* tile, int x, int y)
{
	char str[128];
	DWORD read;

	HANDLE hFile;
	hFile = CreateFile(szfileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(hFile, tile, sizeof(tagTile) *x *y, &read, NULL);

	CloseHandle(hFile);
}


DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}
