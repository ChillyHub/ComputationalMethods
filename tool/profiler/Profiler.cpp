#include "Profiler.h"

namespace Tool
{
	std::unordered_map<std::string, Profiler::AnalysisInfo> Profiler::m_analysis;
	int Profiler::m_idCount = 0;
	
	void Profiler::AddAnalysis(const std::string& name, const std::string& info)
	{
		AnalysisInfo ai;
		ai.ID = m_idCount++;
		ai.Name = name;
		ai.Info = info;

		m_analysis[name] = ai;
	}

	void Profiler::StartAnlysis(const std::string& name)
	{
		if (m_analysis.find(name) == m_analysis.end())
			throw std::runtime_error("ERROR: Unknow profile");

		m_analysis[name].StartTime = Time::GetTimeMicroseconds();
	}

	void Profiler::EndAnlysis(const std::string& name)
	{
		if (m_analysis.find(name) == m_analysis.end())
			throw std::runtime_error("ERROR: Unknow profile");

		m_analysis[name].EndTime = Time::GetTimeMicroseconds();
	}

	std::string Profiler::GetAnlysisInfo(const std::string& name)
	{
		if (m_analysis.find(name) == m_analysis.end())
			throw std::runtime_error("ERROR: Unknow profile");

		auto info = m_analysis[name];
		
		std::stringstream ss;
		ss << name << "[ID: " << info.ID << "] : ";
		ss << "( " << info.Info << " )\n";
		ss << "______________________________________________________\n";
		ss << std::right << std::setw(18) << "StartTime";
		ss << std::right << std::setw(18) << "EndTime";
		ss << std::right << std::setw(18) << "PassTime";
		ss << "\n";

		double starttime = info.StartTime * 0.001;
		double endtime = info.EndTime * 0.001;
		double passtime = endtime - starttime;
		ss << std::right << std::setw(15) << starttime << " ms";
		ss << std::right << std::setw(15) << endtime << " ms";
		ss << std::right << std::setw(15) << passtime << " ms";
		ss << "\n______________________________________________________\n";

		return ss.str();
	}
} // namespace Tool