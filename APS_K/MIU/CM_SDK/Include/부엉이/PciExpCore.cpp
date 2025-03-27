
#include "stdafx.h"
#include "PciExpCore.h"
#include "pci_error.h"

#include <objbase.h>
#include "pcixp_guid.h"
#include "ioControl.h"
#include "IoctlCode.h"
#include "rio.h"
#include <winioctl.h> // for CTL_CODE macro
#include <setupapi.h>

#pragma comment(lib, "setupapi")
#pragma warning(disable: 4244)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPciExpCore::CPciExpCore()
{
	m_bOpened = 0;
	m_hPCI_XP = NULL;	
}

CPciExpCore::~CPciExpCore()
{
}



int CPciExpCore::OpenDevice(int openID)
{
//	int		l_i;

	if (!m_bOpened) {
		m_bOpened = TRUE;
		m_hPCI_XP = GetDeviceViaInterface((LPGUID)&GUID_PERIPCIXP, openID);
		if (m_hPCI_XP == NULL)	{ 
			m_bOpened = FALSE;
			return STATUS_PCIEXP_NODEVICE;  
		}
		else {
			// OpenID를 이용해서 Driver의 UI정보를 넣자.
			return STATUS_PCIEXP_SUCCESS;
		}
	}
	return STATUS_PCIEXP_CLOSEFIRST;
}

int	CPciExpCore::CloseDevice() {

	UINT nRtn;

	nRtn = STATUS_PCIEXP_SUCCESS;
	
	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;

	if (m_hPCI_XP != NULL) {
		if (CloseHandle(m_hPCI_XP)) { 
			m_hPCI_XP = NULL; 
			m_bOpened = FALSE; 
		}
		else {
			nRtn = STATUS_PCIEXP_NOTOPEN;
		}
	}
	return nRtn;
}


