#pragma once
class CSerial
{
public:
	CSerial();
	~CSerial();

	bool Open(unsigned int nPort, unsigned int nBaudRate);
	void Close();
	unsigned int ReadData(unsigned char* pBuffer, unsigned int nBuffSize);
	unsigned int SendData(const unsigned char* pBuffer, unsigned int nBuffSize);

private:
	HANDLE m_hConsole;
	OVERLAPPED m_stReadOverlapped;
	OVERLAPPED m_stWriteOverlapped;
	bool m_sbOpen;
};

