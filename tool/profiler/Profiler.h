#pragma once

#include "Time.h"

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <unordered_map>

#define StartProfile(name, info) ::Tool::Profiler::AddAnalysis(#name, #info); \
								 ::Tool::Profiler::StartAnlysis(#name);
#define EndProfile(name) ::Tool::Profiler::EndAnlysis(#name);
#define ProfileStr(name) ::Tool::Profiler::GetAnlysisInfo(#name);

namespace Tool
{
	class Profiler
	{
	public:
		static void AddAnalysis(const std::string& name, const std::string& info);
		static void StartAnlysis(const std::string& name);
		static void EndAnlysis(const std::string& name);
		static std::string GetAnlysisInfo(const std::string& name);
	private:
		struct AnalysisInfo
		{
			int ID = 0;
			std::string Name;
			std::string Info;
			double StartTime;
			double EndTime;
		};
		static std::unordered_map<std::string, AnalysisInfo> m_analysis;
		static int m_idCount;
	};
} // namespace Tool