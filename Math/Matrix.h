#pragma once

#include "../Integrian2D_API.h"
#include "AreEqual.h"
#include "Point.h"
#include "Vector.h"

namespace Integrian2D::Math
{
	/* A Matrix(for example a 3x3 Matrix) looks like this internally:
	   [ A B C ]
	   [ D E F ]
	   [ G H I ] */

	template<int R, int C, typename T>
	struct Matrix
	{
	#pragma region Constructors

		Matrix();

	#pragma endregion

	#pragma region Data

		T Data[R][C];

	#pragma endregion

	#pragma region Member Operators

		Vector<C, T>& operator[](const int r)
		{
			__ASSERT(r < R && "Matrix::operator[] > Index is out of bounds!");
			return *(reinterpret_cast<Vector<C, T>*>(Data[r]));
		}

		const Vector<C, T>& operator[](const int r) const
		{
			__ASSERT(r < R && "Matrix::operator[] > Index is out of bounds!");
			return *(reinterpret_cast<Vector<C, T>*>(Data[r]));
		}

		T& operator()(const int r, const int c)
		{
			__ASSERT((r < R&& c < C) && "Matrix::operator() > Indices are out of bounds!");
			return Data[r][c];
		}

		const T& operator()(const int r, const int c) const
		{
			__ASSERT((r < R&& c < C) && "Matrix::operator() > Indices are out of bounds!");
			return Data[r][c];
		}

	#pragma endregion
	};

	template<int R, int C, typename T>
	Matrix<R, C, T>::Matrix()
	{
		for (int r{}; r < R; ++r)
			for (int c{}; c < C; ++c)
				Data[r][c] = static_cast<T>(0.f);
	}

	template<int R, int C, typename T>
	Matrix<R, C, T> operator+(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs)
	{
		Matrix<R, C, T> matrix{};

		for (int r{}; r < R; ++r)
			for (int c{}; c < C; ++c)
				matrix.Data[r][c] = lhs.Data[r][c] + rhs.Data[r][c];

		return matrix;
	}

	template<int R, int C, typename T>
	Matrix<R, C, T> operator-(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs)
	{
		Matrix<R, C, T> matrix{};

		for (int r{}; r < R; ++r)
			for (int c{}; c < C; ++c)
				matrix.Data[r][c] = lhs.Data[r][c] - rhs.Data[r][c];

		return matrix;
	}

	template<int R1, int C1, int R2, int C2, typename T>
	Matrix<R1, C1, T> operator*(const Matrix<R1, C1, T>& lhs, const Matrix<R2, C2, T>& rhs)
	{
		static_assert(C1 == R2, "Matrix::operator*() > Matrix<R1, C1> * Matrix<R2, C2>. C1 and R2 must be equal!");

		Matrix<R1, C2, T> matrix{};

		constexpr int maxMatrixLength{ C1 };

		for (int row{}; row < R1; ++row)
			for (int col{}; col < C2; ++col)
				for (int i{}; i < maxMatrixLength; ++i)
					matrix.Data[row][col] += lhs.Data[row][i] * rhs.Data[i][col];

		return matrix;
	}

	template<int R, int C, typename T>
	Matrix<R, C, T> operator*(const Matrix<R, C, T>& lhs, const T& rhs)
	{
		Matrix<R, C, T> matrix{};

		for (int row{}; row < R; ++row)
			for (int col{}; col < C; ++col)
				matrix.Data[row][col] += lhs.Data[row][col] * rhs;

		return matrix;
	}

	template<int R, int C, typename T>
	Vector<C, T> operator*(const Matrix<R, C, T>& lhs, const Vector<C, T>& rhs)
	{
		Vector<C, T> vector{};

		for (int row{}; row < R; ++row)
			for (int col{}; col < C; ++col)
				vector[row] += lhs.Data[row][col] * rhs.Data[row];

		return vector;
	}

	template<int R1, int C1, int R2, int C2, typename T>
	Matrix<R1, C1, T> operator/(const Matrix<R1, C1, T>& lhs, const Matrix<R2, C2, T>& rhs)
	{
		static_assert(R2 == C2, "Matrix::operator/() > The divider must be square!");
		static_assert(C1 == R2, "Matrix::operator/() > Matrix<R1, C1> * Matrix<R2, C2>. C1 and R2 must be equal!");

		// this is pain
		// it has cost me blood, sweat and tears to make this
		// if you think it is wrong, congratulations

		return lhs * GetInverseMatrix(rhs);
	}

	template<int R, int C, typename T>
	Matrix<R, C, T> operator/(const Matrix<R, C, T>& lhs, const T& rhs)
	{
		Matrix<R, C, T> matrix{};

		for (int row{}; row < R; ++row)
			for (int col{}; col < C; ++col)
				matrix.Data[row][col] += lhs.Data[row][col] / rhs;

		return matrix;
	}

