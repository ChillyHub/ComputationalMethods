#include "math/Math.h"
#include "tool/Tool.h"

using namespace Math;
using namespace Tool;
using namespace std;

int main()
{
	try
	{
		Deserializer ds;
		Serializer ser;
		int method;

		// Amat5
		ds.ReadFile("datas/Amat5.m");
		MatX Amat5 = ds.GetData<MatX>(); // Matrix with float
		MatX Qmat5, Rmat5;

		if (!IsSquareMat(Amat5))
			throw runtime_error("ERROR: [main] Matrix Amat5 is not a square matrix");

		method = ds.GetMethod();
		switch (method)
		{
		case 1:
			cout << "Using Householder Reflection" << endl;
			QRDecompose_HouseholderReflection(Amat5, Qmat5, Rmat5);
			break;
		case 2:
			cout << "Using Givens Rotation" << endl;
			QRDecompose_GivensRotation(Amat5, Qmat5, Rmat5);
			break;
		case 3:
			cout << "Using Modified Gram-Schmidt Orthogonalization" << endl;
			QRDecompose_ModifiedGramSchmidtOrthogonalization(Amat5, Qmat5, Rmat5);
			break;
		default:
			throw std::runtime_error("ERROR: Unknown method");
			break;
		}

		ser << WriteState::IndentAlign;
		ser << "Q" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Qmat5;
		cout << ser << endl;
		ser.Save("Qmat5.m");
		ser.Clear();

		ser << WriteState::IndentAlign;
		ser << "R" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Rmat5;
		cout << ser << endl;
		ser.Save("Rmat5.m");
		ser.Clear();

		// Amat6
		ds.ReadFile("datas/Amat6.m");
		DMatX Amat6 = ds.GetData<DMatX>(); // Matrix with float
		DMatX Qmat6, Rmat6;

		if (!IsSquareMat(Amat6))
			throw runtime_error("ERROR: [main] Matrix Amat6 is not a square matrix");

		method = ds.GetMethod();
		switch (method)
		{
		case 1:
			cout << "Using Householder Reflection" << endl;
			QRDecompose_HouseholderReflection(Amat6, Qmat6, Rmat6);
			break;
		case 2:
			cout << "Using Givens Rotation" << endl;
			QRDecompose_GivensRotation(Amat6, Qmat6, Rmat6);
			break;
		case 3:
			cout << "Using Modified Gram-Schmidt Orthogonalization" << endl;
			QRDecompose_ModifiedGramSchmidtOrthogonalization(Amat6, Qmat6, Rmat6);
			break;
		default:
			throw std::runtime_error("ERROR: Unknown method");
			break;
		}

		ser.SetPrecision(16);
		ser << WriteState::IndentAlign;
		ser << "Q" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Qmat6;
		cout << ser << endl;
		ser.Save("Qmat6.m");
		ser.Clear();

		ser.SetPrecision(16);
		ser << WriteState::IndentAlign;
		ser << "R" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Rmat6;
		cout << ser << endl;
		ser.Save("Rmat6.m");
		ser.Clear();

		// Amat7
		ds.ReadFile("datas/Amat7.m");
		MatX Amat7 = ds.GetData<MatX>(); // Matrix with float
		MatX Qmat7, Rmat7;

		if (!IsSquareMat(Amat7))
			throw runtime_error("ERROR: [main] Matrix Amat7 is not a square matrix");

		method = ds.GetMethod();
		switch (method)
		{
		case 1:
			cout << "Using Householder Reflection" << endl;
			QRDecompose_HouseholderReflection(Amat7, Qmat7, Rmat7);
			break;
		case 2:
			cout << "Using Givens Rotation" << endl;
			QRDecompose_GivensRotation(Amat7, Qmat7, Rmat7);
			break;
		case 3:
			cout << "Using Modified Gram-Schmidt Orthogonalization" << endl;
			QRDecompose_ModifiedGramSchmidtOrthogonalization(Amat7, Qmat7, Rmat7);
			break;
		default:
			throw std::runtime_error("ERROR: Unknown method");
			break;
		}

		ser << WriteState::IndentAlign;
		ser << "Q" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Qmat7;
		cout << ser << endl;
		ser.Save("Qmat7.m");
		ser.Clear();

		ser << WriteState::IndentAlign;
		ser << "R" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Rmat7;
		cout << ser << endl;
		ser.Save("Rmat7.m");
		ser.Clear();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}