#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/*
    RELEASED UNDER BEER-LICENSE!
    Joakim Børlum Petersen \ #roevhat
    AAU
*/

/*
TODO + BUGS + DIV.
==================
(X) Lav output funktioner, afhængige af matrix-størrelse osv

(X) Gem og læs fra fil. Nem format, så det er nemt at lave en matrix.

(X) Måske matlab-format / mathematica format? [n n n; n n n] eller {{n, n, n},{n, n, n}}

(X) Herefter løse alle problemer vi kan blive stillet overfor i LIAL-eksamen
*/

typedef struct {
    int m;
    int n;
    float matrix[100][100];
    
} matrix;

matrix parseInput(char * argument1);

void fillMatrix(matrix * entity);

void printMatrix(matrix * entity);

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

matrix toRowEchelonForm(matrix * entity);

matrix toReducedRowEchelonForm(matrix * entity);

matrix inverseOfMatrix(matrix * entity);

int matrixRank(matrix * entity);

int matrixNullity(matrix * entity);

int timeNow();

int outputRref(matrix * entity, int all, int timer);

int outputInverse(matrix * entity, int all, int timer);

int main(int argc, char *argv[]){
    int timer = 0;
    int all = 0;

    if (argc < 2){
        printf("%s\n", "matriC needs additional arguments!");
    } else {
        if (strstr(argv[1], "t")){
            timer = 1;
        }

        if (strstr(argv[1], "all")){
            all = 1;
        }

        if (strstr(argv[1], "R")){
            matrix input = parseInput(argv[2]);
            outputRref(&input, all, timer);
        } else if (strstr(argv[1], "I")){
            matrix input = parseInput(argv[2]);
            outputInverse(&input, all, timer);
        } else {
            printf("%s\n", "matriC needs a primary function specified as an argument:");
            printf("%s\n", "    -> R (reduced row echelon form)");
            printf("%s\n", "    -> I (inverse)");
        }      
    }
}

matrix parseInput(char * argument1){
    matrix input;

    char * parsed = NULL;
    char delims[] = " ][";

    parsed = strtok(argument1, delims);

    int row = 0;
    int col = 0;

    int maxCol = 0;

    while(parsed != NULL) {
        input.matrix[row][col] = atoi(parsed);

        col++;

        if (strstr(parsed, ";")){
            row++;
            if (col > maxCol){
                maxCol = col;
            }
            col = 0;
        }

        parsed = strtok(NULL, delims);

    }
    //This might need optimization for more defensive programming.. But what the heck!
    //The problem is ";" initiates new row. So having it at the end of the matrix, means we need to
    //do like this
    input.m = row;
    //Else we need to say that input.m = row+1
    input.n = maxCol;

    return input;
}

void fillMatrix(matrix * entity){
    for (int i = 0; i < entity->m; i++){
        for (int j = 0; j < entity->n; j++){
            printf("(%i,", i);
            printf("%i) = ", j);
            scanf("%f", &entity->matrix[i][j]);
            printf("\n");
        }
    }
}

void printMatrix(matrix * entity){
    for(int i = 0; i < entity->m; i++){
        printf("| ");
        for(int j = 0; j < entity->n; j++){
            if (entity->matrix[i][j] < 0){
                printf(" %f  ", entity->matrix[i][j]);
            } else {
                printf("  %f  ", entity->matrix[i][j]);
            }
        }
        printf("|\n");
    }
}

float dotProduct(int row, int col, matrix * entity1, matrix * entity2){
    float result = 0;
    for (int i = 0; i < entity1->n; i++){
        result += (entity1->matrix[row][i] * entity2->matrix[i][col]);
    }
    return result;
}

matrix concatMatrices(matrix * entity1, matrix * entity2){
    matrix result;
    result.m = entity1->m;
    result.n = entity1->n + entity2->n;

    for (int i = 0; i < result.m; i++){
        for (int j = 0; j < result.n; j++){
            if (j < entity1->n){
                result.matrix[i][j] = entity1->matrix[i][j];
            } else {
                result.matrix[i][j] = entity2->matrix[(result.m-1)-i][(result.n-1)-j];
            }
        }
    }

    return result;
}

matrix addMatrix(matrix * entity1, matrix * entity2){
    matrix result;
    result.m = entity1->m;
    result.n = entity1->n;

    for (int i = 0; i < result.m; i++){
        for (int j = 0; j < result.n; j++){
            result.matrix[i][j] = entity1->matrix[i][j] + entity2->matrix[i][j];
        }
    }

    return result;
}

matrix scaleMatrix(matrix * entity, float scalar){
    matrix result;
    result.m = entity->m;
    result.n = entity->n;

    for (int i = 0; i < result.m; i++){
        for (int j = 0; j < result.n; j++){
            result.matrix[i][j] = scalar * entity->matrix[i][j];
        }
    }

    return result;
}

