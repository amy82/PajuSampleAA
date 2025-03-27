#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <tchar.h>

class CSVRow
{
public:
	std::string const& operator[](std::size_t index) const
	{
		return m_data[index];
	}
	std::size_t size() const
	{
		return m_data.size();
	}
	bool empty() const
	{
		return m_data.size() == 0 ? true : false;
	}
	int ReadNextRow(std::istream& str)
	{
		std::string line;
		std::getline(str,line);

		std::stringstream lineStream(line);
		std::string cell;

		m_data.clear();
		while(std::getline(lineStream,cell,','))
		{
			m_data.push_back(cell);
		}
		return (int)m_data.size();
	}
private:
	std::vector<std::string>    m_data;
};

class CSVReader
{
public:
	CSVReader(void) {}
	~CSVReader(void) {}

	bool Open(std::string strPath)
	{
		m_Buffer.clear();
		std::ifstream file(strPath);
		CSVRow row;

		if( false == file.is_open() ) 
			return false;

		while(file.good())
		{
			row.ReadNextRow(file);
			if( !row.empty())
				m_Buffer.push_back(row);
		}

		return m_Buffer.empty() ? false : true;
	}

	int GetColumnNum(int row=0) { return m_Buffer.empty() ? 0 : (int)m_Buffer[row].size(); }
	int GetRowNum() { return (int)m_Buffer.size(); }

	const char* GetDataString(int row, int column)
	{
		if (row > ((int)m_Buffer.size() - 1))
			return _T("");

		if (column > ((int)m_Buffer[row].size() - 1))
			return _T("");

		const std::string& str = m_Buffer[row][column];
		return str.c_str();
	}

	int GetDataInt(int row, int column)
	{
		if (row > ((int)m_Buffer.size() - 1))
			return 0;

		if (column > ((int)m_Buffer[row].size() - 1))
			return 0;

		std::string str = m_Buffer[row][column];
		return _tcstol(str.c_str(), NULL, 0);
	}

	double GetDataDouble(int row, int column)
	{
		if (row > ((int)m_Buffer.size() - 1))
			return 0.0;

		if (column > ((int)m_Buffer[row].size() - 1))
			return 0.0;

		std::string str = m_Buffer[row][column];
		return _tcstod(str.c_str(), NULL);
	}

private:
	std::vector<CSVRow>	m_Buffer;
};
