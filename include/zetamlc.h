/* *************************************************************************************** */
/* 						THE ZETA MATHS LIBRARY LICENSE INFORMATION						   */
/* *************************************************************************************** */
/* Copyright (c) 2022 Jack Bennett														   */
/* --------------------------------------------------------------------------------------- */
/* THE  SOFTWARE IS  PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY KIND, EXPRESS  OR IMPLIED, */
/* INCLUDING  BUT  NOT  LIMITED  TO  THE  WARRANTIES  OF  MERCHANTABILITY,  FITNESS FOR  A */
/* PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN  NO EVENT SHALL  THE  AUTHORS  OR COPYRIGHT */
/* HOLDERS  BE  LIABLE  FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF */
/* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR */
/* THE USE OR OTHER DEALINGS IN THE SOFTWARE.											   */
/* *************************************************************************************** */

#pragma once
#ifndef __ZETAML_H__
#define __ZETAML_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ZML_32_BIT
#	ifndef ZML_USING_FLOATS
#		warning "You are using a 32-bit build of zetaml but are not using floats. Using doubles might cause problems, you should rebuild zetaml with -DZML_USE_FLOATS=ON!"
#	endif
#endif

#define PI (__floating) 3.141592653589793238463

// ---
// The following macros are flags that can be used in zmlSetLibFlag().

#define ZML_USE_DEGREES 0x01		// use degrees instead of radians.
#define ZML_USE_LEFT_COORDS 0x02	// use left-handed coordinates instead of right-handed coordinates

// ==============================================================================
// *****					 CONFIGURATION FUNCTIONS						*****
// ==============================================================================

/**
 * @brief Sets a library flag 'flag' to the given boolean val.
 * 
 * @param flag the flag to modify
 * @param val the value to set the flag to
 */
extern void zmlSetLibFlag(unsigned int flag, unsigned char val);

// ==============================================================================
// *****				   PUBLIC VECTOR FUNCTIONALITY						*****
// ==============================================================================

/**
 * @brief A vector construct of any given size. 
 * 
 */
typedef struct {
	unsigned int size;
	__floating *elements;
} zmlVector;

/**
 * @brief An undefined vector; no dimension.
 * 
 */
extern const zmlVector ZML_NULL_VECTOR;

/**
 * @brief Allocate memory for a vector struct, and return the empty vector. Elements are NOT initialised!
 * 
 * @param size the size of the vector.
 */
extern zmlVector zmlAllocVector(unsigned int size);
/**
 * @brief Free a vector's memory.
 * 
 * @param vec the vector to free.
 */
extern void zmlFreeVector(zmlVector *vec);

/**
 * @brief Construct a vector with a default value.
 * 
 * @param size the size of the vector.
 * @param val the value to initialise the vector with.
 */
extern zmlVector zmlConstructVectorDefault(unsigned int size, __floating val);

/**
 * @brief Construct a vector with a default value.
 * 
 * @param size the size of the vector.
 * @param ... the values to initialise the vector with. Must be floating-point!
 */
extern zmlVector zmlConstructVector(unsigned int size, ...);

/**
 * @brief copy a vector's values
 * 
 * @param val the pointer to the vector to be copied
 */
extern zmlVector zmlCopyVector(zmlVector *val);

/**
 * @brief produces a vector that is the cross product of the two given vectors; this represents the vector perpendicular to the plane that v1 and v2 create. 
 * 
 * @param v1 the first vector to operate on.
 * @param v2 the second vector to operate on.
 */
extern zmlVector zmlCross(zmlVector v1, zmlVector v2);

/**
 * @brief produces a vector that is the dot (scalar) product of the two given vectors v1 and v2. 
 * 
 * @param v1 the first vector to operate on.
 * @param v2 the second vector to operate on.
 */
extern __floating zmlDot(zmlVector v1, zmlVector v2);

/**
 * @brief returns the magnitude (length) of the given vector vec. 
 * 
 * @param vec the specified vector.
 */
extern __floating zmlMagnitude(zmlVector vec);

/**
 * @brief returns the given vector in its normalised state (magnitude of 1).
 * 
 * @param vec the specified vector.
 */
extern zmlVector zmlNormalised(zmlVector vec);

/**
 * @brief normalises (modifies) the specified vector.
 * 
 * @param vec the specified vector.
 */
extern void zmlNormalise(zmlVector *vec);

// -------------------------------------------
// Boolean/arithmetic operation functions.
// These are self-explanatory, and so are not documented.
// 	NAMING CONVENTION: (explained in docs)
//	 zmlAddVecs_r adds two vectors and *returns* the result, hence the '_r'.
// 	 zmlAddVecs adds v2 to v1, modifying v1. There is no '_r' - it does not return anything, but rather modifies v1.
//	 zmlAddVecScalar_r adds a vector and a scalar and returns the result. etc.
// -------------------------------------------

extern unsigned char zmlVecEquals(zmlVector v1, zmlVector v2);
extern unsigned char zmlVecGT(zmlVector v1, zmlVector v2);
extern unsigned char zmlVecGTE(zmlVector v1, zmlVector v2);
extern unsigned char zmlVecLT(zmlVector v1, zmlVector v2);
extern unsigned char zmlVecLTE(zmlVector v1, zmlVector v2);

extern zmlVector 	zmlAddVecs_r(zmlVector v1, zmlVector v2);
extern void			zmlAddVecs(zmlVector *v1, zmlVector v2);
extern zmlVector 	zmlSubtractVecs_r(zmlVector v1, zmlVector v2);
extern void 		zmlSubtractVecs(zmlVector *v1, zmlVector v2);
extern zmlVector 	zmlMultiplyVecs_r(zmlVector v1, zmlVector v2);
extern void 		zmlMultiplyVecs(zmlVector *v1, zmlVector v2);
extern zmlVector 	zmlDivideVecs_r(zmlVector v1, zmlVector v2);
extern void 		zmlDivideVecs(zmlVector *v1, zmlVector v2);

