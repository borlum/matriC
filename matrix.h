/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * @roevhat wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * /Joakim Børlum Petersen @roevhat
 * ----------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ERROR_LIMIT 0.000010
#define MATRIX_LIM 100

typedef struct {
    int m;
    int n;
    float matrix[MATRIX_LIM][MATRIX_LIM];
    
} matrix;

int parseInput(matrix * ouput, char * input, int isFile);

void fillMatrix(matrix * entity);

void printMatrix(matrix * entity);

int fprintMatrix(FILE * file, matrix * entity);

float dotProduct(int row, int col, matrix * entity1, matrix * entity2);

int addMatrix(matrix * result, matrix * entity1, matrix * entity2);

int scaleMatrix(matrix * result, matrix * entity, float scalar);

int concatMatrices(matrix * result, matrix * entity1, matrix * entity2);

int transposeMatrix(matrix * transpose, matrix * entity);

int multiplyMatrices(matrix * product, matrix * entity1, matrix * entity2);

int identityMatrix(matrix * identity, int m, int n);

int scaleMatrixRow(matrix * entity, int row, float factor);

int interchangeRows(matrix * entity, int row1, int row2);

int addXTimesRowToRow(matrix * entity, float times, int row1, int row2);

int toRowEchelonForm(matrix * result, matrix * entity, int verbose);

int toReducedRowEchelonForm(matrix * result, matrix * entity, int verbose);

int inverseOfMatrix(matrix * result, matrix * entity);

int matrixRank(matrix * entity);

int matrixNullity(matrix * entity);

float twoXtwoDeterminat(matrix * entity);

int deleteIJ(matrix * result, matrix * entity, int row, int col);

float cofactorExpansion(matrix * entity, int row);

float absolute(float n);