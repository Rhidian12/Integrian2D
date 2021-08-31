#pragma once

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
			: data{ other.data }
		{}
		Matrix<Rows, Columns, Type>(Matrix<Rows, Columns, Type>&& other) noexcept
			: data{ std::move(other.data) }
		{}
		Matrix<Rows, Columns, Type>& operator=(const Matrix<Rows, Columns, Type>& other) noexcept
		{
			data = other.data;

			return *this;
		}
		Matrix<Rows, Columns, Type>& operator=(Matrix<Rows, Columns, Type>&& other) noexcept
		{
			data = std::move(other.data);

			return *this;
		}
#pragma endregion

#pragma region Data
		Type data[Rows][Columns];
#pragma endregion
	};

#pragma region Arithmetic Operators
	template<int Rows, int Columns, typename Type>
	Matrix<Rows, Columns, Type> operator+(const Matrix<Rows, Columns, Type>& lhs, const Matrix<Rows, Columns, Type>& rhs) noexcept
	{
		Matrix<Rows, Columns, Type> matrix{};

		for (int r{}; r < Rows; ++r)
			for (int c{}; c < Columns; ++c)
				matrix[r][c] = lhs[r][c] + rhs[r][c];

		return matrix;
	}

	template<int Rows, int Columns, typename Type>
	Matrix<Rows, Columns, Type> operator-(const Matrix<Rows, Columns, Type>& lhs, const Matrix<Rows, Columns, Type>& rhs) noexcept
	{
		Matrix<Rows, Columns, Type> matrix{};

		for (int r{}; r < Rows; ++r)
			for (int c{}; c < Columns; ++c)
				matrix[r][c] = lhs[r][c] - rhs[r][c];

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
					matrix[row][col] += lhs[row][i] * rhs[i][col];

		return matrix;
	}

	template<int Rows, int Columns, typename Type>
	Matrix<Rows, Columns, Type> operator/(const Matrix<Rows, Columns, Type>& lhs, const Matrix<Rows, Columns, Type>& rhs) noexcept
	{
		// this is pain
		// == First get the Matrix of Minors ==
		Matrix<Rows, Columns, Type> matrixOfMinors{};
		Type determinant{};
		int counter{};
		for (int r{}; r < Rows; ++r)
		{
			for (int c{}; c < Columns; ++c)
			{
				Type value{ rhs[r][c] };

				Matrix<2, 2, Type> minorMatrix{};

				for (int minorRow{}; Rows - minorRow == 2; ++minorRow)
				{
					if (r == minorRow)
						continue;

					for (int minorCol{}; Columns - minorCol == 2; ++minorCol)
					{
						if (c == minorCol)
							continue;


					}
				}
			}
		}
	}
#pragma endregion

	// == Useful Non-Member Functions ==
	template<int Rows, int Columns, typename Type>
	static Matrix<Rows, Columns, Type> GetIdentity() noexcept
	{
		static_assert(Rows == Columns, "Identity Matrices must be square!");

		Matrix<Rows, Columns, Type> matrix{};

		for (int i{}; i < Rows; ++i)
			matrix[i][i] = static_cast<Type>(1.f);

		return matrix;
	}
}