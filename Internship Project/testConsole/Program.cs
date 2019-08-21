using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.LinearAlgebra.Complex32;
using MathNet.Numerics.LinearAlgebra.Double;
using Extreme.Mathematics.Curves;
using Extreme.Mathematics;


namespace Production
{
    class LinearCurveFitting
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            // This QuickStart sample illustrates linear least squares
            // curve fitting using polynomials and linear combinations
            // of arbitrary functions.

            // Linear least squares fits are calculated using the
            // LinearCurveFitter class:
            LinearCurveFitter fitter = new LinearCurveFitter();

            // We use data from the National Institute for Standards 
            // and Technology's Statistical Reference Datasets library 
            // at http://www.itl.nist.gov/div898/strd/.

            // Note that, due to round-off error, the results here will not be exactly
            // the same as the NIST results, which were calculated using 500 digits
            // of precision!

            // We use the 'Pontius' dataset, which contains measurement data
            // from the calibration of load cells. The independent variable is the load.
            // The dependent variable is the deflection.
            var deflectionData = Vector.Create(.11019, .21956,
                .32949, .43899, .54803, .65694, .76562, .87487, .98292,
                1.09146, 1.20001, 1.30822, 1.41599, 1.52399, 1.63194, 1.73947,
                1.84646, 1.95392, 2.06128, 2.16844, .11052, .22018, .32939,
                .43886, .54798, .65739, .76596, .87474, .98300, 1.09150, 1.20004,
                1.30818, 1.41613, 1.52408, 1.63159, 1.73965,
                1.84696, 1.95445, 2.06177, 2.16829);
            var loadData = Vector.Create(
                150.0, 300, 450, 600, 750, 900,
                1050, 1200, 1350, 1500, 1650, 1800,
                1950, 2100, 2250, 2400, 2550, 2700,
                2850, 3000, 150, 300, 450, 600,
                750, 900, 1050, 1200, 1350, 1500,
                1650, 1800, 1950, 2100, 2250, 2400,
                2550, 2700, 2850, 3000);

            // You must supply the curve whose parameters will be
            // fit to the data. The curve must inherit from LinearCombination.
            //
            // Here, we use a quadratic polynomial:
            fitter.Curve = new Polynomial(2);

            // The X values go into the XValues property:
            fitter.XValues = loadData;
            // ...and Y values go into the YValues property:
            fitter.YValues = deflectionData;

            // The Fit method performs the actual calculation:
            fitter.Fit();

            // A var containing the parameters of the best fit
            // can be obtained through the
            // BestFitParameters property.
            var solution = fitter.BestFitParameters;
            // The standard deviations associated with each parameter
            // are available through the GetStandardDeviations method.
            var s = fitter.GetStandardDeviations();

            Console.WriteLine("Calibration of load cells");
            Console.WriteLine("    deflection = c1 + c2*load + c3*load^2 ");
            Console.WriteLine("Solution:");
            Console.WriteLine("c1: {0,20:E10} {1,20:E10}", solution[0], s[0]);
            Console.WriteLine("c2: {0,20:E10} {1,20:E10}", solution[1], s[1]);
            Console.WriteLine("c3: {0,20:E10} {1,20:E10}", solution[2], s[2]);

            Console.WriteLine("Residual sum of squares: {0}", fitter.Residuals.Norm());

            // Now let's redo the same operation, but with observations weighted
            // by 1/Y^2. To do this, we set the WeightFunction property.
            // The WeightFunctions class defines a set of ready-to-use weight functions.
            fitter.WeightFunction = WeightFunctions.OneOverYSquared;
            // Refit the curve:
            fitter.Fit();
            solution = fitter.BestFitParameters;
            s = fitter.GetStandardDeviations();

            // The solution is slightly different:
            Console.WriteLine("Solution (weighted observations):");
            Console.WriteLine("c1: {0,20:E10} {1,20:E10}", solution[0], s[0]);
            Console.WriteLine("c2: {0,20:E10} {1,20:E10}", solution[1], s[1]);
            Console.WriteLine("c3: {0,20:E10} {1,20:E10}", solution[2], s[2]);
            Console.WriteLine();

            //
            // Fitting combinations of arbitrary functions
            //

            // The following example estimates the two parameters, c1 and c2
            // in the theoretical model for conductance:
            //     k(T) = 1 / (c1 / T + c2 * T*T)

            var temperature = Vector.Create(12.2900, 13.7500, 14.8200,
                16.1200, 18.0400, 18.6700, 20.5200, 22.6800, 25.1500,
                27.7200, 30.2400, 33.2100, 36.4800, 39.8600, 50.4000);
            var conductance = Vector.Create(25.3500, 27.8800, 29.9300,
                30.4200, 31.0000, 31.9600, 32.4700, 30.3300, 31.1400,
                27.4600, 23.2900, 20.7200, 17.2400, 14.7100, 9.5000);

            // First, we transform the dependent variable:
            var y = Vector.Reciprocal(conductance);

            // y is a linear combination of basis functions 1/T and T*T.
            // Create a function basis object:
            Func<double, double>[] basisFunctions = new Func<double, double>[] { new Func<double, double>(f1), new Func<double, double>(f2) };
            GeneralFunctionBasis basis = new GeneralFunctionBasis(basisFunctions);

            // Create a LinearCombination curve using this function basis:
            LinearCombination curve = new LinearCombination(basis);

            // Set the curve fitter properties:
            fitter.Curve = curve;
            fitter.XValues = temperature;
            fitter.YValues = y;
            // Reset the weights
            fitter.WeightFunction = null;
            fitter.WeightVector = null;

            // Now compute the solution:
            fitter.Fit();
            solution = fitter.BestFitParameters;
            s = fitter.GetStandardDeviations();

            // Print the results
            Console.WriteLine("Conductance of copper: k(T) = 1 / (c1/T + c2*T^2)");
            Console.WriteLine("Solution:");
            Console.WriteLine("c1: {0,20:E10} {1,20:E10}", solution[0], s[0]);
            Console.WriteLine("c2: {0,20:E10} {1,20:E10}", solution[1], s[1]);

            Console.WriteLine("Residual sum of squares: {0}", fitter.Residuals.Norm());

            Console.Write("Press Enter key to exit...");
            Console.ReadLine();
        }

        // First basis function for the conductance sample.
        static double f1(double x)
        {
            return 1 / x;
        }

        // Second basis function for the conductance sample.
        static double f2(double x)
        {
            return x * x;
        }
    }
}