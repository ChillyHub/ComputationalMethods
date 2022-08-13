#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "math/Math.h"

#define VARNAME(name) (#name)

namespace Tool
{
	enum WriteState : unsigned int
	{
		Default = 0x00,

		IndentWithSpace1 = 0x01,
		IndentWithSpace2 = 0x02,
		IndentWithSpace3 = 0x03,
		IndentWithSpace4 = 0x04,
		IndentWithTab = 0x05,
		IndentAlign = 0x06,

		VecNoSpace = 0x10,

		FloatFixed = 0x100
	};

	struct Sign
	{
		static const std::string Equal;
		static const std::string Newline;
		static const std::string ThreeDot;
		static const std::string ThreeDotNewline;
	};
	
	class Serializer
	{
	public:
		Serializer() = default;
		void Save(const std::string& filename);
		void Clear();
	public:
		void SetPrecision(int p);
	private:
		std::string m_text;
		WriteState m_writeState = WriteState::Default;
		int m_indentation = 0;
		int m_precision = 6;

	public:
		friend std::ostream& operator<<(std::ostream& os, const Serializer& serializer);
		
		friend Serializer& operator<<(Serializer&, WriteState);
		friend Serializer& operator<<(Serializer&, const std::string&);

		template <size_t N, typename T>
		friend Serializer& operator<<(Serializer&, const Math::Vec<N, T>&);
		template <size_t N, typename T>
		friend Serializer& operator<<(Serializer&, const Math::Vec<N, Math::Complex<T>>&);
		template <typename T>
		friend Serializer& operator<<(Serializer&, const Math::Vec<Math::Type::Dynamic, T>&);
		template <typename T>
		friend Serializer& operator<<(Serializer&, const Math::Vec<Math::Type::Dynamic, Math::Complex<T>>&);
		template <size_t M, size_t N, typename T>
		friend Serializer& operator<<(Serializer&, const Math::Mat<M, N, T>&);
		template <size_t M, size_t N, typename T>
		friend Serializer& operator<<(Serializer&, const Math::Mat<M, N, Math::Complex<T>>&);
		template <typename T>
		friend Serializer& operator<<(Serializer&, const Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, T>&);
		template <typename T>
		friend Serializer& operator<<(Serializer&, const Math::Mat<Math::Type::Dynamic, Math::Type::Dynamic, Math::Complex<T>>&);
	};
} // namespace Tool

// inline file
#include "Serializer.inl"