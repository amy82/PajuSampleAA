
typedef struct _IOCTLDATA {
	UINT64			*pBufferAddr;
	UINT64			unData[4];
	UINT32			ReturnCode;
	UINT32			Addr;
    
} IOCTLDATA;
