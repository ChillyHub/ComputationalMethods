#include "math/Math.h"
#include "tool/Tool.h"

using namespace Math;
using namespace Tool;

int main()
{
	try
	{
		Deserializer ds;
		Serializer ser;

		Serializer profile;

		// Amat10
		ds.ReadFile("datas/Amat10.m");
		MatX Amat10 = ds.GetData<MatX>();
		ds.Clear();

		if (!IsSquareMat(Amat10))
			throw std::runtime_error("ERROR: Matrix Amat10 is not a square matrix");

		if (!IsTridiagonalMat(Amat10))
			throw std::runtime_error("ERROR: Matrix Amat10 is not a tridiagonal matrix");

		VecX v = FindEigenByTridiagonalMat(Amat10);

		ser << WriteState::VecNoSpace;
		ser << VARNAME(v) << Sign::Equal;
		ser << v;
		std::cout << ser << std::endl;
		ser.Save("vvec10.m");
		ser.Clear();


		// Amat11
		ds.ReadFile("datas/Amat11.m");
		LDMatX Amat11 = ds.GetData<LDMatX>();
		ds.Clear();

		if (!IsSquareMat(Amat11))
			throw std::runtime_error("ERROR: Matrix Amat11 is not a square matrix");

		if (!IsTridiagonalMat(Amat11))
			throw std::runtime_error("ERROR: Matrix Amat11 is not a tridiagonal matrix");

		StartProfile(Find Eigen, Amat11: long double)
		LDVecX v11 = FindEigenByTridiagonalMat(Amat11);
		EndProfile(Find Eigen)
		profile << ProfileStr(Find Eigen)

		ser << WriteState::VecNoSpace;
		ser << "v" << Sign::Equal;
		ser << v11;
		std::cout << "Get eigen poly succeed, view result in file vvec11.m" << std::endl;
		ser.Save("vvec11.m");
		ser.Clear();

		std::cout << "\n[Analysis]\n";
		std::cout << profile;
		profile.Save("task_3c.txt");
		profile.Clear();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}