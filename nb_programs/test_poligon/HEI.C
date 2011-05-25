/*
**	HEI.C - Platform independent code for communicating with Host Automation Products
**			line of ethernet modules.
** 
**	Copyright (C) - 1996-1997 Host Automation Products, Inc.
**
*/
#include "windows.h"
#include "defs.h"
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include "hei.h"

void (*pAsyncPacketHandler)(HEIDevice *pDevice, BYTE *pResponse, int ResponseLen) = 0;


/* Interface functions */
int HEIIOpen(void);
int HEIIClose(void);
int HEIIOpenDevice(HEITransport *pTransport, HEIDevice *pDevice);
int HEIICloseDevice(HEIDevice *pDevice);
int HEIIOpenTransport(HEITransport *pTransport);
int HEIICloseTransport(HEITransport *pTransport);
int HEIIReceivePacket(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize);
int HEIISendPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize);
DWORD HEIIGetCounter(void);

#define DEBUG_FILE 0

#if DEBUG_FILE
#include <stdio.h>
#include <stdarg.h>
#include "windows.h"

FILE *pOutFile=NULL;

void DebugString(char  *String, ...)
	{
	char  Buffer[200];

	va_list ap;

	va_start(ap, String);

	wvsprintf(Buffer, String, ap);

   	//OutputDebugString(Buffer);
   	pOutFile = fopen("c:\\heiout.txt", "a+");

	if (pOutFile)
		{
		fputs("\n", pOutFile);
		fputs(Buffer, pOutFile);
		fclose(pOutFile);
		}

	va_end(ap);
	}


#endif


__declspec(dllexport) int HEISetAsyncHandler(void (*pFun)(HEIDevice *pDevice, BYTE *pResponse, int ResponseLen))
	{
	pAsyncPacketHandler = pFun;
	return 0;
	}

__declspec(dllexport) int HEIGetAsyncHandler(void (**pFun)(HEIDevice *pDevice, BYTE *pResponse, int ResponseLen))
	{
	*pFun = pAsyncPacketHandler;
	return 0;
	}


/*
** This macro will return the difference between a start time (in milliseconds) and an end time (also in milliseconds).
** It handles the fact that a DWORD millisecond indicator will wrap every 49.XXX days.
*/
#define TimeDiff(StartTime, EndTime)  (((DWORD)EndTime > (DWORD)StartTime) ? ((DWORD)EndTime - (DWORD)StartTime) : ((DWORD)EndTime + ((DWORD)ULONG_MAX - (DWORD)StartTime) + 1))

#define WordDiff(Start, End)  (((WORD)End > (WORD)Start) ? ((WORD)End - (WORD)Start) : ((WORD)End + ((WORD)0xFFFF - (WORD)Start) + 1))
         
#ifdef NOCRC
int DoCRC = 0;
#else         
int DoCRC = 1;
#endif

#define EXTRA_TIME_FOR_SETUP_DATA 10

int DoEncrypt(Encryption *pEncrypt, BYTE *ptr, WORD Num);
__declspec(dllexport) int _SendPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize, BYTE *pResponse, int *pResponseSize, BOOL WaitForResponse, BOOL ReturnWarnings);
   

#if defined(SUPERVISOR)
int PrepareSupervisorPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize);
#endif /* #if defined(SUPERVISOR) */


WORD CalcCRC(WORD    icrc, BYTE   *icp, WORD    icnt);
  
int InsertCRC(BYTE *pBuffer, WORD Len)
	{
	WORD *pWord = (WORD *) (pBuffer+5);
	
	if (DoCRC)
		{
		(*pWord) = CalcCRC(0, (BYTE *) (pBuffer+PACKET_HEADER_SIZE), (WORD) (Len - PACKET_HEADER_SIZE));
		}
	else
		{
		(*pWord) = 0;
		}
		
	return 0;
	}

BOOL CRCCorrect(BYTE *pBuffer, WORD Len)
	{
	if (!DoCRC)
		return TRUE;
	else if (Len < PACKET_HEADER_SIZE)
		return FALSE;
	else
		{
		WORD *pCRC = (WORD *) (pBuffer+5);
		WORD CRC;

		if (!*pCRC)
			return TRUE;

		CRC = CalcCRC(0, (BYTE *) (pBuffer+PACKET_HEADER_SIZE), (WORD) (Len - PACKET_HEADER_SIZE));

		return (CRC == (*pCRC));
		}
	}


/* int GetResponse(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize, WORD ExtraTime=0, BOOL ProcessTimeout=TRUE, BOOL CheckAppVal=TRUE)*/
__declspec(dllexport) int GetResponse(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize, WORD ExtraTime, BOOL ProcessTimeout, BOOL CheckAppVal)
	{
	unsigned short ThisAppVal = pDevice->LastAppVal;
	DWORD DeviceTimeout = pDevice->Timeout;
	int SavedSize = *pResponseSize;
	int Error;

	DWORD Timeout = DeviceTimeout + ExtraTime;
	DWORD StartTime = HEIIGetCounter();

	while (1) 
		{
		*pResponseSize = SavedSize;

		Error = HEIIReceivePacket(pDevice, pResponse, pResponseSize);
		
		if (!Error && (*pResponseSize))
			{
			/* We have a packet to look at. */
			/* Check the App Val. */
			WORD *pWord = (WORD *) (pResponse+3);
					
			if (*pWord == ThisAppVal || !ThisAppVal || !CheckAppVal)
				{
				int Retval;
				
				if (!CheckAppVal)
					pDevice->LastAppVal = *pWord;

				Retval = 0;

				if (CRCCorrect((BYTE *) pResponse, (WORD) *pResponseSize))
					{
					/* We have our response! */
					}
				else 
					{
					pDevice->BadCRCCount++;
					Retval =  HEIE_CRC_MISMATCH;
					}
							
				return Retval;
				}
			else
				{
				if (pAsyncPacketHandler)
					{
					(*pAsyncPacketHandler)(pDevice, pResponse, *pResponseSize);
					}

				pDevice->LatePacketCount++; 
				continue;
				}
			}
		else if (Error && Error != HEIE_NO_RESPONSE)
			{
			return Error;
			}
		else if (!ProcessTimeout)
			{
			/* No more packets to look at. */
			return HEIE_NO_RESPONSE;
			}
			
		if (ProcessTimeout && (TimeDiff(StartTime, HEIIGetCounter()) >= Timeout))
			{
			/* Timeout! */
			break;
			}
		}
			
	*pResponseSize = 0;
	return HEIE_TIMEOUT;
	}


static unsigned short AppVal = 1;

__declspec(dllexport) int HEIGetResponse(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize, BOOL CheckAppVal)
	{
	int Retval;
	
#if DEBUG_FILE
	DebugString("In GetResponse %u", AppVal);
#endif	

	Retval = GetResponse(pDevice, pResponse, pResponseSize, 0, FALSE, CheckAppVal);
	
#if DEBUG_FILE
	DebugString("Leaving GetResponse %u -> %d (0x%X)", AppVal, Retval, Retval);
#endif	

	return Retval;
	}
	
int WriteERMCommandData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE *pData, WORD NumBytes, WORD Offset)
	{
	return HEIWriteERMData(pDevice, Base, Slot, DATA_COMMAND, pData, NumBytes, Offset);
	}

int ReadERMCommandData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE *pData, WORD NumBytes, WORD Offset)
	{
	return HEIReadERMData(pDevice, Base, Slot, DATA_COMMAND, pData, NumBytes, Offset);
	}


#if HEIAPIVERSION>=3
int _SendProxyPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize, BYTE *pResponse, int *pResponseSize, BOOL WaitForResponse, BOOL ReturnWarnings)
	{
	int Retval = 0;
	WORD DataOffset = pDevice->DataOffset;
	WORD SubTotal = PacketSize - DataOffset;
	BYTE *pCmd = pPacket+PacketSize-SubTotal;

	// Disable proxying.
	pDevice->UseProxy = FALSE;

	Retval = WriteERMCommandData(pDevice, pDevice->ProxyBase, pDevice->ProxySlot, pCmd, SubTotal, 0);

	if (Retval)
		{
	//	printf("\nError %d (0x%X) from WriteERMCommandData", Retval, Retval);
		}
	else
		{
		BYTE Extra[10];
		WORD ExtraLen;
		WORD *pWord;

		pWord = (WORD *) &Extra[0];

		*pWord++ = pDevice->ProxyDevNum;
		*pWord++ = 0;		// CmdOffset
		*pWord++ = SubTotal;		// CmdLength
		*pWord++ = 0;		// RspOffset;
		*pWord++ = 0x800; // RspLength
		ExtraLen = 10;

		Retval = HEIDoERMCommandEx(pDevice, pDevice->ProxyBase, pDevice->ProxySlot, COMMAND_PROCESS_COMMAND_BUFFER, Extra, ExtraLen);

		if (Retval)
			{
	//		printf("Error %d (0x%X) from call to WPLCDoERMCommandEx", Retval, Retval);
			}
		else
			{
			// Read response from command buffer.
			BYTE ResponseBuffer[4];
			Retval = ReadERMCommandData(pDevice, pDevice->ProxyBase, pDevice->ProxySlot, ResponseBuffer, 4, 0);

			if (Retval)
				{
	//			printf("\nError %d (0x%X) from ReadERMCommandData", Retval, Retval);
				}
			else
				{
				WORD *pError = (WORD *) &ResponseBuffer[0];
				WORD *pLen = (WORD *) &ResponseBuffer[2];

				if (*pError)
					{
	//				printf("\nCommand Error: %d  Len: %d", *pError, *pLen);
					}
				else
					{
					Retval = ReadERMCommandData(pDevice, pDevice->ProxyBase, pDevice->ProxySlot, pResponse+PACKET_HEADER_SIZE, *pLen, 4);

					if (Retval)
						{
	//					printf("\nError %d (0x%X) from ReadERMCommandData", Retval, Retval);
						}
					else
						{
						// Fix pResponse[0] - pResponse[PACKET_HEADER_SIZE-1]
						(*pResponseSize) = (*pLen) + PACKET_HEADER_SIZE;
						}
					}
				}
			}
		}

	// Reenable proxying.
	pDevice->UseProxy = TRUE;
	return Retval;
	}
#endif

	
/*int SendPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize, BYTE *pResponse, int *pResponseSize, BOOL WaitForResponse=TRUE, BOOL ReturnWarnings=FALSE)*/
__declspec(dllexport) int _SendPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize, BYTE *pResponse, int *pResponseSize, BOOL WaitForResponse, BOOL ReturnWarnings)
	{
#if HEIAPIVERSION>=3
	if (pDevice->UseProxy == TRUE)
		{
		// Proxy this command to the device.
		//printf("\nUse proxy.");
		return _SendProxyPacket(pDevice, pPacket, PacketSize, pResponse, pResponseSize, WaitForResponse, ReturnWarnings);
		}
#endif
		{
		BYTE *ptr;
		WORD *pWord;
		unsigned short ThisAppVal;
		unsigned short *pWordAppVal;
		BYTE *pBegin = pPacket;
		WORD PreHeaderBytes = pDevice->DataOffset - PACKET_HEADER_SIZE;
		WORD Retry;

		if (pDevice->UseAddressedBroadcast)
			PreHeaderBytes -= 7;
				
		pPacket += PreHeaderBytes;
				
		ptr = pPacket;
				
		if (pDevice->UseAddressedBroadcast)
			{
			pPacket[PACKET_HEADER_SIZE] = FUN_ADDRESSED_BROADCAST;
			memcpy(&pPacket[PACKET_HEADER_SIZE+1], pDevice->ENetAddress, 6);
			}
			
		*ptr++ = 'H';
		*ptr++ = 'A';
		*ptr   = 'P';
				
		/* Calculate CRC */
		InsertCRC(pPacket, (WORD) (PacketSize-PreHeaderBytes));
			
		/* Insert the number of bytes which were checksumed. */
		pWord = (WORD *) (pPacket+7);
			
		*pWord = (WORD) PacketSize - PreHeaderBytes - PACKET_HEADER_SIZE;	/* This is the bytes to follow/checksum */
			
		/* Do encryption (if required) */
		if (pDevice->_pTransport->Encrypt.Algorithm)
			DoEncrypt(&pDevice->_pTransport->Encrypt, pPacket+5, (WORD) (PacketSize-5-PreHeaderBytes));
			
		pWordAppVal = (unsigned short *) (pPacket+3);
				
					
	#if defined(SUPERVISOR)
		PrepareSupervisorPacket(pDevice, pPacket, PacketSize);
	#endif	/* #if defined(SUPERVISOR) */

		for (Retry = 0; Retry<=pDevice->Retrys; Retry++)
   			{
			int ResponseSize = *pResponseSize;
			int Error;
					
			ThisAppVal = AppVal++;
			pDevice->LastAppVal = ThisAppVal;
					
			if (!AppVal)
				AppVal++;
			
			if (Retry)
				pDevice->RetryCount++;
						
			/* Insert the app value. */
			*pWordAppVal = ThisAppVal;
			
			Error = HEIISendPacket(pDevice, pBegin, PacketSize);
					
			if (Error)
				{
				*pResponseSize = 0;
				return Error;
				}
					
			if (!WaitForResponse)
				{
				*pResponseSize = 0;
				return HEIE_NO_RESPONSE;
				}

			Error = GetResponse(pDevice, pResponse, &ResponseSize, 0, TRUE, TRUE);

			if (!Error)
				{
				*pResponseSize = ResponseSize;

				if (Retry != 0 && ReturnWarnings)
					return HEIW_RETRY;

				return 0;   /* Success! */
				}
			else if (Error != HEIE_TIMEOUT)
				return Error;
			}
			
		*pResponseSize = 0;
		return HEIE_TIMEOUT;
		}
	}


