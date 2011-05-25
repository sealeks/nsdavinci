/*
**	HEI.C - Platform dependent code for communicating with Host Automation Products
**			line of ethernet modules using the WinSock transport.
** 
**	Copyright (C) - 1996-1998 Host Automation Products, Inc.
**
*/
#include "winsock.h"		/* Needed for winsock calls */
#include "wsipx.h"			/* Needed for winsock IPX calls */
#include "mmsystem.h"		/* Needed for timer stuff */
#include "hei.h"	
#include <memory.h>

/*
**	Notes for porting code to another platform:
**
**	This file contains the transport/system dependant code for use with the
**	Host Ethernet Interface (HEI).  There are nine functions which must be
**	implemented by this code:
**
**		1) int HEIIOpen();
**		2) int HEIIClose();
**		3) int HEIIOpenTransport(HEITransport *pTransport);
**		4) int HEIICloseTransport(HEITransport *pTransport);
**		5) int HEIIOpenDevice(HEITransport *pTransport, HEIDevice *pDevice);
**		6) int HEIICloseDevice(HEIDevice *pDevice);
**		7) int HEIIReceivePacket(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize);
**		8) int HEIISendPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize);
**		9) DWORD HEIIGetCounter();
**
**	Make changes in this file, do not change HEI.C or any structures in HEI.H!  
**	If you find that you must change something in HEI.C, contact the person
**	you got this source from.
**
**	Feel free to remove any of the WinSock specific code from this module.
**	
**	To compile the code for ANSI C, ANSI_C must be defined!
**
**	See all sections containing "TODO_FOR_OTHER_SYSTEM" for further details.
**
*/


/* Counter for the number of times that OpenTransport has been called */
static int WinSockLoadCount = 0;	

/* 
** Windows version gets stored here.  It is used for setting winsock options 
** Win 16 is slightly different than Win 32.
*/
WORD  WinVer=0;

/* This is the port number to use when talking to a module. */
#define PORT_ID 0x7070

/* This function should return a millisecond resolution tick counter. */
DWORD HEIIGetCounter()
	{
	/*return timeGetTime(); */
	LARGE_INTEGER freq, count;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&count);
	return (DWORD)((count.QuadPart * 1000) / freq.QuadPart);
	}



/* 
** This function is called from within HEIOpen. It gives the opportunity
** to do initialization type stuff.  NOTE: This function may be called more
** than once!
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIOpen()
	{
	/* Save the windows version for later use. */
	DWORD dwVersion = GetVersion();
	WinVer = LOWORD(dwVersion);

	/* 
	** TODO_FOR_OTHER_SYSTEM 
	** Do system level init stuff here.  
	** Be aware that this may be called more than once.
	*/
	return HEIE_NULL;
	}
	
/* 
** This function is called from within HEIClose. It gives the opportunity
** to do shutdown type stuff.  NOTE: This function may be called more
** than once!
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIClose()	
	{
	/* 
	** TODO_FOR_OTHER_SYSTEM 
	** Do system level shut down stuff here.  
	** Be aware that this may be called more than once.
	*/
	return HEIE_NULL;	
	}	
	
/*
** This function is called from within HEIOpenTransport.  It is used to prepare
** the given Transport to be used in subsequent HEIOpenDevice calls.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIOpenTransport(HEITransport *pTransport)
	{	
	switch (pTransport->Transport)	
		{
		case HEIT_WINSOCK:			/* Open Transport type HEIT_WINSOCK */
			{
			/* WinSock Transport. Protocol must be either IPX or IP */
			if (pTransport->Protocol == HEIP_IPX || pTransport->Protocol == HEIP_IP)
				{
				/* Keep track of load count, Initialize winsock if zero. */
				if (!WinSockLoadCount)
					{
					WSADATA wsaData;
					WORD wVersionRequested = MAKEWORD(2, 0);
		
					/* Initialize winsock dll */
					if(WSAStartup(wVersionRequested, &wsaData) == SOCKET_ERROR)
						return WSAGetLastError();
					}

				WinSockLoadCount++;
				}
			else
				return HEIE_UNSUPPORTED_PROTOCOL;
			break;
			}
			
		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM 
			** Do one time init stuff by keeping track of the number of times this
			** transport has been opened.
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
		
	return HEIE_NULL;
   }
   
   
