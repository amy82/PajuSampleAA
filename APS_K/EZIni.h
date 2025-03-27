#pragma once
#include <vector>

class EZIni
{
public:
	class Exception
	{
	public:
		Exception(LPCTSTR lpErrorMessage) : m_sErrorMessage(lpErrorMessage) {}
		CString GetErrorMessage() const { return m_sErrorMessage; }

	private:
		CString m_sErrorMessage;
	};

	class Key;
	class Section
	{
		friend class EZIni;

	public:
		// Get Key Object
		Key operator[](LPCSTR lpKeyName);
		Key operator[](LPCWSTR lpKeyName);

		// Ini Section Helper function
		BOOL IsExist() const;
		BOOL Delete();
		BOOL EnumKeyNames(std::vector<CString>& listOfKeyNames) const;

	private:
		Section(LPCTSTR lpFileName, LPCTSTR lpSectionName);

	private:
		CString m_sFileName;
		CString m_sSectionName;
	};

	class Key
	{
		friend class EZIni;
		friend class EZIni::Section;

	public:
		// Write Operation
		Key& operator=(int nValue);
		Key& operator=(UINT uValue);
		Key& operator=(INT64 n64Value);
		Key& operator=(UINT64 u64Value);
		Key& operator=(bool bValue);
		Key& operator=(double dValue);
		Key& operator=(float fValue);
		Key& operator=(LPCTSTR lpValue);
		Key& operator=(POINT ptValue);
		Key& operator=(LPCRECT lpRectValue);
		Key& operator=(const COleDateTime& dtValue);

		// Read Operation
		operator int();
		operator UINT();
		operator INT64();
		operator UINT64();
		operator bool();
		operator double();
		operator float();
		operator CString();
		operator CPoint();
		operator CRect();
		operator COleDateTime();
		
		// Arithmetic/Logical Operation
		Key& operator++();
		Key& operator--();
		Key& operator+=(int nValue);
		Key& operator-=(int nValue);
		Key& operator*=(int nValue);
		Key& operator/=(int nValue);
		Key& operator%=(int nValue);

		Key& operator+=(UINT uValue);
		Key& operator-=(UINT uValue);
		Key& operator*=(UINT uValue);
		Key& operator/=(UINT uValue);
		Key& operator%=(UINT uValue);
		Key& operator<<=(UINT uValue);
		Key& operator>>=(UINT uValue);
		Key& operator&=(UINT uValue);
		Key& operator|=(UINT uValue);
		Key& operator^=(UINT uValue);

		Key& operator+=(double dValue);
		Key& operator-=(double dValue);
		Key& operator*=(double dValue);
		Key& operator/=(double dValue);

		Key& operator+=(float fValue);
		Key& operator-=(float fValue);
		Key& operator*=(float fValue);
		Key& operator/=(float fValue);

		Key& operator+=(POINT ptValue);
		Key& operator-=(POINT ptValue);
		Key& operator+=(SIZE sizeValue);
		Key& operator-=(SIZE sizeValue);
		Key& operator+=(LPCRECT lpRectValue);
		Key& operator-=(LPCRECT lpRectValue);
		Key& operator+=(COleDateTimeSpan dateSpan);
		Key& operator-=(COleDateTimeSpan dateSpan);

		// Append Operation
		Key& operator+=(LPCTSTR lpText);

		// Set Default Value
		Key& operator<<(int nDefaultValue);
		Key& operator<<(UINT uDefaultValue);
		Key& operator<<(INT64 n64DefaultValue);
		Key& operator<<(UINT64 u64DefaultValue);
		Key& operator<<(bool bDefaultValue);
		Key& operator<<(double dDefaultValue);
		Key& operator<<(float fDefaultValue);
		Key& operator<<(LPCTSTR lpDefaultValue);
		Key& operator<<(POINT ptDefaultValue);
		Key& operator<<(LPCRECT lpDefaultValue);
		Key& operator<<(const COleDateTime& dtDefaultValue);