__declspec(dllexport) int SendPacketTwoResponses(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize, BYTE *pResponse, int *pResponseSize, 
									BOOL WaitForResponse, BOOL ReturnWarnings, WORD Bytes2Verify, BYTE *pVerifyData, 
									WORD ExtraTime, BOOL ProcessTimeout, BOOL CheckAppVal)
	{
	WORD SaveRetryCount = pDevice->RetryCount;
	WORD SaveRetrys = pDevice->Retrys;
	int SaveResponseSize = *pResponseSize;

#if HEIAPIVERSION>=3
	if (pDevice->UseProxy == TRUE)
		{
		// Proxy this command to the device.
		//printf("\nUse proxy.");
		return _SendProxyPacket(pDevice, pPacket, PacketSize, pResponse, pResponseSize, WaitForResponse, ReturnWarnings);
		}
#endif

	while (TRUE)
		{
		int Error = _SendPacket(pDevice, pPacket, PacketSize,pResponse, pResponseSize, WaitForResponse, ReturnWarnings);

		if (Error && !(Error & HEIW_FIRST_WARNING))
			{
			/* Restore retrys value */
			pDevice->Retrys = SaveRetrys;
			return Error;
			}

		/* Check and make sure we got an ack. */
		if (Bytes2Verify)
			{
			BYTE *pRet = (pResponse+PACKET_HEADER_SIZE);
	
			while (Bytes2Verify)
				{
				if (*pRet++ != *pVerifyData++)
					{
					/* Restore retrys value */
					pDevice->Retrys = SaveRetrys;
					return HEIE_INVALID_RESPONSE;
					}

				Bytes2Verify--;
				}
			}

		/* Restore size of response buffer. */
		*pResponseSize = SaveResponseSize;

		Error = GetResponse(pDevice, pResponse, pResponseSize, ExtraTime, ProcessTimeout, CheckAppVal);

		if (Error == HEIE_TIMEOUT)
			{
			WORD TotalRetrys;

			/* Perform a retry */
			pDevice->RetryCount++;

			/* See how many retrys we have already done. */
			TotalRetrys = WordDiff(SaveRetryCount, pDevice->RetryCount);

			if (TotalRetrys >= SaveRetrys)
				{
				/* Restore retrys value */
				pDevice->Retrys = SaveRetrys;

				return Error;
				}

			/* Prepare to go again. */
			*pResponseSize = SaveResponseSize;

			/* Adjust number of retrys left to do. */
			pDevice->Retrys = SaveRetrys - TotalRetrys;
			}
		else
			{
			/* Restore retrys value */
			pDevice->Retrys = SaveRetrys;

			if (!Error && pDevice->RetryCount != SaveRetryCount)
				Error = HEIW_RETRY;

			if (Error)
				return Error;

			return HEIE_NULL;
			}
		}
	}


/* Transport Stuff */
__declspec(dllexport) int HEIOpenTransport(HEITransport *pTransport, WORD Ver, ENetAddress *pSourceAddress)
/* __declspec(dllexport) int HEIOpenTransport(HEITransport *pTransport, WORD Ver, DWORD NetworkAddress)*/
	{
	int Retval;
	
#if DEBUG_FILE
	DebugString("In HEIOpenTransport");
#endif
	if (HEIAPIVERSION != Ver)
		return HEIE_VER_MISMATCH;

	if (!pTransport)
		return HEIE_NULL_TRANSPORT;
		
	pTransport->Encrypt.Algorithm = HEIEN_NONE;
	/*pTransport->NetworkAddress = NetworkAddress;*/
	pTransport->pSourceAddress = pSourceAddress;
	
	Retval = HEIIOpenTransport(pTransport);
	
#if DEBUG_FILE
	DebugString("Leaving HEIOpenTransport", Retval);
#endif
	
	return Retval;
	}
	
	
__declspec(dllexport) int HEICloseTransport(HEITransport *pTransport)
	{
	if (!pTransport)
		return HEIE_NULL_TRANSPORT;
		
	return HEIICloseTransport(pTransport);
	}

__declspec(dllexport) int HEIOpenDevice
		(
		HEITransport *pTransport, 
		HEIDevice *pDevice, 
		WORD Ver, 
		WORD iTimeout, 
		WORD iRetrys, 
		BOOL UseBroadcast
		)
	{
	int Retval;
	
#if 0
		{
		char Buffer[200];

		wsprintf(Buffer, "Timeout: %d  Retrys: %d  UseBroadCast: %d", iTimeout, iRetrys, UseBroadcast);

		MessageBox(NULL, Buffer, "HEIOpenDevice", 0);
		}
#endif


#if DEBUG_FILE
	DebugString("In HEIOpenDevice");
#endif
	
	if (HEIAPIVERSION != Ver)
		return HEIE_VER_MISMATCH;

	if (!pTransport)
		return HEIE_NULL_TRANSPORT;
		
	if (!pDevice)
		return HEIE_INVALID_DEVICE;

	pDevice->_dwParam				= 0;
	pDevice->Timeout				= iTimeout;
	pDevice->Retrys				= iRetrys;
	pDevice->UseAddressedBroadcast	= UseBroadcast;
	pDevice->UseBroadcast		= UseBroadcast;
	pDevice->pData					= 0;
	pDevice->SizeOfData			= 0;
	pDevice->DataOffset			= PACKET_HEADER_SIZE;
	pDevice->pBuffer				= 0;
	pDevice->RetryCount			= 0;
	pDevice->BadCRCCount			= 0;
	pDevice->LatePacketCount	= 0; 
	pDevice->ParallelPackets	= FALSE;
	pDevice->_pTransport = pTransport;

#if HEIAPIVERSION==3
	pDevice->UseProxy = 0;
	pDevice->ProxyBase = 0;
	pDevice->ProxySlot = 0;
	pDevice->ProxyDevNum = 0;
	memset(pDevice->Reserved, 0, sizeof(pDevice->Reserved));		/* Reserved bytes, set to zero */
#endif

	if (pDevice->UseAddressedBroadcast)
		pDevice->DataOffset += 7;

	Retval = HEIIOpenDevice(pTransport, pDevice);
	
#if DEBUG_FILE
	DebugString("Leaving HEIOpenDevice", Retval);
#endif
	return Retval;
	}

__declspec(dllexport) int HEICloseDevice(HEIDevice *pDevice)
	{
	int Retval = HEIE_NULL;

	if (!pDevice)
		return HEIE_INVALID_DEVICE;
	
	if (pDevice->_pTransport)
		{
		Retval = HEIICloseDevice(pDevice);
		pDevice->_pTransport = (HEITransport *) NULL;
		}
	
	return Retval;
	}


__declspec(dllexport) int HEIOpen(WORD Ver)
	{
	if (HEIAPIVERSION != Ver)
		return HEIE_VER_MISMATCH;
	
	return HEIIOpen();
	}

__declspec(dllexport) int HEIClose()
	{
	return HEIIClose();
	}


int DoEncrypt(Encryption *pEncrypt, BYTE *ptr, WORD Num)
	{
	switch (pEncrypt->Algorithm)
		{
		case 1:		/* Private key encryption (XOR) */
			{
			BYTE *keyptr = pEncrypt->Key;
			WORD x;
			
			for (x=0; x<Num; x++)
				{
				*ptr++ ^= *keyptr++;
				
				if (!*keyptr)
					keyptr = pEncrypt->Key;
				}
				
			return 0;
			}
			
		default:
			return -1;
		}
	}

int OpenQueryableDevice(HEITransport *pTransport, HEIDevice *pDevice, WORD Ver)
	{
	/* Open a device which I can use for broadcasting a packet. */
	int RetVal = HEIOpenDevice(pTransport, pDevice, Ver, 20, 0, TRUE);

	if (!RetVal)
		{
		pDevice->UseAddressedBroadcast = FALSE;    /* Don't want to use 'Addressed' Broadcast, just Broadcast! */
		pDevice->DataOffset -= 7;  /* We are not using addressed broadcast. */
		pDevice->wParam = 0;
		}

	return RetVal;
	}
	
	
DWORD QueryTimeout = 600;

__declspec(dllexport) DWORD HEISetQueryTimeout(DWORD NewTimeout)
	{
	DWORD Save = QueryTimeout;

	QueryTimeout = NewTimeout;

	return Save;
	}

__declspec(dllexport) DWORD HEIGetQueryTimeout()
	{
	return QueryTimeout;
	}


int DoQuery(HEITransport *pTransport, HEIDevice *pDevice, HEIDevice *pDevices, WORD *pNumDevices, WORD Ver, BYTE *pBuffer, WORD BufferSize)
	{
	BYTE RetBuffer[600];
	int ResponseSize = sizeof(RetBuffer);
	BYTE FromAddress[20];					
	int Error;
	WORD Count = 0;
	DWORD Timeout = QueryTimeout;
	DWORD StartTime;
	int Retval;

	pDevice->pData = FromAddress;
	pDevice->SizeOfData = sizeof(FromAddress);

	Error = _SendPacket(pDevice, pBuffer, BufferSize, RetBuffer, &ResponseSize, TRUE, FALSE);

	StartTime = HEIIGetCounter();
	Retval = HEIE_NULL;

	while (1) 
		{
		switch ((WORD) Error)
			{
			case HEIE_NULL:
				{
				/* No Error, so process packet. */
				if (RetBuffer[0] == 'H' && RetBuffer[1] == 'A' && (RetBuffer[2] == 'P' || RetBuffer[2] == 'A') &&
					RetBuffer[PACKET_HEADER_SIZE] == 0x55 &&
					(BYTE) RetBuffer[PACKET_HEADER_SIZE+1] == 0xAA)
					{
					if (Count < (*pNumDevices))
						{
						memcpy(pDevices[Count].Address.Raw, pDevice->pData, pDevice->SizeOfData);
						memcpy(pDevices[Count].ENetAddress, (char *) (RetBuffer+PACKET_HEADER_SIZE+2), 6);

						if (pTransport->Protocol == HEIP_IP)
							{
							if (RetBuffer[PACKET_HEADER_SIZE+8] == 1)
								pDevices[Count].Address.Raw[19] = 1; /* The modules IP address is not initialized. */
							else 
								pDevices[Count].Address.Raw[19] = 0;
							}

						Count++;
						}
					else
						{
						Count++;
						Retval = HEIE_BUFFER_TOO_SMALL;
						}
					}

				break;
				}

			case HEIE_TIMEOUT:
				break;
				
			case HEIW_RETRY:
				break;

			default:
				{
				/* Other error, so bail out. */
				pDevice->pData = 0;
				pDevice->SizeOfData = 0;
				return Error;
				}
			}

		if (TimeDiff(StartTime, HEIIGetCounter()) < Timeout)
			{
			ResponseSize = sizeof(RetBuffer);
			pDevice->SizeOfData = sizeof(FromAddress);
			Error = GetResponse(pDevice, RetBuffer, &ResponseSize, 0, TRUE, TRUE);
			}
		else
			break;
		}

	*pNumDevices = Count;
	pDevice->pData = 0;
	pDevice->SizeOfData = 0;
	return Retval;
	}	


