/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * @roevhat wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * /Joakim Børlum Petersen @roevhat
 * ----------------------------------------------------------------------------
 */

/*
TODO + BUGS + DIV.
==================
    (X) Logge til JSON! :D
    ( ) Klar seperation imellem logik og output.. ma3.c er rodet!!
    ( ) Alt egenvektor og egenværdi-halløjet
    ( ) Måske finde en cool måde at lave sets på?
    ( ) Ny struktur forslået af Jens: Istedet for at returnere matrix,
        så skal returværdien være til at se hvordan det gik.
        Dvs. at funktionerne i stedet skal tage en pointer til en matrix,
        hvor resultatet så bliver gemt, i stedet for at returnere en matrix.
        Tænk fil-operationer.
    ( ) Defensivt: Tjek på om det er en 0x0 matrix. Tjek på dimensionerne + andet gøgl.
    ( ) Defensivt: Flere tjeks i ParseInput, og generelt bedre CLI - mere fejlhåndtering.
*/

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
/* ---Magic library--- */
#include "matrix.h"

int timeNowUsec();

int timeNowSec();

unsigned long timestampNow();

int outputRref(matrix * entity, int all, int timer);

int outputInverse(matrix * entity, int all, int timer);

int outputDet(matrix * entity, int all, int timer);

int logToJSON(matrix * input, matrix * output, int runtime, char * tag);

int main(int argc, char *argv[]){
    int timer = 0;
    int all   = 0;
    int file  = 0;
    matrix input;

    if (argc < 2){
        printf("%s\n", "matriC needs additional arguments!");
        printf("%s\n", "Specify a primary function as an argument:");
        printf("%s\n", "    -> R (reduced row echelon form)");
        printf("%s\n", "    -> I (inverse)");
        printf("%s\n", "    -> D (determinant)");
        printf("%s\n", "Additional arguments:");
        printf("%s\n", "    -> t (add timer)");
        printf("%s\n", "    -> all (verbose output)");
        printf("%s\n", "    -> f (specify a file instead of inline matrix)");
    } else {

        if (strstr(argv[1], "t")){
            timer = 1;
        }

        if (strstr(argv[1], "all")){
            all = 1;
        }

        if (strstr(argv[1], "f")){
            file = 1;
        }

        if (strstr(argv[1], "R")){

            if (file){

                if (parseInput(&input, argv[2], 1)){
                    outputRref(&input, all, timer);
                } else {
                    return 0;
                }

            } else {

                if (parseInput(&input, argv[2], 0)){
                    outputRref(&input, all, timer);
                } else {
                    return 0;
                }

            }

        } else if (strstr(argv[1], "I")){

            if (file){

                if (parseInput(&input, argv[2], 1)){
                    outputInverse(&input, all, timer);
                } else {
                    return 0;
                }

            } else {

                if (parseInput(&input, argv[2], 0)){
                    outputInverse(&input, all, timer);
                } else {
                    return 0;
                }

            }

        } else if (strstr(argv[1], "D")){

            if (file){

                if (parseInput(&input, argv[2], 1)){
                    outputDet(&input, all, timer);
                } else {
                    return 0;
                }

            } else {

                if (parseInput(&input, argv[2], 0)){
                    outputDet(&input, all, timer);
                } else {
                    return 0;
                }

            }

        } else {
            printf("%s\n", "matriC needs a primary function specified as an argument:");
            printf("%s\n", "    -> R (reduced row echelon form)");
            printf("%s\n", "    -> I (inverse)");
            printf("%s\n", "    -> D (determinant)");
        }      
    }
}

int timeNowUsec(){
    //Struct for holding elapsed time!
    struct timeval now;

    //Tager pointers til en timeval struct og en timezone struct
    //Og sætter i timeval tiden i sekunder og microsekunder siden EPOCH!
    //Lad den sidste parameter være NULL, den skal vi ikke bruge til noget.
    gettimeofday(&now, NULL);

    //Returner fra vores timeval struct, "now", tiden kun i microsekunder, siden EPOCH!
    return (now.tv_sec) * 1000000 + (now.tv_usec);
}

unsigned long timestampNow(){

    char timestamp[32];

    //Epoch time datatype, holds seconds since Epoch
    time_t currentTime;

    //A calendar struct, containing tm_sec, tm_min, tm_hour... (all int)
    struct tm * ts;
    
    //Grab current Epoch-time (time returns time since Epoch)
    currentTime = time(NULL);

    //Turn ts into localtime, relative to users timezone, using currentTime
    ts = localtime(&currentTime);

    //Remember its calendar time => Add +1 to month, +1900 to year
    //sprintf functions as printf, except the result is not displayed, but saved in the first parameter!
    sprintf(timestamp,"%02i%02i%i%02i%02i%02i", ts->tm_mday, ts->tm_mon+1, ts->tm_year+1900, ts->tm_hour, ts->tm_min, ts->tm_sec);


    //We first make a char array with the timestamp, then turn it into an unsigned long.
    //This may seem stupid, since we need to turn it back into a char array for later use,
    //but I really don't like the idea of having to set a global variable, for just holding a timestamp!

    //String-to-unsigned-long: takes the string, a pointer to store invalid chars, and the base.
    return strtoul(timestamp, NULL, 10);
}

