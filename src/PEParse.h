/******************************************************************* 
 *  File Nmae  : PEParse.h
 *  Description: File Parser class declaration
 *   
 *  Version	:1.0 
 *  author	:Zephyr 
 *  Date	:2017-05-30 
 ******************************************************************/

#ifndef PE_PARSE_H
#define PE_PARSE_H

#include "stdafx.h"
#include <vector>
#include "PEStruct.h"

using namespace std;

class PEParse{

public:
	PEParse();
	~PEParse();
	BOOL SetParseFileName(CString *fileName);
	BOOL IsValidPE();
	BOOL ParseStart();
	BOOL ParseImageNTHeaders();
	BOOL ParseImageOptionHeaders();
	BOOL ParseSectionHeader();
	stMS_DOS *GetDosHeader();
	stPE_HEADER *GetPeHeader();
	stPE_ExtHeader *GetExtPeHeader();
	vector<stSECTION_HEADER> *GetSectionHeader();
private:
	stMS_DOS m_stMS_DOS;
	stPE_HEADER m_stPeHeader;
	stPE_ExtHeader m_stExtPeHeader;
	vector<stSECTION_HEADER> m_vctSectionHeader;
	CString m_fileName;
	FILE *m_pFile;
};

#endif
