typedef  unsigned char      boolean;      
typedef  unsigned int      uint32;       
typedef  unsigned short     uint16;       
typedef  unsigned char      uint8;        
typedef  signed int         int32;        
typedef  signed short       int16;        
typedef  signed char        int8;         
typedef  unsigned long      uintnt;      
typedef  unsigned char      byte;          
typedef  unsigned short     word;          
typedef  unsigned int       dword;         
typedef  unsigned char      uint1;         
typedef  unsigned short     uint2;         
typedef  unsigned int       uint4;         
typedef  signed char        int1;          
typedef  signed short       int2;          
typedef  signed int         int4;          
typedef  signed int         sint31;        
typedef  signed short       sint15;        
typedef  signed char        sint7;         
typedef uint16 UWord16 ;
typedef uint32 UWord32 ;
typedef int32  Word32 ;
typedef int16  Word16 ;
typedef uint8  UWord8 ;
typedef int8   Word8 ;
typedef int32  Vect32 ;
    typedef long long     int64;        
    typedef  unsigned long long  uint64;       
typedef uint32  DALBOOL;
typedef uint32  DALDEVICEID;
typedef uint32  DalPowerCmd;
typedef uint32  DalPowerDomain;
typedef uint32  DalSysReq;
typedef uint32  DALHandle;
typedef int     DALResult;
typedef void  * DALEnvHandle;
typedef void  * DALSYSEventHandle;
typedef uint32  DALMemAddr;
typedef uint32  DALSYSMemAddr;
typedef uint32  DALInterfaceVersion;
typedef unsigned char * DALDDIParamPtr;
typedef struct DALEventObject DALEventObject;
struct DALEventObject
{
    uint32 obj[8];
};
typedef DALEventObject * DALEventHandle;
typedef struct _DALMemObject
{
   uint32        memAttributes;
   uint32        sysObjInfo[2];
   uint32        dwLen;
   uint32        ownerVirtAddr;
   uint32        virtAddr;
   uint32        physAddr;
}
DALMemObject;
typedef struct _DALDDIMemBufDesc
{
   uint32       dwOffset;
   uint32       dwLen;
   uint32       dwUser;
}
DALDDIMemBufDesc;
typedef struct _DALDDIMemDescList
{
   uint32          dwFlags;
   uint32          dwNumBufs;
   DALDDIMemBufDesc   bufList[1];  
}
DALDDIMemDescList;
typedef struct DALSysMemDescBuf DALSysMemDescBuf;
struct DALSysMemDescBuf
{
   DALSYSMemAddr VirtualAddr;
   DALSYSMemAddr PhysicalAddr;
   uint32 size;
   uint32 user;
};
typedef struct DALSysMemDescList DALSysMemDescList;
struct DALSysMemDescList
{
   uint32 dwObjInfo; uint32 hOwnerProc; DALSYSMemAddr thisVirtualAddr;
   DALSYSMemAddr PhysicalAddr;
   DALSYSMemAddr VirtualAddr;
   uint32        dwCurBufIdx;
   uint32        dwNumDescBufs;
   DALSysMemDescBuf BufInfo[1];
};
typedef struct DalDeviceInfo DalDeviceInfo;
struct DalDeviceInfo
{
   uint32 sizeOfActual;
   uint32 Version;
   char Name[32];
};
typedef struct DalDeviceStatus DalDeviceStatus;
struct DalDeviceStatus
{
   uint32 sizeOfActual;
   uint32 Status;
};
typedef struct DalDeviceHandle DalDeviceHandle;
typedef struct DalDevice DalDevice;
struct DalDevice
{
   DALResult (*Attach)(const char*,DALDEVICEID,DalDeviceHandle **);
   uint32    (*Detach)(DalDeviceHandle *);
   DALResult (*Init)(DalDeviceHandle *);
   DALResult (*DeInit)(DalDeviceHandle *);
   DALResult (*Open)(DalDeviceHandle *, uint32);
   DALResult (*Close)(DalDeviceHandle *);
   DALResult (*Info)(DalDeviceHandle *, DalDeviceInfo *, uint32);
   DALResult (*PowerEvent)(DalDeviceHandle *, DalPowerCmd, DalPowerDomain);
   DALResult (*SysRequest)(DalDeviceHandle *, DalSysReq, const void *, uint32,
                           void *,uint32, uint32*);
};
typedef struct DalInterface DalInterface;
struct DalInterface
{
   struct DalDevice DalDevice;
};
struct DalDeviceHandle
{
   uint32 dwDalHandleId;
   const DalInterface *pVtbl;
   void         *pClientCtxt;
};
typedef struct DalDeviceHandle * DALDEVICEHANDLE;
typedef struct DalRemoteHandle DalRemoteHandle;
typedef struct DalRemote DalRemote;
struct DalRemote
{
   struct DalDevice DalDevice;
   DALResult (* FCN_0) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1 );
   DALResult (* FCN_1) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, uint32 u2 );
   DALResult (* FCN_2) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, uint32* p_u2 );
   DALResult (* FCN_3) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, uint32 u2, uint32 u3 );
   DALResult (* FCN_4) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, uint32 u2, uint32* p_u3 );
   DALResult (* FCN_5) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen);
   DALResult (* FCN_6) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, void * ibuf, uint32 ilen);
   DALResult (* FCN_7) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * obuf, uint32 olen, uint32 *oalen);
   DALResult (* FCN_8) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * obuf, uint32 olen);
   DALResult (* FCN_9) ( uint32 ddi_idx, DalDeviceHandle *h, void * obuf, uint32 olen );
   DALResult (* FCN_10)( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, void * ibuf, uint32 ilen, void * obuf, uint32 olen, uint32 * oalen);
   DALResult (* FCN_11) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, void * obuf, uint32 olen);
   DALResult (* FCN_12) ( uint32 ddi_idx, DalDeviceHandle *h, uint32 u1, void * obuf, uint32 olen, uint32 *oalen);
   DALResult (* FCN_13) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * ibuf2, uint32 ilen2, void * obuf, uint32 olen);
   DALResult (* FCN_14) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * obuf1, uint32 olen, void * obuf2, uint32 olen2, uint32 * oalen);
   DALResult (* FCN_15) ( uint32 ddi_idx, DalDeviceHandle *h, void * ibuf, uint32 ilen, void * ibuf2, uint32 ilen2, void * obuf2, uint32 olen2, uint32 *oalen, void * obuf, uint32 olen );
};
struct DalRemoteHandle
{
   uint32 dwDalHandleId;
   const DalRemote *pVtbl;
   void      *pClientCtxt;
};
static __inline uint32
DalDevice_Detach(DalDeviceHandle *_h)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Detach(_h);
}
static __inline DALResult
DalDevice_Init(DalDeviceHandle *_h)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Init(_h);
}
static __inline DALResult
DalDevice_DeInit(DalDeviceHandle *_h)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.DeInit(_h);
}
static __inline DALResult
DalDevice_PowerEvent(DalDeviceHandle *_h, DalPowerCmd PowerCmd,
                     DalPowerDomain PowerDomain)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.PowerEvent(_h,PowerCmd,PowerDomain);
}
static __inline DALResult
DalDevice_Open(DalDeviceHandle *_h, uint32 mode)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Open(_h,mode);
}
static __inline DALResult
DalDevice_Close(DalDeviceHandle *_h)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Close(_h);
}
static __inline DALResult
DalDevice_Info(DalDeviceHandle *_h, DalDeviceInfo* info, uint32 infoSize)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.Info(_h,info,infoSize);
}
static __inline DALResult
DalDevice_SysRequest(DalDeviceHandle *_h, DalSysReq ReqIdx,
                     const unsigned char* SrcBuf, int SrcBufLen,
                     unsigned char* DestBuf, uint32 DestBufLen, uint32* DestBufLenReq)
{
   (_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
   return _h->pVtbl->DalDevice.SysRequest(_h,ReqIdx,SrcBuf,SrcBufLen,
                                          DestBuf,DestBufLen,DestBufLenReq);
}
DALResult
DAL_DeviceAttach(DALDEVICEID DeviceId,
                 DalDeviceHandle **phDevice);
DALResult
DAL_DeviceAttachLocal(const char *pszArg,DALDEVICEID DeviceId,
                      DalDeviceHandle **phDevice);
DALResult
DAL_DeviceAttachEx(const char *pszArg, DALDEVICEID DeviceId,
               DALInterfaceVersion ClientVersion,DalDeviceHandle **phDevice);
DALResult
DAL_DeviceAttachRemote(const char *pszArg,
                   DALDEVICEID DevId,
                   DALInterfaceVersion ClientVersion,
                   DalDeviceHandle **phDALDevice);
DALResult
DAL_DeviceDetach(DalDeviceHandle *hDevice);
DALResult
DAL_StringDeviceAttachLocal(const char *pszArg, const char *pszDevName, 
                           DalDeviceHandle **phDalDevice);
DALResult
DAL_StringDeviceAttach(const char *pszDevName, DalDeviceHandle **phDalDevice);
DALResult
DAL_StringDeviceAttachEx(const char *pszArg,
      const char *pszDevName,
      DALInterfaceVersion ClientVersion,
      DalDeviceHandle **phDALDevice); 
typedef struct DALREG_DriverInfo DALREG_DriverInfo;
struct DALREG_DriverInfo
{
	DALResult (*pfnDALNewFunc)(const char * , DALDEVICEID, DalDeviceHandle**);
	uint32 dwNumDevices;
	DALDEVICEID *pDeviceId;
};
typedef struct DALREG_DriverInfoList DALREG_DriverInfoList;
struct DALREG_DriverInfoList
{
	uint32 dwLen;
	DALREG_DriverInfo ** pDriverInfo;
};
typedef void  * DALSYSObjHandle;
typedef void  * DALSYSSyncHandle;
typedef void  * DALSYSMemHandle;
typedef void  * DALSYSWorkLoopHandle;
typedef uint32 *DALSYSPropertyHandle;
typedef struct  DALSYSPropertyVar DALSYSPropertyVar;
struct DALSYSPropertyVar
{
    uint32 dwType;
    uint32 dwLen;
    union
    {
        byte *pbVal;
        char *pszVal;
        uint32 dwVal;
        uint32 *pdwVal;
        const void *pStruct;
    }Val;
};
typedef struct  StringDevice StringDevice;
 struct StringDevice{
   const char *pszName; 
   uint32 dwHash; 
   uint32 dwOffset; 
   DALREG_DriverInfo *pFunctionName; 
   uint32 dwNumCollision; 
   uint32 *pdwCollisions; 
};
typedef struct DALProps DALProps;
struct DALProps
{
   const byte *pDALPROP_PropBin;
   const void **pDALPROP_StructPtrs;
   uint32 dwDeviceSize; 
   const StringDevice * pDevices;     
};
typedef struct DALSYSBaseObj DALSYSBaseObj;
struct DALSYSBaseObj
{
   uint32 dwObjInfo;
   uint32 hOwnerProc;
   DALSYSMemAddr thisVirtualAddr;
};
typedef struct DALSYSMemObjBase DALSYSMemObjBase;
struct DALSYSMemObjBase
{
   uint32 dwObjInfo; uint32 hOwnerProc; DALSYSMemAddr thisVirtualAddr;
   uint32        dwLen;
   DALSYSMemAddr OwnerVirtualAddr;
   DALSYSMemAddr VirtualAddr;
   DALSYSMemAddr PhysicalAddr;
};
typedef struct DALSYSEventObj  DALSYSEventObj;
struct DALSYSEventObj
{
   unsigned long long _bSpace[64/sizeof(unsigned long long)];
};
typedef struct DALSYSSyncObj  DALSYSSyncObj;
struct DALSYSSyncObj
{
   unsigned long long _bSpace[40/sizeof(unsigned long long)];
};
typedef struct DALSYSMemObj  DALSYSMemObj;
struct DALSYSMemObj
{
   unsigned long long _bSpace[36/sizeof(unsigned long long)];
};
typedef struct DALSYSWorkLoopEventObj DALSYSWorkLoopEventObj;
struct DALSYSWorkLoopEventObj
{
   unsigned long long _bSpace[32/sizeof(unsigned long long)];
};
typedef struct DALSYSWorkLoopObj DALSYSWorkLoopObj;
struct DALSYSWorkLoopObj
{
   unsigned long long _bSpace[40/sizeof(unsigned long long)];
};
typedef void * DALSYSCallbackFuncCtx;
typedef void * (*DALSYSCallbackFunc)(void*,uint32,void*,uint32);
typedef struct DALSYSMemInfo DALSYSMemInfo;
struct DALSYSMemInfo
{
    DALSYSMemAddr VirtualAddr;
    DALSYSMemAddr PhysicalAddr;
    uint32        dwLen;
    uint32        dwMappedLen;
    uint32        dwProps;
};
typedef DALResult
(*DALSYSWorkLoopExecute)
(
    DALSYSEventHandle,
    void *
);
typedef void
(*DALSYS_InitSystemHandleFncPtr)
(
    DalDeviceHandle * hDalDevice
);
typedef DALResult
(*DALSYS_DestroyObjectFncPtr)
(
    DALSYSObjHandle
);
typedef DALResult
(*DALSYS_CopyObjectFncPtr)
(
    DALSYSObjHandle,
    DALSYSObjHandle *
);
typedef DALResult
(*DALSYS_RegisterWorkLoopFncPtr)
(
    uint32,
    uint32,
    DALSYSWorkLoopHandle *,
    DALSYSWorkLoopObj *
);
typedef DALResult
(*DALSYS_AddEventToWorkLoopFncPtr)
(
    DALSYSWorkLoopHandle,
    DALSYSWorkLoopExecute,
    void *,
    DALSYSEventHandle,
    DALSYSSyncHandle
);
typedef DALResult
(*DALSYS_DeleteEventFromWorkLoopFncPtr)
(
    DALSYSWorkLoopHandle,
    DALSYSEventHandle
);
typedef DALResult
(*DALSYS_EventCreateFncPtr)
(
    uint32 ,
    DALSYSEventHandle *,
    DALSYSEventObj *
);
typedef DALResult
(*DALSYS_EventCtrlFncPtr)
(
    DALSYSEventHandle,
    uint32,
   uint32,
   void *,
   uint32
);
typedef DALResult
(*DALSYS_EventWaitFncPtr)
(
    DALSYSEventHandle
);
typedef DALResult
(*DALSYS_EventMultipleWaitFncPtr)
(
    DALSYSEventHandle*,
    int,
    uint32,
    uint32 *
);
typedef DALResult
(*DALSYS_SetupCallbackEventFncPtr)
(
    DALSYSEventHandle,
    DALSYSCallbackFunc,
    DALSYSCallbackFuncCtx
);
typedef DALResult
(*DALSYS_SyncCreateFncPtr)
(
    uint32,
    DALSYSSyncHandle *,
    DALSYSSyncObj *
);
typedef void
(*DALSYS_SyncEnterFncPtr)
(
    DALSYSSyncHandle
);
typedef void
(*DALSYS_SyncLeaveFncPtr)
(
    DALSYSSyncHandle
);
typedef DALResult
(*DALSYS_MemRegionAllocFncPtr)
(
    uint32,
    DALSYSMemAddr,
    DALSYSMemAddr,
    uint32,
    DALSYSMemHandle *,
    DALSYSMemObj *
);
typedef DALResult
(*DALSYS_MemRegionMapPhysFncPtr)
(
    DALSYSMemHandle,
    uint32,
    DALSYSMemAddr,
    uint32
);
typedef DALResult
(*DALSYS_MemInfoFncPtr)
(
    DALSYSMemHandle,
    DALSYSMemInfo *
);
typedef DALResult
(*DALSYS_CacheCommandFncPtr)
(
    uint32 ,
    DALSYSMemAddr,
    uint32
);
typedef DALResult
(*DALSYS_MallocFncPtr)
(
    uint32 ,
    void **
);
typedef DALResult
(*DALSYS_FreeFncPtr)
(
    void *
);
typedef void
(*DALSYS_BusyWaitFncPtr)
(
   uint32
);
typedef DALResult
(*DALSYS_MemDescAddBufFncPtr)
(
    DALSysMemDescList *,
    uint32,
    uint32,
    uint32
);
typedef DALResult
(*DALSYS_MemDescPrepareFncPtr)
(
    DALSysMemDescList *,
    uint32
);
typedef DALResult
(*DALSYS_MemDescValidateFncPtr)
(
    DALSysMemDescList *,
    uint32
);
typedef DALResult
(*DALSYS_GetDALPropertyHandleFncPtr)
(
    DALDEVICEID,
    DALSYSPropertyHandle
);
typedef DALResult
(*DAL_DeviceAttachFncPtr)
(
    const char *pszArg,
    DALDEVICEID,
    DalDeviceHandle **
);
typedef DALResult
(*DAL_DeviceDetachFncPtr)
(
    DalDeviceHandle *
);
typedef DALResult
(*DAL_DeviceAttachExFncPtr)
(
	const char *pszArg,
    DALDEVICEID DevId,
    DALInterfaceVersion ClientVersion,
    DalDeviceHandle **phDalDevice
);
typedef DALResult
(*DALSYS_GetPropertyValueFncPtr)
(
    DALSYSPropertyHandle,
    const char *,
    uint32,
    DALSYSPropertyVar *
);
typedef void
(*DALSYS_LogEventFncPtr)
(
    DALDEVICEID,
    uint32,
    const char *
);
typedef struct DALSYSFncPtrTbl DALSYSFncPtrTbl;
struct DALSYSFncPtrTbl
{
    DALSYS_InitSystemHandleFncPtr DALSYS_InitSystemHandleFnc;
    DALSYS_DestroyObjectFncPtr DALSYS_DestroyObjectFnc;
    DALSYS_CopyObjectFncPtr DALSYS_CopyObjectFnc;
    DALSYS_RegisterWorkLoopFncPtr DALSYS_RegisterWorkLoopFnc;
    DALSYS_AddEventToWorkLoopFncPtr DALSYS_AddEventToWorkLoopFnc;
    DALSYS_DeleteEventFromWorkLoopFncPtr DALSYS_DeleteEventFromWorkLoopFnc;
    DALSYS_EventCreateFncPtr DALSYS_EventCreateFnc;
    DALSYS_EventCtrlFncPtr DALSYS_EventCtrlFnc;
    DALSYS_EventWaitFncPtr DALSYS_EventWaitFnc;
    DALSYS_EventMultipleWaitFncPtr DALSYS_EventMultipleWaitFnc;
    DALSYS_SetupCallbackEventFncPtr DALSYS_SetupCallbackEventFnc;
    DALSYS_SyncCreateFncPtr DALSYS_SyncCreateFnc;
    DALSYS_SyncEnterFncPtr DALSYS_SyncEnterFnc;
    DALSYS_SyncLeaveFncPtr DALSYS_SyncLeaveFnc;
    DALSYS_MemRegionAllocFncPtr DALSYS_MemRegionAllocFnc;
    DALSYS_MemRegionMapPhysFncPtr DALSYS_MemRegionMapPhysFnc;
    DALSYS_MemInfoFncPtr DALSYS_MemInfoFnc;
    DALSYS_CacheCommandFncPtr DALSYS_CacheCommandFnc;
    DALSYS_MallocFncPtr DALSYS_MallocFnc;
    DALSYS_FreeFncPtr DALSYS_FreeFnc;
    DALSYS_BusyWaitFncPtr DALSYS_BusyWaitFnc;
    DALSYS_MemDescAddBufFncPtr DALSYS_MemDescAddBufFnc;
    DALSYS_MemDescPrepareFncPtr DALSYS_MemDescPrepareFnc;
    DALSYS_MemDescValidateFncPtr DALSYS_MemDescValidateFnc;
    DALSYS_GetDALPropertyHandleFncPtr DALSYS_GetDALPropertyHandleFnc;
    DAL_DeviceAttachFncPtr DALSYS_DeviceAttachFnc;
	 DAL_DeviceAttachExFncPtr DALSYS_DeviceAttachExFnc;
	 DAL_DeviceAttachExFncPtr DALSYS_DeviceAttachRemoteFnc;
    DAL_DeviceDetachFncPtr DALSYS_DeviceDetachFnc;
    DALSYS_GetPropertyValueFncPtr DALSYS_GetPropertyValueFnc;
    DALSYS_LogEventFncPtr DALSYS_LogEventFnc;
};
typedef DALResult
(*DALRemote_NewFncPtr)(const char *, DALDEVICEID, DalDeviceHandle **);
typedef int
(*DALRemote_CommonInitFncPtr)(void);
typedef void
(*DALRemote_IPCInitFcnPtr)(uint32);
typedef void
(*DALRemote_InitFncPtr)(void);
typedef DALSYSEventHandle
(*DALRemote_CreateEventFncPtr)(void *pClientCtxt, DALSYSEventHandle hRemote);
typedef uint32
(*DALRemoteInterProcessCallFncPtr)(void *in_buf, void *out_buf);
typedef void
(*DALRemote_DeinitFncPtr)(void);
typedef struct DALRemoteVtbl DALRemoteVtbl;
struct DALRemoteVtbl
{
   DALRemote_NewFncPtr DALRemote_NewFnc;
   DALRemote_CommonInitFncPtr DALRemote_CommonInitFnc;
   DALRemote_InitFncPtr DALRemote_InitFnc;
   DALRemote_DeinitFncPtr DALRemote_DeinitFnc;
   DALRemote_CreateEventFncPtr DALRemote_CreateEventFnc;
   DALRemote_CreateEventFncPtr DALRemote_CreatePayloadEventFnc;
   DALRemoteInterProcessCallFncPtr DALRemoteInterProcessCallFnc;
   DALRemote_IPCInitFcnPtr DALRemote_IPCInitFcn;
};
typedef struct DALSYSConfig DALSYSConfig;
struct DALSYSConfig
{
    void *pNativeEnv;
    uint32 dwConfig;
   DALRemoteVtbl *pRemoteVtbl;
};
  typedef unsigned int size_t;
extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));
extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));
extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) char *strerror(int  );
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
void
DALSYS_InitMod(DALSYSConfig * pCfg);
void
DALSYS_DeInitMod(void);
void
DALSYS_InitSystemHandle(DalDeviceHandle *hDalDevice);
DALSYS_LogEventFncPtr
DALSYS_SetLogCfg(uint32 dwMaxLogLevel, DALSYS_LogEventFncPtr DALSysLogFcn);
DALResult
DALSYS_DestroyObject(DALSYSObjHandle hObj);
DALResult
DALSYS_CopyObject(DALSYSObjHandle hObjOrig, DALSYSObjHandle *phObjCopy );
DALResult
DALSYS_RegisterWorkLoop(uint32 dwPriority,
                  uint32 dwMaxNumEvents,
                  DALSYSWorkLoopHandle *phWorkLoop,
                  DALSYSWorkLoopObj *pWorkLoopObj);
