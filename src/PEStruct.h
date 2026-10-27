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
	WORD e_magic;//magic number DOSͷ���              00h
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
	DWORD Signature;		//����PE��־��Ϣ 		    00h         ����Ч��PE�ļ���ֵ�� 00 00 45 50

	/*ӳ���ļ�ͷ PE�ļ��Ļ�����Ϣ
	IMAGE_FILE_HEADER ��ʼ*/
	WORD  Machine;		//								04h	
	WORD  NumberOfSections;	//							06h		//pe�ļ������������
	DWORD TimeDateStamp;//								08h		//�ļ�����ʱ���,ָ���pe�ļ����ɵ�ʱ��,����ֵ�Ǵ�1969��12��31��16:00:00����������.
	DWORD PointerToSymbolTable;//						0ch		//Coff���Է��ű���ƫ�Ƶ�ַ.
	DWORD NumberOfSymbols;//							10h		//Coff���ű��з��ŵĸ���. ������ǰ������release�汾�ĳ�������0.
	WORD  SizeOfOptionalHeader;//IMAGE_OPTON_HEADER��С 14h		//IMAGE_OPTIONAL_HEADER32�ṹ�Ĵ�С(�������ֽ�).
	WORD  Characteristics;//							16h		//���������pe�ļ���һЩ������Ϣ,�����Ƿ��ִ��,�Ƿ���һ����̬���ӿ��
};

 //IMAGE_OPTIONAL_HEADERS
 struct stPE_ExtHeader
 {
	 /*_IMAGE_OPTIONAL_HEADER��ʼ*/
	 // Standard fields
	 //Magic������ǿ�ִ���ļ���Rom��������ͨ��ִ�г��� �����һ��Ŀ�ִ�г�������010Bh �����PE32+ ��64λ�� 020Bh
	 WORD    Magic;//									18h		//����,32λpe�ļ���Ϊ010bh
	 BYTE    MajorLinkerVersion;//						1ah		//���������汾��
	 BYTE    MinorLinkerVersion;//						1bh		//���������汾��
	 DWORD   SizeOfCode;//								1ch		//������ܴ�С
	 DWORD   SizeOfInitializedData;//					20h		//�ѳ�ʼ�����ݶ��ܴ�С
	 DWORD   SizeOfUninitializedData;//					24h		//δ��ʼ�����ݶ��ܴ�С
	 DWORD   AddressOfEntryPoint;//						28h		//����ִ����ڵ�ַ(RVA)
	 DWORD   BaseOfCode;//								2ch		//�������ʼ��ַ(RVA)
	 DWORD   BaseOfData;//								30h		//���ݶ���ʼ��ַ(RVA)
	
	 // NT additional fields.
	 DWORD   ImageBase;//								34h		//����Ĭ�ϵ�װ����ʼ��ַ
	 DWORD   SectionAlignment;//						38h		//�ڴ�������Ķ��뵥λ
	 DWORD   FileAlignment;//							3ch		//�ļ�������Ķ��뵥λ
	 WORD    MajorOperatingSystemVersion;//				40h		//�������ϵͳ���汾��
	 WORD    MinorOperatingSystemVersion;//				42h		//�������ϵͳ���汾��
	 WORD    MajorImageVersion;//						44h		//�Զ������汾��
	 WORD    MinorImageVersion;//						46h		//�Զ��帱�汾��
	 WORD    MajorSubsystemVersion;//					48h		//������ϵͳ���汾��
	 WORD    MinorSubsystemVersion;//					4ah		//������ϵͳ���汾��
	 DWORD   Win32VersionValue;//						4ch		//����0
	 DWORD   SizeOfImage;//								50h		//pe�ļ����ڴ��е�ӳ���ܴ�С
	 DWORD   SizeOfHeaders;//							54h		//��pe�ļ���ʼ���ڱ�(�����ڱ�)���ܴ�С
	 DWORD   CheckSum;//								58h		//pe�ļ�CRCУ���
	 WORD    Subsystem;//								5ch		//�û�����ʹ�õ���ϵͳ����
	 WORD    DllCharacteristics;//						5eh		//Ϊ0
	 DWORD   SizeOfStackReserve;//						60h		//Ϊ�̵߳�ջ��ʼ�����������ڴ��Ĭ��ֵ
	 DWORD   SizeOfStackCommit;//						64h		//Ϊ�̵߳�ջ��ʼ�ύ�������ڴ�Ĵ�С
	 DWORD   SizeOfHeapReserve;//						68h		//Ϊ���̵Ķѱ����������ڴ�Ĵ�С
	 DWORD   SizeOfHeapCommit;//						6ch		//Ϊ���̵Ķѳ�ʼ�ύ�������ڴ�Ĵ�С
	 DWORD   LoaderFlags;	//							70h		//Ϊ0	
	 DWORD   NumberOfRvaAndSizes;//						74h		//����Ŀ¼�ṹ���������,��Ϊ 00000010h
	 IMAGE_DATA_DIRECTORY DataDirectory[16];		//78h	
	 /*_IMAGE_OPTIONAL_HEADER����*/
 };

 struct stSECTION_HEADER
 {
	  BYTE    Name[IMAGE_SIZEOF_SHORT_NAME]; //			00h			����,8���ֽڳ� 
	  union {
		 DWORD   PhysicalAddress; //					08h			obj�ļ���,���ε�ʵ�ʵ�ַ
		 DWORD   VirtualSize;    //									exe��dll�ļ����������ļ��ж���ǰ�Ĵ�С
	 } Misc;
	  DWORD   VirtualAddress;         //				0ch			���RVA(��������ַ)  
	  DWORD   SizeOfRawData;          //				10h			���ļ��ж����Ĵ�С 
	  DWORD   PointerToRawData;       //                14h			���ļ��е�ƫ�� 
	  DWORD   PointerToRelocations;   //				18h			�ض�λ��ƫ��(obj�ļ���ʹ��)
	  DWORD   PointerToLinenumbers;   // 				1ch			�кű���ƫ��(������) 
	  WORD    NumberOfRelocations;    //				1eh			�ض�λ����Ŀ(obj�ļ���ʹ��)
	  WORD    NumberOfLinenumbers;    //				20h			�кű����кŵ���Ŀ
	  DWORD   Characteristics;        //				24h			������
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