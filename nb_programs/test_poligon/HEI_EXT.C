#include "defs.h"
#include <memory.h>
#include <malloc.h>
#include "hei.h"

#define TimeDiff(StartTime, EndTime)  (((DWORD)EndTime > (DWORD)StartTime) ? ((DWORD)EndTime - (DWORD)StartTime) : ((DWORD)EndTime + ((DWORD)ULONG_MAX - (DWORD)StartTime) + 1))
DWORD HEIIGetCounter();

int GetResponseEx(HEIDevice *apDevice[], BYTE *apData[], WORD aSizeofData[], int aErrorCode[], int DeviceCount)
	{
	int Done = TRUE;
	int idx = 0;

	for(idx = 0; idx < DeviceCount; idx++)
		{
		/* Handle NULL device */
		if(!apDevice[idx])
			continue;

		if(aErrorCode[idx] == HEIE_NO_RESPONSE)
			{
			BYTE Buff[500];
			int BuffLen = sizeof(Buff);
			aErrorCode[idx] = HEIGetResponse(apDevice[idx], Buff, &BuffLen, TRUE);

			/* If no response, continue */
			if(aErrorCode[idx] == HEIE_NO_RESPONSE)
				{
				Done = FALSE;
				continue;
				}

			/* Check for error and not warning. */
			if(aErrorCode[idx] && !(aErrorCode[idx] & HEIW_FIRST_WARNING))
				{
				/* Set data size to 0 */
				aSizeofData[idx] = 0;
				}
			else
				{
				if(BuffLen)
					{
					short int *pInt = (short int *)&Buff[PACKET_HEADER_SIZE];

					BuffLen -= PACKET_HEADER_SIZE;
					BuffLen -= 2;

					if((WORD)BuffLen > aSizeofData[idx])
						{
						BuffLen = aSizeofData[idx];
						aErrorCode[idx] = HEIE_BUFFER_TOO_SMALL;
						}

					if(*pInt)
						aErrorCode[idx] = (*pInt) | 0x8000;

					memcpy(apData[idx], Buff+PACKET_HEADER_SIZE+2, BuffLen);
					aSizeofData[idx] = BuffLen;
					}
				else
					{
					/* Set data size to 0 */
					aSizeofData[idx] = 0;
					aErrorCode[idx] = HEIE_ZERO_BYTES_RECEIVED;
					}
				}
			}
		}

	return Done;
	}

DWORD StartHEIReadIO(HEIDevice *pDevice, BYTE *pData, WORD *pSizeofData, int *pErrorCode)
	{
	DWORD StartTime = 0;
	BOOL OldPP = FALSE;

	/* Force parallel packet mode */
	OldPP = pDevice->ParallelPackets;
	pDevice->ParallelPackets = TRUE;

	/* Init error code */
	*pErrorCode = HEIE_NO_RESPONSE;

	/* Log the time */
	StartTime = HEIIGetCounter();

	/* Send request */
	HEIReadIO(pDevice, pData, pSizeofData);

	/* Restore parallel packet mode */
	pDevice->ParallelPackets = OldPP;

	return StartTime;
	}

__declspec(dllexport) int HEIReadIOEx
	(
	HEIDevice *apDevice[], 
	BYTE *apData[], 
	WORD aSizeofData[], 
	int aErrorCode[], 
	int DeviceCount
	)
	{
	int idx = 0;
	BOOL Done = FALSE;
	DWORD *pStartTime = (DWORD *)calloc(sizeof(DWORD), DeviceCount);
	int MaxStarted = 0;
	int StartAt = 0;

	/* Reset retry count */
	for(idx = 0; idx < DeviceCount; idx++)
		if(apDevice[idx])
			apDevice[idx]->SizeOfData = 0;

	while(!Done)
		{
		/* Start a request */
		for(idx = StartAt; idx < DeviceCount; idx++)
			{
			/* Handle NULL device */
			if(!apDevice[idx])
				{
				StartAt = idx + 1;
				if(idx+1 > MaxStarted)
					MaxStarted = idx + 1;
				}
			/* If request not started, start it */
			else if(!pStartTime[idx])
				{
				pStartTime[idx] = StartHEIReadIO(apDevice[idx], apData[idx], &aSizeofData[idx], &aErrorCode[idx]);
				StartAt = idx + 1;
				if(idx+1 > MaxStarted)
					MaxStarted = idx + 1;
				break;
				}
			}

		/* Test for completion of requests */
		GetResponseEx(apDevice, apData, aSizeofData, aErrorCode, MaxStarted);

		/* When all have been started, we're done until proven otherwise */
		Done = MaxStarted == DeviceCount;
		
		/* Test for timeout of requests */
		for(idx = 0; idx < MaxStarted; idx++)
			{
			/* Handle NULL device */
			if(!apDevice[idx])
				continue;

			/* If request started, test timeout */
			if(aErrorCode[idx] == HEIE_NO_RESPONSE && pStartTime[idx])
				{
				/* Check timeout for device */
				if(TimeDiff(pStartTime[idx], HEIIGetCounter()) >= apDevice[idx]->Timeout)
					{
					/* Timed out, check retries */
					if(apDevice[idx]->SizeOfData < apDevice[idx]->Retrys)
						{
						apDevice[idx]->SizeOfData++;
						apDevice[idx]->RetryCount++;

						/* Reset */
						pStartTime[idx] = 0;
						aErrorCode[idx] == HEIE_NO_RESPONSE;

						if(idx < StartAt)
							StartAt = idx;
						
						/* Not done */
						Done = FALSE;
						}
					/* No more retries */
					else
						{
						/* Set error code */
						aErrorCode[idx] = HEIE_TIMEOUT;
						
						/* This device is done */
						}
					}
				/* Started but not timed out */
				else
					/* Not done */
					Done = FALSE;
				}
			/* If not started... */
			else if(!pStartTime[idx])
				{
				/* Can't be done */
				Done = FALSE;
				}
			}
		}

	free(pStartTime);

	return 0;
	}

