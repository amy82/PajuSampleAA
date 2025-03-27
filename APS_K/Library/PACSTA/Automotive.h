#pragma once

// automotive interface



class ICommPacketReceiver
{
public:
	virtual ~ICommPacketReceiver() {}
	virtual bool OnPacketReceive(unsigned char* pPacket, int size, int& processedSize) = 0;
};


class FunctionReceiver : public ICommPacketReceiver
{
public:
	typedef bool (*RECEIVER)(unsigned char* pPacket, int size, int& processedSize);

	FunctionReceiver( RECEIVER f) : m_pfnReceiver(f) {}
	virtual bool OnPacketReceive(unsigned char* pPacket, int size, int& processedSize) { return m_pfnReceiver(pPacket, size, processedSize); }

private:
	RECEIVER m_pfnReceiver;
};


template<typename T> class MemberReceiver : public ICommPacketReceiver
{
public:
	typedef bool (T::*RECEIVER)(unsigned char* pPacket, int size, int& processedSize);
	
	MemberReceiver(RECEIVER f, T* p) : m_pfnReceiver(f), m_pObject(p) {}
	virtual bool OnPacketReceive(unsigned char* pPacket, int size, int& processedSize) { return (m_pObject->*m_pfnReceiver)(pPacket, size, processedSize); }

private:
	T* m_pObject;
	RECEIVER m_pfnReceiver;
};


template<typename T> inline MemberReceiver<T>* _COMM_CREATE_RECEIVER( typename MemberReceiver<T>::RECEIVER f, T* p )
{
	return new MemberReceiver<T>(f, p);
}

inline FunctionReceiver* _COMM_CREATE_RECEIVER(FunctionReceiver::RECEIVER f)
{
	return new FunctionReceiver( f );
}

class IAutomotiveComm
{
protected:
	ICommPacketReceiver* m_pReceiver;

public:
	IAutomotiveComm() : m_pReceiver(nullptr) {}
	virtual~IAutomotiveComm() {}

	void AddReceiver(ICommPacketReceiver* p) { m_pReceiver = p; }

	virtual int Send(unsigned char* buffer, int length, unsigned long timeOutms = 1000) = 0;
	virtual int Receive(unsigned char* buffer, int length, unsigned long timeOutms = 1000) = 0;
	virtual int GetReceivedPacket(unsigned char* pPacket, int size) = 0;
};

class IUDS;
class IReprogramming;

typedef void (*fnLogOut)(void* lpUserData, int nParaIndex, const char* lpszLog);


class IAutomotiveCamera
{
public:
	IAutomotiveCamera() : m_pUDS(nullptr), m_pComm(nullptr), m_pReprogramming(nullptr),
		m_pfnLogOut(nullptr), m_pLogUserData(nullptr) {}
	virtual~IAutomotiveCamera() {}

	virtual int Setup() = 0;

	virtual int OriginalView(bool on, int* reserved) = 0;
	virtual int WriteSerialNumber(unsigned char* addr, int dataLength, unsigned char* serialNumber) = 0;

	virtual int SetValue(const char* pItemName, int id, int value, bool pending = false) = 0;
	virtual int SetValue(const char* pItemName, int id, double value, bool pending = false) = 0;
	
	virtual void SetComm(IAutomotiveComm* pComm) 
	{ 
		m_pComm = pComm; 
	};

	virtual void SetLogConfig(fnLogOut fn, void* lpUserData, int nParaIndex=0 ) 
	{ 
		m_pfnLogOut = fn; m_pLogUserData = lpUserData;
	}

	IUDS* GetUDS() const { return m_pUDS; }
	IReprogramming* GetReprogramming() const { return m_pReprogramming; }

protected:
	IUDS* m_pUDS;
	IReprogramming* m_pReprogramming;
	IAutomotiveComm* m_pComm;
	fnLogOut m_pfnLogOut;
	void* m_pLogUserData;

};



class IUDS
{
public:
	IUDS() {}
	virtual ~IUDS() {}

	enum eUDSService
	{
		DIAGNOSTIC_SESSION_CONTROL			= 0x10, 
		ECU_RESET							= 0x11,
		READ_DATA_BY_IDENTIFIER				= 0x22,    
		READ_MEMORY_BY_ADDRESS				= 0x23,
		SECURITY_ACCESS						= 0x27,			
		WRITE_DATA_BY_IDENTIFIER			= 0x2e,
		INPUT_OUTPUT_CONTROL_BY_IDENTIFIER	= 0x2f,
		ROUTINE_CONTROL						= 0x31,		
		REQUEST_DOWNLOAD					= 0x34,		
		TRANSFER_DATA						= 0x36,			
		REQUEST_TRANSFER_EXIT				= 0x37,		
		WRITE_MEMORY_BY_ADDRESS				= 0x3d,	
		TESTER_PRESENT						= 0x3e      
	};

