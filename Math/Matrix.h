#pragma once

#include "../Utils/Utils.h"
#include <utility>

namespace Integrian2D
{
	// A Matrix (for example a 3x3 Matrix) looks like this:
	// [ A B C ]
	// [ D E F ]
	// [ G H I ]
	template<int Rows, int Columns, typename Type>
	struct Matrix
	{
#pragma region Constructors
		Matrix<Rows, Columns, Type>()
		{
			for (int r{}; r < Rows; ++r)
				for (int c{}; c < Columns; ++c)
					data[r][c] = static_cast<Type>(0.f);
		}
#pragma endregion

#pragma region Rule Of 5
		Matrix<Rows, Columns, Type>(const Matrix<Rows, Columns, Type>& other) noexcept
		{
			for (int r{}; r < Rows; ++r)
				for (int c{}; c < Columns; ++c)
					data[r][c] = other.data[r][c];
		}
		Matrix<Rows, Columns, Type>(Matrix<Rows, Columns, Type>&& other) noexcept
		{
			for (int r{}; r < Rows; ++r)
				for (int c{}; c < Columns; ++c)
					data[r][c] = std::move(other.data[r][c]);
		}
		Matrix<Rows, Columns, Type>& operator=(const Matrix<Rows, Columns, Type>& other) noexcept
		{
			for (int r{}; r < Rows; ++r)
				for (int c{}; c < Columns; ++c)
					data[r][c] = other.data[r][c];

			return *this;
		}
		Matrix<Rows, Columns, Type>& operator=(Matrix<Rows, Columns, Type>&& other) noexcept
		{
			for (int r{}; r < Rows; ++r)
				for (int c{}; c < Columns; ++c)
					data[r][c] = std::move(other.data[r][c]);

			return *this;
		}
#pragma endregion

#pragma region Data
		Type data[Rows][Columns];
#pragma endregion

#pragma region Member Operators
		const Type& operator()(const int r, const int c) const noexcept
		{
			Utils::Assert((r < Rows&& c < Columns), "Matrix::operator() > Indices are out of bounds!");
			return data[r][c];
		}

		Type& operator()(const int r, const int c) noexcept
		{
			Utils::Assert((r < Rows&& c < Columns), "Matrix::operator() > Indices are out of bounds!");
			return data[r][c];
		}
#pragma endregion
	};

#pragma region Arithmetic Operators
	template<int Rows, int Columns, typename Type>
	Matrix<Rows, Columns, Type> operator+(const Matrix<Rows, Columns, Type>& lhs, const Matrix<Rows, Columns, Type>& rhs) noexcept
	{
		Matrix<Rows, Columns, Type> matrix{};

		for (int r{}; r < Rows; ++r)
			for (int c{}; c < Columns; ++c)
				matrix.data[r][c] = lhs.data[r][c] + rhs.data[r][c];

		return matrix;
	}

	template<int Rows, int Columns, typename Type>
	Matrix<Rows, Columns, Type> operator-(const Matrix<Rows, Columns, Type>& lhs, const Matrix<Rows, Columns, Type>& rhs) noexcept
	{
		Matrix<Rows, Columns, Type> matrix{};

		for (int r{}; r < Rows; ++r)
			for (int c{}; c < Columns; ++c)
				matrix.data[r][c] = lhs.data[r][c] - rhs.data[r][c];

		return matrix;
	}

	template<int RowsM1, int ColumnsM1, int RowsM2, int ColumnsM2, typename Type>
	Matrix<RowsM1, ColumnsM1, Type> operator*(const Matrix<RowsM1, ColumnsM1, Type>& lhs, const Matrix<RowsM2, ColumnsM2, Type>& rhs) noexcept
	{
		static_assert(ColumnsM1 == RowsM2, "Matrix::operator*() > Matrix<Rows1, Columns1> * Matrix<Rows2, Columns2>. Columns1 and Rows2 must be equal!");

		Matrix<RowsM1, ColumnsM2, Type> matrix{};

		constexpr int maxMatrixLength{ ColumnsM1 };

		for (int row{}; row < RowsM1; ++row)
			for (int col{}; col < ColumnsM2; ++col)
				for (int i{}; i < maxMatrixLength; ++i)
					matrix.data[row][col] += lhs.data[row][i] * rhs.data[i][col];

		return matrix;
	}

	template<int Rows, int Columns, typename Type>
	Matrix<Rows, Columns, Type> operator*(const Matrix<Rows, Columns, Type>& lhs, const Type& rhs) noexcept
	{
		Matrix<Rows, Columns, Type> matrix{};

		for (int row{}; row < Rows; ++row)
			for (int col{}; col < Columns; ++col)
				matrix.data[row][col] += lhs.data[row][col] * rhs;

		return matrix;
	}