int outputRref(matrix * entity, int all, int timer){

    if (all){
        printf("{INPUT(%ix%i)}\n", entity->m, entity->n);
        printf("\n");
        printMatrix(entity);
        printf("\n");
    }

    int t1 = timeNowUsec();

    matrix rowEchelonForm;

    if (all){
        toRowEchelonForm(&rowEchelonForm, entity, 1);
    } else {
        toRowEchelonForm(&rowEchelonForm, entity, 0);
    }

    if (all){
        printf("%s\n", "{ROW ECHELON FORM}");
        printf("\n");
        printMatrix(&rowEchelonForm);
        printf("\n");
    }

    matrix reducedRowEchelonForm;

    if (all){
        toReducedRowEchelonForm(&reducedRowEchelonForm, &rowEchelonForm, 1);
    } else {
        toReducedRowEchelonForm(&reducedRowEchelonForm, &rowEchelonForm, 0);
    }
    
    int t2    = timeNowUsec();
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

    //logToJSON -> input, output, runtime, tag
    logToJSON(entity, &reducedRowEchelonForm, tDiff, "rref");

    return 1;
}

int outputInverse(matrix * entity, int all, int timer){

    if (all){
        printf("{INPUT(%ix%i)}\n", entity->m, entity->n);
        printf("\n");
        printMatrix(entity);
        printf("\n");
    }

    int t1 = timeNowUsec();

    matrix inverse;
    inverseOfMatrix(&inverse, entity);

    int t2    = timeNowUsec();
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

    //logToJSON -> input, output, runtime, tag
    logToJSON(entity, &inverse, tDiff, "inverse");

    return 1;

}

int outputDet(matrix * entity, int all, int timer){
    if (all){
        printf("{INPUT(%ix%i)}\n", entity->m, entity->n);
        printf("\n");
        printMatrix(entity);
        printf("\n");
    }

    int t1 = timeNowUsec();

    float det = cofactorExpansion(entity, 1);

    int t2    = timeNowUsec();
    int tDiff = t2-t1;

    if (all){
        printf("%s\n", "{DETERMINANT OF MATRIX}");
        printf("\n");
    }

    printf("det(INPUT) = %f\n", det);

    if (timer){
        printf("\n");
        printf("%s\n", "{TIMER}");
        printf("It took %i microseconds!\n", tDiff);
        printf("\n");
    }

    return 1;
}

int logToJSON(matrix * input, matrix * output, int runtime, char * tag){

    unsigned long timestamp = timestampNow();
    char filepath[32];
    
    sprintf(filepath,"logs/%lu.json", timestamp);

    FILE * file = fopen(filepath,"a");

    if (file == NULL) {
        printf("File does exist!");
        return 0;
    }

    fprintf(file, "{");

    //Log input-matrix

    fprintf(file, "\"input\": [");

    for (int i = 0; i < input->m; i++){

        fprintf(file, "[");

        for (int j = 0; j < input->n; j++){
            if (j == input->n -1){
                fprintf(file, "%f", input->matrix[i][j]);   
            } else {
                fprintf(file, "%f, ", input->matrix[i][j]);
            }
        }

        if (i == input->m -1){
            fprintf(file, "]");
        } else {
            fprintf(file, "], ");
        }

    }

    fprintf(file, "], ");

    //Log output-matrix

    fprintf(file, "\"output\": [");
    
    for (int i = 0; i < output->m; i++){

        fprintf(file, "[");

        for (int j = 0; j < output->n; j++){
            if (j == output->n -1){
                fprintf(file, "%f", output->matrix[i][j]);   
            } else {
                fprintf(file, "%f, ", output->matrix[i][j]);
            }
        }

        if (i == output->m -1){
            fprintf(file, "]");
        } else {
            fprintf(file, "], ");
        }

    }

    fprintf(file, "], ");

    //Log runtime, tag, timestamp
    fprintf(file, "\"tag\": \"%s\", ", tag);
    fprintf(file, "\"timestamp\": %lu, ", timestamp);
    fprintf(file, "\"runtime\": %i", runtime);

    fprintf(file, "}");

    fclose(file);

    return 1;

}