__declspec(dllexport) int HEIQueryDevices(HEITransport *pTransport, HEIDevice *pDevices, WORD *pNumDevices, WORD Ver)
	{
	HEIDevice qDevice;
	WORD DataOffset;
	BYTE Buffer[100];
	WORD Total;
	int Retval;
	int Error;

	if (pTransport->Protocol == HEIP_SERIAL)
		{
		*pNumDevices = 0;
		return HEIE_NULL;
		}

	Error = OpenQueryableDevice(pTransport, &qDevice, Ver);
	
	if (Error)
		return Error;

	/* Build the buffer.		 */
	DataOffset = qDevice.DataOffset;

	Buffer[DataOffset] = FUN_POLLING_ALL;	 	/* This is the function code! */

	Total = DataOffset+1;

	Retval = DoQuery(pTransport, &qDevice, pDevices, pNumDevices, Ver, Buffer, Total);

	HEICloseDevice(&qDevice);
	
	return Retval;	
	}

__declspec(dllexport) int HEIQueryDeviceData(HEITransport *pTransport, HEIDevice *pDevices, WORD *pNumDevices, WORD Ver, WORD DataType, BYTE *pData, WORD SizeofData)
	{
	HEIDevice qDevice;
	WORD DataOffset;
	BYTE Buffer[600];
	WORD *pWord;
	WORD Total;
	int Retval;
	
	int Error = OpenQueryableDevice(pTransport, &qDevice, Ver);
	
	if (Error)
		return Error;

	/* Build the buffer.		 */
	DataOffset = qDevice.DataOffset;

	Buffer[DataOffset] = FUN_QUERY_SETUP_DATA;	 	/* This is the function code! */
	Buffer[DataOffset+1] = 0;

	pWord = (WORD *) (Buffer+DataOffset+2);
		 
	if (SizeofData > 512)
		 SizeofData = 512;

	*pWord++ = DataType;
	*pWord = SizeofData;
	
	memcpy(Buffer+DataOffset+6, pData, SizeofData);

	Total = qDevice.DataOffset+6+SizeofData;

	Retval = DoQuery(pTransport, &qDevice, pDevices, pNumDevices, Ver, Buffer, Total);

	HEICloseDevice(&qDevice);
	
	return Retval;	
	}


/* SUPPORT INFORMATION */
__declspec(dllexport) int HEIReadSupportInfo(HEIDevice *pDevice, BYTE *pSupportInfo, WORD SizeOfSupportInfo)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int NumBytes;
	int Error;
	int Retval;

	Buffer[DataOffset] = (BYTE) FUN_READ_SUPPORT_INFO;	 		/* This is the function code! */

	Total = DataOffset+1;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		NumBytes -= PACKET_HEADER_SIZE;

		if ((WORD) NumBytes > SizeOfSupportInfo)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = SizeOfSupportInfo;
			}

		memcpy(pSupportInfo, RetBuffer+PACKET_HEADER_SIZE, NumBytes);
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}


/* VERSION INFORMATION */
__declspec(dllexport) int HEIReadVersionInfo(HEIDevice *pDevice, BYTE *pVerInfo, WORD SizeVerInfo)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = (BYTE) FUN_READ_VER_INFO;	 		/* This is the function code! */

	Total = DataOffset+1;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		NumBytes -= PACKET_HEADER_SIZE;

		if ((WORD) NumBytes > SizeVerInfo)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = SizeVerInfo;
			}

		memcpy(pVerInfo, RetBuffer+PACKET_HEADER_SIZE, NumBytes);
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}


/* BASE DEFINITION */
__declspec(dllexport) int HEIReadBaseDef(HEIDevice *pDevice, BYTE *pBaseDefInfo, WORD *pSizeOfBaseDefInfo)
	{
	BYTE Buffer[300];
	BYTE RetBuffer[1000];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_READ_BASE_DEF;	 		/* This is the function code! */

	Total = DataOffset+1;

	if (pBaseDefInfo && *pBaseDefInfo == 0xB1)
		{
		Buffer[DataOffset+1] = *pBaseDefInfo;
		Total++;
		}

	NumBytes = sizeof(RetBuffer);

	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		NumBytes -= PACKET_HEADER_SIZE;

		if ((WORD) NumBytes > *pSizeOfBaseDefInfo)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = *pSizeOfBaseDefInfo;
			}

		memcpy(pBaseDefInfo, RetBuffer+PACKET_HEADER_SIZE, NumBytes);
		(*pSizeOfBaseDefInfo) = NumBytes;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		(*pSizeOfBaseDefInfo) = 0;
		}

	return Retval;
	}

__declspec(dllexport) int HEIRescanBase(HEIDevice *pDevice, DWORD Flags, BYTE *pBaseDefInfo, WORD *pSizeOfBaseDefInfo)
	{
	BYTE Buffer[300];
	BYTE RetBuffer[1000];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;
	DWORD *pDWord;

	Buffer[DataOffset] = FUN_INIT_BASE_DEF;	 		/* This is the function code! */
	pDWord = (DWORD *) &Buffer[DataOffset+1];
	*pDWord = Flags;

	Total = DataOffset+5;

	NumBytes = sizeof(RetBuffer);

	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		NumBytes -= PACKET_HEADER_SIZE;

		if ((WORD) NumBytes > *pSizeOfBaseDefInfo)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = *pSizeOfBaseDefInfo;
			}

		memcpy(pBaseDefInfo, RetBuffer+PACKET_HEADER_SIZE, NumBytes);
		(*pSizeOfBaseDefInfo) = NumBytes;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		(*pSizeOfBaseDefInfo) = 0;
		}

	return Retval;
	}

__declspec(dllexport) int HEIInitBaseDef(HEIDevice *pDevice, BYTE *pBaseDefInfo, WORD *pSizeOfBaseDefInfo)
	{
	BYTE Buffer[300];
	BYTE RetBuffer[600];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_INIT_BASE_DEF;	 		/* This is the function code! */

	Total = DataOffset+1;

	NumBytes = sizeof(RetBuffer);

	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		NumBytes -= PACKET_HEADER_SIZE;

		if ((WORD) NumBytes > *pSizeOfBaseDefInfo)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = *pSizeOfBaseDefInfo;
			}

		memcpy(pBaseDefInfo, RetBuffer+PACKET_HEADER_SIZE, NumBytes);
		(*pSizeOfBaseDefInfo) = NumBytes;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		(*pSizeOfBaseDefInfo) = 0;
		}

	return Retval;
	}

__declspec(dllexport) int HEIWriteBaseDef(HEIDevice *pDevice, BYTE *pInputBaseDef, WORD SizeOfInputBaseDef, BYTE *pOutputBaseDef, WORD *pSizeOfOutputBaseDef)
	{
	BYTE Buffer[600];
	BYTE RetBuffer[600];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;
	WORD *pWord;

	Buffer[DataOffset] = FUN_WRITE_BASE_DEF;	 		/* This is the function code! */
	Buffer[DataOffset+1] = 0;
	
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord = SizeOfInputBaseDef;

	Total = DataOffset+4+SizeOfInputBaseDef;

	if (Total > sizeof(Buffer))
		{
		return HEIE_DATA_TOO_LARGE;
		}
	
	memcpy(Buffer+DataOffset+4, pInputBaseDef, SizeOfInputBaseDef);


	NumBytes = sizeof(RetBuffer);

	Error = SendPacketTwoResponses(pDevice, Buffer, Total, RetBuffer, &NumBytes, 
									TRUE, FALSE, 
									0, NULL, 
									30000, TRUE, TRUE);


#if 0
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;
		
	NumBytes = sizeof(RetBuffer);
	Error = GetResponse(pDevice, RetBuffer, &NumBytes, 30000, TRUE, TRUE);
#endif

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;
	
	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);
		
		if (*pInt)
			Retval = *pInt;
		else if (pOutputBaseDef)
			{
			NumBytes -= (PACKET_HEADER_SIZE+2);
	
			if ((WORD) NumBytes > *pSizeOfOutputBaseDef)
				{
				Retval = HEIE_BUFFER_TOO_SMALL;
				NumBytes = *pSizeOfOutputBaseDef;
				}
	
			memcpy(pOutputBaseDef, RetBuffer+PACKET_HEADER_SIZE+2, NumBytes);
			(*pSizeOfOutputBaseDef) = NumBytes;
			}
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		
		if (pOutputBaseDef && pSizeOfOutputBaseDef)
			(*pSizeOfOutputBaseDef) = 0;
		}

	return Retval;
	}

/* DEVICE DEFINITION */
__declspec(dllexport) int HEIReadDeviceDef(HEIDevice *pDevice, BYTE *pDeviceDefInfo, WORD SizeOfDeviceDefInfo)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = (BYTE) FUN_READ_DEVICE_INFO;	 		/* This is the function code! */

	Total = DataOffset+1;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;
   
	if (NumBytes)
		{
		NumBytes -= PACKET_HEADER_SIZE;

		if ((WORD) NumBytes > SizeOfDeviceDefInfo)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = SizeOfDeviceDefInfo;
			}

		memcpy(pDeviceDefInfo, RetBuffer+PACKET_HEADER_SIZE, NumBytes);
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}


/* SETUP */
__declspec(dllexport) int HEIReadSetupData(HEIDevice *pDevice, WORD SetupType, BYTE *pData, WORD *pSizeofData)
	{
	BYTE Buffer[100];
	BYTE RetBuffer[600];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;
	WORD *pWord;

	Buffer[DataOffset] = (BYTE) FUN_READ_SETUP_DATA;	 		/* This is the function code! */
	Buffer[DataOffset+1] = 0;

	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord = SetupType;

	Total = DataOffset+4;

	NumBytes = sizeof(RetBuffer);

	pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);

		NumBytes -= (PACKET_HEADER_SIZE+2);

		if ((WORD) NumBytes > *pSizeofData)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = *pSizeofData;
			}

		if (*pInt)
			Retval = *pInt;

		(*pSizeofData) = NumBytes;

		memcpy(pData, RetBuffer+PACKET_HEADER_SIZE+2, NumBytes);
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}

__declspec(dllexport) int HEIWriteSetupData(HEIDevice *pDevice, WORD SetupType, BYTE *pData, WORD SizeofData)
	{
	BYTE Buffer[600];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD *pWord;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = (BYTE) FUN_WRITE_SETUP_DATA;	 		/* This is the function code! */
	Buffer[DataOffset+1] = 0;

	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord = SetupType;

	Total = DataOffset+4+SizeofData;

	if (Total > sizeof(Buffer))
		{
#if 0
		BYTE Text[200];

		wsprintf(Text, "Total=%d  DataOffset=%d  SizeofData=%d  SizeofBuffer=%d",
			Total, DataOffset, SizeofData, sizeof(Buffer));
		MessageBox(NULL, Text, "HEIWriteSetupData", 0);
#endif
		return HEIE_DATA_TOO_LARGE;
		}

	memcpy(&Buffer[DataOffset+4], pData, SizeofData);

	NumBytes = sizeof(RetBuffer);
		
	pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;

	Error = SendPacketTwoResponses(pDevice, Buffer, Total, RetBuffer, &NumBytes, 
									TRUE, FALSE,
									0, NULL, 
									30000, TRUE, TRUE);

	pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;

#if 0
	pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;

	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	NumBytes = sizeof(RetBuffer);
	Error = GetResponse(pDevice, RetBuffer, &NumBytes, 30000, TRUE, TRUE);
#endif

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);

		if (*pInt)
			Retval = *pInt;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}

__declspec(dllexport) int HEIDeleteSetupData(HEIDevice *pDevice, WORD SetupType)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD *pWord;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = (BYTE) FUN_DELETE_SETUP_DATA;	 		/* This is the function code! */
	Buffer[DataOffset+1] = 0;

	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord = SetupType;

	Total = DataOffset+4;

	NumBytes = sizeof(RetBuffer);

	pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;

	Error = SendPacketTwoResponses(pDevice, Buffer, Total, RetBuffer, &NumBytes, 
									TRUE, FALSE,
									0, NULL, 
									30000, TRUE, TRUE);

	pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;
	
	
