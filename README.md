# Computational methods

[TOC]

### File composition

- **/main:**  The main program source file. Such as make_lu, lu_gauss ... (Link to Math.a(lib) and Tool.a(lib))
- **/math:**  All math related calculation code is here. (Compile to libary Math)
  - **/type:**  Define data structures such as Complex, Vector, and Matrix, including constructors, operator overloading. Types are divided into fixed-size types stored on the stack and dynamically allocated types stored on the heap.
  - **/func:**  Define basic functions related to mathematical operations, and matrix algorithms used in this assignment. The relevant code is in the file math/func/algorithm.
- **/tool:**  Code for file IO, timing. (Compile to libary Tool)
  - **/serializer:**  Define serializer and deserializer, help file input and output.
  - **/profiler:**  Define timer and profiler, calculate code runtime



### How to compile

This project is configured by **CMake**. 

Make sure the version number of CMake is greater than **3.15**.
The compiler best supports **C++20**. 

**MinGW (g++)** is recommended. **MSVC ** is **not** recommended. Because MSVC do not have type **long double**.

**Windows** is recommended.

Then, in root direction, there are some Win bat help to quickly configure and build.
**MinGWConfigBuild.bat** is recommended.

Also, you can configure from the command line

```shell
cmake --B <build_floder_name>
cmake --build <build_floder_name>
```

After compile succeed, you can run **Run_MinGW.bat** (compiled by G++) or **Run_MSVC.bat** (compiled by MSVC). It will **run all five programs**.



### Result

Raw data is stored in folder **/datas**

The output files can be found in folder **/dataout** ( If the folder does not exist, it will be created automatically when the program runs )



### Main algorithm

> All main algorithms are in file **/math/func/Algorithm.inl**

**Matrix is column-major order storage, so A\[i]\[j] means element on column i, row j.**



##### LU Decompose