/*
** This function is called from within HEICloseTransport.  It indicates
** that the given Transport is no longer in use.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIICloseTransport(HEITransport *pTransport)
	{
	switch (pTransport->Transport)	
		{
		case HEIT_WINSOCK:    		/* Close Transport type HEIT_WINSOCK */
			{
			/* WinSock Transport. Protocol must be IPX or IP */
			if (pTransport->Protocol == HEIP_IPX || pTransport->Protocol == HEIP_IP)
				{
				/* Decrement load count.  Shut down WinSock if zero */
				if (WinSockLoadCount)
					{
					WinSockLoadCount--;

					if (!WinSockLoadCount)
						WSACleanup();
					}
				}
			else
				return HEIE_UNSUPPORTED_PROTOCOL; 
				
			break;
			}
			
		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM 
			** Decrement load counter, do cleanup stuff if zero.
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
		
	return HEIE_NULL;	
   }
   
   
/*
** This function is called from within HEIOpenDevice.  It is used to prepare
** the given Device to be used with the given Transprot.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIOpenDevice(HEITransport *pTransport, HEIDevice *pDevice)
	{
	switch (pTransport->Transport)	
		{
		case HEIT_WINSOCK: 	/* Open Device type HEIT_WINSOCK */
			{
			/* WinSock Transport. */
			SOCKET sock;
			struct sockaddr *pRemAddr, *pMyAddr;
			int SizeRemAddr, SizeMyAddr;
			u_long NonBlockingMode;

			if (pTransport->Protocol == HEIP_IPX)
				{
				static SOCKADDR_IPX RemAddr, MyAddr;

				/* Initialize remote address */
				if (!pDevice->UseBroadcast)
					memcpy(&RemAddr, pDevice->Address.Raw, sizeof(SOCKADDR_IPX));

				if (pTransport->pSourceAddress)
					{
					MyAddr.sa_family = pTransport->pSourceAddress->AddressIPX.Family;
					memcpy(MyAddr.sa_netnum, pTransport->pSourceAddress->AddressIPX.Netnum, 4);
					memcpy(MyAddr.sa_nodenum, pTransport->pSourceAddress->AddressIPX.Nodenum, 6);
					MyAddr.sa_socket = pTransport->pSourceAddress->AddressIPX.Socket;
					}
				else
					{
					/* Initialize MyAddr to all zeros so that windows can tell me who I am! */
					MyAddr.sa_family = AF_IPX;
					/*memcpy(MyAddr.sa_netnum, &pTransport->NetworkAddress, 4);*/
					memset(MyAddr.sa_netnum, 0, 4);
					memset(MyAddr.sa_nodenum, 0, 6);
					MyAddr.sa_socket = 0x00;
					}

				/* get socket handle */
				sock = socket(AF_IPX,        /* IPX family */
							  SOCK_DGRAM,    /* Datagram */
							  NSPROTO_IPX);  

				pRemAddr = (struct sockaddr *) &RemAddr;
				pMyAddr = (struct sockaddr *) &MyAddr;
				SizeRemAddr = sizeof(RemAddr);
				SizeMyAddr = sizeof(MyAddr);
				}
			else if (pTransport->Protocol == HEIP_IP)
				{
				static struct sockaddr_in RemAddr, MyAddr;

				/*
				** If Protocol is IP and we are not using broadcast, and 
				** Address.Raw[19] == 1 then the IP address in the module
				** is undefined.
				*/
				if (!pDevice->UseBroadcast && (pDevice->Address.Raw[19] == 1))
					return HEIE_IP_ADDR_NOT_INITIALIZED;
					
				/* Initialize remote address */
				if (!pDevice->UseBroadcast)
					memcpy(&RemAddr, pDevice->Address.Raw, sizeof(RemAddr));

				if (pTransport->pSourceAddress)
					{
					MyAddr.sin_family = pTransport->pSourceAddress->AddressIP.Family;
					MyAddr.sin_port = pTransport->pSourceAddress->AddressIP.Port;
					MyAddr.sin_addr.s_addr = pTransport->pSourceAddress->AddressIP.AddressingType.lAddr;
					}
				else
					{
					/* Initialize MyAddr to all zeros so that windows can tell me who I am! */
					MyAddr.sin_family = AF_INET;
					MyAddr.sin_port = 0;
					MyAddr.sin_addr.s_addr = 0;
					}

				/* get socket handle */
				sock = socket(AF_INET,       /* IP family */
							  SOCK_DGRAM,    /* Datagram */
							  IPPROTO_UDP);      

				pRemAddr = (struct sockaddr *) &RemAddr;
				pMyAddr = (struct sockaddr *) &MyAddr;
				SizeRemAddr = sizeof(RemAddr);
				SizeMyAddr = sizeof(MyAddr);
				}
			else 
				return HEIE_UNSUPPORTED_PROTOCOL;


			if(sock == INVALID_SOCKET) 
				return WSAGetLastError();

			if (bind (sock,	pMyAddr, SizeMyAddr) == SOCKET_ERROR)
				{
				int Error = WSAGetLastError();
				closesocket(sock);
				return Error;
				} 

			if (pDevice->UseBroadcast)
				{
				int rSetSockOpt;
			   
				if (WinVer < 0x0332)	/* Check for WinVer < 3.50 */
					{
					/* 16 Bit uses int type. */
					int AllowBroadcast = TRUE;
					rSetSockOpt = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char *) &AllowBroadcast, sizeof(AllowBroadcast));
					}
				else
					{
					/* 32 Bit uses long type. */
					long AllowBroadcast = TRUE;
					rSetSockOpt = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char *) &AllowBroadcast, sizeof(AllowBroadcast));
					}
				
				if (rSetSockOpt == SOCKET_ERROR)
					{
					int Error = WSAGetLastError();
					closesocket(sock);
					return Error;
					}
				}
			else
				{
				if (connect (sock,	pRemAddr, SizeRemAddr) == SOCKET_ERROR)
					{
					int Error = WSAGetLastError();
					closesocket(sock);
					return Error;
					} 
				}

			/* Setup for non-blocking mode */
			NonBlockingMode = 1;

			if (ioctlsocket (sock, FIONBIO, &NonBlockingMode) == SOCKET_ERROR)
				{
				int Error = WSAGetLastError();
				closesocket(sock);
				return Error;
				}
			
			pDevice->_dwParam = (DWORD) sock;
			break;
			}
			
		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM 
			** Prepare to communicate with the given device.
			** The address to talk to is stored in pDevice->Address (see HEI.H for format)
			** Be aware that pDevice->UseBroadcast indicates that we
			** will be broadcasting to the module.
			** For IP, pDevice->Address.Raw[19] == 1 (after a query)
			** if the given module's IP address is not initialized.  In
			** this case, the only way to talk to it (using IP) is by 
			** using addressed broadcast.
			** You can use pDevice->_dwParam to store whatever (such as
			** a socket number).
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
		
	return HEIE_NULL;
	}

	