#if 0
	pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;

	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	NumBytes = sizeof(RetBuffer);

	Error = GetResponse(pDevice, RetBuffer, &NumBytes, 30000, TRUE, TRUE);
#endif

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);

		if (*pInt)
			Retval = *pInt;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}

__declspec(dllexport) int HEIEnumSetupData(HEIDevice *pDevice, WORD *pData, WORD *pSizeofDataInWords)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[600];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = (BYTE) FUN_ENUM_SETUP_DATA;	 		/* This is the function code! */

	Total = DataOffset+1;

	NumBytes = sizeof(RetBuffer);

	pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;
	
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		/*int NumWords; */
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);
		short int *pNumWords = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);

		if ((WORD) *pNumWords > *pSizeofDataInWords)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			*pNumWords = *pSizeofDataInWords;
			}

		if (*pInt)
			Retval = *pInt;

		(*pSizeofDataInWords) = *pNumWords;

		memcpy((char *) pData, (char *) (RetBuffer+PACKET_HEADER_SIZE+4), *pNumWords * 2);
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}



/* IO ACCESS */
__declspec(dllexport) int HEIReadIO(HEIDevice *pDevice, BYTE *pData, WORD *DataSize)
	{
	BYTE Buffer[100];
	BYTE RetBuffer[1200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;
	
	Buffer[DataOffset] = FUN_READ_IO; /* This is the function code! */

	Total = DataOffset+1;

	if (pData && *pData == 0xB1)
		{
		Buffer[DataOffset+1] = *pData;
		Total++;
		}

	NumBytes = sizeof(RetBuffer);
	//NumBytes = *DataSize;

	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, (pDevice->ParallelPackets) ? FALSE : TRUE, TRUE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) &RetBuffer[PACKET_HEADER_SIZE];

		NumBytes -= PACKET_HEADER_SIZE;
		NumBytes -= 2;

		if ((WORD) NumBytes > *DataSize)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = *DataSize;
			}

		if (*pInt)
			Retval = (*pInt) | 0x8000;

		memcpy(pData, RetBuffer+PACKET_HEADER_SIZE+2, NumBytes);
		(*DataSize) = NumBytes;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		(*DataSize) = 0;
		}

	return Retval;
	}


__declspec(dllexport) int HEIWriteIO(HEIDevice *pDevice, BYTE *pData, WORD SizeofData, BYTE *pReturnData, WORD *pSizeofReturnData)
	{
	BYTE Buffer[1200];
	BYTE RetBuffer[1200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_WRITE_IO;	 		/* This is the function code! */
	
	Total = DataOffset+1+SizeofData;

	if (Total > sizeof(Buffer))
		return HEIE_DATA_TOO_LARGE;

	memcpy(Buffer+DataOffset+1, pData, SizeofData);

	NumBytes = sizeof(RetBuffer);
	//NumBytes = *pSizeofReturnData;
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, (pDevice->ParallelPackets) ? FALSE : TRUE, TRUE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) &RetBuffer[PACKET_HEADER_SIZE];

		if (pReturnData && pSizeofReturnData)
			{
			NumBytes -= PACKET_HEADER_SIZE;
			NumBytes -= 2;

			if ((WORD) NumBytes > *pSizeofReturnData)
				{
				Retval = HEIE_BUFFER_TOO_SMALL;
				NumBytes = *pSizeofReturnData;
				}

			memcpy(pReturnData, RetBuffer+PACKET_HEADER_SIZE+2, NumBytes);
			(*pSizeofReturnData) = NumBytes;
			}

		if (*pInt)
			Retval = (*pInt) | 0x8000;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;

		if (pSizeofReturnData)
			(*pSizeofReturnData) = 0;
		}

	return Retval;
	}


__declspec(dllexport) int HEIWriteIONoRead(HEIDevice *pDevice, BYTE *pData, WORD SizeofData)
	{
	BYTE Buffer[1200];
	BYTE RetBuffer[1200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_WRITE_IO_NO_READ;	 		/* This is the function code! */
	
	Total = DataOffset+1+SizeofData;

	if (Total > sizeof(Buffer))
		return HEIE_DATA_TOO_LARGE;

	memcpy(Buffer+DataOffset+1, pData, SizeofData);

	NumBytes = sizeof(RetBuffer);
	//NumBytes = *pSizeofReturnData;
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, (pDevice->ParallelPackets) ? FALSE : TRUE, TRUE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) &RetBuffer[PACKET_HEADER_SIZE];

		if (*pInt)
			Retval = (*pInt) | 0x8000;
		}
	else
		Retval = HEIE_ZERO_BYTES_RECEIVED;

	return Retval;
	}


__declspec(dllexport) int HEIPetDevice(HEIDevice *pDevice)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int NumBytes;

	Buffer[DataOffset] = FUN_PET_LINK;
	Buffer[DataOffset+1] = 0;

	Total = DataOffset+2;

	NumBytes = sizeof(RetBuffer);

	return _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);
	}

__declspec(dllexport) int HEIReadEthernetStats(HEIDevice *pDevice, BYTE *pData, WORD *DataSize, BOOL Clear)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_READ_ETHERNET_STATS;	 	/* This is the function code! */
	Buffer[DataOffset+1] = 0;
	Buffer[DataOffset+2] = Clear ? 1 : 0;

	Total = DataOffset+3;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		NumBytes -= PACKET_HEADER_SIZE;

		if ((WORD) NumBytes > *DataSize)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = *DataSize;
			}

		memcpy(pData, RetBuffer+PACKET_HEADER_SIZE, NumBytes);
		(*DataSize) = NumBytes;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		(*DataSize) = 0;
		}

	return Retval;
	}


__declspec(dllexport) int HEIReadModuleStatus(HEIDevice *pDevice, BYTE *pData, WORD *DataSize, BOOL Reset)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[600];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_READ_MODULE_STATUS;	 	/* This is the function code! */

	if (pData && *pData == 0xB1)
		Buffer[DataOffset+1] = 1;
	else
		Buffer[DataOffset+1] = 0;

	Buffer[DataOffset+2] = Reset ? 1 : 0;

	Total = DataOffset+3;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) &RetBuffer[PACKET_HEADER_SIZE];

		NumBytes -= PACKET_HEADER_SIZE;
		NumBytes -= 2;

		if ((WORD) NumBytes > *DataSize)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = *DataSize;
			}

		if (*pInt)
			Retval = *pInt;

		memcpy(pData, RetBuffer+PACKET_HEADER_SIZE+2, NumBytes);
		(*DataSize) = NumBytes;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		(*DataSize) = 0;
		}

	return Retval;
	}
	
	
/* CCM STUFF */
#define CCM_READ			0x1E
#define CCM_WRITE			0x20
	
__declspec(dllexport) int HEICCMRequest(HEIDevice *pDevice, BOOL bWrite, BYTE DataType, WORD Address, WORD DataLen, BYTE *pData)
	{
	BYTE Buffer[320];
	BYTE RetBuffer[320];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;
	BYTE *pRet;
	short int *pError;
	BYTE VerifyData[2];
	
#if DEBUG_FILE
	DebugString("In HEICCMRequest %u", AppVal);
#endif		

	if(DataLen > 256)
		return HEIE_INVALID_REQUEST;
   
   /* Function */
	Buffer[DataOffset] = FUN_CCM_REQUEST;
	
	/* Unused */
	Buffer[DataOffset+1] = 0;

	/* Request Code. */
	Buffer[DataOffset+2] = 0x01;
	
	/* Direction */
	Buffer[DataOffset+3] = bWrite ? CCM_WRITE : CCM_READ;
	
	/* Length */
	Buffer[DataOffset+4] = (DataLen == 256) ? 0 : (BYTE)DataLen;
	
	/* LSB of Address */
	Buffer[DataOffset+5] = (BYTE) (Address & 0xFF);
	
	/* MSB of Address */
	Buffer[DataOffset+6] = (BYTE) ((Address>>8) & 0xFF);
	
	/* Data Type */
	Buffer[DataOffset+7] = DataType;

	Total = DataOffset+8;

	if (bWrite)	
		{
		/* We are writing. */
		memcpy(&Buffer[DataOffset+8], pData, DataLen);
		Total += DataLen;
		}

	NumBytes = sizeof(RetBuffer);


	VerifyData[0] = FUN_ACK;
	VerifyData[1] = FUN_CCM_REQUEST;
	Error = SendPacketTwoResponses(pDevice, Buffer, Total, RetBuffer, &NumBytes, 
									(pDevice->ParallelPackets) ? FALSE : TRUE, TRUE, 
									2, VerifyData, 
									0, TRUE, TRUE);

	if (Error == HEIE_INVALID_RESPONSE)
		{
		short int *pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);
#if DEBUG_FILE
		DebugString("Error %d (0x%X) from HEICCMRequest %u", *pError, *pError, AppVal);
#endif		
		return *pError;
		}


#if 0
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, (pDevice->ParallelPackets) ? FALSE : TRUE, TRUE);

	if (Error && !(Error & HEIW_FIRST_WARNING))
		{
#if DEBUG_FILE
		DebugString("Error %d (0x%X) from HEICCMRequest %u", Error, Error, AppVal);
#endif		
		return Error;
		}

	/* Check and make sure we got an ack. */
	pRet = (RetBuffer+PACKET_HEADER_SIZE);
	
	if (*pRet != FUN_ACK || (*(pRet+1) != FUN_CCM_REQUEST))
		{
		short int *pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);
#if DEBUG_FILE
		DebugString("Error %d (0x%X) from HEICCMRequest %u", *pError, *pError, AppVal);
#endif		
		return *pError;
		}

	NumBytes = sizeof(RetBuffer);
	Error = GetResponse(pDevice, RetBuffer, &NumBytes, 0, TRUE, TRUE);
#endif


	if (Error && !(Error & HEIW_FIRST_WARNING))
		{
#if DEBUG_FILE
		DebugString("Error %d (0x%X) from HEICCMRequest %u", Error, Error, AppVal);
#endif		
		return Error;
		}

	NumBytes -= PACKET_HEADER_SIZE;

	pRet = (RetBuffer + PACKET_HEADER_SIZE);

	if (*pRet != FUN_RESPONSE || *(pRet+1) != FUN_CCM_REQUEST)
		{
#if DEBUG_FILE
		Error = HEIE_INVALID_RESPONSE;
		DebugString("Error %d (0x%X) from HEICCMRequest %u", Error, Error, AppVal);
#endif		
		return HEIE_INVALID_RESPONSE;
		}
	
	pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);
	
	if (*pError)
		{
#if DEBUG_FILE
		DebugString("Error %d (0x%X) from HEICCMRequest %u", *pError, *pError, AppVal);
#endif		
		return *pError;
		}
		
	NumBytes -= 4;

	if(!bWrite && NumBytes != (int)DataLen)
		{
#if DEBUG_FILE
		Error = HEIE_INVALID_REQUEST;
		DebugString("Error %d (0x%X) from HEICCMRequest %u", Error, Error, AppVal);
#endif		
		return HEIE_INVALID_REQUEST;
		}
	
	memcpy(pData, RetBuffer+PACKET_HEADER_SIZE+4, DataLen);

#if DEBUG_FILE
	DebugString("Leaving HEICCMRequest %u", AppVal);
#endif		
	
	return HEIE_NULL;
	}


__declspec(dllexport) int HEIKSEQRequest(HEIDevice *pDevice, WORD DataLenIn, BYTE *pData, WORD *pDataLen)
	{
	BYTE Buffer[320];
	BYTE RetBuffer[320];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;
	BYTE *pRet;
	short int *pError;
	int Retval;
	BYTE VerifyData[2];

#if DEBUG_FILE
	DebugString("In HEIKSEQRequest %u", AppVal);
#endif		

	if(DataLenIn > 256)
		return HEIE_INVALID_REQUEST;

	/* Function */
	Buffer[DataOffset] = FUN_KSEQ_REQUEST;
	
	/* Unused */
	Buffer[DataOffset+1] = 0;

	/* Request Code. */
	Buffer[DataOffset+2] = (DataLenIn == 256) ? 0 : (BYTE)DataLenIn;
	
	/* Unused */
	Buffer[DataOffset+3] = 0;
	
	/* Copy task code data. */
	memcpy(&Buffer[DataOffset+4], pData, DataLenIn);

	Total = DataOffset+4+DataLenIn;

	NumBytes = sizeof(RetBuffer);


	VerifyData[0] = FUN_ACK;
	VerifyData[1] = FUN_KSEQ_REQUEST;
	Error = SendPacketTwoResponses(pDevice, Buffer, Total, RetBuffer, &NumBytes, 
									(pDevice->ParallelPackets) ? FALSE : TRUE, TRUE, 
									2, VerifyData, 
									0, TRUE, TRUE);

	if (Error == HEIE_INVALID_RESPONSE)
		{
		short int *pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);
		return *pError;
		}

