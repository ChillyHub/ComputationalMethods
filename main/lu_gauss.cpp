#include "math/Math.h"
#include "tool/Tool.h"

using namespace Math;
using namespace Tool;
using namespace std;

int main()
{
	try
	{
		Deserializer dsl;
		Deserializer dsu;
		Deserializer ds;
		Serializer ser;

		Serializer profile;

		// Amat3
		try
		{
			dsl.ReadFile("dataout/Lmat3.m");
			dsu.ReadFile("dataout/Umat3.m");
		}
		catch (const std::exception& e)
		{
			cout << "INFO: Can not find L or U matrix file" << endl;
			cout << "INFO: Creating L, U matrix file" << endl;

			ds.ReadFile("datas/Amat3.m");
			DMatX Lmat3, Umat3;
			DMatX Amat3 = ds.GetData<DMatX>();
			ds.Clear();

			if (!IsSquareMat(Amat3))
				throw runtime_error("ERROR: [main] Matrix Amat4 is not a square matrix");

			if (!IsRegularMat(Amat3))
				throw runtime_error("ERROR: [main] Matrix Amat4 is not a regular matrix");

			LUDecompose(Amat3, Lmat3, Umat3);

			ser.SetPrecision(16);
			ser << WriteState::IndentAlign;
			ser << "L" << Sign::Equal << Sign::ThreeDotNewline;
			ser << Lmat3;
			cout << ser << endl;
			ser.Save("Lmat3.m");
			ser.Clear();

			ser.SetPrecision(16);
			ser << WriteState::IndentAlign;
			ser << "U" << Sign::Equal << Sign::ThreeDotNewline;
			ser << Umat3;
			cout << ser << endl;
			ser.Save("Umat3.m");
			ser.Clear();

			dsl.ReadFile("dataout/Lmat3.m");
			dsu.ReadFile("dataout/Umat3.m");
		}
		
		DMatX Lmat3 = dsl.GetData<DMatX>();
		DMatX Umat3 = dsu.GetData<DMatX>();
		dsl.Clear();
		dsu.Clear();
		
		ds.ReadFile("datas/bvec3.m");
		DVecX bvec3 = ds.GetData<DVecX>();
		ds.Clear();
		
		DVecX xvec3 = SolveLU(Lmat3, Umat3, bvec3);
		
		ser.SetPrecision(17);
		ser << "x" << Sign::Equal;
		ser << xvec3;
		cout << "The solution (Amat3 * x = bvec3) is: " << ser << endl;
		ser.Save("xvec3.m");
		ser.Clear();


		// Amat4
		try
		{
			dsl.ReadFile("dataout/Lmat4.m");
			dsu.ReadFile("dataout/Umat4.m");
		}
		catch (const std::exception& e)
		{
			cout << "INFO: Can not find L or U matrix file" << endl;
			cout << "INFO: Creating L, U matrix file" << endl;

			StartProfile(Load Amat4, Amat4: float)
			ds.ReadFile("datas/Amat4.m");
			MatX Lmat4, Umat4;
			MatX Amat4 = ds.GetData<MatX>();
			ds.Clear();
			EndProfile(Load Amat4)
			profile << ProfileStr(Load Amat4)

			if (!IsSquareMat(Amat4))
				throw runtime_error("ERROR: [main] Matrix Amat4 is not a square matrix");

			if (!IsRegularMat(Amat4))   
				throw runtime_error("ERROR: [main] Matrix Amat4 is not a regular matrix");

			StartProfile(LU Calculate, Amat4: float)
			LUDecompose(Amat4, Lmat4, Umat4);
			EndProfile(LU Calculate)
			profile << ProfileStr(LU Calculate)

			cout << "LU decompose of Amat4 succeed, view result in file Lmat4.m, Umat4.m" << endl;

			ser << WriteState::IndentAlign;
			ser << "L" << Sign::Equal << Sign::ThreeDotNewline;
			ser << Lmat4;
			ser.Save("Lmat4.m");
			ser.Clear();

			ser << WriteState::IndentAlign;
			ser << "U" << Sign::Equal << Sign::ThreeDotNewline;
			ser << Umat4;
			ser.Save("Umat4.m");
			ser.Clear();

			dsl.ReadFile("dataout/Lmat4.m");
			dsu.ReadFile("dataout/Umat4.m");
		}

		MatX Lmat4 = dsl.GetData<MatX>();
		MatX Umat4 = dsu.GetData<MatX>();
		dsl.Clear();
		dsu.Clear();

		ds.ReadFile("datas/bvec4.m");
		VecX bvec4 = ds.GetData<VecX>();
		ds.Clear();

		StartProfile(LU Solve, Amat4 * x = bvec4: float)
		VecX xvec4 = SolveLU(Lmat4, Umat4, bvec4);
		EndProfile(LU Solve)
		profile << ProfileStr(LU Solve)

		ser << WriteState::VecNoSpace;
		ser << "x" << Sign::Equal;
		ser << xvec4;
		cout << "Solve (Amat4 * x = bvec4) succeed, view result in file xvec4.m" << endl;
		ser.Save("xvec4.m");
		ser.Clear();

		cout << "\n[Analysis]\n";
		cout << profile;
		profile.Save("task_1c.txt");
		profile.Clear();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	
	return 0;
}