	template<int R, int C, typename T>
	Matrix<R, C, T> operator/(const Matrix<R, C, T>& lhs, const Vector<C, T>& rhs)
	{
		Matrix<C, 1, T> vecMatrix{};

		for (int i{}; i < C; ++i)
			vecMatrix.Data[i][0] = rhs.Data[i];

		return lhs * GetInverseMatrix(vecMatrix);
	}

	// == Useful Non-Member Functions ==
	template<int R, int C, typename T>
	constexpr int GetAmountOfRowsInMatrix(const Matrix<R, C, T>&)
	{
		return R;
	}

	template<int R, int C, typename T>
	constexpr int GetAmountOfColumnsInMatrix(const Matrix<R, C, T>&)
	{
		return C;
	}

	template<int R, int C, typename T>
	Matrix<R, C, T> GetIdentityMatrix()
	{
		static_assert(R == C, "Identity Matrices must be square!");

		Matrix<R, C, T> matrix{};

		for (int i{}; i < R; ++i)
			matrix.Data[i][i] = static_cast<T>(1.f);

		return matrix;
	}

	template<int R, int C, typename T>
	Matrix<R, C, T> GetMatrixCofactor(const Matrix<R, C, T>& m, const int rowToIgnore, const int colToIgnore, const int length)
	{
		static_assert(R == C, "GetMatrixCofactor() > Matrix must be square!");

		int rowCounter{}, columnCounter{};
		Matrix<R, C, T> matrix{};

		for (int r{}; r < length; ++r)
		{
			for (int c{}; c < length; ++c)
			{
				if (r != rowToIgnore && c != colToIgnore)
				{
					matrix.Data[rowCounter][columnCounter++] = m.Data[r][c];

					if (columnCounter == length - 1)
					{
						columnCounter = 0;
						++rowCounter;
					}
				}
			}
		}

		return matrix;
	}

	template<int R, int C, typename T>
	T GetDeterminantOfMatrix(const Matrix<R, C, T>& m, const int length)
	{
		static_assert(R == C, "GetDeterminant() > Matrix must be square!");

		if (length == 1)
		{
			return m.Data[0][0];
		}
		else if (length == 2)
		{
			return (m.Data[0][0] * m.Data[1][1]) - (m.Data[0][1] * m.Data[1][0]); // ad - bc
		}
		else
		{
			T determinant{};
			int sign{ 1 };

			for (int i{}; i < length; ++i)
			{
				Matrix<R, C, T> matrix{ GetMatrixCofactor<R, C, T>(m, 0, i, length) };
				determinant += sign * m.Data[0][i] * GetDeterminantOfMatrix<R, C, T>(matrix, length - 1);
				sign = -sign;
			}

			return determinant;
		}
	}

	template<int R, int C, typename T>
	Matrix<C, R, T> TransposeMatrix(const Matrix<R, C, T>& m)
	{
		Matrix<C, R, T> matrix{};

		for (int r{}; r < R; ++r)
			for (int c{}; c < C; ++c)
				matrix.Data[c][r] = m.Data[r][c];

		return matrix;
	}

	template<int R, int C, typename T>
	Matrix<C, R, T> GetAdjointMatrix(const Matrix<C, R, T>& m)
	{
		static_assert(R == C, "Matrix::GetAdjointMatrix() > Matrix must be square!");

		Matrix<C, R, T> matrix{};

		if constexpr (R == 1)
		{
			matrix[0][0] = 1;
		}
		else
		{
			int sign{ 1 };

			for (int r{}; r < R; ++r)
			{
				for (int c{}; c < C; ++c)
				{
					Matrix<C, R, T> cofactorMatrix{ GetMatrixCofactor(m, r, c, R) };

					sign = ((r + c) % 2 == 0) ? 1 : -1;

					matrix.Data[c][r] = sign * GetDeterminantOfMatrix(cofactorMatrix, R - 1);
				}
			}
		}

		return matrix;
	}

	template<int R, int C, typename T>
	Matrix<R, C, T> GetInverseMatrix(const Matrix<R, C, T>& m)
	{
		static_assert(R == C, "Matrix::GetInverseMatrix() > Matrix must be square!");

		const T determinant{ GetDeterminantOfMatrix(m, R) };

		// if determinant is 0, return identity matrix
		if (AreEqual(determinant, static_cast<T>(0.f)))
		{
			return GetIdentityMatrix<R, C, T>();
		}

		Matrix<R, C, T> adjointMatrix{ GetAdjointMatrix(m) };

		Matrix<R, C, T> inverseMatrix{};

		for (int r{}; r < R; ++r)
			for (int c{}; c < C; ++c)
				inverseMatrix.Data[r][c] = adjointMatrix.Data[r][c] / determinant;

		return inverseMatrix;
	}
}