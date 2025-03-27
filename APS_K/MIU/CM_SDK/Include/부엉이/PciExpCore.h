// ETG_PCI_XP.h: interface for the CETG_PCI_XP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ETG_PCI_XP_H__2DCAB0FE_B47K_434F_979F_766863B10455__INCLUDED_)
#define AFX_ETG_PCI_XP_H__2DCAB0FE_B47K_434F_979F_766863B10455__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPciExpCore  
{
public:
	int GrabMemClose();
	int GrabChkDone(int *nCurrentIndex);
	int GrabChkDone64(int *nLeftLength);
	int GrabMemAlloc(int **npImageIn, int nGrabSizeBytes);
	int GrabMemAlloc64(__int64 **npImageIn, __int64 nGrabSizeBytes);

	BOOL	m_bOpened;
	HANDLE	m_hPCI_XP;
	BOOL	m_bOddReq;
	int		*m_kernelMemory;
	int		m_nGrabBufferNum;
	int		m_nGrabBufferSize[16];

	int		OpenDevice(int openID);
	int		CloseDevice();
	int		InitDevPhyMemory(int nGrabLength, int nMsTimeOut);
	int		InitDevPhyMemory64(__int64 nGrabLength, int nMsTimeOut);
	int		ChkPhyMemStatus();
	int		GetDeviceInformation(int *pciCardNum, int *nDriverVersion, int *nBusNum, int *nFuncNum, int *devNum);
	int		ReqChkDone(int nRequestNo, int nThreadId, int *nCurrentIndex);
	int		srio_user_rst();
	int		srio_peer_reset();
	int		srio_nread(int nDestinationID, int *Addr, int byte_count);
	int		srio_nread_done_chk(int *dataBuffer);
	int		srio_nwrite(int nDestinationID, int *n64Addr, int byte_count, int *data);

	int		srio_config_read (int nDestinationID, int nHopCount, int nOffset, int nLocal);
	int		srio_config_write(int nDestinationID, int nHopCount, int nOffset, int nWrData, int nLocal);
	int		srio_config_done_chk(int *nRtnVal);
	int		KernelMemoryAllocate(int nBytesMemSize);
	int		KernelMemroyFree();
	
	int		PhyMemCopy(int **pBuffer, int nPhyIndex, int nAddrOffset, int nLengthBytes) ;

	int		mem_phymem_copy				(int *buffer, int nPhyIndex, int nLengthBytes);
	int		mem_phymem_copy_back		(int *buffer, int nPhyIndex, int nLengthBytes);
	int		mem_phymem_copy_back_safe	(int **buffer, int nPhyIndex, int nLengthBytes);
	
	int		srio_phymem_nwrite(int nDestinationID,	int *n64Addr,	int byte_count, int nPhyBufferIndex);

	int		srio_done_chk(int nMsWait);
	int		IFCardResetSet();
	int		IFCardResetClr();
	CPciExpCore();
	virtual ~CPciExpCore();
protected:

	HANDLE	GetDeviceViaInterface(GUID* pGuid, DWORD instance);
//	int		*StoredMemPointer;

};

#endif // !defined(AFX_ETG_PCI_XP_H__2DCAB0FE_B47K_434F_979F_766863B10455__INCLUDED_)
