#include "stdafx.h"
#include "algo_base.h"

//using namespace algo_base;
//
//namespace algo_base // algo_base
//{
void GetIni(string file,CMapData &db,bool is_clear)
{
	string line;
	ifstream infile(file);
	sregex_iterator end;
	string key,data;
	string tag_name;
	bool tag_found=false;

	smatch sm;
	regex ex_tag("\\s*\\[([\\w]+)\\].*"); /*tag pattern*/
	regex ex_data("\\s*(\\w+)\\s*=([-+]?[\\w\\.\\\\:]+).*"); /*key & data pattern*/
	regex ex_int("([-+]?\\d+)|(0[Xx][\\da-fA-F]+)"); /*integer pattern*/
	regex ex_float("([-+]?\\d+\\.\\d+)"); /*double pattern*/

	if(is_clear) db.clear();
	
	while (getline(infile,line))
	{
		if(regex_match(line,sm,ex_tag)) 
		{
			if(sm[0].str()=="END")
			{
				tag_found = false;
			}
			else
			{
				tag_found = true;
				tag_name = sm[1].str();
			}
			continue;
		}
		
		if(tag_found)
		{
			if(regex_match(line,sm,ex_data))
			{
				key=sm[1].str();
				data=sm[2].str();
				if(regex_match(data,sm,ex_int))  /*integral*/
				{
					db[tag_name+"."+key+".i"]=stoi(data,0,0);
				}
				else if(regex_match(data,sm,ex_float)) /*float*/
				{
					db[tag_name+"."+key+".d"]=stod(data);
				} else { /*string*/
					db[tag_name+"."+key+".s"]=data;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////
// duration time class
//////////////////////////////////////////////////////////////////
CDuration::CDuration(void)
{
	LARGE_INTEGER liFrequency;

	QueryPerformanceFrequency(&liFrequency);
	m_llFrequency = liFrequency.QuadPart;

	// Calibration
	Start();
	Stop();

	m_llCorrection = m_liStop.QuadPart-m_liStart.QuadPart;
}

void CDuration::Start(void)
{
	// Ensure we will not be interrupted by any other thread for a while
	Sleep(0);
	QueryPerformanceCounter(&m_liStart);
}

void CDuration::Stop(void)
{
	QueryPerformanceCounter(&m_liStop);
}

double CDuration::GetDuration(void) const
{
	return (double)(m_liStop.QuadPart-m_liStart.QuadPart-m_llCorrection)*1000000.0 / m_llFrequency;
}
//////////////////////////////////////////////////////////////////

//}