HANDLE CPciExpCore::GetDeviceViaInterface(GUID *pGuid, DWORD instance)
{
	PSP_INTERFACE_DEVICE_DETAIL_DATA ifDetail;
	SP_INTERFACE_DEVICE_DATA		ifdata;
	HDEVINFO	info;
	HANDLE		rv;
	DWORD		ReqLen;

	info = SetupDiGetClassDevs(pGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if(info==INVALID_HANDLE_VALUE) 
		return NULL;
	
	ifdata.cbSize = sizeof(ifdata);
	if (!SetupDiEnumDeviceInterfaces(info, NULL, pGuid, instance, &ifdata)) {
		SetupDiDestroyDeviceInfoList(info);
		return NULL;
	}

	SetupDiGetDeviceInterfaceDetail(info, &ifdata, NULL, 0, &ReqLen, NULL);
	ifDetail = (PSP_INTERFACE_DEVICE_DETAIL_DATA)(new char[ReqLen]);
	if(ifDetail==NULL) {
		SetupDiDestroyDeviceInfoList(info);
		return NULL;
	}

	ifDetail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

	if(!SetupDiGetDeviceInterfaceDetail(info, &ifdata, ifDetail, ReqLen, NULL, NULL)) {
		SetupDiDestroyDeviceInfoList(info);
		delete ifDetail;
		return NULL;
	}
	
	rv = CreateFile(ifDetail->DevicePath, GENERIC_READ | GENERIC_WRITE,
						FILE_SHARE_READ | FILE_SHARE_WRITE,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (rv==INVALID_HANDLE_VALUE) rv = NULL;

	delete ifDetail;
	SetupDiDestroyDeviceInfoList(info);
	return rv;
}



int	CPciExpCore::srio_done_chk(int nMsWait) {

	return STATUS_PCIEXP_SUCCESS;
}


int CPciExpCore::srio_user_rst()
{
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;

	codeval = IOCTL_USER_RESET;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), &IoBuffer, 
								sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

//	Sleep(100);
	return IoBuffer.ReturnCode;
}

int CPciExpCore::srio_peer_reset() // V2
{
	IOCTLDATA	IoBuffer;
	DWORD		codeval;
	UINT		unError;
	UINT64		nReturnedBytes;
	
	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;
	
	codeval = IOCTL_WRITE_DATA;
	IoBuffer.Addr = 0x28;
	IoBuffer.unData[0] = 0x08;
	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	Sleep(100);
	IoBuffer.Addr = 0x28;
	IoBuffer.unData[0] = 0x00;
	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	return STATUS_PCIEXP_SUCCESS;
}



int CPciExpCore::srio_nread(int nDestinationID, int *Addr, int byte_count)
{
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	int byte_en = 0;
	
	byte_count &= 0xfffffff8;
	if ((m_hPCI_XP == NULL) || (!m_bOpened))	return STATUS_PCIEXP_NOTOPENED;
	if (byte_count < 8)							return STATUS_PCIEXP_LENGTHERR;
	if (byte_count > KERNEL_MEM_SIZE)			return STATUS_PCIEXP_LENGTHERR;
	if (m_kernelMemory == NULL)					return STATUS_PCIEXP_NOTALLOC;

	codeval = IOCTL_SRIO_NREAD;

	IoBuffer.unData[0] = (HIGH_PRIO<<30) | (nDestinationID<<14) | (TT_NREAD<<10) | (0x3&(*(Addr+1)));
	IoBuffer.unData[1] = (FT_2<<25) | (byte_count<<16);
	IoBuffer.Addr = (UINT32) *Addr&0xffffffff;
	

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	return IoBuffer.ReturnCode;
}
/*
int CPciExpCore::srio_nwrite(int nDestinationID, int *n64Addr, int byte_count, int *data)
{
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	volatile int			a;

	if ((m_hPCI_XP == NULL) || (!m_bOpened))	return STATUS_PCIEXP_NOTOPENED;
	if (byte_count < 8)							return STATUS_PCIEXP_LENGTHERR;
	if (byte_count > KERNEL_MEM_SIZE)			return STATUS_PCIEXP_LENGTHERR;
	if (m_kernelMemory == NULL)					return STATUS_PCIEXP_NOTALLOC;

	//::EnterCriticalSection(&m_cs);

	byte_count &= 0xfffffff8;

	codeval = IOCTL_SRIO_NWRITE;

	IoBuffer.Addr = 0;
	IoBuffer.unData[0] = nDestinationID;
	IoBuffer.unData[1] = byte_count;
	IoBuffer.unData[2] = n64Addr[0];
	IoBuffer.unData[3] = n64Addr[1];

	memcpy(m_kernelMemory, data, byte_count);


	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	return IoBuffer.ReturnCode;

}
*/

int CPciExpCore::srio_nwrite(int nDestinationID, int *n64Addr, int byte_count, int *data)
{
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	if ((m_hPCI_XP == NULL) || (!m_bOpened))	return STATUS_PCIEXP_NOTOPENED;
	if (byte_count < 8)							return STATUS_PCIEXP_LENGTHERR;
	if (byte_count > KERNEL_MEM_SIZE)			return STATUS_PCIEXP_LENGTHERR;
	if (m_kernelMemory == NULL)					return STATUS_PCIEXP_NOTALLOC;

	//::EnterCriticalSection(&m_cs);

	byte_count &= 0xfffffff8;

	codeval = IOCTL_SRIO_NWRITE;

	IoBuffer.Addr = n64Addr[0];
	IoBuffer.unData[0] = nDestinationID;
	IoBuffer.unData[1] = byte_count;
	IoBuffer.unData[2] = (UINT64) (data[0]&0xffffffff) | ((UINT64) (data[1]&0xffffffff)<<32);
	IoBuffer.unData[3] = 0;//(UINT64) data[1] | ((UINT64) data[0]<<32);
//	IoBuffer.unData[3] = data[1];

//	memcpy(m_kernelMemory, data, byte_count);


	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	return IoBuffer.ReturnCode;

}




int CPciExpCore::srio_config_read(int nDestinationID, int nHopCount, int nOffset, int nLocal)
{
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	
	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;

	codeval = IOCTL_SRIO_CONFIG_RD;
	IoBuffer.unData[0] = nDestinationID;
	IoBuffer.unData[1] = (nLocal<<29) | nHopCount;
	IoBuffer.Addr = nOffset;
	m_bOddReq = (nOffset %8) ? FALSE : TRUE;
	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	

	return IoBuffer.ReturnCode; //	1: timeout, 0 : success

}

int CPciExpCore::srio_config_write(int nDestinationID, int nHopCount, int nOffset, int nWrData, int nLocal)	// changed 080402 to remove redundant value
{			//	V2
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;
	
	codeval = IOCTL_SRIO_CONFIG_WR;

	IoBuffer.unData[0] = nDestinationID;
	IoBuffer.unData[1] = (nLocal<<29) | nHopCount;
	IoBuffer.unData[2] = nWrData;
	IoBuffer.Addr = nOffset;
	m_bOddReq = (nOffset %8) ? FALSE : TRUE;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	return IoBuffer.ReturnCode;	//	1: timeout, 0 : success
}


int	CPciExpCore::srio_nread_done_chk(int *dataBuffer) {

	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;
	
	codeval = IOCTL_ACT_DONE_CHK;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	if (IoBuffer.ReturnCode == STATUS_PCIEXP_SUCCESS) {
		if (m_kernelMemory != NULL) 
			memcpy(dataBuffer, m_kernelMemory, IoBuffer.unData[0]);
		
		return STATUS_PCIEXP_SUCCESS;
	}
	else  {
		return STATUS_PCIEXP_NOTDONE;
	}

	return 0;

}


int CPciExpCore::srio_config_done_chk(int *nRtnVal) {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;
	
	codeval = IOCTL_ACT_DONE_CHK;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	if (IoBuffer.ReturnCode == 0) {
		if (m_bOddReq)
			nRtnVal[0] = (int) IoBuffer.unData[1];
		else 
			nRtnVal[0] = (int) IoBuffer.unData[0];
		return STATUS_PCIEXP_SUCCESS;
	}
	else  {
		return STATUS_PCIEXP_NOTDONE;
	}

	return 0;	
	
}


int CPciExpCore::IFCardResetSet() {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	
	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;

	codeval = IOCTL_WR_SETRST;
	
	unError = DeviceIoControl(m_hPCI_XP, codeval,
							&IoBuffer, sizeof(IoBuffer),
							&IoBuffer, sizeof(IoBuffer),
							(LPDWORD) &nReturnedBytes, NULL
							);


	return IoBuffer.ReturnCode;	
}

int CPciExpCore::IFCardResetClr() {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	
	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;

	codeval = IOCTL_WR_CLRRST;
	
	unError = DeviceIoControl(m_hPCI_XP, codeval,
							&IoBuffer, sizeof(IoBuffer),
							&IoBuffer, sizeof(IoBuffer),
							(LPDWORD) &nReturnedBytes, NULL
							);


	return IoBuffer.ReturnCode;	
}

int CPciExpCore::KernelMemoryAllocate(int nBytesMemSize) {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	
	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;

	codeval = IOCTL_ALLOCATE_MEMORY;

	IoBuffer.unData[0] = nBytesMemSize;
//	IoBuffer.unData[1] = 128*1024*1024;

	unError = DeviceIoControl(m_hPCI_XP, codeval,
							&IoBuffer, sizeof(IoBuffer),
							&IoBuffer, sizeof(IoBuffer),
							(LPDWORD) &nReturnedBytes, NULL
							);
	m_kernelMemory = (int *) IoBuffer.unData[0];
	if (m_kernelMemory == NULL)	{
		return STATUS_LIB_MEMALLOCERR;
	}
	else {
		return IoBuffer.ReturnCode;	
	}
}


int CPciExpCore::KernelMemroyFree() {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	
	if ((m_hPCI_XP == NULL) || (!m_bOpened)) return STATUS_PCIEXP_NOTOPENED;

	codeval = IOCTL_FREE_MEMORY;
	
	unError = DeviceIoControl(m_hPCI_XP, codeval,
							&IoBuffer, sizeof(IoBuffer),
							&IoBuffer, sizeof(IoBuffer),
							(LPDWORD) &nReturnedBytes, NULL
							);

	m_kernelMemory = NULL;
	return IoBuffer.ReturnCode;	
}
int	CPciExpCore::mem_phymem_copy_back_safe(int **buffer, int nPhyIndex, int nLengthBytes) {
	UINT		unError, nReturnedBytes;
	IOCTLDATA	IoBuffer;
	DWORD		codeval;

	if ((m_hPCI_XP == NULL) || (!m_bOpened))	return STATUS_PCIEXP_NOTOPENED;
	if (nLengthBytes > PHY_MEM_SIZE)			return STATUS_PCIEXP_LENGTHERR;
	//	if (buffer != NULL)							return STATUS_LIB_MEMALLOCERR;

	codeval = IOCTL_PHYMEM_COPYBACK_SAFE;

	IoBuffer.Addr = (UINT) NULL;
	IoBuffer.unData[0] = nPhyIndex;
	IoBuffer.unData[1] = nLengthBytes;
	IoBuffer.unData[2] = 0;	// offset
	IoBuffer.unData[3] = 0;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer),
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	buffer[0] = m_kernelMemory;
	return IoBuffer.ReturnCode;
}
int	CPciExpCore::PhyMemCopy(int **pBuffer, int nPhyIndex, int nAddrOffset, int nLengthBytes)
{
	UINT		unError, nReturnedBytes ;
	IOCTLDATA	IoBuffer ;
	DWORD		codeval ;

	if ( (m_hPCI_XP == NULL) || (!m_bOpened) )	return STATUS_PCIEXP_NOTOPENED;
	if (nLengthBytes > PHY_MEM_SIZE)			return STATUS_PCIEXP_LENGTHERR;

	codeval = IOCTL_PHYMEM_COPYBACK_SAFE;

	IoBuffer.Addr = (UINT) NULL ;
	IoBuffer.unData[0] = nPhyIndex ;
	IoBuffer.unData[1] = nLengthBytes ;
	IoBuffer.unData[2] = nAddrOffset ;	// offset
	IoBuffer.unData[3] = 0 ;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer),
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	pBuffer[0] = m_kernelMemory + (nAddrOffset / 4) ;

	return IoBuffer.ReturnCode ;
}

