#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <regex>
#include <vector>

#include "math/Math.h"

namespace Tool
{
	class Deserializer
	{
	public:
		Deserializer() = default;
		void ReadFile(const std::string& filename);
		void Clear();
	public:
		int GetID() const { return m_data.id; }
		int GetMethod() const { return m_data.method; }
	public:
		template <typename T>
		auto GetData() const;
	private:
		enum StructType
		{
			Vector,
			Matrix
		};
		enum NumType
		{
			Real,
			Complex
		};
		struct Data
		{
			int id = 0;
			int method = 0;
			int collen = 0;
			int rowlen = 0;
			std::string name;
			StructType structType = StructType::Vector;
			NumType numType = NumType::Real;
			std::vector<std::vector<std::string>> dataString;
		};
		Data m_data;
	};
} // namespace Tool

// inline file
#include "Deserializer.inl"