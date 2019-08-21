using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace ViliPetek.LinearAlgebra
{
    /// <summary>
    /// Class implementing LU decomposition
    /// </summary>
    public class LUDecomposition
    {
        public double[,] L { private set; get; }
        public double[,] U { private set; get; }

        private int[] permutation;
        private double[] rowBuffer;

        /// <summary>
        /// An implementation of LU decomposition.
        /// </summary>
        /// <param name="matrix">A square decomposable matrix</param>
        public LUDecomposition(double[,] matrix)
        {
            int rows = matrix.Rows();
            int cols = matrix.Cols();

            if (rows != cols)
            {
                throw new ArgumentException("Matrix is not square");
            }

            // generate LU matrices
            L = Matrix.Identity(cols);
            U = (double[,])matrix.Clone();

            // used for quick swapping rows
            rowBuffer = new double[cols];

            permutation = Enumerable.Range(0, rows).ToArray();

            double singular = 0;
            int pivotRow = 0;

            for (int k = 0; k < cols - 1; k++)
            {
                singular = 0;
                // find the pivot row
                for (int i = k; i < rows; i++)
                {
                    if (Math.Abs(U[i, k]) > singular)
                    {
                        singular = Math.Abs(U[i, k]);
                        pivotRow = i;
                    }
                }

                if (singular == 0)
                {
                    new ArgumentException("Matrix is singlar");
                }

                Swap(ref permutation[k], ref permutation[pivotRow]);

                for (int i = 0; i < k; i++)
                {
                    Swap(ref L[k, i], ref L[pivotRow, i]);
                }

                SwapRows(U, k, pivotRow);

                for (int i = k + 1; i < rows; i++)
                {
                    L[i, k] = U[i, k] / U[k, k];
                    for (int j = k; j < cols; j++)
                    {
                        U[i, j] = U[i, j] - L[i, k] * U[k, j];
                    }
                }
            }
        }

        public double[,] Solve(double[,] matrix)
        {
            if (matrix.Rows() != L.Rows())
            {
                throw new ArgumentException("Invalid matrix size");
            }

            double[,] ret = new double[matrix.Rows(), matrix.Cols()];
            double[] vec = new double[matrix.Rows()];

            // solve each column
            for (int col = 0; col < matrix.Cols(); col++)
            {
                for (int j = 0; j < matrix.Rows(); j++)
                {
                    vec[j] = matrix[permutation[j], col];
                }
                var forwardSub = ForwardSub(L, vec);
                var backSub = BackSub(U, forwardSub);

                // copy the backward subsituted values to the result column
                for (int k = 0; k < backSub.Length; k++)
                {
                    ret[k, col] = backSub[k];
                }
            }
            return ret;
        }

        public double[] Solve(double[] vector)
        {
            if (U.Rows() != vector.Length)
            {
                throw new ArgumentException("Argument matrix has wrong number of rows");
            }

            double[] vec = new double[vector.Length];
            for (int i = 0; i < vector.Length; i++)
            {
                vec[i] = vector[permutation[i]];
            }

            double[] z = ForwardSub(L, vec);
            double[] x = BackSub(U, z);

            return x;
        }

        private double[] ForwardSub(double[,] matrix, double[] b)
        {
            int rows = L.Rows();
            double[] ret = new double[rows];

            for (int i = 0; i < rows; i++)
            {
                ret[i] = b[i];
                for (int j = 0; j < i; j++)
                {
                    ret[i] -= matrix[i, j] * ret[j];
                }
                ret[i] = ret[i] / matrix[i, i];
            }
            return ret;
        }

        private double[] BackSub(double[,] matrix, double[] b)
        {
            int rows = L.Rows();
            double[] ret = new double[rows];

            for (int i = rows - 1; i > -1; i--)
            {
                ret[i] = b[i];
                for (int j = rows - 1; j > i; j--)
                {
                    ret[i] -= matrix[i, j] * ret[j];
                }
                ret[i] = ret[i] / matrix[i, i];
            }
            return ret;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void SwapRows(double[,] matrix, int rowA, int rowB)
        {
            int rowSize = 8 * matrix.Cols();
            Buffer.BlockCopy(matrix, rowB * rowSize, rowBuffer, 0, rowSize);
            Buffer.BlockCopy(matrix, rowA * rowSize, matrix, rowB * rowSize, rowSize);
            Buffer.BlockCopy(rowBuffer, 0, matrix, rowA * rowSize, rowSize);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void Swap<T>(ref T a, ref T b)
        {
            T c = a;
            a = b;
            b = c;
        }
    }
}