DWORD StartHEIWriteIO(HEIDevice *pDevice, BYTE *pData, WORD SizeofData, BYTE *pReturnData, WORD *pSizeofReturnData, int *pErrorCode)
	{
	DWORD StartTime = 0;
	BOOL OldPP = FALSE;

	/* Force parallel packet mode */
	OldPP = pDevice->ParallelPackets;
	pDevice->ParallelPackets = TRUE;

	/* Init error code */
	*pErrorCode = HEIE_NO_RESPONSE;

	/* Log the time */
	StartTime = HEIIGetCounter();

	/* Send request */
	HEIWriteIO(pDevice, pData, SizeofData, pReturnData, pSizeofReturnData);

	/* Restore parallel packet mode */
	pDevice->ParallelPackets = OldPP;

	return StartTime;
	}

__declspec(dllexport) int HEIWriteIOEx
	(
	HEIDevice *apDevice[], 
	BYTE *apData[], 
	WORD aSizeofData[], 
	BYTE *apReturnData[], 
	WORD aSizeofReturnData[], 
	int aErrorCode[], 
	int DeviceCount
	)
	{
	int idx = 0;
	BOOL Done = FALSE;
	DWORD *pStartTime = (DWORD *)calloc(sizeof(DWORD), DeviceCount);
	int MaxStarted = 0;
	int StartAt = 0;

	/* Reset retry count */
	for(idx = 0; idx < DeviceCount; idx++)
		if(apDevice[idx])
			apDevice[idx]->SizeOfData = 0;

	while(!Done)
		{
		/* Start a request */
		for(idx = StartAt; idx < DeviceCount; idx++)
			{
			/* Handle NULL device */
			if(!apDevice[idx])
				{
				StartAt = idx + 1;
				if(idx+1 > MaxStarted)
					MaxStarted = idx + 1;
				}
			/* If request not started, start it */
			else if(!pStartTime[idx])
				{
				pStartTime[idx] = StartHEIWriteIO(apDevice[idx], apData[idx], aSizeofData[idx], apReturnData[idx], &aSizeofReturnData[idx], &aErrorCode[idx]);
				StartAt = idx + 1;
				if(idx+1 > MaxStarted)
					MaxStarted = idx + 1;
				break;
				}
			}

		/* Test for completion of requests */
		GetResponseEx(apDevice, apReturnData, aSizeofReturnData, aErrorCode, MaxStarted);

		/* When all have been started, we're done until proven otherwise */
		Done = MaxStarted == DeviceCount;
		
		/* Test for timeout of requests */
		for(idx = 0; idx < MaxStarted; idx++)
			{
			/* Handle NULL device */
			if(!apDevice[idx])
				continue;

			/* If request started, test timeout */
			if(aErrorCode[idx] == HEIE_NO_RESPONSE && pStartTime[idx])
				{
				/* Check timeout for device */
				if(TimeDiff(pStartTime[idx], HEIIGetCounter()) >= apDevice[idx]->Timeout)
					{
					/* Timed out, check retries */
					if(apDevice[idx]->SizeOfData < apDevice[idx]->Retrys)
						{
						apDevice[idx]->SizeOfData++;
						apDevice[idx]->RetryCount++;

						/* Reset */
						pStartTime[idx] = 0;
						aErrorCode[idx] == HEIE_NO_RESPONSE;

						if(idx < StartAt)
							StartAt = idx;
						
						/* Not done */
						Done = FALSE;
						}
					/* No more retries */
					else
						{
						/* Set error code */
						aErrorCode[idx] = HEIE_TIMEOUT;
						
						/* This device is done */
						}
					}
				/* Started but not timed out */
				else
					/* Not done */
					Done = FALSE;
				}
			/* If not started... */
			else if(!pStartTime[idx])
				{
				/* Can't be done */
				Done = FALSE;
				}
			}
		}

	free(pStartTime);

	return 0;
	}
	