#if 0
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, (pDevice->ParallelPackets) ? FALSE : TRUE, TRUE);

	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	/* Check and make sure we got an ack. */
	pRet = (RetBuffer+PACKET_HEADER_SIZE);
	
	if (*pRet != FUN_ACK || (*(pRet+1) != FUN_KSEQ_REQUEST))
		{
		short int *pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);
		return *pError;
		}

	NumBytes = sizeof(RetBuffer);
	Error = GetResponse(pDevice, RetBuffer, &NumBytes, 0, TRUE, TRUE);
#endif

	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;
	
	NumBytes -= PACKET_HEADER_SIZE;

	pRet = (RetBuffer + PACKET_HEADER_SIZE);

	if (*pRet != FUN_RESPONSE || *(pRet+1) != FUN_KSEQ_REQUEST)
		{
		return HEIE_INVALID_RESPONSE;
		}
	
	pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);
	
	if (*pError)
		return *pError;
		
	NumBytes -= 4;
	
	 Retval = HEIE_NULL;

	if ((WORD) NumBytes > *pDataLen)
		{
		Retval = HEIE_BUFFER_TOO_SMALL;
		NumBytes = *pDataLen;
		}
	
	memcpy(pData, RetBuffer+PACKET_HEADER_SIZE+4, NumBytes);
	*pDataLen = NumBytes;
	
#if DEBUG_FILE
	DebugString("Leaving HEIKSEQRequest", Retval);
#endif		
	
	return Retval;
	}

// Returns number of bytes not written.
__declspec(dllexport) int HEIWriteComm(HEIDevice *pDevice, WORD Num2Write, BYTE *pData)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	WORD *pWord;
	int Error;
	int NumBytes;

	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_WRITE_COMM;
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord = Num2Write;

	if (Num2Write > (sizeof(Buffer) - DataOffset - 4))
		return HEIE_DATA_TOO_LARGE;

	memcpy(Buffer+DataOffset+4, pData, Num2Write);

	Total = DataOffset+4+Num2Write;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}

__declspec(dllexport) int HEIReadComm(HEIDevice *pDevice, WORD *pNum2Read, BYTE *pData)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	WORD *pWord;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_READ_COMM;
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord = *pNum2Read;

	Total = DataOffset+4;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);
		short int *pNumReturned = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);

		if (*pInt)
			Retval = *pInt;

		(*pNum2Read) = *pNumReturned;

		memcpy(pData, RetBuffer+PACKET_HEADER_SIZE+4, *pNumReturned);
		}
	else
		Retval = HEIE_ZERO_BYTES_RECEIVED;

	return Retval;
	}

__declspec(dllexport) int HEIGetRXAvailable(HEIDevice *pDevice, WORD *pAvailable)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_RX_AVAILABLE;

	Total = DataOffset+2;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		{
		*pAvailable = *((WORD *) (RetBuffer+PACKET_HEADER_SIZE+2));
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}

__declspec(dllexport) int HEIFlushRXQueue(HEIDevice *pDevice)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_RX_FLUSH;

	Total = DataOffset+2;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}


__declspec(dllexport) int HEISetupSerialPort(HEIDevice *pDevice, SerialSetup *pSetup, BOOL WriteToFlash)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_SETUP;
	Buffer[DataOffset+2] = (BYTE) WriteToFlash;
	Buffer[DataOffset+3] = 0;

	memcpy(Buffer+DataOffset+4, pSetup, sizeof(SerialSetup));

	Total = DataOffset+4+sizeof(SerialSetup);

	NumBytes = sizeof(RetBuffer);

	if (WriteToFlash)
		{
		pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;

		Error = SendPacketTwoResponses(pDevice, Buffer, Total, RetBuffer, &NumBytes, 
										TRUE, FALSE,
										0, NULL, 
										30000, TRUE, TRUE);

		pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;
		}
	else
		{
		Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);
		}

	//if (Error) 
	//	return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

#if 0
	if (WriteToFlash)
		pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	if (WriteToFlash)
		pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;

	if (Error) return Error;

	if (WriteToFlash)
		{
		NumBytes = sizeof(RetBuffer);
		Error = GetResponse(pDevice, RetBuffer, &NumBytes, 30000, TRUE, TRUE);
		}
#endif

	if (NumBytes)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}
	
__declspec(dllexport) int HEIReadSerialPortSetup(HEIDevice *pDevice, SerialSetup *pSetup)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_READ_SETUP;
	Buffer[DataOffset+2] = 0;
	Buffer[DataOffset+3] = 0;

	Total = DataOffset+4;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		{
		// Copy data into user buffer.
		memcpy(pSetup, RetBuffer+PACKET_HEADER_SIZE, sizeof(SerialSetup));
		return 0;
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}
	

__declspec(dllexport) int HEIGetTXLeft(HEIDevice *pDevice, WORD *pLeft)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	//int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_TX_LEFT;

	Total = DataOffset+2;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	//Retval = Error;

	if (NumBytes)
		{
		*pLeft = *((WORD *) (RetBuffer+PACKET_HEADER_SIZE+2));
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}

/* PLC MEMORY STUFF */
__declspec(dllexport) int HEIReadMemory(HEIDevice *pDevice, WORD Type, DWORD Offset, WORD NumBytes, BYTE *pBuffer)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[600];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Num;
	WORD *pWord;
	DWORD *pDWord;

	Buffer[DataOffset] = FUN_READ_MEMORY;
	Buffer[DataOffset+1] = 0;
	
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord++ = Type;
	*pWord++ = NumBytes;
	pDWord = (DWORD *) &Buffer[DataOffset+6];
	*pDWord++ = Offset;

	Total = DataOffset+10;

	Num = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &Num, TRUE, FALSE);

	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	//if (Error) 
	//	return Error;

	if (Num)
		{
		short int *pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE);
		
		if (!((*pError) & 0x0FFF) || (*pError == HEIE_LENGTH_WARNING))
			{
			// Copy the memory.
			memcpy(pBuffer, RetBuffer+PACKET_HEADER_SIZE+2, NumBytes);
			}
		
		return *pError;
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
		
/*	return 0; */
	}
	
__declspec(dllexport) int HEIWriteMemory(HEIDevice *pDevice, WORD Type, DWORD Offset, WORD NumBytes, BYTE *pBuffer)
	{
	BYTE Buffer[600];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Num;
	WORD *pWord;
	DWORD *pDWord;

	if (NumBytes > 512)
		return HEIE_DATA_TOO_LARGE;

	Buffer[DataOffset] = FUN_WRITE_MEMORY;
	Buffer[DataOffset+1] = 0;
	
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord++ = Type;
	*pWord++ = NumBytes;
	pDWord = (DWORD *) &Buffer[DataOffset+6];
	*pDWord++ = Offset;
	
	memcpy(Buffer+DataOffset+10, pBuffer, NumBytes);

	Total = DataOffset+10+NumBytes;

	Num = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &Num, TRUE, FALSE);

	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;
	//if (Error) return Error;

	if (Num)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
		
	/* return 0; */
	}
	

__declspec(dllexport) int HEIAccessMemory(HEIDevice *pDevice, MemRef MemRefs[], WORD NumRefs)
	{
	WORD DataOffset = pDevice->DataOffset;
	BYTE Buffer[600];
	BYTE RetBuffer[600];
	BYTE *pSendData;
	WORD x;
	WORD *pWord;
	WORD ReadSize = 2 + 2;					// Returned error value is 2 bytes long
											// Returned num MemRefs is 2 bytes long
	WORD TotalSize = 4 + DataOffset;		// Header info is 4 bytes long
	int Num;
	int Error;

	Buffer[DataOffset] = FUN_ACCESS_MEMORY;
	Buffer[DataOffset+1] = 0;
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord = NumRefs;

	pSendData = &Buffer[DataOffset+4];

	for (x=0; x<NumRefs; x++)
		{
		memcpy(pSendData, &MemRefs[x], sizeof(MemRefDetail));
		TotalSize += sizeof(MemRefDetail);
		pSendData += sizeof(MemRefDetail);

		if (MemRefs[x].Detail.Direction == ACCESS_READ)
			{
			// Read request.
			ReadSize += (MemRefs[x].Detail.NumBytes + sizeof(MemRefDetail));
			}
		else if (MemRefs[x].Detail.Direction == ACCESS_WRITE)
			{
			// Write request.
			memcpy(pSendData, MemRefs[x].pBuffer, MemRefs[x].Detail.NumBytes);
			TotalSize += MemRefs[x].Detail.NumBytes;
			pSendData += MemRefs[x].Detail.NumBytes;
			}
		else
			{
			return HEIE_INVALID_REQUEST;
			}

		if ((TotalSize > sizeof(Buffer)) || (ReadSize > sizeof(RetBuffer)))
			{
			return HEIE_DATA_TOO_LARGE;
			}
		}

	// Ready to send.
	Num = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, TotalSize, RetBuffer, &Num, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (Num)
		{
		short int *pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE);
		short int *pNum = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);
		
		//if (!*pError && *pNum)
		if (!((*pError) & 0x0FFF) && *pNum)
			{
			// No errors, and we have some read requests returned.
			WORD x;
			MemRefDetail *pReturnDetail = (MemRefDetail *) (RetBuffer+PACKET_HEADER_SIZE+4);

			for (x=0; x<NumRefs; x++)
				{
				// Find a read request.
				if (MemRefs[x].Detail.Direction == ACCESS_READ)
					{
					// Read request; Make sure it matches.
					if (MemRefs[x].Detail.Type		== pReturnDetail->Type && 
						MemRefs[x].Detail.Offset	== pReturnDetail->Offset &&
						MemRefs[x].Detail.NumBytes	== pReturnDetail->NumBytes)
						{
						// Requests match, so copy data.
						BYTE *pData = (BYTE *) pReturnDetail;
						pData += sizeof(MemRefDetail);

						memcpy(MemRefs[x].pBuffer, pData, MemRefs[x].Detail.NumBytes);

						// Reset for next one.
						pData += MemRefs[x].Detail.NumBytes;
						pReturnDetail = (MemRefDetail *) pData;
						}
					else
						{
						// Requests don't match, so return error.
						return HEIE_INVALID_RESPONSE;
						}
					}
				}
			}
		
		return *pError;
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}


__declspec(dllexport) int HEIENumMemory(HEIDevice *pDevice, WORD *pSizeofDataInTypes, MemoryTypeDef *pData)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[600];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = (BYTE) FUN_ENUM_MEMORY;	 		/* This is the function code! */

	Total = DataOffset+1;

	NumBytes = sizeof(RetBuffer);

	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	/* Check for error and not warning. */
	//if (Error)
	//	return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		/*int NumTypes; */
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);
		short int *pNumTypes = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);

		if ((WORD) *pNumTypes > *pSizeofDataInTypes)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			*pNumTypes = *pSizeofDataInTypes;
			}

		if (*pInt)
			Retval = *pInt;

		(*pSizeofDataInTypes) = *pNumTypes;

		memcpy((char *) pData, (char *) (RetBuffer+PACKET_HEADER_SIZE+4), (*pNumTypes) * sizeof(MemoryTypeDef));
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}

//BYTE SharedRamArea = 0;

__declspec(dllexport) int HEIReadSharedRAM(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Address, WORD Bytes2Read, BYTE *pBuffer)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[600];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Num;
	WORD *pWord;
	BYTE SharedRamArea = 0;

	Buffer[DataOffset] = FUN_READ_SHARED_RAM;

	if (Address & 0x8000)
		{
		SharedRamArea = 1;
		Address &= 0x7FFF;
		}

	Buffer[DataOffset+1] = SharedRamArea;
	
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord++ = Base;
	*pWord++ = Slot;
	*pWord++ = Address;
	*pWord++ = Bytes2Read;

	Total = DataOffset+10;

	Num = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &Num, TRUE, FALSE);

	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;
	//if (Error) 
	//	return Error;

	if (Num)
		{
		short int *pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE);
		
		//if (!*pError || (*pError == LENGTH_WARNING))
		if (!((*pError) & 0x0FFF) || (*pError == HEIE_LENGTH_WARNING))
			{
			// Copy the memory.
			memcpy(pBuffer, RetBuffer+PACKET_HEADER_SIZE+2, Bytes2Read);
			}
		
		return *pError;
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
		
	/* return 0; */
	}
	