DALResult
DALSYS_AddEventToWorkLoop(DALSYSWorkLoopHandle hWorkLoop,
                    DALSYSWorkLoopExecute pfnWorkLoopExecute,
                    void * pArg,
                    DALSYSEventHandle hEvent,
                    DALSYSSyncHandle hSync);
DALResult
DALSYS_DeleteEventFromWorkLoop(DALSYSWorkLoopHandle hWorkLoop,
                         DALSYSEventHandle hEvent);
DALResult
DALSYS_EventCreate(uint32 dwAttribs, DALSYSEventHandle *phEvent,
               DALSYSEventObj *pEventObj);
DALResult
DALSYS_EventCopy(DALSYSEventHandle hEvent,
             DALSYSEventHandle *phEventCopy,DALSYSEventObj *pEventObjCopy,
                 uint32 dwMarshalFlags);
DALResult
DALSYS_EventCtrlEx(DALSYSEventHandle hEvent, uint32 dwCtrl, uint32 dwParam,
                   void *pPayload, uint32 dwPayloadSize);
DALResult
DALSYS_EventWait(DALSYSEventHandle hEvent);
DALResult
DALSYS_EventMultipleWait(DALSYSEventHandle* phEvent, int nEvents,
                         uint32 dwTimeoutUs,uint32 *pdwEventIdx);
