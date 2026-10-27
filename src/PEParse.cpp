/******************************************************************* 
 *  File Nmae  : PEParse.cpp
 *  Description: File Parser class implement
 *   
 *  Version	:1.0 
 *  author	:Zephyr 
 *  Date	:2017-05-30 
 ******************************************************************/

#include "StdAfx.h"
#include <Windows.h>
#include "PEParse.h"

PEParse::PEParse()
{
	m_pFile = NULL;
	m_fileName = "";
	memset(&m_stMS_DOS, 0, sizeof(stMS_DOS));
	memset(&m_stPeHeader, 0, sizeof(stPE_HEADER));
	memset(&m_stExtPeHeader, 0, sizeof(stPE_ExtHeader));
	m_vctSectionHeader.clear();
}

PEParse::~PEParse()
{
	m_fileName = "";
	if(NULL == m_pFile){
		fclose(m_pFile);
		m_pFile = NULL;
	}
	if(false == m_vctSectionHeader.empty()){
		m_vctSectionHeader.clear();
	}
}

BOOL PEParse::SetParseFileName(CString *fileName)
{
	if(NULL == fileName){
		return FALSE;
	}
	m_fileName = *fileName;

	return (TRUE);
}

/** 
 *  Description: whether a standard PE file. 
 */
BOOL PEParse::IsValidPE()
{
	fread_s(&m_stMS_DOS.e_magic, sizeof(DWORD), sizeof(DWORD), 1, m_pFile);
	
	if(m_stMS_DOS.e_magic != IMAGE_DOS_SIGNATURE)
	{
		return FALSE;
	}

	return (TRUE);
}

/** 
 *  Description: start to parse the file. 
 */
BOOL PEParse::ParseStart()
{
	_wfopen_s(&m_pFile, m_fileName.GetBuffer(0), L"r+");
	if(FALSE == IsValidPE()){
		return FALSE;
	}

	if(FALSE == ParseImageNTHeaders()){
		return FALSE;
	}

	if(FALSE == ParseImageOptionHeaders()){
		return FALSE;
	}

	if(FALSE == ParseSectionHeader()){
		return FALSE;
	}

	return TRUE;
}

/** 
 *  Description: Parse IMAGE_NT_HEADERS structure 
 */
BOOL PEParse::ParseImageNTHeaders()
{
	fseek(m_pFile, 0x3c, SEEK_SET);
	fread_s(&m_stMS_DOS.e_lfanew, sizeof(DWORD), sizeof(DWORD), 1, m_pFile);
	if(0 == m_stMS_DOS.e_lfanew){
		return FALSE;
	}

	fseek(m_pFile, m_stMS_DOS.e_lfanew, SEEK_SET);
	fread(&m_stPeHeader, sizeof(stPE_HEADER), 1, m_pFile);
	if(m_stPeHeader.Signature != IMAGE_NT_SIGNATURE){
		return FALSE;
	}
	return TRUE;
}

/** 
 *  Description: Parse IMAGE_OPTIONAL_HEADERS structure 
 */
BOOL PEParse::ParseImageOptionHeaders()
{
	DWORD location = 0;
	
	fread(&m_stExtPeHeader,sizeof(stPE_ExtHeader), 1, m_pFile);
	if(m_stExtPeHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC){
		return FALSE;
	}

	location = m_stMS_DOS.e_lfanew + 0x78;
	fseek(m_pFile, location, SEEK_SET);

	//ExportDirectory
	fread(&m_stExtPeHeader.DataDirectory[0].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[0].Size, sizeof(DWORD), 1, m_pFile);

	//ImportDirectory
	fread(&m_stExtPeHeader.DataDirectory[1].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[1].Size,sizeof(DWORD), 1, m_pFile);

	//ResourceDirectory
	fread(&m_stExtPeHeader.DataDirectory[2].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[2].Size,sizeof(DWORD), 1, m_pFile);

	//ExceptionDirectory
	fread(&m_stExtPeHeader.DataDirectory[3].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[3].Size,sizeof(DWORD), 1, m_pFile);

	//SecurityDirectory
	fread(&m_stExtPeHeader.DataDirectory[4].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[4].Size,sizeof(DWORD), 1, m_pFile);

	//Base Relocation table
	fread(&m_stExtPeHeader.DataDirectory[5].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[5].Size,sizeof(DWORD), 1, m_pFile);

	//DebugDirectory
	fread(&m_stExtPeHeader.DataDirectory[6].VirtualAddress,sizeof(DWORD),1,m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[6].Size,sizeof(DWORD),1,m_pFile);

	//ArchitetureSpecificData
	fread(&m_stExtPeHeader.DataDirectory[7].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[7].Size,sizeof(DWORD), 1, m_pFile);
	
	//GlobalPtr
	fread(&m_stExtPeHeader.DataDirectory[8].VirtualAddress,sizeof(DWORD),1,m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[8].Size,sizeof(DWORD),1,m_pFile);

	//TLSDirectory
	fread(&m_stExtPeHeader.DataDirectory[9].VirtualAddress,sizeof(DWORD),1,m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[9].Size,sizeof(DWORD),1,m_pFile);
	
	//LoadConfigationDirectory
	fread(&m_stExtPeHeader.DataDirectory[10].VirtualAddress,sizeof(DWORD), 1 ,m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[10].Size,sizeof(DWORD), 1, m_pFile);

	//BoundImport
	fread(&m_stExtPeHeader.DataDirectory[11].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[11].Size,sizeof(DWORD), 1, m_pFile);

	//ImportAddressTable
	fread(&m_stExtPeHeader.DataDirectory[12].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[12].Size,sizeof(DWORD), 1, m_pFile);

	//DelayImportDescriptor
	fread(&m_stExtPeHeader.DataDirectory[13].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[13].Size,sizeof(DWORD), 1, m_pFile);

	//CLIHeader
	fread(&m_stExtPeHeader.DataDirectory[14].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[14].Size,sizeof(DWORD), 1, m_pFile);

	//Reserved
	fread(&m_stExtPeHeader.DataDirectory[15].VirtualAddress,sizeof(DWORD), 1, m_pFile);
	fread(&m_stExtPeHeader.DataDirectory[15].Size,sizeof(DWORD), 1, m_pFile);

	return TRUE;
}

/** 
 *  Description: Parse IMAGE_SECTION_HEADER structure 
 */
BOOL PEParse::ParseSectionHeader()
{
	DWORD location = 0;

	location = m_stMS_DOS.e_lfanew + 0x78;
	
	fseek(m_pFile, location, SEEK_SET);
	for (WORD i=0;i<m_stPeHeader.NumberOfSections;i++)
	{
		stSECTION_HEADER m_stSectionHeader;
		fread(&m_stSectionHeader, sizeof(stSECTION_HEADER), 1, m_pFile);
		m_vctSectionHeader.push_back(m_stSectionHeader);

		location += sizeof(stSECTION_HEADER);
		fseek(m_pFile, location, SEEK_SET);
		memset(&m_stSectionHeader, 0, sizeof(stSECTION_HEADER));
	}

	return TRUE;
}

stMS_DOS *PEParse::GetDosHeader()
{
	return &m_stMS_DOS;
}

stPE_HEADER *PEParse::GetPeHeader()
{
	return &m_stPeHeader;
}

stPE_ExtHeader *PEParse::GetExtPeHeader()
{
	return &m_stExtPeHeader;
}

vector<stSECTION_HEADER> *PEParse::GetSectionHeader()
{
	return &m_vctSectionHeader;
}