		Key& operator>>(int nDefaultValue);
		Key& operator>>(UINT uDefaultValue);
		Key& operator>>(INT64 n64DefaultValue);
		Key& operator>>(UINT64 u64DefaultValue);
		Key& operator>>(bool bDefaultValue);
		Key& operator>>(double dDefaultValue);
		Key& operator>>(float fDefaultValue);
		Key& operator>>(LPCTSTR lpDefaultValue);
		Key& operator>>(POINT ptDefaultValue);
		Key& operator>>(LPCRECT lpDefaultValue);
		Key& operator>>(const COleDateTime& dtDefaultValue);

		// Ini Key Helper function
		BOOL IsExist() const;
		BOOL Delete();

	private:
		Key(LPCTSTR lpFileName, LPCTSTR lpSectionName, LPCTSTR lpKeyName);

		template <typename _T>
		void _SetKeyValue(_T value, LPCTSTR lpFormatSpec);
		template <typename _T>
		CString _GetKeyValue(_T defaultValue, LPCTSTR lpFormatSpec);

		CString _Point2String(const POINT& ptValue);
		CString _Rect2String(LPCRECT lpRectValue);
		CString _DateTime2String(const COleDateTime& dtValue);

		CPoint _String2Point(LPCTSTR lpValue);
		CRect _String2Rect(LPCTSTR lpValue);
		COleDateTime _String2DateTime(LPCTSTR lpValue);

	private:
		CString m_sFileName;
		CString m_sSectionName;
		CString m_sKeyName;
		
		CString m_sDefaultValue;
		union
		{
			int m_nDefaultValue;
			UINT m_uDefaultValue;
			INT64 m_n64DefaultValue;
			UINT64 m_u64DefaultValue;
			bool m_bDefaultValue;
			double m_dDefaultValue;
			float m_fDefaultValue;
			POINT m_ptDefaultValue;
			RECT m_rcDefaultValue;
			DATE m_dtDefaultValue;
		};
	};	

	EZIni(void);
	EZIni(LPCTSTR lpFileName, BOOL bCreateAsUnicode = FALSE);
	~EZIni(void);

	// Get Section Object
	Section operator[](LPCSTR lpSectionName);
	Section operator[](LPCWSTR lpSectionName);

	// Initialize Function
	void SetFileName(LPCTSTR lpFileName, BOOL bCreateAsUnicode = FALSE);

	// Ini Helper Function
	BOOL EnumSectionNames(std::vector<CString>& listOfSectionNames) const;

private:
	enum { READ_BUFFER_SIZE = 512 };

	static CString _GetErrorMessage();

private:
	CString m_sFileName;
};

template <typename _T>
void EZIni::Key::_SetKeyValue(_T value, LPCTSTR lpFormatSpec)
{
	ASSERT(!m_sFileName.IsEmpty() && !m_sSectionName.IsEmpty() && !m_sKeyName.IsEmpty());

	CString sValue;
	sValue.Format(lpFormatSpec, value);
	BOOL bResult = WritePrivateProfileString(m_sSectionName, m_sKeyName, sValue, m_sFileName);
	if (!bResult)
	{		
		CString sErrMessage, sFormat;
		sFormat.Format(_T("Failed to write value(%s)."), lpFormatSpec);
		sFormat += _T(" %s");
		sErrMessage.Format(sFormat, value, EZIni::_GetErrorMessage());
		throw EZIni::Exception(sErrMessage);
	}
}

template <typename _T>
CString EZIni::Key::_GetKeyValue(_T defaultValue, LPCTSTR lpFormatSpec)
{
	CString sDefaultValue;
	sDefaultValue.Format(lpFormatSpec, defaultValue);

	DWORD dwLen = READ_BUFFER_SIZE;
	LPTSTR pBuffer = new TCHAR[dwLen + 1];

	DWORD dwCopied = GetPrivateProfileString(m_sSectionName, m_sKeyName, sDefaultValue, pBuffer, dwLen, m_sFileName);
	while (dwCopied + 1 >= dwLen)
	{		
		dwLen += READ_BUFFER_SIZE;
		delete [] pBuffer;
		pBuffer = new TCHAR[dwLen + 1];
		dwCopied = GetPrivateProfileString(m_sSectionName, m_sKeyName, sDefaultValue, pBuffer, dwLen, m_sFileName);
	}

	CString sValue(pBuffer);
	delete [] pBuffer;

	return sValue;
}