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

		// Amat1
		ds.ReadFile("datas/Amat1.m");
		MatX Amat1 = ds.GetData<MatX>(); // Matrix with float
		MatX Lmat1, Umat1;

		if (!IsSquareMat(Amat1))
			throw runtime_error("ERROR: [main] Matrix Amat1 is not a square matrix");

		if (!IsRegularMat(Amat1))
			throw runtime_error("ERROR: [main] Matrix Amat1 is not a regular matrix");

		LUDecompose(Amat1, Lmat1, Umat1);
		
		ser << WriteState::IndentAlign << WriteState::FloatFixed;
		ser << "L" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Lmat1;
		cout << ser << endl;
		ser.Save("Lmat1.m");
		ser.Clear();

		ser << WriteState::IndentAlign << WriteState::FloatFixed;
		ser << "U" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Umat1;
		cout << ser << endl;
		ser.Save("Umat1.m");
		ser.Clear();

		// Amat2
		ds.ReadFile("datas/Amat2.m");
		CDMatX Amat2 = ds.GetData<CDMatX>(); // Matrix with double complex
		CDMatX Lmat2, Umat2;

		if (!IsSquareMat(Amat2))
			throw runtime_error("ERROR: [main] Matrix Amat2 is not a square matrix");

		if (!IsRegularMat(Amat2))
			throw runtime_error("ERROR: [main] Matrix Amat2 is not a regular matrix");

		LUDecompose(Amat2, Lmat2, Umat2);

		ser.SetPrecision(17);
		ser << WriteState::IndentAlign;
		ser << "L" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Lmat2;
		cout << ser << endl;
		ser.Save("Lmat2.m");
		ser.Clear();

		ser.SetPrecision(17);
		ser << WriteState::IndentAlign;
		ser << "U" << Sign::Equal << Sign::ThreeDotNewline;
		ser << Umat2;
		cout << ser << endl;
		ser.Save("Umat2.m");
		ser.Clear();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}
