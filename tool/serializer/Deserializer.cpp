#include "Deserializer.h"

namespace Tool
{
	void Deserializer::ReadFile(const std::string& filename)
	{
		std::ifstream file(S(PROJET_DIR) + filename);

		if (!file.is_open())
		{
			file.close();
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + \
				"] Failed to open file " + S(PROJET_DIR) + filename);
		}

		std::cout << "INFO: Loading File " << filename << " ..." << std::endl;

		std::stringstream ss;
		ss << file.rdbuf();
		std::string data(ss.str());
		file.close();
		ss.clear();
		Clear();

		std::cout << "INFO: Parsing File " << filename << " ..." << std::endl;

		auto it = data.find_first_of("[");
		if (it == std::string::npos)
			throw std::runtime_error(S("ERROR: ") + _FUN_NAME_ + "] File do not have data");

		std::string info;
		info = data.substr(0, it + 1);
		data = data.substr(it + 1);
		
		std::string patternID("^[\\w\\d/]*([\\d]*)\\.[\\w]+");
		std::string patternMethod("Method[\\s]*=[\\s]*[\\d]+");
		std::string patternName("^(?!Method)[\\w]+(?=[\\s]*=)");
		std::string patternType("complex");

		std::regex r0(patternID);
		std::regex r1(patternMethod);
		std::regex r2(patternName);
		std::regex r3(patternType);
		std::smatch result;

		if (std::regex_search(filename, result, r0))
		{
			std::string sid(result.str());
			std::string pattern("[\\d]+");
			std::regex r(pattern);
			std::smatch match;

			if (std::regex_search(sid, match, r))
			{
				m_data.id = std::stoi(match.str());
			}
		}
		
		if (std::regex_search(info, result, r1))
		{
			std::string method(result.str());
			std::string pattern("[\\d]+");
			std::regex r(pattern);
			std::smatch match;

			if (std::regex_search(method, match, r))
			{
				m_data.method = std::stoi(match.str());
			}
		}

		if (std::regex_search(info, result, r2))
		{
			m_data.name = result.str();
		}

		if (std::regex_search(info, result, r3))
		{
			m_data.numType = NumType::Complex;
		}

		std::replace(data.begin(), data.end(), '[', '\n');
		std::replace(data.begin(), data.end(), ';', '\n');

		std::string rowstr;
		std::stringstream sst(data);
		while (std::getline(sst, rowstr))
		{
			if (rowstr == "" || rowstr == "\n" || rowstr == " ...")
				continue;
			
			std::vector<std::string> row;
			std::stringstream ssr(rowstr);
			std::string num;
			row.reserve(m_data.rowlen);
			while (ssr >> num)
			{
				row.emplace_back(num);
			}
			if (row.size() > m_data.rowlen)
			{
				m_data.rowlen = row.size();
			}
			m_data.dataString.emplace_back(row);
			m_data.collen++;
		}

		if (m_data.numType == NumType::Complex)
		{
			m_data.collen /= 2;
		}

		if (m_data.rowlen > 1)
		{
			m_data.structType = StructType::Matrix;
		}
		
		std::cout << "INFO: Parsed File " << filename << " succeed" << std::endl;
	}

	void Deserializer::Clear()
	{
		m_data = Data();
	}
}