__declspec(dllexport) int HEIWriteSharedRAM(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Address, WORD Bytes2Write, BYTE *pBuffer)
	{
	BYTE Buffer[600];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Num;
	WORD *pWord;
	BYTE SharedRamArea = 0;

	if (Bytes2Write > 256)
		return HEIE_DATA_TOO_LARGE;

	Buffer[DataOffset] = FUN_WRITE_SHARED_RAM;

	if (Address & 0x8000)
		{
		SharedRamArea = 1;
		Address &= 0x7FFF;
		}

	Buffer[DataOffset+1] = SharedRamArea;
	
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord++ = Base;
	*pWord++ = Slot;
	*pWord++ = Address;
	*pWord++ = Bytes2Write;
	
	memcpy(Buffer+DataOffset+10, pBuffer, Bytes2Write);

	Total = DataOffset+10+Bytes2Write;

	Num = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &Num, TRUE, FALSE);

	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;
	//if (Error) return Error;

	if (Num)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
		
	/* return 0; */
	}


/*
** Calculate, 16 Bit CRC
*/
/* number of bits in CRC: don't change it.  */
#define W 16

/* this the number of bits per char: don't change it. */
#define B 8

static unsigned short crctab[1<<B] = { 
    0x0000,  0x1021,  0x2042,  0x3063,  0x4084,  0x50a5,  0x60c6,  0x70e7,
    0x8108,  0x9129,  0xa14a,  0xb16b,  0xc18c,  0xd1ad,  0xe1ce,  0xf1ef,
    0x1231,  0x0210,  0x3273,  0x2252,  0x52b5,  0x4294,  0x72f7,  0x62d6,
    0x9339,  0x8318,  0xb37b,  0xa35a,  0xd3bd,  0xc39c,  0xf3ff,  0xe3de,
    0x2462,  0x3443,  0x0420,  0x1401,  0x64e6,  0x74c7,  0x44a4,  0x5485,
    0xa56a,  0xb54b,  0x8528,  0x9509,  0xe5ee,  0xf5cf,  0xc5ac,  0xd58d,
    0x3653,  0x2672,  0x1611,  0x0630,  0x76d7,  0x66f6,  0x5695,  0x46b4,
    0xb75b,  0xa77a,  0x9719,  0x8738,  0xf7df,  0xe7fe,  0xd79d,  0xc7bc,
    0x48c4,  0x58e5,  0x6886,  0x78a7,  0x0840,  0x1861,  0x2802,  0x3823,
    0xc9cc,  0xd9ed,  0xe98e,  0xf9af,  0x8948,  0x9969,  0xa90a,  0xb92b,
    0x5af5,  0x4ad4,  0x7ab7,  0x6a96,  0x1a71,  0x0a50,  0x3a33,  0x2a12,
    0xdbfd,  0xcbdc,  0xfbbf,  0xeb9e,  0x9b79,  0x8b58,  0xbb3b,  0xab1a,
    0x6ca6,  0x7c87,  0x4ce4,  0x5cc5,  0x2c22,  0x3c03,  0x0c60,  0x1c41,
    0xedae,  0xfd8f,  0xcdec,  0xddcd,  0xad2a,  0xbd0b,  0x8d68,  0x9d49,
    0x7e97,  0x6eb6,  0x5ed5,  0x4ef4,  0x3e13,  0x2e32,  0x1e51,  0x0e70,
    0xff9f,  0xefbe,  0xdfdd,  0xcffc,  0xbf1b,  0xaf3a,  0x9f59,  0x8f78,
    0x9188,  0x81a9,  0xb1ca,  0xa1eb,  0xd10c,  0xc12d,  0xf14e,  0xe16f,
    0x1080,  0x00a1,  0x30c2,  0x20e3,  0x5004,  0x4025,  0x7046,  0x6067,
    0x83b9,  0x9398,  0xa3fb,  0xb3da,  0xc33d,  0xd31c,  0xe37f,  0xf35e,
    0x02b1,  0x1290,  0x22f3,  0x32d2,  0x4235,  0x5214,  0x6277,  0x7256,
    0xb5ea,  0xa5cb,  0x95a8,  0x8589,  0xf56e,  0xe54f,  0xd52c,  0xc50d,
    0x34e2,  0x24c3,  0x14a0,  0x0481,  0x7466,  0x6447,  0x5424,  0x4405,
    0xa7db,  0xb7fa,  0x8799,  0x97b8,  0xe75f,  0xf77e,  0xc71d,  0xd73c,
    0x26d3,  0x36f2,  0x0691,  0x16b0,  0x6657,  0x7676,  0x4615,  0x5634,
    0xd94c,  0xc96d,  0xf90e,  0xe92f,  0x99c8,  0x89e9,  0xb98a,  0xa9ab,
    0x5844,  0x4865,  0x7806,  0x6827,  0x18c0,  0x08e1,  0x3882,  0x28a3,
    0xcb7d,  0xdb5c,  0xeb3f,  0xfb1e,  0x8bf9,  0x9bd8,  0xabbb,  0xbb9a,
    0x4a75,  0x5a54,  0x6a37,  0x7a16,  0x0af1,  0x1ad0,  0x2ab3,  0x3a92,
    0xfd2e,  0xed0f,  0xdd6c,  0xcd4d,  0xbdaa,  0xad8b,  0x9de8,  0x8dc9,
    0x7c26,  0x6c07,  0x5c64,  0x4c45,  0x3ca2,  0x2c83,  0x1ce0,  0x0cc1,
    0xef1f,  0xff3e,  0xcf5d,  0xdf7c,  0xaf9b,  0xbfba,  0x8fd9,  0x9ff8,
    0x6e17,  0x7e36,  0x4e55,  0x5e74,  0x2e93,  0x3eb2,  0x0ed1,  0x1ef0
    };

WORD CalcCRC(WORD    icrc,
            BYTE   *icp,
            WORD    icnt)
	{
	register WORD crc = icrc;
	register BYTE *cp = icp;
	register WORD cnt = icnt;

	while( cnt-- )
		crc = (crc<<B) ^ crctab[(crc>>(W-B)) ^ *cp++];

	return( crc );
	}



/*
**
** WinPLC Specific Functions
**
*/
__declspec(dllexport) int WPLCSetOSLoad(HEIDevice *pDevice, int Val)
	{
	BYTE Buffer[100];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int NumBytes;

	Buffer[DataOffset] = FUN_SET_OS_LOAD;
	Buffer[DataOffset+1] = ~FUN_SET_OS_LOAD;
	memcpy(&Buffer[DataOffset+2], &Val, sizeof(int));

	Total = DataOffset+2+sizeof(int);
	NumBytes = sizeof(RetBuffer);

	return _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);
	}


__declspec(dllexport) int WPLCReboot(HEIDevice *pDevice)
	{
	BYTE Buffer[100];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int NumBytes;

	Buffer[DataOffset] = FUN_REBOOT;
	Buffer[DataOffset+1] = ~FUN_REBOOT;

	Total = DataOffset+2;
	NumBytes = sizeof(RetBuffer);

	return _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);
	}

__declspec(dllexport) int HEIReboot(HEIDevice *pDevice)
	{
	BYTE Buffer[100];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int NumBytes;

	Buffer[DataOffset] = FUN_REBOOT;
	Buffer[DataOffset+1] = ~FUN_REBOOT;

	Total = DataOffset+2;
	NumBytes = sizeof(RetBuffer);

	return _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);
	}


__declspec(dllexport) int WPLCRunProgram(HEIDevice *pDevice, BYTE *pProgram)
	{
	BYTE Buffer[500];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	BYTE *pArgs, *pData;
	WORD Total;
	int NumBytes;
	short int *pError;

	memset(Buffer, 0, sizeof(Buffer));
	Buffer[DataOffset] = FUN_RUN_PROGRAM;
	Buffer[DataOffset+1] = ~FUN_RUN_PROGRAM;

	pArgs = pProgram;

	if (!*pArgs)
		return -1;

	// Skip whitespace at front.
	while (*pArgs == ' ')
		pArgs++;

	pData = &Buffer[DataOffset+2];

	// Copy program name.
	while (*pArgs && (*pArgs != ' '))
		{
		*pData++ = *pArgs++;
		}

	while (isspace(*pArgs))
		pArgs++;

	strcpy((char *) &Buffer[DataOffset+66], (char *) pArgs);

	Total = DataOffset+2+64+strlen((char *) pArgs)+1;

	NumBytes = sizeof(RetBuffer);

	_SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	pError = (short int *) (RetBuffer+PACKET_HEADER_SIZE);

	return *pError;
	}


/*
**
** THIS IS THE MODIFIED SERIAL PORT FUNCTIONS THAT ACCEPT A BYTE FOR THE PORT NUMBER
**
*/

__declspec(dllexport) int HEIWriteCommEx(HEIDevice *pDevice, BYTE Port, WORD Num2Write, BYTE *pData)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	WORD *pWord;
	int Error;
	int NumBytes;

	//Port = (Port - 1) << 4;
	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_WRITE_COMM + 0x80; //Port;
	Buffer[DataOffset+2] = Port-1;
	pWord = (WORD *) &Buffer[DataOffset+3];
	*pWord = Num2Write;

	if (Num2Write > (sizeof(Buffer) - DataOffset - 5))
		return HEIE_DATA_TOO_LARGE;

	memcpy(Buffer+DataOffset+5, pData, Num2Write);

	Total = DataOffset+5+Num2Write;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}

__declspec(dllexport) int HEIReadCommEx(HEIDevice *pDevice, BYTE Port, WORD *pNum2Read, BYTE *pData)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];

	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	WORD *pWord;
	int Error;
	int Retval;
	int NumBytes;

	//Port = (Port - 1) << 4;
	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_READ_COMM + 0x80; //Port;
	Buffer[DataOffset+2] = Port-1;
	pWord = (WORD *) &Buffer[DataOffset+3];
	*pWord = *pNum2Read;

	Total = DataOffset+5;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);
		short int *pNumReturned = (short int *) (RetBuffer+PACKET_HEADER_SIZE+2);

		if (*pInt)
			Retval = *pInt;

		(*pNum2Read) = *pNumReturned;

		memcpy(pData, RetBuffer+PACKET_HEADER_SIZE+4, *pNumReturned);
		}
	else
		Retval = HEIE_ZERO_BYTES_RECEIVED;

	return Retval;
	}

__declspec(dllexport) int HEIGetRXAvailableEx(HEIDevice *pDevice, BYTE Port, WORD *pAvailable)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	//Port = (Port - 1) << 4;
	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_RX_AVAILABLE + 0x80; //Port;
	Buffer[DataOffset+2] = Port-1;

	Total = DataOffset+3;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		{
		*pAvailable = *((WORD *) (RetBuffer+PACKET_HEADER_SIZE+2));
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}

__declspec(dllexport) int HEIFlushRXQueueEx(HEIDevice *pDevice, BYTE Port)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	//Port = (Port - 1) << 4;
	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_RX_FLUSH + 0x80; //Port;
	Buffer[DataOffset+2] = Port-1;

	Total = DataOffset+3;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}

__declspec(dllexport) int HEIFlushTXQueueEx(HEIDevice *pDevice, BYTE Port)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	//Port = (Port - 1) << 4;
	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_TX_FLUSH + 0x80; //Port;
	Buffer[DataOffset+2] = Port-1;

	Total = DataOffset+3;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}

