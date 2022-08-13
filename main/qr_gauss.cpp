#include "math/Math.h"
#include "tool/Tool.h"

using namespace Math;
using namespace Tool;
using namespace std;

int main()
{
	try
	{
		Deserializer dsq;
		Deserializer dsr;
		Deserializer ds;
		Serializer ser;

		Serializer profile;

		int method = 0;

		// Amat8
		try
		{
			dsq.ReadFile("dataout/Qmat8.m");
			dsr.ReadFile("dataout/Rmat8.m");
		}
		catch (const std::exception& e)
		{
			std::cout << "INFO: Can not find Q or R matrix file" << endl;
			std::cout << "INFO: Creating Q, R matrix file" << endl;

			ds.ReadFile("datas/Amat8.m");
			DMatX Qmat8, Rmat8;
			DMatX Amat8 = ds.GetData<DMatX>();
			method = ds.GetMethod();
			ds.Clear();

			if (!IsSquareMat(Amat8))
				throw runtime_error("ERROR: [main] Matrix Amat8 is not a square matrix");

			switch (method)
			{
			case 1:
				std::cout << "Using Householder Reflection" << std::endl;
				QRDecompose_HouseholderReflection(Amat8, Qmat8, Rmat8);
				break;
			case 2:
				std::cout << "Using Givens Rotation" << std::endl;
				QRDecompose_GivensRotation(Amat8, Qmat8, Rmat8);
				break;
			case 3:
				std::cout << "Using Modified Gram-Schmidt Orthogonalization" << std::endl;
				QRDecompose_ModifiedGramSchmidtOrthogonalization(Amat8, Qmat8, Rmat8);
				break;
			default:
				throw std::runtime_error("ERROR: Unknown method");
				break;
			}

			ser.SetPrecision(18);
			ser << WriteState::IndentAlign;
			ser << "Q" << Sign::Equal << Sign::ThreeDotNewline;
			ser << Qmat8;
			std::cout << ser << std::endl;
			ser.Save("Qmat8.m");
			ser.Clear();

			ser.SetPrecision(18);
			ser << WriteState::IndentAlign;
			ser << "R" << Sign::Equal << Sign::ThreeDotNewline;
			ser << Rmat8;
			std::cout << ser << std::endl;
			ser.Save("Rmat8.m");
			ser.Clear();

			dsq.ReadFile("dataout/Qmat8.m");
			dsr.ReadFile("dataout/Rmat8.m");
		}

		DMatX Qmat8 = dsq.GetData<DMatX>();
		DMatX Rmat8 = dsr.GetData<DMatX>();
		dsq.Clear();
		dsr.Clear();

		ds.ReadFile("datas/bvec8.m");
		DVecX bvec8 = ds.GetData<DVecX>();
		ds.Clear();

		if (!CanBeSolved(Rmat8, bvec8))  // Check matrix row length and vector length
			throw std::runtime_error("ERROR: Matrix's row length not match Vector length");

		if (!IsSquareMat(Qmat8) && !IsSquareMat(Rmat8))
			throw std::runtime_error("ERROR: Matrix Q, R (A) is not square matrixs");

		if (IsSingularMat(Qmat8) && IsSingularMat(Rmat8))
			throw std::runtime_error("ERROR: Matrix Q, R (A) is singular matrixs");

		std::cout << "INFO: Start Solve by QR" << std::endl;
		DVecX xvec8 = SolveQR(Qmat8, Rmat8, bvec8);

		ser.SetPrecision(16);
		ser << "x" << Sign::Equal;
		ser << xvec8;
		std::cout << "The solution (Amat8 * x = bvec8) is: " << ser << std::endl;
		ser.Save("xvec8.m");
		ser.Clear();


		// Amat9
		try
		{
			dsq.ReadFile("dataout/Qmat9.m");
			dsr.ReadFile("dataout/Rmat9.m");
		}
		catch (const std::exception& e)
		{
			std::cout << "INFO: Can not find Q or R matrix file" << endl;
			std::cout << "INFO: Creating Q, R matrix file" << endl;

			StartProfile(Load Amat9, Amat9: float)
			ds.ReadFile("datas/Amat9.m");
			MatX Qmat9, Rmat9;
			MatX Amat9 = ds.GetData<MatX>();
			method = ds.GetMethod();
			ds.Clear();
			EndProfile(Load Amat9)
			profile << ProfileStr(Load Amat9)

			if (!IsSquareMat(Amat9))
				throw runtime_error("ERROR: [main] Matrix Amat9 is not a square matrix");

			StartProfile(LU Decompose, Amat9: float)
			switch (method)
			{
			case 1:
				std::cout << "Using Householder Reflection" << std::endl;
				QRDecompose_HouseholderReflection(Amat9, Qmat9, Rmat9);
				break;
			case 2:
				std::cout << "Using Givens Rotation" << std::endl;
				QRDecompose_GivensRotation(Amat9, Qmat9, Rmat9);
				break;
			case 3:
				std::cout << "Using Modified Gram-Schmidt Orthogonalization" << std::endl;
				QRDecompose_ModifiedGramSchmidtOrthogonalization(Amat9, Qmat9, Rmat9);
				break;
			default:
				throw std::runtime_error("ERROR: Unknown method");
				break;
			}
			EndProfile(LU Decompose)
			profile << ProfileStr(LU Decompose)

			std::cout << "QR decompose of Amat9 succeed, view result in file Qmat9.m, Rmat9.m" << std::endl;

			ser << WriteState::IndentAlign;
			ser << "Q" << Sign::Equal << Sign::ThreeDotNewline;
			ser << Qmat9;
			ser.Save("Qmat9.m");
			ser.Clear();

			ser << WriteState::IndentAlign;
			ser << "R" << Sign::Equal << Sign::ThreeDotNewline;
			ser << Rmat9;
			ser.Save("Rmat9.m");
			ser.Clear();

			dsq.ReadFile("dataout/Qmat9.m");
			dsr.ReadFile("dataout/Rmat9.m");
		}

		MatX Qmat9 = dsq.GetData<MatX>();
		MatX Rmat9 = dsr.GetData<MatX>();
		dsq.Clear();
		dsr.Clear();

		ds.ReadFile("datas/bvec9.m");
		VecX bvec9 = ds.GetData<VecX>();
		ds.Clear();

		if (!CanBeSolved(Rmat9, bvec9))  // Check matrix row length and vector length
			throw std::runtime_error("ERROR: Matrix's row length not match Vector length");

		if (!IsSquareMat(Qmat9) && !IsSquareMat(Rmat9))
			throw std::runtime_error("ERROR: Matrix Q, R (A) is not square matrixs");

		StartProfile(Is Singular Mat?, Amat9 * x = bvec9: float)
		if (IsSingularMat(Qmat9) && IsSingularMat(Rmat9))
			throw std::runtime_error("ERROR: Matrix Q, R (A) is singular matrixs");
		EndProfile(Is Singular Mat?);
		profile << ProfileStr(Is Singular Mat?);

		std::cout << "INFO: Start Solve by QR" << std::endl;
		StartProfile(QR Solve, Amat9 * x = bvec9: float)
		VecX xvec9 = SolveQR(Qmat9, Rmat9, bvec9);
		EndProfile(QR Solve);
		profile << ProfileStr(QR Solve);

		ser << WriteState::VecNoSpace;
		ser << "x" << Sign::Equal;
		ser << xvec9;
		std::cout << "The solution (Amat9 * x = bvec9) succeed, view result in file xvec9.m" << std::endl;
		ser.Save("xvec9.m");
		ser.Clear();

		std::cout << "\n[Analysis]\n";
		std::cout << profile;
		profile.Save("task_2c.txt");
		profile.Clear();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}