matrix transposeMatrix(matrix * entity){
    matrix transpose;
    transpose.m = entity->n;
    transpose.n = entity->m;

    for (int i = 0; i < transpose.m; i++){
        for (int j = 0; j < transpose.n; j++){
            transpose.matrix[i][j] = entity->matrix[j][i];
        }
    }

    return transpose;
}

matrix multiplyMatrices(matrix * entity1, matrix * entity2){
    matrix product;
    product.m = entity1->m;
    product.n = entity2->n;

    for (int i = 0; i < product.m; i++){
        for (int j = 0; j < product.n; j++)
        {
            product.matrix[i][j] = dotProduct(i, j, entity1, entity2);
        }
    }
    return product;
}

matrix identityMatrix(int m, int n){
    matrix identity;
    identity.m = m;
    identity.n = n;

    for (int i = 0; i < identity.m; i++){
        for (int j = 0; j < identity.n; j++){
            if (i == j){
                identity.matrix[i][j] = 1;
            } else {
                identity.matrix[i][j] = 0;
            }
        }
    }

    return identity;
}

matrix scaleMatrixRow(matrix * entity, int row, float factor){
    matrix product, scale;

    product.m = entity->m;
    product.n = entity->n;

    scale.m = entity->m;
    scale.n = entity->m;

    //Generate elementary matrix
    for (int i = 0; i < scale.m; i++){
        for (int j = 0; j < scale.n; j++)
        {
            if (i == (row - 1) && j == (row - 1)){
                scale.matrix[i][j] = factor;
            } else if (i == j){
                scale.matrix[i][j] = 1;
            } else {
                scale.matrix[i][j] = 0;
            }
        }
    }
    product = multiplyMatrices(&scale, entity);
    return product;
}

matrix interchangeRows(matrix * entity, int row1, int row2){
    matrix product, interchange;

    product.m = entity->m;
    product.n = entity->n;

    interchange.m = entity->m;
    interchange.n = entity->m;

    //Generate identity matrix
    for (int i = 0; i < interchange.m; i++){
        for (int j = 0; j < interchange.n; j++)
        {

            if (i == j){
                interchange.matrix[i][j] = 1;
            } else {
                interchange.matrix[i][j] = 0;
            }

        }
    }

    interchange.matrix[row1 - 1][row2 - 1] = 1;
    interchange.matrix[row2 - 1][row1 - 1] = 1;
    interchange.matrix[row1 - 1][row1 - 1] = 0;
    interchange.matrix[row2 - 1][row2 - 1] = 0;

    product = multiplyMatrices(&interchange, entity);
    return product;
}

matrix addXTimesRowToRow(matrix * entity, float times, int row1, int row2){
    matrix product, addtorow;

    product.m = entity->m;
    product.n = entity->n;

    addtorow.m = entity->m;
    addtorow.n = entity->m;

    //Generate identity matrix
    for (int i = 0; i < addtorow.m; i++){
        for (int j = 0; j < addtorow.n; j++)
        {

            if (i == j){
                addtorow.matrix[i][j] = 1;
            } else {
                addtorow.matrix[i][j] = 0;
            }

        }
    }

    addtorow.matrix[row2 - 1][row1 - 1] = times;
    product = multiplyMatrices(&addtorow, entity);
    return product;    
}

matrix toRowEchelonForm(matrix * entity){
    matrix reduced = * entity;

    //Hvilken række vi er nået til - skal indkorporeres i et stort loop der wrapper det hele
    for (int n = 0; n < reduced.m; n++){
        //Determine the leftmost nonzero column => Pivot column. Topmost position in this column is pivot position.
        int isNonzero  = 0;
        int colNumber = reduced.n-1;
        int rowNumber = reduced.m-1;
        for (int j = 0; j < reduced.n; j++){
            for (int i = n; i < reduced.m; i++){
                if (reduced.matrix[i][j] != 0){
                    isNonzero = 1;
                    if (j <= colNumber){
                        colNumber = j;
                        rowNumber = i;
                        if (n != rowNumber){
                            reduced = interchangeRows(&reduced, n+1, rowNumber+1);
                        }

                        //IF != 1 make leading entry == 1
                        if (reduced.matrix[n][colNumber] != 1){
                            float factor = 1/reduced.matrix[n][colNumber];
                            reduced = scaleMatrixRow(&reduced, n+1, factor);
                        }

                        //Make all entries below == 0!
                        float pivotValue = reduced.matrix[n][colNumber];
                        for (int k = n+1; k < reduced.m; k++){
                            //Check if 0
                            if (reduced.matrix[k][colNumber] != 0){
                                //Find the appropriate multiple
                                //And add to make the value = 0
                                //x * a + b = 0 => x = -b/a | a != 0
                                float colValue = reduced.matrix[k][colNumber];
                                float multiple = (-colValue)/pivotValue;

                                reduced = addXTimesRowToRow(&reduced, multiple, n+1, k+1);        
                            }
                        }
                    }
                }
            }
        }
    }   

    return reduced;
}