__declspec(dllexport) int HEISetupSerialPortEx(HEIDevice *pDevice, BYTE Port, SerialSetup *pSetup, BOOL WriteToFlash)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	//Port = (Port - 1) << 4;
	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_SETUP + 0x80; //Port;
	Buffer[DataOffset+2] = Port-1;
	Buffer[DataOffset+3] = (BYTE) WriteToFlash;
	Buffer[DataOffset+4] = 0;

	memcpy(Buffer+DataOffset+5, pSetup, sizeof(SerialSetup));

	Total = DataOffset+5+sizeof(SerialSetup);

	NumBytes = sizeof(RetBuffer);

	if (WriteToFlash)
		{
		pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;

		Error = SendPacketTwoResponses(pDevice, Buffer, Total, RetBuffer, &NumBytes, 
										TRUE, FALSE,
										0, NULL, 
										30000, TRUE, TRUE);

		pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;
		}
	else
		{
		Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);
		}

	//if (Error) 
	//	return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}
	
__declspec(dllexport) int HEIReadSerialPortSetupEx(HEIDevice *pDevice, BYTE Port, SerialSetup *pSetup)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int NumBytes;

	//Port = (Port - 1) << 4;
	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_READ_SETUP + 0x80; //Port;
	Buffer[DataOffset+2] = Port-1;
	Buffer[DataOffset+3] = 0;
	Buffer[DataOffset+4] = 0;

	Total = DataOffset+5;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	if (NumBytes)
		{
		// Copy data into user buffer.
		memcpy(pSetup, RetBuffer+PACKET_HEADER_SIZE, sizeof(SerialSetup));
		return 0;
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}
	

__declspec(dllexport) int HEIGetTXLeftEx(HEIDevice *pDevice, BYTE Port, WORD *pLeft)
	{
	BYTE Buffer[200];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	//int Retval;
	int NumBytes;

	//Port = (Port - 1) << 4;
	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_TX_LEFT + 0x80; //Port;
	Buffer[DataOffset+2] = Port-1;

	Total = DataOffset+3;

	NumBytes = sizeof(RetBuffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, TRUE, FALSE);

	//if (Error) return Error;
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	//Retval = Error;

	if (NumBytes)
		{
		*pLeft = *((WORD *) (RetBuffer+PACKET_HEADER_SIZE+2));
		return *((short int *) (RetBuffer+PACKET_HEADER_SIZE));
		}
	else
		return HEIE_ZERO_BYTES_RECEIVED;
	}

__declspec(dllexport) int HEIAccessComm(HEIDevice *pDevice, WORD SendDataSize, BYTE *pSendData, WORD *pReturnDataSize, BYTE *pReturnData)
	{
	BYTE Buffer[1500];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	WORD *pWord;
	int Error;
	int NumBytes;
	int Retval;

	Buffer[DataOffset] = FUN_SERIAL_PORT;
	Buffer[DataOffset+1] = SPF_ACCESS_COMM;
	pWord = (WORD *) &Buffer[DataOffset+2];
	*pWord = SendDataSize;

	if (SendDataSize > (sizeof(Buffer) - DataOffset - 4))
		return HEIE_DATA_TOO_LARGE;

	memcpy(Buffer+DataOffset+4, pSendData, SendDataSize);

	Total = DataOffset+4+SendDataSize;

	NumBytes = sizeof(Buffer);
		
	Error = _SendPacket(pDevice, Buffer, Total, Buffer, &NumBytes, TRUE, FALSE);

	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) (Buffer+PACKET_HEADER_SIZE);
		short int *pNumReturned = (short int *) (Buffer+PACKET_HEADER_SIZE+2);

		if (*pInt)
			Retval = *pInt;

		if (pReturnData && pReturnDataSize)
			{
			if (*pNumReturned > *pReturnDataSize)
				{
				Retval = HEIE_BUFFER_TOO_SMALL;
				}
			else
				{
				(*pReturnDataSize) = *pNumReturned;
				}

			memcpy(pReturnData, Buffer+PACKET_HEADER_SIZE+4, *pReturnDataSize);
			}
		}
	else
		Retval = HEIE_ZERO_BYTES_RECEIVED;

	return Retval;
	}


__declspec(dllexport) int HEIWriteEZethernetPgmSpace(HEIDevice *pDevice, BYTE *pData, WORD SizeofData)
	{
	BYTE Buffer[600];
	BYTE RetBuffer[200];
	WORD DataOffset = pDevice->DataOffset;
	WORD *pWord;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = (BYTE)FUN_USER_CONFIG_PANEL;	/* This is the function code! */
	Buffer[DataOffset+1] = 0;

	pWord = (WORD *) &Buffer[DataOffset+2];

	Total = DataOffset+4+SizeofData;

	// FYI: Incoming size should never be greater than 316 bytes.
	//      60 bytes control + 255 Max AVG packet size + 1 byte for 
	//      the start character. 
	if (Total > sizeof(Buffer) || SizeofData > 316)
		return HEIE_DATA_TOO_LARGE;

	(void)memcpy(&Buffer[DataOffset+4], pData, SizeofData);

	NumBytes = sizeof(RetBuffer);
		
	pDevice->Timeout += EXTRA_TIME_FOR_SETUP_DATA;

	Error = SendPacketTwoResponses(pDevice, Buffer, Total, RetBuffer, &NumBytes, 
									TRUE, FALSE,
									0, NULL, 
									30000, TRUE, TRUE);

	pDevice->Timeout -= EXTRA_TIME_FOR_SETUP_DATA;

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) (RetBuffer+PACKET_HEADER_SIZE);

		if (*pInt)
			Retval = *pInt;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		}

	return Retval;
	}


/*
**	ERM Functions.
*/
#define FUN_COMMAND		6
#define FUN_READ_DATA	7	
#define FUN_WRITE_DATA	8

#define FUN_STATUS_INWORK	1
#define FUN_STATUS_DONE		2
#define FUN_STATUS_ERROR	3

__declspec(dllexport) int HEIWriteERMData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE DataType, BYTE *pData, WORD NumBytes, WORD Offset)
	{
	WORD Data[6];
	WORD *pOffset;
	WORD *pExtended;
	WORD *pNumBytes;
	int Index = 0;

	// Common header
	Data[Index++] = 0;						// Function + Status (ClearFunction until all other data is written)
	Data[Index++] = 0;						// Error 

	// Function specific header
	Data[Index++] = DataType;				// Data type 
	pOffset = (WORD *) &Data[Index++];	// Pointer to Offset
	pNumBytes = (WORD *) &Data[Index++];// Pointer to num bytes
	pExtended = (WORD *) &Data[Index++]; // Pointer to extended

	*pOffset = Offset;
	*pNumBytes = 256;
	*pExtended = 0;


	while (NumBytes)
		{
		int Error;

		//memcpy(&Data[11], pOutputData, *pNumBytes);
		if (*pNumBytes > NumBytes)
			*pNumBytes = NumBytes;

		Data[0] = 0;
		Data[1] = 0;

		// Write Header first.
		Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30 + 0x8000, sizeof(Data), (BYTE *) Data);

		if (Error)
			{
			//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
			return Error;
			}

		// Next write data.
		Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30+sizeof(Data) + 0x8000, *pNumBytes, pData);

		if (Error)
			{
			//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
			return Error;
			}

		// Now write the REAL command.
		Data[0] = FUN_WRITE_DATA;

		Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30+ 0x8000, 1, (BYTE *) Data);

		if (Error)
			{
			//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
			return Error;
			}
		else
			{
			// Wait for it to complete.
			DWORD StartTime = HEIIGetCounter();
			BOOL Done = FALSE;

			do
				{
				BYTE bData[4];
				Error = HEIReadSharedRAM(pDevice, Base, Slot, 0x30+ 0x8000, 4, (BYTE *) bData);

				if (Error)
					{
					//printf("\nError %d (0x%X) from HEIReadSharedRAM", Error, Error);
					return Error;
					}
				else
					{
					if ((bData[1] & 0xFF) == FUN_STATUS_DONE)
						{
						Done = TRUE;
						}
					else if ((bData[1] & 0xFF) == FUN_STATUS_ERROR)
						{
						return bData[2];  // Return Error
						}
					}
				} while (!Done && TimeDiff(StartTime, HEIIGetCounter()) < pDevice->Timeout);

			if (!Done)
				{
				//printf("\nTimeout waiting for request to complete.");
				return HEIE_TIMEOUT;
				}
			}

		pData += *pNumBytes;
		(*pOffset) += *pNumBytes;
		NumBytes -= *pNumBytes;
		}

#if 0
	if ((DataType == DATA_OUTPUT) && (Flags & 0x01))
		{
		return WPLCDoERMCommand(Base, Slot, COMMAND_PROCESS_IO, 0, 0);
		}
#endif

	return 0;
	}

__declspec(dllexport) int HEIReadERMData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE DataType, BYTE *pData, WORD NumBytes, WORD Offset)
	{
	WORD Data[6];
	WORD *pOffset;
	WORD *pNumBytes;
	WORD *pExtended;
	int Index = 0;

	// Common header
	Data[Index++] = 0;						// Function + Status (ClearFunction until all other data is written)
	Data[Index++] = 0;						// Error 

	// Function specific header
	Data[Index++] = DataType;				// Data type 
	pOffset = (WORD *) &Data[Index++];	// Pointer to Offset
	pNumBytes = (WORD *) &Data[Index++];// Pointer to num bytes
	pExtended = (WORD *) &Data[Index++]; // Pointer to extended

	*pOffset = Offset;		
	*pNumBytes = 256;
	*pExtended = 0;

	//RETAILMSG(1, (TEXT("\r\nWPLCReadERMData Base: %d Slot: %d  Type: %d  Num: %d"), Base, Slot, DataType, NumBytes));

	while (NumBytes)
		{
		int Error;

		Data[0] = 0;
		Data[1] = 0;

		if (*pNumBytes > NumBytes)
			{
			*pNumBytes = NumBytes;
			}

		Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30+0x8000, sizeof(Data), (BYTE *) Data);

		if (Error)
			{
			//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
			return Error;
			}

		// Now write the REAL command.
		Data[0] = FUN_READ_DATA;

		Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30+0x8000, 2, (BYTE *) Data);

		if (Error)
			{
			//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
			return Error;
			}
		else
			{
			// Wait for it to complete.
			DWORD StartTime = HEIIGetCounter();
			BOOL Done = FALSE;

			do 
				{
				BYTE bData[4];

				Error = HEIReadSharedRAM(pDevice, Base, Slot, 0x30+0x8000, 4, bData);

				if (Error)
					{
					//printf("\nError %d (0x%X) from HEIReadSharedRAM", Error, Error);
					return Error;
					}
				else
					{
			//RETAILMSG(1, (TEXT("\r\nbData: 0x%X 0x%X 0x%X 0x%X"), bData[0], bData[1], bData[2], bData[3]));

					//if (((Data[0]>>8) & 0xFF) == FUN_STATUS_DONE)
					if (bData[1] == FUN_STATUS_DONE)
						{
						// Read the rest of the data.
						Error = HEIReadSharedRAM(pDevice, Base, Slot, 0x30+sizeof(Data)+0x8000, *pNumBytes, pData);

						if (Error)
							{
							//printf("\nError %d (0x%X) from HEIReadSharedRAM", Error, Error);
							return Error;
							}

						Done = TRUE;
						}
					//else if (((Data[0]>>8) & 0xFF) == FUN_STATUS_ERROR)
					else if (bData[1] == FUN_STATUS_ERROR)
						{
						return Data[2];
					//	memcpy(pInputData, &Data[11], *pNumBytes);
						}
					}
				} while (!Done && TimeDiff(StartTime, HEIIGetCounter()) < pDevice->Timeout);

			if (!Done)
				{
				//printf("\nTimeout waiting for request to complete.");
				return HEIE_TIMEOUT;
				}
			}

		pData += *pNumBytes;
		(*pOffset) += *pNumBytes;
		NumBytes -= *pNumBytes;
		}

	return 0;
	}

__declspec(dllexport) int HEIDoERMCommand(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Command)
	{
	DWORD StartTime;
	WORD Data[3];
	int Index = 0;
	int Error;

	// Common header
	Data[Index++] = 0; // Command and Status (Set Command to zero until rest of data is written)
	Data[Index++] = 0;						// Error
	
	// Function specific header
	Data[Index++] = Command;

	Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30 + 0x8000, sizeof(Data), (BYTE *) Data);

	if (Error)
		{
		//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
		return Error;
		}

	// Now write the REAL command.
	Data[0] = FUN_COMMAND;

	Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30+0x8000, 2, (BYTE *) Data);

	if (Error)
		{
		//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
		return Error;
		}

		// Wait for it to complete.
	StartTime = HEIIGetCounter();

	while (TimeDiff(StartTime, HEIIGetCounter()) < pDevice->Timeout)
		{
		BYTE bData[4];
		Error = HEIReadSharedRAM(pDevice, Base, Slot, 0x30+0x8000, 4, (BYTE *) bData);

		if (!Error)
			{
			if ((bData[1] & 0xFF) == FUN_STATUS_DONE)
				return 0;
			else if ((bData[1] & 0xFF) == FUN_STATUS_ERROR)
				return bData[2];
			}
		}

	return HEIE_TIMEOUT;
	}