int	CPciExpCore::mem_phymem_copy_back(int *buffer, int nPhyIndex, int nLengthBytes) {
	UINT		unError, nReturnedBytes;
	IOCTLDATA	IoBuffer;
	DWORD		codeval;

	if ((m_hPCI_XP == NULL) || (!m_bOpened))	return STATUS_PCIEXP_NOTOPENED;
	if (nLengthBytes > PHY_MEM_SIZE)			return STATUS_PCIEXP_LENGTHERR;
//	if (buffer != NULL)							return STATUS_LIB_MEMALLOCERR;

	codeval = IOCTL_PHYMEM_COPYBACK;

	IoBuffer.Addr = (UINT) buffer;
	IoBuffer.unData[0] = nPhyIndex;
	IoBuffer.unData[1] = nLengthBytes;
	IoBuffer.unData[2] = 0;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer),
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

//	outBuffer = m_kernelMemory;
	return IoBuffer.ReturnCode;
}


int	CPciExpCore::mem_phymem_copy(int *data, int nPhyBufferIndex, int nByteLength) {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	
	if ((m_hPCI_XP == NULL) || (!m_bOpened))	return STATUS_PCIEXP_NOTOPENED;
	if (nByteLength > PHY_MEM_SIZE)				return STATUS_PCIEXP_LENGTHERR;
	if (data == NULL)							return STATUS_LIB_MEMALLOCERR;

	codeval = IOCTL_PHYMEM_COPY;

	IoBuffer.Addr = (UINT) data;
	IoBuffer.unData[0] = nByteLength;
	IoBuffer.unData[1] = nPhyBufferIndex;
	
	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer),
							&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	return IoBuffer.ReturnCode;
}