/*
** This function is called from within HEICloseDevice.  It indicates
** that the given Device is no longer in use.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIICloseDevice(HEIDevice *pDevice)
	{
	switch (pDevice->_pTransport->Transport)	
		{
		case HEIT_WINSOCK:		/* Close Device type HEIT_WINSOCK */
			{
			/* WinSock Transport. */
			if (pDevice->_pTransport->Protocol == HEIP_IPX || pDevice->_pTransport->Protocol == HEIP_IP)
				{
				SOCKET sock = (SOCKET) pDevice->_dwParam;
			   
				if (closesocket(sock) == SOCKET_ERROR)
					return WSAGetLastError();
				}
			else
				return HEIE_UNSUPPORTED_PROTOCOL;

			break;
			}
			
		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM
			** Do device type shutdown stuff.
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
   	
	return HEIE_NULL;	
	}
	
	
/*
**	This is the code for receiving a packet from the ethernet driver for the given
**  device.  The response should be stored in the given response buffer - pResponse.
**  On entry, pResponseSize contains the size of the response buffer (pResponse).
**  On exit, pResponseSize MUST contain the number of bytes copied to the response buffer.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIReceivePacket(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize)
	{
	int Retval = HEIE_NULL;
	
	switch (pDevice->_pTransport->Transport)	
		{
		case HEIT_WINSOCK:		/* GetResponse from HEIT_WINSOCK */
			{
			int NumBytes;
			SOCKET sock = (SOCKET) pDevice->_dwParam;
			
			if (pDevice->UseBroadcast)
				{
				struct sockaddr FromAddr;
				int FromLen = sizeof(FromAddr);
		
				NumBytes = recvfrom(sock, (char *) pResponse, *pResponseSize, 0, &FromAddr, &FromLen);
				
				if (pDevice->pData)
					{
					/* Need to copy FROM address. */
					int Num2Copy = FromLen;
			
					if (pDevice->SizeOfData < Num2Copy)
						{
						Retval = HEIE_BUFFER_TOO_SMALL;
						Num2Copy = pDevice->SizeOfData;
						}
			
					memcpy(pDevice->pData, &FromAddr, Num2Copy);					
					}
				}
			else
				{
				NumBytes = recv(sock, (char *) pResponse, *pResponseSize, 0);
				}
			
			if (NumBytes == SOCKET_ERROR)
				{
				/* Check to see if the error is WSAWOULDBLOCK. */
				int Error = WSAGetLastError();
		
				if (Error != WSAEWOULDBLOCK)
					{
					*pResponseSize = 0;
					Retval = Error;
					}
				else
					{
					Retval = HEIE_NO_RESPONSE;
					}
				}
			else
				{
				(*pResponseSize) = NumBytes;
				}
			
			break;
			}

		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM 
			** Receive a packet for the given device into the buffer pResponse.
			** *pResponseSize indicates the length of the pResponse buffer.
			** If pDevice->UseBroadcast && pDevice->pData, 
			** then we need to copy the FROM address into pDevice->pData.
			** pDevice->SizeOfData tells how long the buffer pDevice->pData is.
			** Store the number of bytes received in (*pResponseSize).
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
		
	return Retval;
	}             
	
	
