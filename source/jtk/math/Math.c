/*
 * Copyright 2018-2019 OneCube
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Monday, July 23, 2018

#include <jtk/core/Double.h>
#include <jtk/core/Float.h>
#include <jtk/core/Integer.h>
#include <jtk/core/Long.h>
#include <jtk/core/VariableArguments.h>
#include <jtk/math/Math.h>

#include <math.h>

/*******************************************************************************
 * Math                                                                        *
 *******************************************************************************/

/* Distance */

int32_t jtk_Math_findDistance_i(int32_t* array1, int32_t* array2, int32_t size,
    jtk_DistanceMetric_t metric, ...) {
    jtk_Assert_assertObject(array1, "The specified array (1) is null.");
    jtk_Assert_assertObject(array1, "The specified array (2) is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t result = 0;
    switch (metric) {
        JTK_DISTANCE_METRIC_EUCLIDEAN: {
            result = jtk_DistanceMetric_findEuclideanDistance_i(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_MANHATTAN: {
            result = jtk_DistanceMetric_findManhattanDistance_i(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_CHEBYSHEV: {
            result = jtk_DistanceMetric_findChebyshevDistance_i(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_MINKOWSKI: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            int32_t order = jtk_VariableArguments_argument(arguments, int32_t);
            result = jtk_DistanceMetric_findMinkowskiDistance_i(array1, array2, size, order);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_WEIGHTED_MINKOWSKI: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            int32_t order = jtk_VariableArguments_argument(arguments, int32_t);
            double* weights = jtk_VariableArguments_argument(arguments, double*);
            result = jtk_DistanceMetric_findWeightedMinkowskiDistance_i(array1,
                array2, size, order, weights);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_WEIGHTED_EUCLIDEAN: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            double* weights = jtk_VariableArguments_argument(arguments, double*);
            result = jtk_DistanceMetric_findWeightedEuclideanDistance_i(array1,
                array2, size, weights);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_MAHALANOBIS: {
            break;
        }

        JTK_DISTANCE_METRIC_HAMMING: {
            break;
        }

        JTK_DISTANCE_METRIC_CANBERRA: {
            break;
        }

        JTK_DISTANCE_METRIC_BRAYCURTIS: {
            break;
        }

        JTK_DISTANCE_METRIC_EARTH_MOVERS: {
            break;
        }

        JTK_DISTANCE_METRIC_HAVERSINE: {
            break;
        }

        JTK_DISTANCE_METRIC_JACCARD: {
            break;
        }

        JTK_DISTANCE_METRIC_MATCHING: {
            break;
        }

        JTK_DISTANCE_METRIC_DICE: {
            break;
        }

        JTK_DISTANCE_METRIC_KULSINSKI: {
            break;
        }

        JTK_DISTANCE_METRIC_ROGERS_TANIMOTO: {
            break;
        }

        JTK_DISTANCE_METRIC_RUSSELL_RAO: {
            break;
        }

        JTK_DISTANCE_METRIC_SOKAL_MICHENER: {
            break;
        }

        JTK_DISTANCE_METRIC_SOKAL_SNEATH: {
            break;
        }

        default: {
            // Error!
        }
    }
    return result;
}


int64_t jtk_Math_findDistance_l(int64_t* array1, int64_t* array2, int32_t size,
    jtk_DistanceMetric_t metric, ...) {
    jtk_Assert_assertObject(array1, "The specified array (1) is null.");
    jtk_Assert_assertObject(array1, "The specified array (2) is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int64_t result = 0;
    switch (metric) {
        JTK_DISTANCE_METRIC_EUCLIDEAN: {
            result = jtk_DistanceMetric_findEuclideanmetric_l(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_MANHATTAN: {
            result = jtk_DistanceMetric_findManhattanDistance_l(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_CHEBYSHEV: {
            result = jtk_DistanceMetric_findChebyshevDistance_l(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_MINKOWSKI: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            int32_t order = jtk_VariableArguments_argument(arguments, int32_t);
            result = jtk_DistanceMetric_findMinkowskiDistance_l(array1, array2, size, order);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_WEIGHTED_MINKOWSKI: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            int32_t order = jtk_VariableArguments_argument(arguments, int32_t);
            double* weights = jtk_VariableArguments_argument(arguments, double*);
            result = jtk_DistanceMetric_findWeightedMinkowskiDistance_l(array1,
                array2, size, order, weights);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_WEIGHTED_EUCLIDEAN: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            double* weights = jtk_VariableArguments_argument(arguments, double*);
            result = jtk_DistanceMetric_findWeightedEuclideanDistance_l(array1,
                array2, size, weights);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_MAHALANOBIS: {
            break;
        }

        JTK_DISTANCE_METRIC_HAMMING: {
            break;
        }

        JTK_DISTANCE_METRIC_CANBERRA: {
            break;
        }

        JTK_DISTANCE_METRIC_BRAYCURTIS: {
            break;
        }

        JTK_DISTANCE_METRIC_EARTH_MOVERS: {
            break;
        }

        JTK_DISTANCE_METRIC_HAVERSINE: {
            break;
        }

        JTK_DISTANCE_METRIC_JACCARD: {
            break;
        }

        JTK_DISTANCE_METRIC_MATCHING: {
            break;
        }

        JTK_DISTANCE_METRIC_DICE: {
            break;
        }

        JTK_DISTANCE_METRIC_KULSINSKI: {
            break;
        }

        JTK_DISTANCE_METRIC_ROGERS_TANIMOTO: {
            break;
        }

        JTK_DISTANCE_METRIC_RUSSELL_RAO: {
            break;
        }

        JTK_DISTANCE_METRIC_SOKAL_MICHENER: {
            break;
        }

        JTK_DISTANCE_METRIC_SOKAL_SNEATH: {
            break;
        }

        default: {
            // Error!
        }
    }
    return result;
}

float jtk_Math_findDistance_f(float* array1, float* array2, int32_t size,
    jtk_DistanceMetric_t metric, ...) {
    jtk_Assert_assertObject(array1, "The specified array (1) is null.");
    jtk_Assert_assertObject(array1, "The specified array (2) is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    float result = JTK_FLOAT_NAN;
    switch (metric) {
        JTK_DISTANCE_METRIC_EUCLIDEAN: {
            result = jtk_DistanceMetric_findEuclideanDistance_f(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_MANHATTAN: {
            result = jtk_DistanceMetric_findManhattanDistance_f(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_CHEBYSHEV: {
            result = jtk_DistanceMetric_findChebyshevDistance_l(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_MINKOWSKI: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            int32_t order = jtk_VariableArguments_argument(arguments, int32_t);
            result = jtk_DistanceMetric_findMinkowskiDistance_f(array1, array2, size, order);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_WEIGHTED_MINKOWSKI: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            int32_t order = jtk_VariableArguments_argument(arguments, int32_t);
            double* weights = jtk_VariableArguments_argument(arguments, double*);
            result = jtk_DistanceMetric_findWeightedMinkowskiDistance_f(array1,
                array2, size, order, weights);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_WEIGHTED_EUCLIDEAN: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            double* weights = jtk_VariableArguments_argument(arguments, double*);
            result = jtk_DistanceMetric_findWeightedEuclideanDistance_f(array1,
                array2, size, weights);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_MAHALANOBIS: {
            break;
        }

        JTK_DISTANCE_METRIC_HAMMING: {
            break;
        }

        JTK_DISTANCE_METRIC_CANBERRA: {
            break;
        }

        JTK_DISTANCE_METRIC_BRAYCURTIS: {
            break;
        }

        JTK_DISTANCE_METRIC_EARTH_MOVERS: {
            break;
        }

        JTK_DISTANCE_METRIC_HAVERSINE: {
            break;
        }

        JTK_DISTANCE_METRIC_JACCARD: {
            break;
        }

        JTK_DISTANCE_METRIC_MATCHING: {
            break;
        }

        JTK_DISTANCE_METRIC_DICE: {
            break;
        }

        JTK_DISTANCE_METRIC_KULSINSKI: {
            break;
        }

        JTK_DISTANCE_METRIC_ROGERS_TANIMOTO: {
            break;
        }

        JTK_DISTANCE_METRIC_RUSSELL_RAO: {
            break;
        }

        JTK_DISTANCE_METRIC_SOKAL_MICHENER: {
            break;
        }

        JTK_DISTANCE_METRIC_SOKAL_SNEATH: {
            break;
        }

        default: {
            // Error!
        }
    }
    return result;
}

double jtk_Math_findDistance_d(double* array1, double* array2, int32_t size,
    jtk_DistanceMetric_t metric, ...) {
    jtk_Assert_assertObject(array1, "The specified array (1) is null.");
    jtk_Assert_assertObject(array1, "The specified array (2) is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    double result = JTK_DOUBLE_NAN;
    switch (metric) {
        JTK_DISTANCE_METRIC_EUCLIDEAN: {
            result = jtk_DistanceMetric_findEuclideanDistance_d(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_MANHATTAN: {
            result = jtk_DistanceMetric_findManhattanDistance_d(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_CHEBYSHEV: {
            result = jtk_DistanceMetric_findChebyshevDistance_d(array1, array2, size);
            break;
        }

        JTK_DISTANCE_METRIC_MINKOWSKI: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            int32_t order = jtk_VariableArguments_argument(arguments, int32_t);
            result = jtk_DistanceMetric_findMinkowskiDistance_d(array1, array2, size, order);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_WEIGHTED_MINKOWSKI: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            int32_t order = jtk_VariableArguments_argument(arguments, int32_t);
            double* weights = jtk_VariableArguments_argument(arguments, double*);
            result = jtk_DistanceMetric_findWeightedMinkowskiDistance_d(array1,
                array2, size, order, weights);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_WEIGHTED_EUCLIDEAN: {
            jtk_VariableArguments_t arguments;
            jtk_VariableArguments_start(arguments, metric);

            double* weights = jtk_VariableArguments_argument(arguments, double*);
            result = jtk_DistanceMetric_findWeightedEuclideanDistance_d(array1,
                array2, size, weights);

            jtk_VariableArguments_end(arguments);

            break;
        }

        JTK_DISTANCE_METRIC_MAHALANOBIS: {
            break;
        }

        JTK_DISTANCE_METRIC_HAMMING: {
            break;
        }

        JTK_DISTANCE_METRIC_CANBERRA: {
            break;
        }

        JTK_DISTANCE_METRIC_BRAYCURTIS: {
            break;
        }

        JTK_DISTANCE_METRIC_EARTH_MOVERS: {
            break;
        }

        JTK_DISTANCE_METRIC_HAVERSINE: {
            break;
        }

        JTK_DISTANCE_METRIC_JACCARD: {
            break;
        }

        JTK_DISTANCE_METRIC_MATCHING: {
            break;
        }

        JTK_DISTANCE_METRIC_DICE: {
            break;
        }

        JTK_DISTANCE_METRIC_KULSINSKI: {
            break;
        }

        JTK_DISTANCE_METRIC_ROGERS_TANIMOTO: {
            break;
        }

        JTK_DISTANCE_METRIC_RUSSELL_RAO: {
            break;
        }

        JTK_DISTANCE_METRIC_SOKAL_MICHENER: {
            break;
        }

        JTK_DISTANCE_METRIC_SOKAL_SNEATH: {
            break;
        }

        default: {
            // Error!
        }
    }
    return result;
}

/* Palindrome */
/*
bool jtk_Math_isPalindrome_i(int32_t number) {
	return jtk_Integer_reverse(number) == number;
}

bool jtk_Math_isPalindrome_l(int64_t number) {
	return jtk_Long_reverse(number) == number;
}

/* Power of Two */

int32_t jtk_Math_findPowerOfTwo(int32_t n) {
	int32_t r = 1;
	while (r < n) {
		r <<= 1;
	}
	return r;
}

/* Prime */

bool jtk_Math_isPrime_i(int32_t number) {
	bool result = false;
	if (number > 0) {
		result = true;

		int32_t limit = number / 2;
		int32_t i;
		for (i = 2; i <= limit; i++) {
			if ((number % i) == 0) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool jtk_Math_isPrime_l(int64_t number) {
	bool result = false;
	if (number > 0) {
		result = true;

		int64_t limit = number / 2;
		int64_t i;
		for (i = 2; i <= limit; i++) {
			if ((number % i) == 0) {
				printf("Divisible by %d\n", i);
				result = false;
				break;
			}
		}
	}
	return result;
}
/*
bool jtk_Math_isPrimeFast_i(int32_t number) {
    bool result = true;
    if (((number > 2) && ((number % 2) == 0)) || (number == 1)){
        result = false;
    }
    else {
        int32_t limit = (int32_t)jtk_Math_squareRoot(number);
        int32_t i;
        for (i = 3; i <= limit; i += 2) {
            if((number % i) == 0) {
                result = false;
                break;
            }
        }
    }
    return result;
}

bool jtk_Math_isPrimeFast_l(int64_t number) {
    bool result = true;
    if (((number > 2) && ((number % 2) == 0)) || (number == 1)){
        result = false;
    }
    else {
        int64_t limit = (int64_t)jtk_Math_squareRoot(number);
        int64_t i;
        for (i = 3; i <= limit; i += 2) {
            if ((number % i) == 0) {
                result = false;
                break;
            }
        }
    }
    return result;
}
*/

// Modulus

float jtk_Math_modulo_f(float a, float b) {
    return 0; // fmodf(a, b);
}

double jtk_Math_modulo_d(float a, float b) {
    return 0; // fmod(a, b);
}

// Retain Prime

void jtk_Math_retainPrime_i(int32_t* numbers, int32_t size, int32_t x, int32_t y,
    int32_t** result, int32_t* resultSize) {
    jtk_Assert_assertObject(numbers, "The specified numbers is null.");
    jtk_Assert_assertTrue(size > 0, "The specified array size is invalid.");

    int32_t limit = jtk_Math_squareRoot(y) + 1;

    bool* flags = jtk_Memory_allocate(bool, size);
    jtk_Arrays_fill_b(flags, true);

    int32_t i;
    for (i = 2; i <= limit; i++) {
        int32_t j;
        for (j = 0; j < size; j++) {
            if ((i != numbers[j]) && ((i % numbers[j]) == 0)) {
                flags[j] = false;
            }
        }
    }

    int32_t resultSize0 = 0;
    for (i = 0; i < size; i++) {
        resultSize0 += flags[i]? 1 : 0;
    }

    *resultSize = resultSize0;
    *result = jtk_Memory_allocate(int32_t, resultSize0);

    // jtk_Array_select_i(numbers, size, flags, *result, resultSize0);
}

// Square Root

double jtk_Math_squareRoot(double n) {
    return sqrt(n);
}
