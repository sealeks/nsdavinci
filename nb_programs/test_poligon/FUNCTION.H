#define UDP_PORT_ID  0x7070


#pragma pack(1)
typedef struct
	{
	char *pOSBegin;
	char *pOSEnd;
	char *pOSRun;
	WORD CRC;
	WORD BootSignature;
	WORD OSSignature;
	BYTE Unused[14];
	} OSDef;

     

/* Error/return val List */
#define HEI_NO_ERROR					0

#define ICMP_PKT_FOUND				65
#define ARP_PKT_FOUND				66
#define TYPE_NOT_HANDLED			67
#define LINK_SENSE_TRIGGERED		68

#define UNK_IP_PACKET				100
#define UNK_ETHERTYPE				101
#define UNK_PACKET_TYPE 			102
#define UNK_802X_PACKET_TYPE		103
#define UNK_LLC_TYPE					104
#define CRC_DOES_NOT_MATCH			105
#define CRC_NO_DATA					106
#define ENET_ADDR_REPROGRAMMED	107
#define NULL_DATA_POINTER			108
#define SIZE_ERROR					109
#define NOT_FOUND						110
#define INVALID_TYPE					111
#define RAM_ALREADY_LOCKED			112
#define INVALID_REQUEST				113
#define TIMEOUT_ERROR				114
#define FLASH_PROGRAM_ERROR		115
#define INVALID_OS					116
#define INVALID_LOCATION			117
#define INVALID_SLOT_NUMBER		118
#define INVALID_DATA					119
#define MODULE_BUSY					120
#define CHANNEL_FAILURE				121
#define UNUSED_CHANNELS_EXIST		122
#define INVALID_UDP_PORT			123
#define SHUTDOWN_OS					124
#define NOT_MY_IP_ADDRESS			125
#define PROTECTION_ERROR			126
#define UNK_TYPE_ERROR				127
#define BACKPLANE_INIT_ERROR		128
#define UNK_RESPONSE					129
#define UNK_RXWX_FORMAT				130
#define UNK_ACK						131
#define UNK_NAK						132
#define RANGE_ERROR					133
#define LENGTH_WARNING				134
#define INVALID_BASE_NUMBER			135
#define INVALID_MODULE_TYPE			136
#define INVALID_OFFSET				137
#define INVALID_BOOT_VER_FOR_OS		138
#define BROKEN_TRANSMITTER			139
#define INVALID_ADDRESS				140

#define CHANNELS_UNUSED_0			200
#define CHANNELS_UNUSED_1			201
#define CHANNELS_UNUSED_2        201
#define CHANNELS_UNUSED_3        203
#define CHANNELS_UNUSED_4        204
#define CHANNELS_UNUSED_5        205
#define CHANNELS_UNUSED_6        206
#define CHANNELS_UNUSED_7        207
#define CHANNELS_UNUSED_8        208
#define CHANNELS_UNUSED_9        209
#define CHANNELS_UNUSED_10       210
#define CHANNELS_UNUSED_11       211
#define CHANNELS_UNUSED_12       212
#define CHANNELS_UNUSED_13       213
#define CHANNELS_UNUSED_14       214
#define CHANNELS_UNUSED_15       215
#define CHANNELS_UNUSED_16       216

#pragma pack()