int	CPciExpCore::srio_phymem_nwrite(int nDestinationID,	int *n64Addr,	int byte_count, int nPhyBufferIndex) {

	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	if ((m_hPCI_XP == NULL) || (!m_bOpened))	return STATUS_PCIEXP_NOTOPENED;
	if (byte_count < 8)							return STATUS_PCIEXP_LENGTHERR;
	if (byte_count > KERNEL_PHY_SIZE)			return STATUS_PCIEXP_LENGTHERR;
	if (m_kernelMemory == NULL)					return STATUS_PCIEXP_NOTALLOC;

	byte_count &= 0xfffffff8;

	codeval = IOCTL_NWRITE_NEW;

	IoBuffer.Addr = nPhyBufferIndex;
	IoBuffer.unData[0] = nDestinationID;
	IoBuffer.unData[1] = byte_count;
	IoBuffer.unData[2] = n64Addr[0];
	IoBuffer.unData[3] = n64Addr[1];

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	return IoBuffer.ReturnCode;

}


int	CPciExpCore::InitDevPhyMemory(int nGrabLength, int nMsTimeOut) {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	codeval = IOCTL_MEM_INIT;

	IoBuffer.unData[0] = nGrabLength;
	IoBuffer.unData[1] = nMsTimeOut;

	
	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
												  &IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	if (IoBuffer.ReturnCode != 0) {
		return IoBuffer.ReturnCode;
	}

	codeval = IOCTL_WR_ENABLE;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	codeval = IOCTL_INTR_TRUE;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	return IoBuffer.ReturnCode;
}