DALResult
DALSYS_SetupCallbackEvent(DALSYSEventHandle hEvent, DALSYSCallbackFunc cbFunc,
                          DALSYSCallbackFuncCtx cbFuncCtx);
DALResult
DALSYS_SyncCreate(uint32 dwAttribs,
                  DALSYSSyncHandle *phSync,
                  DALSYSSyncObj *pSyncObj);
void
DALSYS_SyncEnter(DALSYSSyncHandle hSync);
void
DALSYS_SyncLeave(DALSYSSyncHandle hSync);
DALResult
DALSYS_MemRegionAlloc(uint32 dwAttribs, DALSYSMemAddr VirtualAddr,
                      DALSYSMemAddr PhysicalAddr, uint32 dwLen, DALSYSMemHandle *phMem,
                  DALSYSMemObj *pMemObj);
DALResult
DALSYS_MemRegionMapPhys(DALSYSMemHandle hMem, uint32 dwVirtualBaseOffset,
                        DALSYSMemAddr PhysicalAddr, uint32 dwLen);
DALResult
DALSYS_MemInfo(DALSYSMemHandle hMem, DALSYSMemInfo *pMemInfo);
DALResult
DALSYS_CacheCommand(uint32 CacheCmd, DALSYSMemAddr VirtualAddr, uint32 dwLen);
DALResult
DALSYS_Malloc(uint32 dwSize, void **ppMem);
DALResult
DALSYS_Free(void *pmem);
void
DALSYS_BusyWait(uint32 pause_time_us);
DALResult
DALSYS_GetDALPropertyHandle(DALDEVICEID DeviceId,DALSYSPropertyHandle hDALProps);
DALResult
DALSYS_GetDALPropertyHandleStr(const char *pszDevName, DALSYSPropertyHandle hDALProps);
DALResult
DALSYS_GetPropertyValue(DALSYSPropertyHandle hDALProps, const char *pszName,
                  uint32 dwId,
                   DALSYSPropertyVar *pDALPropVar);