/*
** This is the code for sending the given packet for the given device.
** pPacket is the pointer to the actual packet data, and PacketSize is the
** number of bytes in the packet to be sent.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIISendPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize)
	{
	switch (pDevice->_pTransport->Transport)	
		{
		case HEIT_WINSOCK:			/* Send packet of type HEIT_WINSOCK */
			{
			/* WinSock Transport. */
			SOCKET sock = (SOCKET) pDevice->_dwParam;

			if (pDevice->UseBroadcast)
				{
				/* Initialize remote address */
				struct sockaddr *pRemAddr = (struct sockaddr *) NULL;
				int SizeRemAddr = 0;

				if (pDevice->_pTransport->Protocol == HEIP_IP)
					{
					static struct sockaddr_in RemAddr;
		
					RemAddr.sin_family = AF_INET;
					RemAddr.sin_port = PORT_ID;
					RemAddr.sin_addr.s_addr = INADDR_BROADCAST;
		
					pRemAddr = (struct sockaddr *) &RemAddr;
					SizeRemAddr = sizeof(RemAddr);
					}
				else if (pDevice->_pTransport->Protocol == HEIP_IPX)
					{
					static SOCKADDR_IPX RemAddr;
		
					RemAddr.sa_family = AF_IPX;
					memset(RemAddr.sa_netnum, 0, 4);
					memset(RemAddr.sa_nodenum, 0xFF, 6);
					RemAddr.sa_socket = PORT_ID;

					if (pDevice->_pTransport->pSourceAddress)
						memcpy(RemAddr.sa_netnum, pDevice->_pTransport->pSourceAddress->AddressIPX.Netnum, 4);
						/*memcpy(RemAddr.sa_netnum, &pDevice->_pTransport->NetworkAddress, 4);*/
		
					pRemAddr = (struct sockaddr *) &RemAddr;
					SizeRemAddr = sizeof(RemAddr);
					}

				if (sendto(sock, (char *) pPacket, PacketSize, 0, pRemAddr, SizeRemAddr) == SOCKET_ERROR)
					return  WSAGetLastError();
				}
			else
				{
				if (send(sock, (char *) pPacket, PacketSize, 0) == SOCKET_ERROR)
					return  WSAGetLastError();
				}
			
			return HEIE_NULL;
			}

		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM 
			** Send a packet to the given device.
			** If pDevice->UseBroadcast, then we need to broadcast the packet.
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
	}	

	