matrix toReducedRowEchelonForm(matrix * entity){
    matrix reduced = * entity;
    //Loop from bottom of matrix and up
    for (int n = reduced.m-1; n >= 0; n--){
        //Loop row
        int colNumber = reduced.n-1;
        for (int i = 0; i < reduced.n; i++){
            //If row != 0:
            if (reduced.matrix[n][i] == 1){
                colNumber = i;

                //Make all above entries = 0
                for (int j = n-1; j >= 0; j--){
                    if (reduced.matrix[j][i] != 0){
                        //Find the appropriate multiple
                        //And add to make the value = 0
                        //x * a + b = 0 => x = -b/a | a != 0
                        float colValue = reduced.matrix[j][i];
                        float multiple = -(colValue);

                        reduced = addXTimesRowToRow(&reduced, multiple, n+1, j+1);
                    }
                }

                //Stop looping column
                i = reduced.n;
            }
        }
    }
    return reduced;
}

matrix inverseOfMatrix(matrix * entity){
    matrix inverse;
    inverse.m = entity->m;
    inverse.n = entity->n;

    matrix identity = identityMatrix(inverse.m, inverse.n);
    matrix AI = concatMatrices(entity, &identity);
    matrix temp = toRowEchelonForm(&AI);
    matrix RB = toReducedRowEchelonForm(&temp);

    for (int i = 0; i < RB.m; i++){
        for (int j = 0; j < RB.n; j++){
            if (j >= inverse.n){
                inverse.matrix[i][j-inverse.n] = RB.matrix[i][j];
            }
        }
    }

    return inverse;
}

int matrixRank(matrix * entity){
    //Is also the number of pivot columns
    int nonzeroRows = 0;

    int nonZero = 0;

    for (int i = 0; i < entity->m; i++){
        nonZero = 0;
        for (int j = 0; j < entity->n; j++){
            if (entity->matrix[i][j] != 0){
                nonZero = 1;
            }
        }

        if (nonZero == 1){
            nonzeroRows++;
        }
    }

    return nonzeroRows;
}

int matrixNullity(matrix * entity){
    //Is also the number of non-pivot columns
    return entity->n - matrixRank(entity);
}

int timeNow(){
    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    int time1 = (tv1.tv_sec) * 1000 * 1000 + (tv1.tv_usec);

    return time1;
}

int outputRref(matrix * entity, int all, int timer){
    if (all){
        printf("{INPUT(%ix%i)}\n", entity->m, entity->n);
        printf("\n");
        printMatrix(entity);
        printf("\n");
    }

    int t1 = timeNow();

    matrix rowEchelonForm = toRowEchelonForm(entity);

    if (all){
        printf("%s\n", "{ROW ECHELON FORM}");
        printf("\n");
        printMatrix(&rowEchelonForm);
        printf("\n");
    }

    matrix reducedRowEchelonForm = toReducedRowEchelonForm(&rowEchelonForm);

    int t2 = timeNow();
    int tDiff = t2-t1;

    if (all){
        printf("%s\n", "{REDUCED ROW ECHELON FORM}");
        printf("\n");
    }

    printMatrix(&reducedRowEchelonForm);

    if (all){
        printf("\n");
        printf("%s\n", "{RANK AND NULLITY}");
        printf("Rank is %i and nullity is %i\n", matrixRank(&reducedRowEchelonForm), matrixNullity(&reducedRowEchelonForm));
    }

    if (timer){
        printf("\n");
        printf("%s\n", "{TIMER}");
        printf("It took %i microseconds!\n", tDiff);
        printf("\n");
    }

    return 1;
}

int outputInverse(matrix * entity, int all, int timer){
    if (all){
        printf("{INPUT(%ix%i)}\n", entity->m, entity->n);
        printf("\n");
        printMatrix(entity);
        printf("\n");
    }

    int t1 = timeNow();

    matrix inverse = inverseOfMatrix(entity);

    int t2 = timeNow();
    int tDiff = t2-t1;

    if (all){
        printf("%s\n", "{INVERSE OF MATRIX}");
        printf("\n");
    }

    printMatrix(&inverse);

    if (timer){
        printf("\n");
        printf("%s\n", "{TIMER}");
        printf("It took %i microseconds!\n", tDiff);
        printf("\n");
    }

    return 1;

}