#pragma once

#include "Serializer.h"

namespace Tool
{
	template <size_t N, typename T>
	Serializer& operator<<(Serializer& serializer, const Math::Vec<N, T>& v)
	{
		std::stringstream ss;
		if ((serializer.m_writeState & 0x0f00) == WriteState::FloatFixed)
			ss << std::fixed;
		ss << std::setprecision(serializer.m_precision);

		ss << "[";
		for (size_t i = 0; i < N; ++i)
		{
			ss << OUTNUM(v[i]);
			if (i < N - 1)
			{
				ss << ";";
				if ((serializer.m_writeState & 0xf0) != WriteState::VecNoSpace)
					ss << " ";
			}
		}
		ss << "];\n";

		serializer.m_indentation = 0;
		serializer.m_text += ss.str();
		return serializer;
	}

	template <size_t N, typename T>
	Serializer& operator<<(Serializer& serializer, const Math::Vec<N, Math::Complex<T>>& v)
	{
		std::stringstream ss;
		if ((serializer.m_writeState & 0x0f00) == WriteState::FloatFixed)
			ss << std::fixed;
		ss << std::setprecision(serializer.m_precision);

		ss << "complex(";

		ss << "[";
		for (size_t i = 0; i < N; ++i)
		{
			ss << OUTNUM(v[i].real);
			if (i < N - 1)
			{
				ss << ";";
				if ((serializer.m_writeState & 0xf0) != WriteState::VecNoSpace)
					ss << " ";
			}
		}
		ss << "],[";
		for (size_t i = 0; i < N; ++i)
		{
			ss << OUTNUM(v[i].imag);
			if (i < N - 1)
			{
				ss << ";";
				if ((serializer.m_writeState & 0xf0) != WriteState::VecNoSpace)
					ss << " ";
			}
		}
		ss << "]);\n";

		serializer.m_indentation = 0;
		serializer.m_text += ss.str();
		return serializer;
	}

	template <typename T>
	Serializer& operator<<(Serializer& serializer, const Math::Vec<Math::Type::Dynamic, T>& v)
	{
		std::stringstream ss;
		if ((serializer.m_writeState & 0x0f00) == WriteState::FloatFixed)
			ss << std::fixed;
		ss << std::setprecision(serializer.m_precision);

		ss << "[";
		for (size_t i = 0; i < v.length(); ++i)
		{
			ss << OUTNUM(v[i]);
			if (i < v.length() - 1)
			{
				ss << ";";
				if ((serializer.m_writeState & 0xf0) != WriteState::VecNoSpace)
					ss << " ";
			}
		}
		ss << "];\n";

		serializer.m_indentation = 0;
		serializer.m_text += ss.str();
		return serializer;
	}

	template <typename T>
	Serializer& operator<<(Serializer& serializer, const Math::Vec<Math::Type::Dynamic, Math::Complex<T>>& v)
	{
		std::stringstream ss;
		if ((serializer.m_writeState & 0x0f00) == WriteState::FloatFixed)
			ss << std::fixed;
		ss << std::setprecision(serializer.m_precision);

		ss << "complex([";
		for (size_t i = 0; i < v.length(); ++i)
		{
			ss << OUTNUM(v[i].real);
			if (i < v.length() - 1)
			{
				ss << ";";
				if ((serializer.m_writeState & 0xf0) != WriteState::VecNoSpace)
					ss << " ";
			}
		}
		ss << "],[";
		for (size_t i = 0; i < v.length(); ++i)
		{
			ss << OUTNUM(v[i].imag);
			if (i < v.length() - 1)
			{
				ss << ";";
				if ((serializer.m_writeState & 0xf0) != WriteState::VecNoSpace)
					ss << " ";
			}
		}
		ss << "]);\n";

		serializer.m_indentation = 0;
		serializer.m_text += ss.str();
		return serializer;
	}

	template <size_t M, size_t N, typename T>
	Serializer& operator<<(Serializer& serializer, const Math::Mat<M, N, T>& m)
	{
		std::stringstream ss;
		if ((serializer.m_writeState & 0x0f00) == WriteState::FloatFixed)
			ss << std::fixed;
		ss << std::setprecision(serializer.m_precision);

		ss << "[";
		for (size_t i = 0; i < M; ++i)
		{
			auto row = m.GetRow(i);
			if (i != 0)
			{
				if ((serializer.m_writeState & 0x0f) == WriteState::IndentWithTab)
					ss << "\t";
				else if ((serializer.m_writeState & 0x0f) == WriteState::IndentAlign)
					for (int k = 0; k <= serializer.m_indentation; ++k)
						ss << " ";
			}

			for (size_t j = 0; j < N; ++j)
			{
				ss << OUTNUM(row[j]);
				if (j < N - 1)
					ss << " ";
			}
			if (i == M - 1)
				ss << "];\n";
			else
				ss << ";\n";
		}
		
		serializer.m_indentation = 0;
		serializer.m_text += ss.str();
		return serializer;
	}

