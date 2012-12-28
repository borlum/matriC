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

typedef struct {
    int m;
    int n;
    float matrix[100][100];
    
} matrix;

matrix parseInput(char * argument1, int isFile);

matrix parseFile(char * argument1);

void fillMatrix(matrix * entity);

void printMatrix(matrix * entity);

void fprintMatrix(FILE * file, matrix * entity);

float dotProduct(int row, int col, matrix * entity1, matrix * entity2);

matrix addMatrix(matrix * entity1, matrix * entity2);

matrix scaleMatrix(matrix * entity, float scalar);

matrix concatMatrices(matrix * entity1, matrix * entity2);

matrix transposeMatrix(matrix * entity);

matrix multiplyMatrices(matrix * entity1, matrix * entity2);

matrix identityMatrix(int m, int n);

matrix scaleMatrixRow(matrix * entity, int row, float factor);

matrix interchangeRows(matrix * entity, int row1, int row2);

matrix addXTimesRowToRow(matrix * entity, float times, int row1, int row2);

matrix toRowEchelonForm(matrix * entity, int verbose);

matrix toReducedRowEchelonForm(matrix * entity, int verbose);

matrix inverseOfMatrix(matrix * entity);

int matrixRank(matrix * entity);

int matrixNullity(matrix * entity);

float twoXtwoDeterminat(matrix * entity);

matrix deleteIJ(matrix * entity, int row, int col);

float cofactorExpansion(matrix * entity, int row);

float absolute(float n);