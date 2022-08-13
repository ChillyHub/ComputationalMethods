#include "Serializer.h"

namespace Tool
{
	const std::string Sign::Equal = " = ";
	const std::string Sign::Newline = "\n";
	const std::string Sign::ThreeDot = " ... ";
	const std::string Sign::ThreeDotNewline = " ... \n";

	void Serializer::Save(const std::string& filename)
	{
		std::string tmpdir;
		std::string name;
		auto index = filename.find_last_of('/');
		if (index == std::string::npos)
		{
			tmpdir = "";
			name = filename;
		}
		else
		{
			tmpdir = std::string(filename, 0, filename.find_last_of('/') + 1);
			name = std::string(filename, filename.find_last_of('/') + 1);
		}

		std::string globaldir = S(PROJET_DIR) + "dataout/" + tmpdir;
		std::ofstream of(globaldir + name);
		if (!of.is_open())
		{
			std::error_code err;
			std::filesystem::create_directories(globaldir, err);
			if (!std::filesystem::exists(globaldir))
				throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + \
					"] Failed to create dir " + globaldir);

			of.open(globaldir + name);
			if (!of.is_open())
				throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + \
					"] Failed to open file " + globaldir + name);
		}

		of << m_text;
		of.flush();
		of.close();

		std::cout << "INFO: Save file " << filename << " succeed" << std::endl;
	}

	void Serializer::Clear()
	{
		m_text = std::string();
		m_indentation = 0;
		m_precision = 6;
		m_writeState = WriteState::Default;
	}

	void Serializer::SetPrecision(int p)
	{
		m_precision = p;
	}
	
	std::ostream& operator<<(std::ostream& os, const Serializer& serializer)
	{
		os << serializer.m_text;
		return os;
	}

	Serializer& operator<<(Serializer& serializer, const std::string& s)
	{
		serializer.m_text += s;
		if (s == Sign::Newline || s == Sign::ThreeDotNewline || s.back() == '\n')
			serializer.m_indentation = 0;
		else if (serializer.m_writeState & WriteState::IndentAlign)
			serializer.m_indentation += s.length();

		return serializer;
	}

	Serializer& operator<<(Serializer& serializer, WriteState writeState)
	{
		unsigned int a = writeState & 0x000f;
		unsigned int b = writeState & 0x00f0;
		unsigned int c = writeState & 0x0f00;
		if (a == 0)
			a = serializer.m_writeState & 0x000f;
		if (b == 0)
			b = serializer.m_writeState & 0x00f0;
		if (c == 0)
			c = serializer.m_writeState & 0x0f00;
		serializer.m_writeState = WriteState(a | b | c);
		return serializer;
	}
}