	template <size_t M, size_t N, typename T>
	Serializer& operator<<(Serializer& serializer, const Math::Mat<M, N, Math::Complex<T>>& m)
	{
		std::stringstream ss;
		if ((serializer.m_writeState & 0x0f00) == WriteState::FloatFixed)
			ss << std::fixed;
		ss << std::setprecision(serializer.m_precision);

		Math::Mat<N, M, Math::Complex<T>> rows;
		for (size_t i = 0; i < M; ++i)
			rows[i] = m.GetRow(i);

		ss << "complex([";
		for (size_t i = 0; i < M; ++i)
		{
			if (i != 0)
			{
				if ((serializer.m_writeState & 0x0f) == WriteState::IndentWithTab)
					ss << "\t";
				else if ((serializer.m_writeState & 0x0f) == WriteState::IndentAlign)
					for (int k = 0; k < serializer.m_indentation + 9; ++k)
						ss << " ";
			}

			for (size_t j = 0; j < N; ++j)
			{
				ss << OUTNUM(rows[i][j].real);
				if (j < N - 1)
					ss << " ";
			}
			if (i == M - 1)
				ss << "],[";
			else
				ss << ";\n";
		}
		for (size_t i = 0; i < M; ++i)
		{
			if (i != 0)
			{
				if ((serializer.m_writeState & 0x0f) == WriteState::IndentWithTab)
					ss << "\t";
				else if ((serializer.m_writeState & 0x0f) == WriteState::IndentAlign)
					for (int k = 0; k < serializer.m_indentation + 9; ++k)
						ss << " ";
			}

			for (size_t j = 0; j < N; ++j)
			{
				ss << OUTNUM(rows[i][j].imag);
				if (j < N - 1)
					ss << " ";
			}
			if (i == M - 1)
				ss << "]);\n";
			else
				ss << ";\n";
		}

		serializer.m_indentation = 0;
		serializer.m_text += ss.str();
		return serializer;
	}

	template <typename T>
	Serializer& operator<<(Serializer& serializer, const Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, T>& m)
	{
		std::stringstream ss;
		if ((serializer.m_writeState & 0x0f00) == WriteState::FloatFixed)
			ss << std::fixed;
		ss << std::setprecision(serializer.m_precision);

		ss << "[";
		for (size_t i = 0; i < m.col_len(); ++i)
		{
			auto row = m.GetRow(i);
			if (i != 0)
			{
				if ((serializer.m_writeState & 0x0f) == WriteState::IndentWithTab)
					ss << "\t";
				else if ((serializer.m_writeState & 0x0f) == WriteState::IndentAlign)
					for (int k = 0; k <= serializer.m_indentation; ++k)
						ss << " ";
			}

			for (size_t j = 0; j < m.row_len(); ++j)
			{
				ss << OUTNUM(row[j]);
				if (j < m.row_len() - 1)
					ss << " ";
			}
			if (i == m.col_len() - 1)
				ss << "];\n";
			else
				ss << ";\n";
		}

		serializer.m_indentation = 0;
		serializer.m_text += ss.str();
		return serializer;
	}

	template <typename T>
	Serializer& operator<<(Serializer& serializer, const Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, Math::Complex<T>>& m)
	{
		std::stringstream ss;
		if ((serializer.m_writeState & 0x0f00) == WriteState::FloatFixed)
			ss << std::fixed;
		ss << std::setprecision(serializer.m_precision);

		Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, Math::Complex<T>>
			rows(m.row_len(), m.col_len());
		for (size_t i = 0; i < m.col_len(); ++i)
			rows[i] = m.GetRow(i);

		ss << "complex([";
		for (size_t i = 0; i < m.col_len(); ++i)
		{
			if (i != 0)
			{
				if ((serializer.m_writeState & 0x0f) == WriteState::IndentWithTab)
					ss << "\t";
				else if ((serializer.m_writeState & 0x0f) == WriteState::IndentAlign)
					for (int k = 0; k < serializer.m_indentation + 9; ++k)
						ss << " ";
			}

			for (size_t j = 0; j < m.row_len(); ++j)
			{
				ss << OUTNUM(rows[i][j].real);
				if (j < m.row_len() - 1)
					ss << " ";
			}
			if (i == m.col_len() - 1)
				ss << "],[";
			else
				ss << ";\n";
		}
		for (size_t i = 0; i < m.col_len(); ++i)
		{
			if (i != 0)
			{
				if ((serializer.m_writeState & 0x0f) == WriteState::IndentWithTab)
					ss << "\t";
				else if ((serializer.m_writeState & 0x0f) == WriteState::IndentAlign)
					for (int k = 0; k < serializer.m_indentation + 9; ++k)
						ss << " ";
			}

			for (size_t j = 0; j < m.row_len(); ++j)
			{
				ss << OUTNUM(rows[i][j].imag);
				if (j < m.row_len() - 1)
					ss << " ";
			}
			if (i == m.col_len() - 1)
				ss << "]);\n";
			else
				ss << ";\n";
		}

		serializer.m_indentation = 0;
		serializer.m_text += ss.str();
		return serializer;
	}
} // namespace Tool