void
DALSYS_LogEvent(DALDEVICEID DeviceId, uint32 dwLogEventType, const char * pszFmt,
                ...);
DALRemoteVtbl *
DALSYS_GetRemoteInterfaceVtbl(void);
uint32 DALSYS_SetThreadPriority(uint32 priority);
uint32 _DALSYS_memscpy(void * pDest, uint32 iDestSz, 
      const void * pSrc, uint32 iSrcSize);
typedef uint32 DalChipInfoVersionType;
typedef uint32 DalChipInfoModemType;
typedef enum
{
  DALCHIPINFO_ID_UNKNOWN    = 0,
  DALCHIPINFO_ID_MDM1000    = 1,
  DALCHIPINFO_ID_ESM6235    = 2,
  DALCHIPINFO_ID_QSC6240    = 3,
  DALCHIPINFO_ID_MSM6245    = 4,
  DALCHIPINFO_ID_MSM6255    = 5,
  DALCHIPINFO_ID_MSM6255A   = 6,
  DALCHIPINFO_ID_MSM6260    = 7,
  DALCHIPINFO_ID_MSM6246    = 8,
  DALCHIPINFO_ID_QSC6270    = 9,
  DALCHIPINFO_ID_MSM6280    = 10,
  DALCHIPINFO_ID_MSM6290    = 11,
  DALCHIPINFO_ID_MSM7200    = 12,
  DALCHIPINFO_ID_MSM7201    = 13,
  DALCHIPINFO_ID_ESM7205    = 14,
  DALCHIPINFO_ID_ESM7206    = 15,
  DALCHIPINFO_ID_MSM7200A   = 16,
  DALCHIPINFO_ID_MSM7201A   = 17,
  DALCHIPINFO_ID_ESM7205A   = 18,
  DALCHIPINFO_ID_ESM7206A   = 19,
  DALCHIPINFO_ID_ESM7225    = 20,
  DALCHIPINFO_ID_MSM7225    = 21,
  DALCHIPINFO_ID_MSM7500    = 22,
  DALCHIPINFO_ID_MSM7500A   = 23,
  DALCHIPINFO_ID_MSM7525    = 24,
  DALCHIPINFO_ID_MSM7600    = 25,
  DALCHIPINFO_ID_MSM7601    = 26,
  DALCHIPINFO_ID_MSM7625    = 27,
  DALCHIPINFO_ID_MSM7800    = 28,
  DALCHIPINFO_ID_MDM8200    = 29,
  DALCHIPINFO_ID_QSD8650    = 30,
  DALCHIPINFO_ID_MDM8900    = 31,
  DALCHIPINFO_ID_QST1000    = 32,
  DALCHIPINFO_ID_QST1005    = 33,
  DALCHIPINFO_ID_QST1100    = 34,
  DALCHIPINFO_ID_QST1105    = 35,
  DALCHIPINFO_ID_QST1500    = 40,
  DALCHIPINFO_ID_QST1600    = 41,
  DALCHIPINFO_ID_QST1700    = 42,
  DALCHIPINFO_ID_QSD8250    = 36,
  DALCHIPINFO_ID_QSD8550    = 37,
  DALCHIPINFO_ID_QSD8850    = 38,
  DALCHIPINFO_ID_MDM2000    = 39,
  DALCHIPINFO_ID_MSM7227    = 43,
  DALCHIPINFO_ID_MSM7627    = 44,
  DALCHIPINFO_ID_QSC6165    = 45,
  DALCHIPINFO_ID_QSC6175    = 46,
  DALCHIPINFO_ID_QSC6185    = 47,
  DALCHIPINFO_ID_QSC6195    = 48,
  DALCHIPINFO_ID_QSC6285    = 49,
  DALCHIPINFO_ID_QSC6295    = 50,
  DALCHIPINFO_ID_QSC6695    = 51,
  DALCHIPINFO_ID_ESM6246    = 52,
  DALCHIPINFO_ID_ESM6290    = 53,
  DALCHIPINFO_ID_ESC6270    = 54,
  DALCHIPINFO_ID_ESC6240    = 55,
  DALCHIPINFO_ID_MDM8220    = 56,
  DALCHIPINFO_ID_MDM9200    = 57,
  DALCHIPINFO_ID_MDM9600    = 58,
  DALCHIPINFO_ID_MSM7630    = 59,
  DALCHIPINFO_ID_MSM7230    = 60,
  DALCHIPINFO_ID_ESM7227    = 61,
  DALCHIPINFO_ID_MSM7625D1  = 62,
  DALCHIPINFO_ID_MSM7225D1  = 63,
  DALCHIPINFO_ID_QSD8250A   = 64,
  DALCHIPINFO_ID_QSD8650A   = 65,
  DALCHIPINFO_ID_MSM7625D2  = 66,
  DALCHIPINFO_ID_MSM7227D1  = 67,
  DALCHIPINFO_ID_MSM7627D1  = 68,
  DALCHIPINFO_ID_MSM7627D2  = 69,
  DALCHIPINFO_ID_MSM8260    = 70,
  DALCHIPINFO_ID_MSM8660    = 71,
  DALCHIPINFO_ID_MDM8200A   = 72,
  DALCHIPINFO_ID_QSC6155    = 73,
  DALCHIPINFO_ID_MSM8255    = 74,
  DALCHIPINFO_ID_MSM8655    = 75,
  DALCHIPINFO_ID_ESC6295    = 76,
  DALCHIPINFO_ID_MDM3000    = 77,
  DALCHIPINFO_ID_MDM6200    = 78,
  DALCHIPINFO_ID_MDM6600    = 79,
  DALCHIPINFO_ID_MDM6210    = 80,
  DALCHIPINFO_ID_MDM6610    = 81,
  DALCHIPINFO_ID_QSD8672    = 82,
  DALCHIPINFO_ID_MDM6215    = 83,
  DALCHIPINFO_ID_MDM6615    = 84,
  DALCHIPINFO_ID_APQ8055    = 85,
  DALCHIPINFO_ID_APQ8060    = 86,
  DALCHIPINFO_ID_MSM8960    = 87,
  DALCHIPINFO_ID_MSM7225A   = 88,
  DALCHIPINFO_ID_MSM7625A   = 89,
  DALCHIPINFO_ID_MSM7227A   = 90,
  DALCHIPINFO_ID_MSM7627A   = 91,
  DALCHIPINFO_ID_ESM7227A   = 92,
  DALCHIPINFO_ID_QSC6195D2  = 93,
  DALCHIPINFO_ID_FSM9200    = 94,
  DALCHIPINFO_ID_FSM9800    = 95,
  DALCHIPINFO_ID_MSM7225AD1 = 96,
  DALCHIPINFO_ID_MSM7227AD1 = 97,
  DALCHIPINFO_ID_MSM7225AA   = 98,
  DALCHIPINFO_ID_MSM7225AAD1 = 99,
  DALCHIPINFO_ID_MSM7625AA   = 100,
  DALCHIPINFO_ID_MSM7227AA   = 101,
  DALCHIPINFO_ID_MSM7227AAD1 = 102,
  DALCHIPINFO_ID_MSM7627AA   = 103,
  DALCHIPINFO_ID_MDM9615     = 104,
  DALCHIPINFO_ID_MDM9615M    = DALCHIPINFO_ID_MDM9615,
  DALCHIPINFO_ID_MDM8215     = 106,
  DALCHIPINFO_ID_MDM9215     = 107,  
  DALCHIPINFO_ID_MDM9215M    = DALCHIPINFO_ID_MDM9215,
  DALCHIPINFO_ID_APQ8064     = 109,
  DALCHIPINFO_ID_QSC6270D1   = 110,
  DALCHIPINFO_ID_QSC6240D1   = 111,
  DALCHIPINFO_ID_ESC6270D1   = 112,
  DALCHIPINFO_ID_ESC6240D1   = 113,
  DALCHIPINFO_ID_MDM6270     = 114,
  DALCHIPINFO_ID_MDM6270D1   = 115,
  DALCHIPINFO_ID_MSM8930     = 116,
  DALCHIPINFO_ID_MSM8630     = 117,  
  DALCHIPINFO_ID_MSM8230     = 118,
  DALCHIPINFO_ID_APQ8030     = 119, 
  DALCHIPINFO_ID_MSM8627     = 120, 
  DALCHIPINFO_ID_MSM8227     = 121, 
  DALCHIPINFO_ID_MSM8660A    = 122, 
  DALCHIPINFO_ID_MSM8260A    = 123,
  DALCHIPINFO_ID_APQ8060A    = 124,
  DALCHIPINFO_ID_MPQ8062     = 125,
  DALCHIPINFO_ID_MSM8974     = 126,
  DALCHIPINFO_ID_MSM8225     = 127,
  DALCHIPINFO_ID_MSM8225D1   = 128,
  DALCHIPINFO_ID_MSM8625     = 129,
  DALCHIPINFO_ID_MPQ8064     = 130,
  DALCHIPINFO_ID_MSM7225AB   = 131,
  DALCHIPINFO_ID_MSM7225ABD1 = 132,
  DALCHIPINFO_ID_MSM7625AB   = 133,
  DALCHIPINFO_ID_MDM9625     = 134,
  DALCHIPINFO_ID_MSM7125A    = 135,
  DALCHIPINFO_ID_MSM7127A    = 136,
  DALCHIPINFO_ID_MSM8125AB   = 137,
  DALCHIPINFO_ID_MSM8960AB   = 138,
  DALCHIPINFO_ID_APQ8060AB   = 139,
  DALCHIPINFO_ID_MSM8260AB   = 140,
  DALCHIPINFO_ID_MSM8660AB   = 141,
  DALCHIPINFO_ID_MSM8930AA   = 142,
  DALCHIPINFO_ID_MSM8630AA   = 143,
  DALCHIPINFO_ID_MSM8230AA   = 144,
  DALCHIPINFO_ID_MSM8626     = 145,
  DALCHIPINFO_ID_MPQ8092     = 146,
  DALCHIPINFO_ID_MSM8610     = 147,
  DALCHIPINFO_ID_MDM8225     = 148,
  DALCHIPINFO_ID_MDM9225     = 149,
  DALCHIPINFO_ID_MDM9225M    = 150,
  DALCHIPINFO_ID_MDM8225M    = 151,
  DALCHIPINFO_ID_MDM9625M    = 152,
  DALCHIPINFO_ID_APQ8064_V2PRIME   = 153,
  DALCHIPINFO_ID_MSM8930AB   = 154,
  DALCHIPINFO_ID_MSM8630AB   = 155,
  DALCHIPINFO_ID_MSM8230AB   = 156,
  DALCHIPINFO_ID_APQ8030AB   = 157,
  DALCHIPINFO_ID_MSM8226     = 158,
  DALCHIPINFO_ID_MSM8526     = 159,
  DALCHIPINFO_ID_APQ8030AA   = 160,
  DALCHIPINFO_ID_MSM8110     = 161,  
  DALCHIPINFO_ID_MSM8210     = 162,  
  DALCHIPINFO_ID_MSM8810     = 163,  
  DALCHIPINFO_ID_MSM8212     = 164,  
  DALCHIPINFO_ID_MSM8612     = 165,  
  DALCHIPINFO_ID_MSM8112     = 166,
  DALCHIPINFO_ID_MSM8125     = 167,
  DALCHIPINFO_ID_MSM8225Q    = 168,
  DALCHIPINFO_ID_MSM8625Q    = 169,
  DALCHIPINFO_ID_MSM8125Q    = 170,
  DALCHIPINFO_ID_MDM9310     = 171,
  DALCHIPINFO_ID_APQ8064_SLOW_PRIME = 172,
  DALCHIPINFO_ID_MDM8110M    = 173,
  DALCHIPINFO_ID_MDM8615M    = 174,
  DALCHIPINFO_ID_MDM9320     = 175,  
  DALCHIPINFO_ID_MDM9225_1   = 176,  
  DALCHIPINFO_ID_MDM9225M_1  = 177,
  DALCHIPINFO_ID_APQ8084     = 178,
  DALCHIPINFO_ID_MSM8130     = 179,
  DALCHIPINFO_ID_MSM8130AA   = 180,
  DALCHIPINFO_ID_MSM8130AB   = 181,
  DALCHIPINFO_ID_MSM8627AA   = 182,
  DALCHIPINFO_ID_MSM8227AA   = 183,
  DALCHIPINFO_ID_APQ8074     = 184,
  DALCHIPINFO_ID_MSM8274     = 185,
  DALCHIPINFO_ID_MSM8674     = 186,
  DALCHIPINFO_ID_MDM9635     = 187,
  DALCHIPINFO_ID_FSM9900     = 188,
  DALCHIPINFO_ID_FSM9965     = 189,
  DALCHIPINFO_ID_FSM9955     = 190,
  DALCHIPINFO_ID_FSM9950     = 191,
  DALCHIPINFO_ID_FSM9915     = 192,
  DALCHIPINFO_ID_FSM9910     = 193,
  DALCHIPINFO_ID_MSM8974_PRO = 194,
  DALCHIPINFO_ID_MSM8962     = 195,
  DALCHIPINFO_ID_MSM8262     = 196,
  DALCHIPINFO_ID_APQ8062     = 197,
  DALCHIPINFO_ID_MSM8126     = 198,
  DALCHIPINFO_ID_APQ8026     = 199,
  DALCHIPINFO_ID_MSM8926     = 200,
  DALCHIPINFO_ID_MSM8326     = 205,
  DALCHIPINFO_ID_MSM8916     = 206,
  DALCHIPINFO_ID_MSM8994     = 207,
  DALCHIPINFO_ID_APQ8074_AA  = 208,
  DALCHIPINFO_ID_APQ8074_AB  = 209,
  DALCHIPINFO_ID_APQ8074_PRO = 210,
  DALCHIPINFO_ID_MSM8274_AA  = 211,
  DALCHIPINFO_ID_MSM8274_AB  = 212,
  DALCHIPINFO_ID_MSM8274_PRO = 213,
  DALCHIPINFO_ID_MSM8674_AA  = 214,
  DALCHIPINFO_ID_MSM8674_AB  = 215,
  DALCHIPINFO_ID_MSM8674_PRO = 216,
  DALCHIPINFO_ID_MSM8974_AA  = 217,
  DALCHIPINFO_ID_MSM8974_AB  = 218,
  DALCHIPINFO_ID_APQ8028     = 219,
  DALCHIPINFO_ID_MSM8128     = 220,
  DALCHIPINFO_ID_MSM8228     = 221,
  DALCHIPINFO_ID_MSM8528     = 222,
  DALCHIPINFO_ID_MSM8628     = 223,
  DALCHIPINFO_ID_MSM8928     = 224,
  DALCHIPINFO_ID_MSM8510     = 225,
  DALCHIPINFO_ID_MSM8512     = 226,
  DALCHIPINFO_ID_MDM9630     = 227,
  DALCHIPINFO_ID_MDM9635M    = DALCHIPINFO_ID_MDM9635,
  DALCHIPINFO_ID_MDM9230     = 228,
  DALCHIPINFO_ID_MDM9235M    = 229,
  DALCHIPINFO_ID_MDM8630     = 230,
  DALCHIPINFO_ID_MDM9330     = 231, 
  DALCHIPINFO_ID_MPQ8091     = 232,
  DALCHIPINFO_ID_MSM8936     = 233,
  DALCHIPINFO_ID_MDM9240     = 234,
  DALCHIPINFO_ID_MDM9340     = 235,
  DALCHIPINFO_ID_MDM9640     = 236,
  DALCHIPINFO_ID_MDM9245     = 237,
  DALCHIPINFO_ID_MDM9645     = 238,
  DALCHIPINFO_ID_MSM8939     = 239,
  DALCHIPINFO_ID_APQ8036     = 240,
  DALCHIPINFO_ID_APQ8039     = 241,
  DALCHIPINFO_ID_MSM8236     = 242,
  DALCHIPINFO_ID_MSM8636     = 243,
  DALCHIPINFO_ID_APQ8064_AU  = 244,
  DALCHIPINFO_ID_MSM8909     = 245,
  DALCHIPINFO_ID_MSM8996     = 246,
  DALCHIPINFO_ID_APQ8016     = 247,
  DALCHIPINFO_ID_MSM8216     = 248,
  DALCHIPINFO_ID_MSM8116     = 249,
  DALCHIPINFO_ID_MSM8616     = 250,
  DALCHIPINFO_ID_MSM8992     = 251,
  DALCHIPINFO_ID_APQ8092     = 252,
  DALCHIPINFO_ID_APQ8094     = 253,
  DALCHIPINFO_ID_FSM9008     = 254,
  DALCHIPINFO_ID_FSM9010     = 255,
  DALCHIPINFO_ID_FSM9016     = 256,
  DALCHIPINFO_ID_FSM9055     = 257,
  DALCHIPINFO_ID_MSM8209     = 258,
  DALCHIPINFO_ID_MSM8208     = 259,
  DALCHIPINFO_ID_MDM9209     = 260,
  DALCHIPINFO_ID_MDM9309     = 261,
  DALCHIPINFO_ID_MDM9609     = 262,
  DALCHIPINFO_ID_MSM8239     = 263,
  DALCHIPINFO_ID_MSM8952     = 264,
  DALCHIPINFO_ID_APQ8009     = 265,
  DALCHIPINFO_ID_MSM8956     = 266,
  DALCHIPINFO_ID_QDF2432     = 267,
  DALCHIPINFO_ID_MSM8929     = 268,
  DALCHIPINFO_ID_MSM8629     = 269,
  DALCHIPINFO_ID_MSM8229     = 270,
  DALCHIPINFO_ID_APQ8029     = 271,
  DALCHIPINFO_ID_QCA9618     = 272,
  DALCHIPINFO_ID_QCA9619     = 273,
  DALCHIPINFO_ID_APQ8056     = 274,
  DALCHIPINFO_ID_MSM8609     = 275,
  DALCHIPINFO_ID_FSM9916     = 276,
  DALCHIPINFO_ID_APQ8076     = 277,
  DALCHIPINFO_ID_MSM8976     = 278,
  DALCHIPINFO_ID_MDM9650     = 279,
  DALCHIPINFO_ID_IPQ8065     = 280,
  DALCHIPINFO_ID_IPQ8069     = 281,
  DALCHIPINFO_ID_MSM8939_BC  = 282,
  DALCHIPINFO_ID_MDM9250     = 283,
  DALCHIPINFO_ID_MDM9255     = 284,
  DALCHIPINFO_ID_MDM9350     = 285,
  DALCHIPINFO_ID_MDM9655     = 286,
  DALCHIPINFO_ID_IPQ4028     = 287,
  DALCHIPINFO_ID_IPQ4029     = 288,
  DALCHIPINFO_ID_APQ8052     = 289,
  DALCHIPINFO_ID_MDM9607     = 290,
  DALCHIPINFO_ID_APQ8096     = 291,
  DALCHIPINFO_ID_MSM8998     = 292,
  DALCHIPINFO_ID_MSM8953     = 293,
  DALCHIPINFO_ID_MSM8937     = 294,
  DALCHIPINFO_ID_APQ8037     = 295,
  DALCHIPINFO_ID_MDM8207     = 296,
  DALCHIPINFO_ID_MDM9207     = 297,
  DALCHIPINFO_ID_MDM9307     = 298,
  DALCHIPINFO_ID_MDM9628     = 299,
  DALCHIPINFO_ID_MSM8909W    = 300,
  DALCHIPINFO_ID_APQ8009W    = 301,
  DALCHIPINFO_NUM_IDS        = 302,
  DALCHIPINFO_ID_32BITS     = 0x7FFFFFF
} DalChipInfoIdType;
typedef enum
{
  DALCHIPINFO_FAMILY_UNKNOWN    = 0,
  DALCHIPINFO_FAMILY_MSM6246    = 1,
  DALCHIPINFO_FAMILY_MSM6260    = 2,
  DALCHIPINFO_FAMILY_QSC6270    = 3,
  DALCHIPINFO_FAMILY_MSM6280    = 4,
  DALCHIPINFO_FAMILY_MSM6290    = 5,
  DALCHIPINFO_FAMILY_MSM7200    = 6,
  DALCHIPINFO_FAMILY_MSM7500    = 7,
  DALCHIPINFO_FAMILY_MSM7600    = 8,
  DALCHIPINFO_FAMILY_MSM7625    = 9,
  DALCHIPINFO_FAMILY_MSM7X30    = 10,
  DALCHIPINFO_FAMILY_MSM7800    = 11,
  DALCHIPINFO_FAMILY_MDM8200    = 12,
  DALCHIPINFO_FAMILY_QSD8650    = 13,
  DALCHIPINFO_FAMILY_MSM7627    = 14,
  DALCHIPINFO_FAMILY_QSC6695    = 15,
  DALCHIPINFO_FAMILY_MDM9X00    = 16,
  DALCHIPINFO_FAMILY_QSD8650A   = 17,
  DALCHIPINFO_FAMILY_MSM8X60    = 18,
  DALCHIPINFO_FAMILY_MDM8200A   = 19,
  DALCHIPINFO_FAMILY_QSD8672    = 20,
  DALCHIPINFO_FAMILY_MDM6615    = 21,
  DALCHIPINFO_FAMILY_MSM8660    = DALCHIPINFO_FAMILY_MSM8X60,
  DALCHIPINFO_FAMILY_MSM8960    = 22,
  DALCHIPINFO_FAMILY_MSM7625A   = 23,
  DALCHIPINFO_FAMILY_MSM7627A   = 24,
  DALCHIPINFO_FAMILY_MDM9X15    = 25,
  DALCHIPINFO_FAMILY_MSM8930    = 26,
  DALCHIPINFO_FAMILY_MSM8630    = DALCHIPINFO_FAMILY_MSM8930,
  DALCHIPINFO_FAMILY_MSM8230    = DALCHIPINFO_FAMILY_MSM8930,
  DALCHIPINFO_FAMILY_APQ8030    = DALCHIPINFO_FAMILY_MSM8930,
  DALCHIPINFO_FAMILY_MSM8627    = 30,
  DALCHIPINFO_FAMILY_MSM8227    = DALCHIPINFO_FAMILY_MSM8627,
  DALCHIPINFO_FAMILY_MSM8974    = 32,
  DALCHIPINFO_FAMILY_MSM8625    = 33,
  DALCHIPINFO_FAMILY_MSM8225    = DALCHIPINFO_FAMILY_MSM8625,
  DALCHIPINFO_FAMILY_APQ8064    = 34,
  DALCHIPINFO_FAMILY_MDM9x25	= 35,
  DALCHIPINFO_FAMILY_MSM8960AB  = 36,
  DALCHIPINFO_FAMILY_MSM8930AB  = 37,
  DALCHIPINFO_FAMILY_MSM8x10	= 38,
  DALCHIPINFO_FAMILY_MPQ8092    = 39,
  DALCHIPINFO_FAMILY_MSM8x26    = 40,
  DALCHIPINFO_FAMILY_MSM8225Q	= 41,
  DALCHIPINFO_FAMILY_MSM8625Q	= 42,
  DALCHIPINFO_FAMILY_APQ8x94    = 43,
  DALCHIPINFO_FAMILY_APQ8084    = DALCHIPINFO_FAMILY_APQ8x94,
  DALCHIPINFO_FAMILY_MSM8x32    = 44,
  DALCHIPINFO_FAMILY_MDM9x35	= 45,
  DALCHIPINFO_FAMILY_MSM8974_PRO= 46,
  DALCHIPINFO_FAMILY_FSM9900	= 47,
  DALCHIPINFO_FAMILY_MSM8x62	= 48,
  DALCHIPINFO_FAMILY_MSM8926	= 49,
  DALCHIPINFO_FAMILY_MSM8994	= 50,
  DALCHIPINFO_FAMILY_IPQ8064	= 51,
  DALCHIPINFO_FAMILY_MSM8916	= 52,
  DALCHIPINFO_FAMILY_MSM8936	= 53,
  DALCHIPINFO_FAMILY_MDM9x45	= 54,
  DALCHIPINFO_FAMILY_APQ8096	= 55,
  DALCHIPINFO_FAMILY_MSM8996	= 56,
  DALCHIPINFO_FAMILY_MSM8992	= 57,
  DALCHIPINFO_FAMILY_MSM8909	= 58,
  DALCHIPINFO_FAMILY_FSM90xx	= 59,
  DALCHIPINFO_FAMILY_MSM8952	= 60,
  DALCHIPINFO_FAMILY_QDF2432    = 61,
  DALCHIPINFO_FAMILY_MSM8929    = 62,
  DALCHIPINFO_FAMILY_MSM8956    = 63,
  DALCHIPINFO_FAMILY_QCA961x    = 64,
  DALCHIPINFO_FAMILY_MSM8976    = DALCHIPINFO_FAMILY_MSM8956,
  DALCHIPINFO_NUM_FAMILIES      = 65,
  DALCHIPINFO_FAMILY_32BITS     = 0x7FFFFFF
} DalChipInfoFamilyType;
typedef enum
{
  DALCHIPINFO_FOUNDRYID_UNKNOWN    = 0,
  DALCHIPINFO_FOUNDRYID_TSMC       = 1,
  DALCHIPINFO_FOUNDRYID_GF         = 2,
  DALCHIPINFO_FOUNDRYID_SS         = 3,
  DALCHIPINFO_FOUNDRYID_IBM        = 4,
  DALCHIPINFO_FOUNDRYID_UMC        = 5,
  DALCHIPINFO_NUM_FOUNDRYIDS       = 6,
  DALCHIPINFO_FOUNDRYID_32BITS     = 0x7FFFFFF
} DalChipInfoFoundryIdType;
typedef uint32 DalChipInfoSerialNumType;
typedef struct DalChipInfo DalChipInfo;
struct DalChipInfo
{
   DalDevice DalChipInfoDevice;
   DALResult (*GetChipVersion)(DalDeviceHandle * _h,  uint32  nNotUsed,  DalChipInfoVersionType * pnVersion);
   DALResult (*GetRawChipVersion)(DalDeviceHandle * _h,  uint32  nNotUsed,  uint32 * pnVersion);
   DALResult (*GetChipId)(DalDeviceHandle * _h,  uint32  nNotUsed,  DalChipInfoIdType * peId);
   DALResult (*GetRawChipId)(DalDeviceHandle * _h,  uint32  nNotUsed,  uint32 * pnId);
   DALResult (*GetChipIdString)(DalDeviceHandle * _h,  char * szIdString,  uint32  nMaxLength);
   DALResult (*GetChipFamily)(DalDeviceHandle * _h,  uint32  nNotUsed,  DalChipInfoFamilyType * peFamily);
   DALResult (*GetModemSupport)(DalDeviceHandle * _h,  uint32  nNotUsed,  DalChipInfoModemType * pnModem);
   DALResult (*GetFoundryId)(DalDeviceHandle * _h,  uint32  nNotUsed, DalChipInfoFoundryIdType * peFoundryId);
   DALResult (*GetSerialNumber)(DalDeviceHandle * _h,  uint32  nNotUsed, DalChipInfoSerialNumType * pnSerialNum);
};
typedef struct DalChipInfoHandle DalChipInfoHandle; 
struct DalChipInfoHandle 
{
   uint32 dwDalHandleId;
   const DalChipInfo * pVtbl;
   void * pClientCtxt;
};
static __inline DALResult
DalChipInfo_GetChipVersion(DalDeviceHandle * _h,  DalChipInfoVersionType * pnVersion)
{
   if((((DALHandle)_h) & 0x00000001))
   {
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_2(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetChipVersion)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (uint32 )0, (uint32 *)pnVersion);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetChipVersion( _h, 0, pnVersion);
}
static __inline DALResult
DalChipInfo_GetRawChipVersion(DalDeviceHandle * _h,  uint32 * pnVersion)
{
   if((((DALHandle)_h) & 0x00000001))
   {
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_2(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetRawChipVersion)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (uint32 )0, (uint32 *)pnVersion);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetRawChipVersion( _h, 0, pnVersion);
}
static __inline DALResult
DalChipInfo_GetChipId(DalDeviceHandle * _h,  DalChipInfoIdType * peId)
{
   if((((DALHandle)_h) & 0x00000001))
{
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_2(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetChipId)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (uint32 )0, (uint32 *)peId);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetChipId( _h, 0, peId);
}
static __inline DALResult
DalChipInfo_GetRawChipId(DalDeviceHandle * _h,  uint32 * pnId)
{
   if((((DALHandle)_h) & 0x00000001))
{
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_2(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetRawChipId)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (uint32 )0, (uint32 *)pnId);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetRawChipId( _h, 0, pnId);
}
static __inline DALResult
DalChipInfo_GetChipIdString(DalDeviceHandle * _h,  void * szIdString,  uint32  nMaxLength)
{
   if((((DALHandle)_h) & 0x00000001))
   {
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_9(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetChipIdString)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (void * )szIdString, nMaxLength);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetChipIdString( _h, szIdString, nMaxLength);
}
static __inline DALResult
DalChipInfo_GetChipFamily(DalDeviceHandle * _h,  DalChipInfoFamilyType * peFamily)
{
   if((((DALHandle)_h) & 0x00000001))
{
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_2(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetChipFamily)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (uint32 )0, (uint32 *)peFamily);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetChipFamily( _h, 0, peFamily);
}
static __inline DALResult
DalChipInfo_GetModemSupport(DalDeviceHandle * _h,  DalChipInfoModemType * pnModem)
{
   if((((DALHandle)_h) & 0x00000001))
{
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_2(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetModemSupport)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (uint32 )0, (uint32 *)pnModem);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetModemSupport( _h, 0, pnModem);
}
static __inline DalChipInfoVersionType
DalChipInfo_ChipVersion(void)
{
  static DalDeviceHandle        *phChipInfo = 0;
  DALResult                     eResult;
  DalChipInfoVersionType        nVersion;
  if (phChipInfo == 0)
  {
    eResult = 
      DAL_DeviceAttachEx(0,0x0200006F,(((1&0xFFFF)<<16)|(0&0xFFFF)),&phChipInfo);
    if (eResult != 0)
    {
      return (DalChipInfoVersionType)0;
    }
  }
  DalChipInfo_GetChipVersion(phChipInfo, &nVersion);
  return nVersion;
}
static __inline DalChipInfoIdType
DalChipInfo_ChipId(void)
{
  static DalDeviceHandle        *phChipInfo = 0;
  DALResult                     eResult;
  DalChipInfoIdType             neId;
  if (phChipInfo == 0)
  {
    eResult = 
      DAL_DeviceAttachEx(0,0x0200006F,(((1&0xFFFF)<<16)|(0&0xFFFF)),&phChipInfo);
    if (eResult != 0)
    {
      return DALCHIPINFO_ID_UNKNOWN;
    }
  }
  DalChipInfo_GetChipId(phChipInfo, &neId);
  return neId;
}
static __inline DalChipInfoFamilyType
DalChipInfo_ChipFamily(void)
{
  static DalDeviceHandle        *phChipInfo = 0;
  DALResult                     eResult;
  DalChipInfoFamilyType         neFamily;
  if (phChipInfo == 0)
  {
    eResult = 
      DAL_DeviceAttachEx(0,0x0200006F,(((1&0xFFFF)<<16)|(0&0xFFFF)),&phChipInfo);
    if (eResult != 0)
    {
      return DALCHIPINFO_FAMILY_UNKNOWN;
    }
  }
  DalChipInfo_GetChipFamily(phChipInfo, &neFamily);
  return neFamily;
}
static __inline DALResult
DalChipInfo_GetFoundryId(DalDeviceHandle * _h,  DalChipInfoFoundryIdType * peId)
{
   if((((DALHandle)_h) & 0x00000001))
{
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_2(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetFoundryId)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (uint32 )0, (uint32 *)peId);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetFoundryId( _h, 0, peId);
}
static __inline DALResult
DalChipInfo_GetSerialNumber(DalDeviceHandle * _h,  DalChipInfoSerialNumType * pnSerialNum)
{
   if((((DALHandle)_h) & 0x00000001))
{
      DalRemoteHandle *hRemote = (DalRemoteHandle *)(_h = (DalDeviceHandle *)(((DALHandle)_h) & ~0x00000001));
      return hRemote->pVtbl->FCN_2(((uint32 *)&((((DalChipInfoHandle *)_h)->pVtbl)->GetSerialNumber)-(uint32 *)(((DalChipInfoHandle *)_h)->pVtbl)), _h, (uint32 )0, (uint32 *)pnSerialNum);
   }
   return ((DalChipInfoHandle *)_h)->pVtbl->GetSerialNumber( _h, 0, pnSerialNum);
}
typedef enum
{
  CLOCK_BOOT_PERF_NONE,
  CLOCK_BOOT_PERF_MIN,
  CLOCK_BOOT_PERF_NOMINAL,
  CLOCK_BOOT_PERF_MAX,
  CLOCK_BOOT_PERF_DEFAULT,
  CLOCK_BOOT_PERF_NUM,
  CLOCK_BOOT_PERF_32BITS = 0x7FFFFFFF
} ClockBootPerfLevelType;
typedef enum
{
   CLK_SDC_NONE,
   CLK_SDC1,
   CLK_SDC2,
   CLK_SDC3,
   CLK_SDC4,
   CLK_SDC5,
   CLK_SDC_NUM_CLKS
} ClockSDCType;
typedef enum
{
   CLK_BLSP_UART_NONE,
   CLK_BLSP1_UART1_APPS,
   CLK_BLSP1_UART2_APPS,
   CLK_BLSP1_UART3_APPS,
   CLK_BLSP1_UART4_APPS,
   CLK_BLSP1_UART5_APPS,
   CLK_BLSP1_UART6_APPS,
   CLK_BLSP2_UART1_APPS,
   CLK_BLSP2_UART2_APPS,
   CLK_BLSP2_UART3_APPS,
   CLK_BLSP2_UART4_APPS,
   CLK_BLSP2_UART5_APPS,
   CLK_BLSP2_UART6_APPS,
   CLK_BLSP_UART_NUM_CLKS
} ClockUARTType;
typedef enum
{
   CLK_BLSP_QUP_I2C_NONE,
   CLK_BLSP1_QUP1_I2C_APPS,
   CLK_BLSP1_QUP2_I2C_APPS,
   CLK_BLSP1_QUP3_I2C_APPS,
   CLK_BLSP1_QUP4_I2C_APPS,
   CLK_BLSP1_QUP5_I2C_APPS,
   CLK_BLSP1_QUP6_I2C_APPS,
   CLK_BLSP_QUP_I2C_NUM_CLKS
} ClockQUPI2CType;
typedef enum
{
  CLOCK_RESOURCE_QUERY_INVALID         = 0,
  CLOCK_RESOURCE_QUERY_NUM_PERF_LEVELS,
  CLOCK_RESOURCE_QUERY_MIN_FREQ_KHZ, 
  CLOCK_RESOURCE_QUERY_ALL_FREQ_KHZ,
} ClockQueryType;
typedef enum
{
  CLOCK_VREG_LEVEL_OFF          = 0,  
  CLOCK_VREG_LEVEL_LOW_MINUS    = 2,  
  CLOCK_VREG_LEVEL_LOW          = 3,  
  CLOCK_VREG_LEVEL_LOW_PLUS     = 4,  
  CLOCK_VREG_LEVEL_NOMINAL      = 5,  
  CLOCK_VREG_LEVEL_NOMINAL_PLUS = 6,  
  CLOCK_VREG_LEVEL_HIGH_MINUS   = 7,  
  CLOCK_VREG_LEVEL_HIGH         = 8,  
  CLOCK_VREG_LEVEL_HIGH_NO_CPR  = 9,  
  CLOCK_VREG_NUM_LEVELS,
} ClockVRegLevelType;
typedef enum
{
   CLK_APPS,
   CLK_DDR,
   CLK_NUM,
   CLOCK_CLOCK_TYPE_32BITS = 0x7FFFFFFF
} ClockType;
typedef struct 
{
  uint32             nFreqKHz;
  ClockVRegLevelType eVRegLevel;
}ClockPlanType;
boolean Clock_PreDDRInit( uint32 ddr_type );
boolean Clock_PreDDRInitEx( uint32 ddr_type );
boolean Clock_Init(ClockBootPerfLevelType eSysPerfLevel,
                    ClockBootPerfLevelType eCPUPerfLevel);