int	CPciExpCore::InitDevPhyMemory64(__int64 nGrabLength, int nMsTimeOut) {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	codeval = IOCTL_MEM_INIT;

	IoBuffer.unData[0] = nGrabLength;
	IoBuffer.unData[1] = nMsTimeOut;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	if (IoBuffer.ReturnCode != 0) {
		return IoBuffer.ReturnCode;
	}

	codeval = IOCTL_WR_ENABLE;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	codeval = IOCTL_INTR_TRUE;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	return IoBuffer.ReturnCode;
}




int	CPciExpCore::ChkPhyMemStatus() {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	codeval = IOCTL_CHK_PHYMEM;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	
	if (IoBuffer.Addr	==	0x010f)	return STATUS_PCIEXP_SUCCESS;
	else							return STATUS_PCIEXP_ALLOCERR;
	
}



int CPciExpCore::GrabMemAlloc(int **npImageIn, int nGrabSizeBytes)
{

	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	codeval = IOCTL_SET_USERMEM;
	IoBuffer.unData[0] = (UINT32) 0xffffffff;
	IoBuffer.unData[1] = (UINT32) nGrabSizeBytes;

	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	npImageIn[0] = (int *) IoBuffer.pBufferAddr;

	return IoBuffer.ReturnCode;
}



int CPciExpCore::GrabMemAlloc64(__int64 **npImageIn, __int64 nGrabSizeBytes)
{

	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	
	codeval = IOCTL_SET_USERMEM;
	IoBuffer.unData[0] = 0xffffffff;
	IoBuffer.unData[1] = nGrabSizeBytes;
	IoBuffer.pBufferAddr = (UINT64 *) npImageIn;
	
	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	
	m_nGrabBufferNum		= (int) npImageIn[0];
	m_nGrabBufferSize[0]	= (int) npImageIn[2];

	return IoBuffer.ReturnCode;
}


int CPciExpCore::ReqChkDone(int nRequestNo, int nThreadId, int *nCurrentIndex)
{
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	codeval = IOCTL_I2C_CHKDONE;
	IoBuffer.unData[0] = nRequestNo;
	IoBuffer.unData[1] = nThreadId;

	unError = DeviceIoControl(m_hPCI_XP, codeval, 
		&IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	nCurrentIndex[0] = (int) (IoBuffer.unData[0]&0xffffffff);
	nCurrentIndex[1] = (int) ((IoBuffer.unData[0]>>32)&0xffffffff);
	return IoBuffer.ReturnCode;

}


int CPciExpCore::GrabChkDone(int *nCurrentIndex)
{
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;
	
	codeval = IOCTL_CHK_RCVDONE;
	
	unError = DeviceIoControl(m_hPCI_XP, codeval, 
		&IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	
	nCurrentIndex[0] = (int) IoBuffer.unData[0];

	return IoBuffer.ReturnCode;

}

int CPciExpCore::GrabChkDone64(int *nCurrentIndex)
{
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	codeval = IOCTL_CHK_RCVDONE;

	unError = DeviceIoControl(m_hPCI_XP, codeval, 
		&IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);
	
	nCurrentIndex[0] = (int) IoBuffer.unData[0];

	return IoBuffer.ReturnCode;

}

int CPciExpCore::GrabMemClose()
{	
	IOCTLDATA IoBuffer;
	DWORD codeval;

	codeval = IOCTL_CLR_USERMEM;
	IoBuffer.ReturnCode = 0;

	return IoBuffer.ReturnCode;

}

int	CPciExpCore::GetDeviceInformation(int *pciCardNum, int *nDriverVersion, int *nBusNum, int *nFuncNum, int *devNum) {
	UINT unError, nReturnedBytes;
	IOCTLDATA IoBuffer;
	DWORD codeval;

	codeval = IOCTL_MPORT_GET_DRV_VER;


	unError = DeviceIoControl(m_hPCI_XP, codeval, &IoBuffer, sizeof(IoBuffer), 
		&IoBuffer, sizeof(IoBuffer), (LPDWORD) &nReturnedBytes, NULL);

	pciCardNum[0] = IoBuffer.Addr;
	
	nDriverVersion[0]	= (int) IoBuffer.unData[0];
	nBusNum[0]			= (int) IoBuffer.unData[1];
	nFuncNum[0]			= (int) IoBuffer.unData[2];
	devNum[0]			= (int) IoBuffer.unData[3];

	return IoBuffer.ReturnCode;
}