extern zmlVector 	zmlAddVecScalar_r(zmlVector v1, __floating v2);
extern void		 	zmlAddVecScalar(zmlVector *v1, __floating v2);
extern zmlVector 	zmlSubtractVecScalar_r(zmlVector v1, __floating v2);
extern void		 	zmlSubtractVecScalar(zmlVector *v1, __floating v2);
extern zmlVector 	zmlMultiplyVecScalar_r(zmlVector v1, __floating v2);
extern void		 	zmlMultiplyVecScalar(zmlVector *v1, __floating v2);
extern zmlVector 	zmlDivideVecScalar_r(zmlVector v1, __floating v2);
extern void		 	zmlDivideVecScalar(zmlVector *v1, __floating v2);

// ==============================================================================
// *****				   PUBLIC MATRIX FUNCTIONALITY						*****
// ==============================================================================

/**
 * @brief Matrix structure
 * 
 */
typedef struct {
	unsigned int rows;
	unsigned int cols;
	__floating **elements; // 2d array of elements
} zmlMatrix;

/**
 * @brief An undefined matrix; no elements.
 * 
 */
extern const zmlMatrix ZML_NULL_MATRIX;

/**
 * @brief Allocate memory for a matrix
 * @param rows the number of rows
 * @param cols the number of cols
 */
extern zmlMatrix zmlAllocMatrix(unsigned int rows, unsigned int cols);
/**
 * @brief Free a matrix's memory.
 * 
 * @param mat the matrix to free.
 */
extern void zmlFreeMatrix(zmlMatrix *mat);

/**
 * @brief Allocate and return an identity matrix with width and height size.
 * 
 * @param size the size (rows and columns) of the matrix.
 */
extern zmlMatrix zmlIdentityMatrix(unsigned int rows, unsigned int cols);

/**
 * @brief copy a matrix's values
 * 
 * @param val the pointer to the matrix to be copied
 */
extern zmlMatrix zmlCopyMatrix(zmlMatrix *val);

/**
 * @brief get a specified row from the given matrix as a vector.
 * 
 * @param val the matrix to be observed
 * @param index the index of the row to retrieve.
 */
extern zmlVector zmlGetMatrixRow(zmlMatrix val, unsigned int index);
/**
 * @brief set a row in the given matrix to a specified vector.
 * 
 * @param mat the matrix to be observed
 * @param index the index of the row to set.
 * @param vec the vector to set the row to. Must be the same length as the amount of columns in mat.
 */
extern void zmlSetMatrixRow(zmlMatrix *mat, unsigned int index, zmlVector vec);

/**
 * @brief get a specified column from the given matrix as a vector.
 * 
 * @param val the matrix to be observed
 * @param index the index of the column to retrieve.
 */
extern zmlVector zmlGetMatrixCol(zmlMatrix val, unsigned int index);
/**
 * @brief set a column in the given matrix to a specified vector.
 * 
 * @param mat the matrix to be observed
 * @param index the index of the column to set.
 * @param vec the vector to set the column to. Must be the same length as the amount of rows in mat.
 */
extern void zmlSetMatrixCol(zmlMatrix *mat, unsigned int index, zmlVector vec);

/**
 * @brief allocate and return the given matrix in its transposed state - that is to say, the rows and columns of the matrix are swapped. 
 * 
 * @param mat the matrix to transpose
 */
extern zmlMatrix zmlTransposed(zmlMatrix mat);
/**
 * @brief transpose the given matrix by modifying it directly. 
 * 
 * @param mat the matrix to transpose
 */
extern void zmlTranspose(zmlMatrix *mat);

// ==============================================================================
// *****					PUBLIC UTILITY FUNCTIONS						*****
// ==============================================================================

/**
 * @brief Takes a value rad, expressed in radians, and converts it to degrees. 
 * 
 * @param rad the value, in radians, to convert to degrees.
 */
extern __floating zmlToDegrees(__floating rad);

/**
 * @brief Takes a value deg, expressed in degrees, and converts it to radians. 
 * 
 * @param deg the value, in degrees, to convert to radians.
 */
extern __floating zmlToRadians(__floating deg);

/**
 * @brief Takes a vector value, val, and converts it to a formatted string.
 * 
 * @param val the vector to format and express as a string.
 * @param str the string to return the value into.
 */
extern void zmlToStringV(zmlVector val, char *str);

/**
 * @brief Takes a matrix value, val, and converts it to a formatted string.
 * 
 * @param val the matrix to format and express as a string.
 * @param str the string to return the value into.
 */
extern void zmlToStringM(zmlMatrix val, char *str);

/**
 * @brief Prints the output of zmlToStringV(val) to stdout (with new line!).
 * 
 * @param val the vector to format and print.
 */
extern void zmlPrintV(zmlVector val);

/**
 * @brief Prints the output of zmlToStringM(val) to stdout (with new line!).
 * 
 * @param val the matrix to format and print.
 */
extern void zmlPrintM(zmlMatrix val);

/**
 * @brief Performs a linear interpolation operation on value val.
 * 
 * @param val the value to interpolate
 * @param start1 the min point of the input range
 * @param stop1 the max point of the input range
 * @param start2 the min point of the output range
 * @param stop2 the max point of the output range
 */
extern __floating zmlLerp(__floating val, __floating start1, __floating stop1, __floating start2, __floating stop2);

#ifdef __cplusplus
}
#endif

#endif