	template<int RowsM1, int ColumnsM1, int RowsM2, int ColumnsM2, typename Type>
	Matrix<RowsM1, ColumnsM1, Type> operator/(const Matrix<RowsM1, ColumnsM1, Type>& lhs, const Matrix<RowsM2, ColumnsM2, Type>& rhs) noexcept
	{
		static_assert(RowsM2 == ColumnsM2, "Matrix::operator/() > The divider must be square!");
		static_assert(ColumnsM1 == RowsM2, "Matrix::operator/() > Matrix<Rows1, Columns1> * Matrix<Rows2, Columns2>. Columns1 and Rows2 must be equal!");

		// this is pain
		// == First get the Matrix of Minors ==
		Matrix<RowsM1, ColumnsM2, Type> matrixOfMinors{};
		for (int r{}; r < RowsM1; ++r)
		{
			for (int c{}; c < ColumnsM2; ++c)
			{
				int rowCounter{}, colCounter{};
				Matrix<RowsM1 - 1, ColumnsM2 - 1, Type> matrix{};
				for (int row{}; row < RowsM1; ++row)
				{
					if (r == row)
						continue;

					for (int col{}; col < ColumnsM2; ++col)
					{
						if (c == col)
							continue;

						matrix.data[rowCounter][colCounter++] = rhs.data[row][col];
					}

					++rowCounter;
				}

				matrixOfMinors.data[r][c] = GetDeterminant(matrix, GetAmountOfRowsInMatrix(matrix));
			}
		}

		// == Checkboard ==
		int sign{ 1 };
		for (int r{}; r < RowsM1; ++r)
		{
			for (int c{}; c < ColumnsM2; ++c)
			{
				matrixOfMinors.data[r][c] *= sign;
				sign = -sign;
			}
		}

		// == Transpose Matrix ==
		Matrix<ColumnsM2, RowsM1, Type> transposedMatrix{ TransposeMatrix(matrixOfMinors) };

		// == Multiply By 1 / Determinant ==
		Matrix<ColumnsM2, RowsM1, Type> inverseRHSMatrix{ transposedMatrix * static_cast<Type>(1.f / GetDeterminant(rhs, GetAmountOfRowsInMatrix(rhs))) };

		return lhs * inverseRHSMatrix;
	}
#pragma endregion

	// == Useful Non-Member Functions ==
	template<int Rows, int Columns, typename Type>
	constexpr int GetAmountOfRowsInMatrix(const Matrix<Rows, Columns, Type>&) noexcept
	{
		return Rows;
	}

	template<int Rows, int Columns, typename Type>
	constexpr int GetAmountOfColumnsInMatrix(const Matrix<Rows, Columns, Type>&) noexcept
	{
		return Columns;
	}

	template<int Rows, int Columns, typename Type>
	static Matrix<Rows, Columns, Type> GetIdentityMatrix() noexcept
	{
		static_assert(Rows == Columns, "Identity Matrices must be square!");

		Matrix<Rows, Columns, Type> matrix{};

		for (int i{}; i < Rows; ++i)
			matrix.data[i][i] = static_cast<Type>(1.f);

		return matrix;
	}

	template<int Rows, int Columns, typename Type>
	Matrix<Rows, Columns, Type> MakeSubMatrix(const Matrix<Rows, Columns, Type>& m, const int rowToIgnore, const int colToIgnore, const int length) noexcept
	{
		static_assert(Rows == Columns, "MakeSubMatrix() > Matrix must be square!");

		int rowCounter{}, columnCounter{};
		Matrix<Rows, Columns, Type> matrix{};

		for (int r{}; r < length; ++r)
		{
			for (int c{}; c < length; ++c)
			{
				if (r != rowToIgnore && c != colToIgnore)
				{
					matrix.data[rowCounter][columnCounter++] = m.data[r][c];

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

	template<int Rows, int Columns, typename Type>
	Type GetDeterminant(const Matrix<Rows, Columns, Type>& m, const int length) noexcept
	{
		static_assert(Rows == Columns, "GetDeterminant() > Matrix must be square!");

		if (length == 1)
			return m.data[0][0];
		else if (length == 2)
			return (m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]); // ad - bc
		else
		{
			Type determinant{};
			int sign{ 1 };

			for (int i{}; i < length; ++i)
			{
				Matrix<Rows, Columns, Type> matrix{ MakeSubMatrix<Rows, Columns, Type>(m, 0, i, length) };
				determinant += sign * m.data[0][i] * GetDeterminant<Rows, Columns, Type>(matrix, length - 1);
				sign = -sign;
			}

			return determinant;
		}
	}

	template<int Rows, int Columns, typename Type>
	Matrix<Columns, Rows, Type> TransposeMatrix(const Matrix<Rows, Columns, Type>& m) noexcept
	{
		Matrix<Columns, Rows, Type> matrix{};

		for (int r{}; r < Rows; ++r)
			for (int c{}; c < Columns; ++c)
				matrix.data[c][r] = m.data[r][c];

		return matrix;
	}
}