__declspec(dllexport) int HEIDoERMCommandEx(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Command, BYTE *pExtra, WORD ExtraLen)
	{
	DWORD StartTime;
	BYTE Data[300];
	int Index = 0;
	int Error;
	WORD *pCommand;
	BOOL Done;

	// Common header
	Data[Index++] = 0; // Command and Status (Set Command to zero until rest of data is written)
	Data[Index++] = 0;						// Error
	Data[Index++] = 0; // Command and Status (Set Command to zero until rest of data is written)
	Data[Index++] = 0;						// Error
	
	// Function specific header
	pCommand = (WORD *) &Data[Index];
	*pCommand = Command;
	Index += 2;

	memcpy(&Data[Index], pExtra, ExtraLen);

	Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30 + 0x8000,  (WORD)(ExtraLen + 6), Data);

	if (Error)
		{
		//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
		return Error;
		}

	// Now write the REAL command.
	Data[0] = FUN_COMMAND;
	Data[1] = 0;

	Error = HEIWriteSharedRAM(pDevice, Base, Slot, 0x30+0x8000, 2, (BYTE *) Data);

	if (Error)
		{
		//printf("\nError %d (0x%X) from HEIWriteSharedRAM", Error, Error);
		return Error;
		}

		// Wait for it to complete.
	Done = FALSE;
	StartTime = HEIIGetCounter();

	do
		{
		BYTE bData[4];
		Error = HEIReadSharedRAM(pDevice, Base, Slot, 0x30+0x8000, 4, bData);

		if (!Error)
			{
			if (bData[1] == FUN_STATUS_DONE)
				Done = TRUE;
			else if (bData[1] == FUN_STATUS_ERROR)
				return (int) (((WORD) bData[2]) + (((WORD) bData[3]) << 8));
			}
		} while (!Done && TimeDiff(StartTime, HEIIGetCounter()) < pDevice->Timeout);

	if (!Done)
		return HEIE_TIMEOUT;

	return 0;
	}


NODELIST *EZGetNodeList(unsigned short int *TotalEZ)
{

    static NODELIST EZList[200];  
    static HEIDevice HEIDevices[100];
    static HEITransport   TP;
    unsigned short int i, j;   // Index variables 
    int Error, MaxDevices, MaxEZDevices;     

    WORD  Timeout   = 100;
    WORD  Retrys    = 2;    
    WORD  SizeofData;
    BOOL  Broadcast = FALSE;	
    BYTE  Data[500];	
	BYTE *pData = Data;
    DeviceDef dd;
	 WORD NumDevices;

    HEITransport *tp = &TP;    
    ENetAddress  *pSourceAddress = (ENetAddress *)NULL;    

	tp->Transport = HEIT_WINSOCK;		
    tp->Protocol  = HEIP_IPX;

    *TotalEZ = 0;   // Set to zero until proven otherwise.

	Error = HEIOpenTransport(tp, HEIAPIVERSION, pSourceAddress);	
    if (Error)
	{
        //printf("Error returned from HEIOpenTransport()\n");  
        return (NODELIST *)NULL;      
	}

    MaxDevices   = sizeof(HEIDevices) / sizeof(HEIDevice);    
    MaxEZDevices = sizeof(EZList)     / sizeof(NODELIST);
	NumDevices = MaxEZDevices;

	Error = HEIQueryDevices(tp, HEIDevices, &NumDevices, HEIAPIVERSION);
	if (Error)
	{
        //printf("Error returned from HEIQueryDevices()\n");  
        (void)HEIClose();
        return (NODELIST *)NULL;
	}
           
    j = 0;
    for (i = 0; i < NumDevices; i++)
    {	
        if (i > MaxDevices)
        {
            goto ReturnIncompleteList; 
        }

        Error = HEIOpenDevice(tp, &HEIDevices[i], HEIAPIVERSION, Timeout, Retrys, Broadcast);
        if (Error)
        {
            //printf("IsDeviceEZEthernet: Error %d returned from HEIOpenDevice\n", Error);
            return (NODELIST *)NULL;
        }	

	    Error = HEIReadDeviceDef(&HEIDevices[i], (BYTE *) &dd, sizeof(dd));
        if (Error)
        {        
            //printf("IsDeviceEZEthernet: Error returned from HEIReadDeviceDef\n");
            goto ErrorHandler;
        }

        if (dd.ModuleType == MT_AVG_DISP)
        {
            if (j >= MaxEZDevices)
                goto ErrorHandler;

            SizeofData = sizeof(WORD);
            Error = HEIReadSetupData( &HEIDevices[i], DT_NODE_NUMBER, pData, &SizeofData);
		    if (Error)
		    {
                //printf("Error %d returned from HEIReadSetupData1\n", Error);
                goto ErrorHandler;
            }
		    else
            { 
                 (void)memcpy(EZList[j].Node_ID, pData, sizeof(WORD));
		    }  

            // Get the Node Name 
		    SizeofData = sizeof(EZList[0].Name);
            Error = HEIReadSetupData(&HEIDevices[i], DT_NODE_NAME, pData, &SizeofData);	
		    if (Error)
		    {                    
                //printf("Error returned from HEIReadSetupData2\n");           
                goto ErrorHandler;
            }
            else
            {
	            (void)memcpy(EZList[j].Name, pData, SizeofData);
            }

            EZList[j].pDevice = &HEIDevices[i];
            j++;
        }
        else
        {
            // Close the device since it is not an EZ_Ethernet.
            (void)HEICloseDevice(&HEIDevices[i]);
        }

    }   // End of for


    if (j == 0)
    {
        goto ErrorHandler;
    }
    else
    {    
        (void)HEIClose();
        *TotalEZ = j;
        return EZList;
    }
    
    ReturnIncompleteList: 
        // If we have process the maximum number of devices we can
        // do, return a list of what we got.       
        (void)HEIClose();        
        *TotalEZ = j;
	    return EZList;

    ErrorHandler:               
        (void)HEICloseDevice(&HEIDevices[i]);
        (void)HEIClose();
	    return (NODELIST *)NULL;

}


BOOL EZSendPacket(HEIDevice *pDevice, PGM_BUF *pBuffer, BYTE *Error_message, unsigned short int Len)
{

    int Error;

#if TC_DEBUG
    int i;

    printf("EZSendPacket: Incoming buffer has:\n");
    for (i = 0; i < Len; i++)
        printf("%c", pBuffer->PgmData[i]);
    printf("\n");
#endif

    Error = HEIWriteEZethernetPgmSpace(pDevice,	(BYTE *)pBuffer->PgmData, Len );

	switch (Error)
    {
        case HEIE_DATA_TOO_LARGE:
        {
            (void)memcpy(&Error_message, "Message size too large", 81);
            return FALSE;
        }
       
        case HEIE_ZERO_BYTES_RECEIVED:
        {
            (void)memcpy(&Error_message, "Attempted to send zero-length message", 81);
             return FALSE;
        }

        case -1:
        {
            // printf("Error %X returned from  HEIWriteEZethernetPgmSpace!\n", Error);
             (void)memcpy(&Error_message, "HEIWriteEZethernetPgmSpace call failed with -1", 81);        
             return FALSE;
        }

        case NO_ERROR:
        {             
              //printf("Successfull send from HEIWriteEZethernetPgmSpace\n");
              Error_message[0] = '\0';
              return TRUE;
        }

            
        default:
        {
             //printf("Error %X returned from  HEIWriteEZethernetPgmSpace!\n", Error);
             (void)memcpy(&Error_message, "HEIWriteEZethernetPgmSpace call failed with unknown error", 81);        
             return FALSE;
        }

    }

	return TRUE;
}



int WPLCWriteERMData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE DataType, BYTE *pData, WORD NumBytes, WORD Offset)
	{
	return HEIWriteERMData(pDevice, Base, Slot, DataType, pData, NumBytes, Offset);
	}

int WPLCReadERMData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE DataType, BYTE *pData, WORD NumBytes, WORD Offset)
	{
	return HEIReadERMData(pDevice, Base, Slot, DataType, pData, NumBytes, Offset);
	}

int WPLCDoERMCommand(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Command)
	{
	return HEIDoERMCommand(pDevice, Base, Slot, Command);
	}

int WPLCDoERMCommandEx(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Command, BYTE *pExtra, WORD ExtraLen)
	{
	return HEIDoERMCommandEx(pDevice, Base, Slot, Command, pExtra, ExtraLen);
	}


__declspec(dllexport) int SetCRCMode(int Mode)
	{
	int Old = DoCRC;

	DoCRC = Mode;

	return Old;
	}


/* CONFIG DATA ACCESS */
__declspec(dllexport) int HEIReadConfigData(HEIDevice *pDevice, BYTE *pData, WORD *DataSize)
	{
	BYTE Buffer[100];
	BYTE RetBuffer[1200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;
	
	Buffer[DataOffset] = FUN_READ_CONFIG_DATA; /* This is the function code! */

	Total = DataOffset+1;

	if (pData && *pData == 0xB1)
		{
		Buffer[DataOffset+1] = *pData;
		Total++;
		}

	NumBytes = sizeof(RetBuffer);

	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, (pDevice->ParallelPackets) ? FALSE : TRUE, TRUE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) &RetBuffer[PACKET_HEADER_SIZE];

		NumBytes -= PACKET_HEADER_SIZE;
		NumBytes -= 2;

		if ((WORD) NumBytes > *DataSize)
			{
			Retval = HEIE_BUFFER_TOO_SMALL;
			NumBytes = *DataSize;
			}

		if (*pInt)
			Retval = (*pInt) | 0x8000;

		memcpy(pData, RetBuffer+PACKET_HEADER_SIZE+2, NumBytes);
		(*DataSize) = NumBytes;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;
		(*DataSize) = 0;
		}

	return Retval;
	}


__declspec(dllexport) int HEIWriteConfigData(HEIDevice *pDevice, BYTE *pData, WORD SizeofData, BYTE *pReturnData, WORD *pSizeofReturnData)
	{
	BYTE Buffer[1200];
	BYTE RetBuffer[1200];
	WORD DataOffset = pDevice->DataOffset;
	WORD Total;
	int Error;
	int Retval;
	int NumBytes;

	Buffer[DataOffset] = FUN_WRITE_CONFIG_DATA;	 		/* This is the function code! */
	
	Total = DataOffset+1+SizeofData;

	if (Total > sizeof(Buffer))
		return HEIE_DATA_TOO_LARGE;

	memcpy(Buffer+DataOffset+1, pData, SizeofData);

	NumBytes = sizeof(RetBuffer);
	//NumBytes = *pSizeofReturnData;
		
	Error = _SendPacket(pDevice, Buffer, Total, RetBuffer, &NumBytes, (pDevice->ParallelPackets) ? FALSE : TRUE, TRUE);

	/* Check for error and not warning. */
	if (Error && !(Error & HEIW_FIRST_WARNING))
		return Error;

	Retval = Error;

	if (NumBytes)
		{
		short int *pInt = (short int *) &RetBuffer[PACKET_HEADER_SIZE];

		if (pReturnData && pSizeofReturnData)
			{
			NumBytes -= PACKET_HEADER_SIZE;
			NumBytes -= 2;

			if ((WORD) NumBytes > *pSizeofReturnData)
				{
				Retval = HEIE_BUFFER_TOO_SMALL;
				NumBytes = *pSizeofReturnData;
				}

			memcpy(pReturnData, RetBuffer+PACKET_HEADER_SIZE+2, NumBytes);
			(*pSizeofReturnData) = NumBytes;
			}

		if (*pInt)
			Retval = (*pInt) | 0x8000;
		}
	else
		{
		Retval = HEIE_ZERO_BYTES_RECEIVED;

		if (pSizeofReturnData)
			(*pSizeofReturnData) = 0;
		}

	return Retval;
	}