$$
A = 
\begin{bmatrix}
a_{11} & w^T \\
     v & A^{'}
\end{bmatrix}
=
\begin{bmatrix}
        1 & 0 \\
 v/a_{11} & I_{n-1}
\end{bmatrix}
\begin{bmatrix}
  a_{11} & w^T \\
       0 & A^{'}-vw^T/a_{11}
\end{bmatrix}
\\ =
\begin{bmatrix}
       1 & 0 \\
v/a_{11} & I_{n-1}
\end{bmatrix}
\begin{bmatrix}
a_{11} & w^T \\
     0 & L^{'}U^{'}
\end{bmatrix}
=
\begin{bmatrix}
       1 & 0 \\
v/a_{11} & L^{'}
\end{bmatrix}
\begin{bmatrix}
a_{11} & w^T \\
     0 & U^{'}
\end{bmatrix}
= LU
$$

We can block the matrix as above, and then iterate layer by layer.

```c++
// math/func/Algorithm.inl

template <typename T>
inline void LUDecompose(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
	Mat<Type::Dynamic, Type::Dynamic, T>& L, Mat<Type::Dynamic, Type::Dynamic, T>& U)
{
	const size_t N = A.col_len();
		
	if (!IsSquareMat(A))
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a square matrix");

	Mat<Type::Dynamic, Type::Dynamic, T> AA(A);
	L = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
	U = std::move(Mat<Type::Dynamic, Type::Dynamic, T>(N, N));
	for (size_t k = 0; k < N; ++k)
	{
		if (AA[k][k] == T(0))
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A can not LU decompose");
			
		L[k][k] = T(1);
		U[k][k] = AA[k][k];
		for (size_t i = k + 1; i < N; ++i)
		{
			L[k][i] = AA[k][i] / U[k][k];
			U[i][k] = AA[i][k];
		}
		for (size_t i = k + 1; i < N; ++i)
		{
			for (size_t j = k + 1; j < N; ++j)
			{
				AA[i][j] -= L[k][j] * U[i][k];
			}
		}
	}
}
```

##### LU Solve

$$
Ax=b \Rightarrow
QRx=b \Rightarrow
Qc=b \Rightarrow
Rx=c
$$

```c++
// math/func/Algorithm.inl
template <typename T>
inline Vec<Type::Dynamic, T> SolveLU(const Mat<Type::Dynamic, Type::Dynamic, T>& L,
	const Mat<Type::Dynamic, Type::Dynamic, T>& U,
	const Vec<Type::Dynamic, T>& b)
{
	const size_t N = L.col_len();

	if (!IsSquareMat(L) || !IsSquareMat(U))
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix L or U are not square matrix");
		
	Vec<Type::Dynamic, T> c(N);
	c[0] = b[0];
	for (size_t k = 1; k < N; ++k)
	{
		c[k] = b[k];
		for (size_t i = 0; i < k; ++i)
			c[k] -= c[i] * L[i][k];
	}

	Vec<Type::Dynamic, T> x(N);
	x[N - 1] = c[N - 1] / U[N - 1][N - 1];
	for (int k = N - 2; k >= 0; --k)
	{
		x[k] = c[k];
		for (size_t i = N - 1; i > k; --i)
			x[k] -= x[i] * U[i][k];
		x[k] /= U[k][k];
	}

	return x;
}
```

##### QR Decompose - Householder Reflection

$$
x_i = A_{col_i}  \\
w_i = [0, \cdot\cdot\cdot,(||x||_2)_i, 0, 0, \cdot\cdot\cdot] \\
v_i = w_i - x_i \\
P_i = \frac{v_iv_i^T}{v_i^Tv_i} \\
H_i = I - 2P_i \\
Q = H_1H_2H_3\cdot\cdot\cdot H_n \\
R = H_nH_{n-1}\cdot\cdot\cdot H_1A
$$

```C++
// math/func/Algorithm.inl

template <typename T>
inline void QRDecompose_HouseholderReflection(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
	Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R)
{
	const size_t M = A.col_len(), N = A.row_len();

	Q = Mat<Type::Dynamic, Type::Dynamic, T>(T(1), M, M);
	R = Mat<Type::Dynamic, Type::Dynamic, T>(A);
	for (size_t i = 0; i < N; ++i)
	{
		Vec<Type::Dynamic, T> w(M - i), x(M - i);
		for (size_t j = 0; j < M - i; ++j)
			x[j] = R[i][i + j];
		w[0] = Norm(x);  // ||x||2

		Vec<Type::Dynamic, T> v = w - x;

		T vtv = Dot(v, v);
		Mat<Type::Dynamic, Type::Dynamic, T> H(T(1), M, M);
		if (vtv != T(0))
		{
			Mat<Type::Dynamic, Type::Dynamic, T> P = v * Transpose(v) / vtv;
			for (size_t j = i; j < M; ++j)
			{
				for (size_t k = i; k < M; ++k)
				{
					H[j][k] -= P[j - i][k - i] * T(2);
				}
			}
		}

		Q = Q * H;
		R = H * R;
	}
}
```

##### QR Decompose - Givens Rotation

```C++
// math/func/Algorithm.inl

template <typename T>
inline void QRDecompose_GivensRotation(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
	Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R)
{
	const size_t M = A.col_len(), N = A.row_len();
		
	Q = Mat<Type::Dynamic, Type::Dynamic, T>(T(1), M, M);
	R = Mat<Type::Dynamic, Type::Dynamic, T>(A);
	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = M - 1; j > i; --j)
		{
			T t, s, c;
			if (R[i][j] == T(0))
			{
				continue;
			}
			else if (R[i][j - 1] == T(0))
			{
				s = T(1);
				c = T(0);
			}
			else if (Abs(R[i][j - 1]) < Abs(R[i][j]))
			{
				t = R[i][j - 1] / R[i][j];
				s = T(1) / std::sqrt(T(1) + t * t);
				c = s * t;
			}
			else
			{
				t = R[i][j] / R[i][j - 1];
				c = T(1) / std::sqrt(T(1) + t * t);
				s = c * t;
			}

			for (size_t k = 0; k < N; ++k)
			{
				T o = R[k][j - 1], p = R[k][j];
				T q = Q[k][j - 1], r = Q[k][j];
				R[k][j - 1] = c * o + s * p;
				R[k][j] = -s * o + c * p;
				Q[k][j - 1] = c * q + s * r;
				Q[k][j] = -s * q + c * r;
			}
		}
	}
	Q = Transpose(Q);
}
```

##### QR Decompose - Modified Gram-Schmidt Orthogonalization

> To improve the speed, the number of iterations M in the modified algorithm is equal to 1

```c++
// math/func/Algorithm.inl

template <typename T>
inline void QRDecompose_ModifiedGramSchmidtOrthogonalization(const Mat<Type::Dynamic, Type::Dynamic, T>& A,
	Mat<Type::Dynamic, Type::Dynamic, T>& Q, Mat<Type::Dynamic, Type::Dynamic, T>& R)
{
	const size_t M = A.col_len(), N = A.row_len();
		
	Q = Mat<Type::Dynamic, Type::Dynamic, T>(T(0), M, M);
	R = Mat<Type::Dynamic, Type::Dynamic, T>(T(0), M, N);
	for (size_t i = 0; i < N; ++i)
	{
		// Number of iterations M = 1
		Vec<Type::Dynamic, T> y = A[i];
		for (size_t j = 0; j < i; ++j)
		{
			R[i][j] = Dot(Q[j], y);
			y -= R[i][j] * Q[j];
		}
		R[i][i] = Norm(y);   // moudle y: ||y||2
		Q[i] = y / R[i][i];
	}
}
```

##### QR Solve

$$
Ax=b \Rightarrow QRx=b \Rightarrow Q\space is\space orthogonal\space matrix \\
\Rightarrow Rx=Q^{-1}b \Rightarrow Rx=Q^Tb
$$

```C++
// math/func/Algorithm.inl

template <typename T>
inline Vec<Type::Dynamic, T> SolveQR(const Mat<Type::Dynamic, Type::Dynamic, T>& Q,
	const Mat<Type::Dynamic, Type::Dynamic, T>& R, const Vec<Type::Dynamic, T>& b)
{
	const size_t N = Q.col_len();

	if (!IsSquareMat(Q) || !IsSquareMat(R))
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix Q or R are not square matrix");

	if (Q.col_len() != R.col_len() || Q.col_len() != b.length())
		throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrixs and vector size not match");

	Vec<Type::Dynamic, T> c = Transpose(Q) * b;

	Vec<Type::Dynamic, T> x(N);
	x[N - 1] = c[N - 1] / R[N - 1][N - 1];
	for (int k = N - 2; k >= 0; --k)
	{
		x[k] = c[k];
		for (size_t i = N - 1; i > k; --i)
			x[k] -= x[i] * R[i][k];
		x[k] /= R[k][k];
	}

	return x;
}
```

##### Find Eigen

$$
D_k(\lambda)=(a_{kk}-\lambda)D_{k-1}(\lambda)-a_{k,k-1}a_{k-1,k}D_{k-2}(\lambda)
$$

```C++
// math/func/Algorithm.inl

template <typename T>
	inline Vec<Type::Dynamic, T> FindEigenByTridiagonalMat(const Mat<Type::Dynamic, Type::Dynamic, T>& A)
	{
		const size_t N = A.col_len();

		if (!IsTridiagonalMat(A))
			throw std::runtime_error(S("ERROR: [") + _FUN_NAME_ + "] Matrix A is not a tridiagonal matrix");

		Vec<Type::Dynamic, T> b(N);
		Vec<Type::Dynamic, T> a(N - 1), c(N - 1);
		for (size_t i = 0; i < N; ++i)
			b[i] = A[i][i];
		for (size_t i = 0; i < N - 1; ++i)
		{
			a[i] = A[i][i + 1];
			c[i] = A[i + 1][i];
		}

		Vec<Type::Dynamic, T> res(N + 1);
		Vec<Type::Dynamic, T> ores(N + 1);
		Vec<Type::Dynamic, T> oores(N + 1);
		ores[0] = -b[0];
		ores[1] = T(1);
		oores[0] = T(1);
		for (size_t i = 1; i < N; ++i)
		{
			T ac = a[i - 1] * c[i - 1];
			res[0] = -b[i] * ores[0] - ac * oores[0];
			for (size_t j = 1; j <= i; ++j)
			{
				res[j] = -b[i] * ores[j] + ores[j - 1] - ac * oores[j];
			}

			for (size_t j = 0; j < i; ++j)
				oores[j] = ores[j];
			for (size_t j = 0; j <= i; ++j)
				ores[j] = res[j];
			oores[i] = T(1);
			ores[i + 1] = T(1);
		}
		res[N] = T(1);

		Vec<Type::Dynamic, T> v(N + 1);
		for (size_t i = 0; i <= N; ++i)
			v[i] = res[N - i];
		return v;
	}
```

In program find_poly, Amat11 is so big, that need to use **long double** type, or answer will overflow
(MinGW supports long double, but MSVC does not support).

##### Other algorithm

Other algorithms for judging the properties of matrices, such as judging whether the matrix is a square matrix, can be found in the file **/math/func/Algorithm.inl**



### Other

I am also writing a software rasterization renderer, and using this math model, so the code also provides functions for inverting matrices, constructing transformation matrices and perspective matrices, and quaternion types.