#if 0
int GetResponseEx(HEIDevice *apDevice[], BYTE *apData[], WORD aSizeofData[], int aErrorCode[], int DeviceCount)
	{
	int Done = TRUE;
	int idx = 0;

	for(idx = 0; idx < DeviceCount; idx++)
		{
		/* Handle NULL device */
		if(!apDevice[idx])
			continue;

		if(aErrorCode[idx] == HEIE_NO_RESPONSE)
			{
			BYTE Buff[500];
			int BuffLen = sizeof(Buff);
			aErrorCode[idx] = HEIGetResponse(apDevice[idx], Buff, &BuffLen, TRUE);

			/* If no response, continue */
			if(aErrorCode[idx] == HEIE_NO_RESPONSE)
				{
				Done = FALSE;
				continue;
				}

			/* Check for error and not warning. */
			if(aErrorCode[idx] && !(aErrorCode[idx] & HEIW_FIRST_WARNING))
				{
				/* Set data size to 0 */
				aSizeofData[idx] = 0;
				}
			else
				{
				if(BuffLen)
					{
					short int *pInt = (short int *)&Buff[PACKET_HEADER_SIZE];

					BuffLen -= PACKET_HEADER_SIZE;
					BuffLen -= 2;

					if((WORD)BuffLen > aSizeofData[idx])
						{
						BuffLen = aSizeofData[idx];
						aErrorCode[idx] = HEIE_BUFFER_TOO_SMALL;
						}

					if(*pInt)
						aErrorCode[idx] = (*pInt) | 0x8000;

					memcpy(apData[idx], Buff+PACKET_HEADER_SIZE+2, BuffLen);
					aSizeofData[idx] = BuffLen;
					}
				else
					{
					/* Set data size to 0 */
					aSizeofData[idx] = 0;
					aErrorCode[idx] = HEIE_ZERO_BYTES_RECEIVED;
					}
				}
			}
		}

	return Done;
	}

__declspec(dllexport) int HEIReadIOEx
	(
	HEIDevice *apDevice[], 
	BYTE *apData[], 
	WORD aSizeofData[], 
	int aErrorCode[], 
	int DeviceCount, 
	DWORD Timeout
	)
	{
	DWORD StartTime = HEIIGetCounter();
	int idx = 0;
	BOOL Done = FALSE;
	BOOL OldPP = FALSE;

	for(idx = 0; idx < DeviceCount; idx++)
		{
		/* Handle NULL device */
		if(!apDevice[idx])
			continue;

		/* Force parallel packet mode */
		OldPP = apDevice[idx]->ParallelPackets;
		apDevice[idx]->ParallelPackets = TRUE;

		/* Init error code */
		aErrorCode[idx] = HEIE_NO_RESPONSE;

		/* Send request */
		HEIReadIO(apDevice[idx], apData[idx], &aSizeofData[idx]);

		/* Check for response */
		GetResponseEx(apDevice, apData, aSizeofData, aErrorCode, idx+1);

		/* Restore parallel packet mode */
		apDevice[idx]->ParallelPackets = OldPP;
		}

	/* Spin on GetResponseEx waiting for timeout */
	while(!Done)
		{
		Done = GetResponseEx(apDevice, apData, aSizeofData, aErrorCode, idx);
		if(TimeDiff(StartTime, HEIIGetCounter()) >= Timeout)
			return HEIE_TIMEOUT;
		}

	return 0;
	}

__declspec(dllexport) int HEIWriteIOEx
	(
	HEIDevice *apDevice[], 
	BYTE *apData[], 
	WORD aSizeofData[], 
	BYTE *apReturnData[], 
	WORD aSizeofReturnData[], 
	int aErrorCode[], 
	int DeviceCount, 
	DWORD Timeout
	)
	{
	DWORD StartTime = HEIIGetCounter();
	int idx = 0;
	BOOL Done = FALSE;
	BOOL OldPP = FALSE;

	for(idx = 0; idx < DeviceCount; idx++)
		{
		/* Handle NULL device */
		if(!apDevice[idx])
			continue;

		/* Force parallel packet mode */
		OldPP = apDevice[idx]->ParallelPackets;
		apDevice[idx]->ParallelPackets = TRUE;

		/* Init error code */
		aErrorCode[idx] = HEIE_NO_RESPONSE;

		/* Send request */
		HEIWriteIO(apDevice[idx], apData[idx], aSizeofData[idx], apReturnData[idx], &aSizeofReturnData[idx]);

		/* Check for response */
		GetResponseEx(apDevice, apReturnData, aSizeofReturnData, aErrorCode, idx+1);

		/* Restore parallel packet mode */
		apDevice[idx]->ParallelPackets = OldPP;
		}

	/* Spin on GetResponseEx waiting for timeout */
	while(!Done)
		{
		Done = GetResponseEx(apDevice, apReturnData, aSizeofReturnData, aErrorCode, idx);
		if(TimeDiff(StartTime, HEIIGetCounter()) >= Timeout)
			return HEIE_TIMEOUT;
		}

	return 0;
	}
#endif