boolean Clock_SetSysPerfLevel(ClockBootPerfLevelType eSysPerfLevel);
boolean Clock_SetCPUPerfLevel(ClockBootPerfLevelType eCPUPerfLevel);
boolean Clock_SetL2PerfLevel(ClockBootPerfLevelType eL2PerfLevel);
boolean Clock_SetSDCClockFrequency(ClockBootPerfLevelType ePerfLevel,
                                    ClockSDCType eClock);
uint32 Clock_SetSDCClockFrequencyExt( uint32 nFreqKHz, ClockSDCType eClock);
boolean Clock_SetUARTClockFrequency(ClockBootPerfLevelType ePerfLevel,
                                    ClockUARTType eClock);
boolean Clock_DisableUARTClock(ClockUARTType eClock);
boolean Clock_SetI2CClockFrequency
(
  ClockBootPerfLevelType ePerfLevel,
  ClockQUPI2CType eClock
);
boolean Clock_DisableI2CClock(ClockQUPI2CType eClock);
void Clock_InitForDownloadMode(void);
boolean Clock_InitUSB(void);
boolean Clock_InitCrypto(void);
boolean Clock_ExitBoot(void);
boolean Clock_DebugInit(void);
boolean Clock_DisableUSB(void);
uint32 Clock_DDRSpeed(void);
boolean Clock_I2CInit(void);
boolean Clock_EnableQPICForDownloadMode( void );
void Clock_BIMCQuery(ClockQueryType nQuery,void* pResource);
void Clock_SwitchBusVoltage(ClockVRegLevelType eVoltageLevel);
boolean Clock_SetBIMCSpeed(uint32 nFreqKHz );
boolean Clock_ExtBuckGPIOMisc( void );
boolean Clock_Usb30SwitchPipeClk(void);
boolean Clock_Usb30EnableSWCollapse(boolean enable);
boolean Clock_Usb30GetSWCollapse(void);
boolean Clock_EnableQPICForDownloadMode( void );
boolean Clock_GetClockFrequency(ClockType  eClock,  uint32 * pnFrequencyHz);
DalChipInfoIdType Clock_GetChipId(void);
<driver name="I2C">
    <global_def> 
      <var_seq name="i2cqup1_gpio_config_arr" type=DALPROP_DATA_TYPE_UINT32_SEQ>
         0x2001c063, 0x2001c073,end 
      </var_seq>
      <var_seq name="i2cqup2_gpio_config_arr" type=DALPROP_DATA_TYPE_UINT32_SEQ>
         0x2001c6f3, 0x2001c703,end 
      </var_seq>
      <var_seq name="i2cqup3_gpio_config_arr" type=DALPROP_DATA_TYPE_UINT32_SEQ>
         0x2001c1d1, 0x2001c1e1,end 
      </var_seq>    
      <var_seq name="i2cqup4_gpio_config_arr" type=DALPROP_DATA_TYPE_UINT32_SEQ>
         0x2001c0e2, 0x2001c0f2,end 
      </var_seq>
      <var_seq name="i2cqup5_gpio_config_arr" type=DALPROP_DATA_TYPE_UINT32_SEQ>
         0x2001c122, 0x2001c132,end 
      </var_seq>
      <var_seq name="i2cqup6_gpio_config_arr" type=DALPROP_DATA_TYPE_UINT32_SEQ>
         0x2001c0a2, 0x2001c0b2,end 
      </var_seq>  
    </global_def>
    <device id=0x02000021>
        <props name="CHIP_CLK_INDEX" type=DALPROP_ATTR_TYPE_UINT32>            CLK_BLSP1_QUP1_I2C_APPS    </props> 
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32>        0x78B5000</props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32>    19200</props>
        <props name="CHIP_GPIO_CONFIG_ARR" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR> i2cqup1_gpio_config_arr   </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32>      0    </props>
    </device>
    <device id=0x02000022>
        <props name="CHIP_CLK_INDEX" type=DALPROP_ATTR_TYPE_UINT32>            CLK_BLSP1_QUP2_I2C_APPS    </props> 
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32>        0x78B6000</props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32>    19200</props>
        <props name="CHIP_GPIO_CONFIG_ARR" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR> i2cqup2_gpio_config_arr   </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32>      0    </props>
    </device>
    <device id=0x02000023>
        <props name="CHIP_CLK_INDEX" type=DALPROP_ATTR_TYPE_UINT32>            CLK_BLSP1_QUP3_I2C_APPS    </props> 
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32>        0x78B7000</props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32>    19200</props>
        <props name="CHIP_GPIO_CONFIG_ARR" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR> i2cqup3_gpio_config_arr   </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32>      0    </props>
    </device>
    <device id=0x02000024>
        <props name="CHIP_CLK_INDEX" type=DALPROP_ATTR_TYPE_UINT32>            CLK_BLSP1_QUP4_I2C_APPS    </props> 
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32>        0x78B8000</props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32>    19200</props>
        <props name="CHIP_GPIO_CONFIG_ARR" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR> i2cqup4_gpio_config_arr   </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32>      0    </props>
    </device>
    <device id=0x02000025>
        <props name="CHIP_CLK_INDEX" type=DALPROP_ATTR_TYPE_UINT32>            CLK_BLSP1_QUP5_I2C_APPS    </props> 
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32>        0x78B9000</props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32>    19200</props>
        <props name="CHIP_GPIO_CONFIG_ARR" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR> i2cqup5_gpio_config_arr   </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32>      0    </props>
    </device>
    <device id=0x02000064>
        <props name="CHIP_CLK_INDEX" type=DALPROP_ATTR_TYPE_UINT32>            CLK_BLSP1_QUP6_I2C_APPS    </props> 
        <props name="CHIP_QUP_BASE_ADDR" type=DALPROP_ATTR_TYPE_UINT32>        0x78BA000</props>
        <props name="CHIP_APPS_CLK_FREQ_KHZ" type=DALPROP_ATTR_TYPE_UINT32>    19200</props>
        <props name="CHIP_GPIO_CONFIG_ARR" type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR> i2cqup6_gpio_config_arr   </props>
        <props name="SW_ENABLE_INTERRUPTS" type=DALPROP_ATTR_TYPE_UINT32>      0    </props>
    </device>
</driver>
