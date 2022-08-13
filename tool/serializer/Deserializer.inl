#pragma once

#include "Deserializer.h"

namespace Tool
{
	// float
	template <>
	inline auto Deserializer::GetData<Math::Vec<Math::Type::Dynamic, float>>() const
	{
		if (m_data.structType == StructType::Vector && m_data.numType == NumType::Real)
		{
			Math::Vec<Math::Type::Dynamic, float> v(m_data.collen);
			for (size_t i = 0; i < m_data.collen; ++i)
				v[i] = std::stof(m_data.dataString[i][0]);
				
			return v;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	template <>
	inline auto Deserializer::GetData<Math::Vec<Math::Type::Dynamic, Math::Complex<float>>>() const
	{
		if (m_data.structType == StructType::Vector && m_data.numType == NumType::Complex)
		{
			Math::Vec<Math::Type::Dynamic, Math::Complex<float>> v(m_data.collen);
			for (size_t i = 0; i < m_data.collen; ++i)
				v[i].real = std::stof(m_data.dataString[i][0]);
			for (size_t i = m_data.collen; i < m_data.collen * 2; ++i)
				v[i - m_data.collen].imag = std::stof(m_data.dataString[i][0]);
			return v;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	template <>
	inline auto Deserializer::GetData<Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, float>>() const
	{
		if (m_data.structType == StructType::Matrix && m_data.numType == NumType::Real)
		{
			Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, float> m(m_data.collen, m_data.rowlen);
			for (size_t i = 0; i < m_data.rowlen; ++i)
			{
				Math::Vec<Math::Type::Dynamic, float> v(m_data.collen);
				for (size_t j = 0; j < m_data.collen; ++j)
					v[j] = std::stof(m_data.dataString[j][i]);
				m[i] = v;
			}
			return m;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	template <>
	inline auto Deserializer::GetData<Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, Math::Complex<float>>>() const
	{
		if (m_data.structType == StructType::Matrix && m_data.numType == NumType::Complex)
		{
			Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, Math::Complex<float>> m(m_data.collen, m_data.rowlen);
			for (size_t i = 0; i < m_data.rowlen; ++i)
			{
				Math::Vec<Math::Type::Dynamic, Math::Complex<float>> v(m_data.collen);
				for (size_t j = 0; j < m_data.collen; ++j)
					v[j].real = std::stof(m_data.dataString[j][i]);
				for (size_t j = m_data.collen; j < m_data.collen * 2; ++j)
					v[j - m_data.collen].imag = std::stof(m_data.dataString[j][i]);
				m[i] = v;
			}
			return m;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	// Double
	template <>
	inline auto Deserializer::GetData<Math::Vec<Math::Type::Dynamic, double>>() const
	{
		if (m_data.structType == StructType::Vector && m_data.numType == NumType::Real)
		{
			Math::Vec<Math::Type::Dynamic, double> v(m_data.collen);
			for (size_t i = 0; i < m_data.collen; ++i)
				v[i] = std::stod(m_data.dataString[i][0]);
			return v;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	template <>
	inline auto Deserializer::GetData<Math::Vec<Math::Type::Dynamic, Math::Complex<double>>>() const
	{
		if (m_data.structType == StructType::Vector && m_data.numType == NumType::Complex)
		{
			Math::Vec<Math::Type::Dynamic, Math::Complex<double>> v(m_data.collen);
			for (size_t i = 0; i < m_data.collen; ++i)
				v[i].real = std::stod(m_data.dataString[i][0]);
			for (size_t i = m_data.collen; i < m_data.collen * 2; ++i)
				v[i - m_data.collen].imag = std::stof(m_data.dataString[i][0]);
			return v;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	template <>
	inline auto Deserializer::GetData<Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, double>>() const
	{
		if (m_data.structType == StructType::Matrix && m_data.numType == NumType::Real)
		{
			Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, double> m(m_data.collen, m_data.rowlen);
			for (size_t i = 0; i < m_data.rowlen; ++i)
			{
				Math::Vec<Math::Type::Dynamic, double> v(m_data.collen);
				for (size_t j = 0; j < m_data.collen; ++j)
					v[j] = std::stod(m_data.dataString[j][i]);
				m[i] = v;
			}
			return m;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	template <>
	inline auto Deserializer::GetData<Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, Math::Complex<double>>>() const
	{
		if (m_data.structType == StructType::Matrix && m_data.numType == NumType::Complex)
		{
			Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, Math::Complex<double>> m(m_data.collen, m_data.rowlen);
			for (size_t i = 0; i < m_data.rowlen; ++i)
			{
				Math::Vec<Math::Type::Dynamic, Math::Complex<double>> v(m_data.collen);
				for (size_t j = 0; j < m_data.collen; ++j)
					v[j].real = std::stod(m_data.dataString[j][i]);
				for (size_t j = m_data.collen; j < m_data.collen * 2; ++j)
					v[j - m_data.collen].imag = std::stof(m_data.dataString[j][i]);
				m[i] = v;
			}
			return m;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	// Long double
	template <>
	inline auto Deserializer::GetData<Math::Vec<Math::Type::Dynamic, long double>>() const
	{
		if (m_data.structType == StructType::Vector && m_data.numType == NumType::Real)
		{
			Math::Vec<Math::Type::Dynamic, long double> v(m_data.collen);
			for (size_t i = 0; i < m_data.collen; ++i)
				v[i] = std::stod(m_data.dataString[i][0]);
			return v;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}

	template <>
	inline auto Deserializer::GetData<Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, long double>>() const
	{
		if (m_data.structType == StructType::Matrix && m_data.numType == NumType::Real)
		{
			Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, long double> m(m_data.collen, m_data.rowlen);
			for (size_t i = 0; i < m_data.rowlen; ++i)
			{
				Math::Vec<Math::Type::Dynamic, long double> v(m_data.collen);
				for (size_t j = 0; j < m_data.collen; ++j)
					v[j] = std::stod(m_data.dataString[j][i]);
				m[i] = v;
			}
			return m;
		}
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Data type not match");
	}
} // namespace Tool