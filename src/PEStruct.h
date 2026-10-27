/******************************************************************* 
 *  File Nmae  : PEStruct.h
 *  Description: PE file structure definition
 *   
 *  Version	:1.0 
 *  author	:Zephyr 
 *  Date	:2017-05-30 
 ******************************************************************/
#ifndef PESTRUCT_H_
#define PESTRUCT_H_

// IMAGE_DOS_HEADER(MS_DOS)
struct   stMS_DOS
{
	WORD e_magic;//magic number DOS                    00h
	WORD e_cblp; // Bytes on last page of file		   02h
	WORD e_cp;	//pages in file						   04h
	WORD e_crlc;// Relocations						   06h
	WORD e_cparhdr;// Size of header in paragraphs	   08h
	WORD e_minalloc;// Minimum extra paragraphs needed 0ah
	WORD e_maxalloc;// Maximum extra paragraphs needed 0ch
	WORD e_ss;	//  Initial (relative) SS value        0eh
	WORD e_sp;	//  Initial SPvalue					   10h
	WORD e_csum;//check sum							   12h
	WORD e_ip; //Initial IP value					   14h
	WORD e_cs;// Initial (relative) CS value		   16h
	WORD e_lfarlc;// File address of relocation table  18h
	WORD e_ovno;  // Overlay number					   1ah
	WORD e_res[4];// Reserved words					   1ch
	WORD e_oemid;// OEM identifier (for e_oeminfo)	   24h
	WORD e_oeminfo;//OEM information; e_oemid specific 26h
	WORD e_res2[10];// Reserved words				   28h	
	long e_lfanew;	//File address of new exe header   3ch
};

//IMAGE_NT_HEADERS 
 struct stPE_HEADER
{
	DWORD Signature;

	/* IMAGE_FILE_HEADER */
	WORD  Machine;		//								04h	
	WORD  NumberOfSections;	//							06h
	DWORD TimeDateStamp;//								08h
	DWORD PointerToSymbolTable;//						0ch
	DWORD NumberOfSymbols;//							10h
	WORD  SizeOfOptionalHeader;//IMAGE_OPTON_HEADER     14h		//IMAGE_OPTIONAL_HEADER32
	WORD  Characteristics;//							16h
};

 //IMAGE_OPTIONAL_HEADERS
 struct stPE_ExtHeader
 {
	 /*_IMAGE_OPTIONAL_HEADER */
	 // Standard fields
	
	 WORD    Magic;//									18h
	 BYTE    MajorLinkerVersion;//						1ah
	 BYTE    MinorLinkerVersion;//						1bh
	 DWORD   SizeOfCode;//								1ch
	 DWORD   SizeOfInitializedData;//					20h
	 DWORD   SizeOfUninitializedData;//					24h
	 DWORD   AddressOfEntryPoint;//						28h
	 DWORD   BaseOfCode;//								2ch
	 DWORD   BaseOfData;//								30h
	
	 // NT additional fields.
	 DWORD   ImageBase;//								34h
	 DWORD   SectionAlignment;//						38h
	 DWORD   FileAlignment;//							3ch
	 WORD    MajorOperatingSystemVersion;//				40h
	 WORD    MinorOperatingSystemVersion;//				42h
	 WORD    MajorImageVersion;//						44h
	 WORD    MinorImageVersion;//						46h
	 WORD    MajorSubsystemVersion;//					48h
	 WORD    MinorSubsystemVersion;//					4ah
	 DWORD   Win32VersionValue;//						4ch
	 DWORD   SizeOfImage;//								50h
	 DWORD   SizeOfHeaders;//							54h
	 DWORD   CheckSum;//								58h
	 WORD    Subsystem;//								5ch
	 WORD    DllCharacteristics;//						5eh
	 DWORD   SizeOfStackReserve;//						60h
	 DWORD   SizeOfStackCommit;//						64h
	 DWORD   SizeOfHeapReserve;//						68h
	 DWORD   SizeOfHeapCommit;//						6ch
	 DWORD   LoaderFlags;	//							70h
	 DWORD   NumberOfRvaAndSizes;//						74h
	 IMAGE_DATA_DIRECTORY DataDirectory[16];		//78h	
	 /*_IMAGE_OPTIONAL_HEADER */
 };

 struct stSECTION_HEADER
 {
	  BYTE    Name[IMAGE_SIZEOF_SHORT_NAME]; //			00h
	  union {
		 DWORD   PhysicalAddress; //					08h
		 DWORD   VirtualSize;    //
	 } Misc;
	  DWORD   VirtualAddress;         //				0ch
	  DWORD   SizeOfRawData;          //				10h
	  DWORD   PointerToRawData;       //                14h
	  DWORD   PointerToRelocations;   //				18h
	  DWORD   PointerToLinenumbers;   // 				1ch
	  WORD    NumberOfRelocations;    //				1eh
	  WORD    NumberOfLinenumbers;    //				20h
	  DWORD   Characteristics;        //				24h
 };

 struct stIMAGE_IMPORT_DESCRIPTOR 
 {
	 union {
		 DWORD   Characteristics;    // 0 for terminating null import descriptor
		 DWORD   OriginalFirstThunk; // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
	 };
	 DWORD   TimeDateStamp;          // 0 if not bound,
	 // -1 if bound, and real date\time stamp
	 //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
	 // O.W. date/time stamp of DLL bound to (Old BIND)

	 DWORD   ForwarderChain;         // -1 if no forwarders
	 DWORD   Name;
	 DWORD   FirstThunk;             // RVA to IAT (if bound this IAT has actual addresses)
 } ; 

#endif