	typedef enum eNegativeResponseCode
	{
		uds_success                              = 0x0,
		uds_service_not_supported                = 0x11,
		uds_subfunction_not_supported            = 0x12,
		uds_incorrect_length_or_format           = 0x13,
		uds_conditions_not_correct               = 0x22,
		uds_request_sequence_error               = 0x24,
		uds_request_out_of_range                 = 0x31,
		uds_security_access_denied               = 0x33,
		uds_invalid_key                          = 0x35,
		uds_too_many_attemps                     = 0x36,
		uds_time_delay_not_expired               = 0x37,
		uds_transfer_data_suspended              = 0x71,
		uds_general_programming_failure          = 0x72,
		uds_wrong_block_sequence_counter         = 0x73,
		uds_response_pending                     = 0x78,
		uds_service_not_supported_active_session = 0x7F
	} negative_response_code;

	enum eDiagnosticSession
	{
		defaultSession = 0x01,
		defaultSessionSuppressed = 0x81,

		programmingSession = 0x02,
		programmingSessionSuppressed = 0x82,

		extendedSession = 0x03,
		extendedSessionSuppressed = 0x83,
	};

	enum eSecurityAccessType
	{
		requestSeed = 0x01,
		sendKey = 0x02
	};

	enum eUdsErrorCode
	{
		UdsErrorCode_success = 1,
		UdsErrorCode_NegativeResponse = 0, 
		UdsErrorCode_DataError = -1,
		UdsErrorCode_NoResponse = -2,
		UdsErrorCode_TimeOut = -3,
		UdsErrorCode_ChecksumError = -4
	};

	virtual int ECUReset(unsigned char resetType) = 0;
	virtual int DiagnosticSessionControl(unsigned char sessionType) = 0;
	virtual int InputOutputControlByIdentifier(unsigned short did, unsigned char* options, int optionLength) = 0;
	virtual int TesterPresent(unsigned char zeroSubFunction) = 0;
	virtual int ReadDataByIdentifier(unsigned short did, int readBytes, unsigned char* readData ) = 0;
	virtual int WriteDataByIdentifier(unsigned short did, int writeBytes, unsigned char* dataRecord ) = 0;
	virtual int ReadMemoryByAddress(unsigned char formatId, unsigned char* memoryAddress, unsigned char* readSize, unsigned char* dataRecord) = 0;
	virtual int WriteMemoryByAddress(unsigned char formatId, unsigned char* memoryAddress, unsigned char* writeSize, unsigned char* dataRecord) = 0;
	virtual int SecurityAccess() = 0;
	// @ ret > 0, maxNumberOfBlockLength
	//   ret <= 0, error
	virtual int RequestDownload(unsigned char dataformatId, unsigned char addrNlengthFormatId, unsigned char* memoryAddr, unsigned char* memorySize) = 0;
	virtual int TransferData(int maxNumberOfBlockLength, unsigned char* recordData, int length) = 0;
	virtual int RequestTransferExit(unsigned char* paramRecord, int length) = 0;
	virtual int RoutineControl(unsigned char routineType, unsigned short routineId, unsigned char* option, int optionLength) = 0;
};


class IReprogramming
{
public:
	IReprogramming() {}
	virtual ~IReprogramming() {}

	enum eReprogrammingErrorCode
	{
		ReprogrammingErrorCode_success = 1,
		ReprogrammingErrorCode_fileError = -5,
		ReprogrammingErrorCode_PreCondition = -6
	};

	virtual void GetFileDescription(const char* pFilePathName, char* pDescription, int maxDescriptionSize = 256) = 0;

	virtual int EraseMemory(unsigned char* memoryAddr, int eraseLength) = 0;

	virtual int Download(const char* pFilePathName) = 0;

	// dataformatId -> bit 7-4: length (number of bytes) of the data parameter
	//                 bit 3-0: length (number of bytes) of the address parameter 
	virtual int Download(unsigned char dataformatId, unsigned char* memoryAddr, int writeSize, unsigned char* dataRecord ) = 0;

};

#ifdef AUTOMOTIVE_EXPORTS
#define AUTOMOTIVE_API	__declspec(dllexport)
#else
#define AUTOMOTIVE_API	__declspec(dllimport)
#endif


typedef IAutomotiveCamera* (*pfnGetAutomotiveCamera)();


#ifdef __cplusplus
extern "C" {
#endif

	AUTOMOTIVE_API	IAutomotiveCamera* GetAutomotiveCamera();

#ifdef __cplusplus
}
#endif

