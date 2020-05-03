#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <string.h>

#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    int h;
    int w;
    int *data;
} Matrix;

void createMatrixFromFile (Matrix **m, char* fileName) {
    (*m) = malloc(sizeof(Matrix));
    (*m)->w = 2;
    (*m)->h = 2;
    (*m)->data = malloc(sizeof(int) * 2);
    for (int i=0; i<2; i++)
        ((int*)((*m)->data))[i] = malloc(sizeof(int) * 2);

    if ((*m) == NULL)
        return;

    FILE *fp;
    fp = fopen(fileName, "r");

    if (fp == NULL)
        return;

    int i = 0, w = 0, h = 0;
    char ch = NULL, buffer[16];

    while (ch != EOF) {
        ch = fgetc(fp);

        if (ch == ' ' || ch == '\n' || ch == EOF) {
            ((int*)(*m)->data[h])[w] = atoi(buffer);

            w++;
            if (ch == '\n') {
                w = 0;
                h++;
            }

            if (w == (*m)->w) {
                (*m)->w = w + 1;
                for (int j=0; j<(*m)->h; j++) {
                    ((int*)((*m)->data))[j] = realloc(((int*)((*m)->data))[j], sizeof(int) * (*m)->w);
                }
            }
            if (h == (*m)->h) {
                (*m)->h = h + 1;
                (*m)->data = realloc((*m)->data, sizeof(int) * (*m)->h);
                ((int*)((*m)->data))[(*m)->h - 1] = malloc(sizeof(int) * (*m)->w);
            }

            memset(buffer, 16, 16);
            i = 0;

        }
        else {
            buffer[i] = ch;
            i++;
        }
    }

    (*m)->w--;
    fclose(fp);
}

void copyMatrix(Matrix *from, Matrix **to, int startH, int startW, int h, int w) {
    if (startH + h > from->h || startW + w > from->w)
        return;

    (*to) = malloc(sizeof(Matrix));
    (*to)->h = h;
    (*to)->w = w;
    (*to)->data = malloc(sizeof(int) * h);

    for (int i=0; i<h; i++) {
        (*to)->data[i] = malloc(sizeof(int) * w);
        for (int j=0; j<w; j++) {
            ((int*)(*to)->data[i])[j] = ((int*)from->data[i+startH])[j+startW];
        }
    }
}

void zeroMatrix (Matrix **matrix, int h, int w) {
    if (w <= 0 || h <= 0)
        return;

    (*matrix) = malloc(sizeof(Matrix));
    (*matrix)->h = h;
    (*matrix)->w = w;
    (*matrix)->data = malloc(sizeof(int) * h);
    for (int i=0; i<h; i++)
        (*matrix)->data[i] = calloc(w, sizeof(int));
}

void oneMatrix (Matrix **matrix, int h, int w) {
    if (w <= 0 || h <= 0)
        return;

    (*matrix) = malloc(sizeof(Matrix));
    (*matrix)->h = h;
    (*matrix)->w = w;
    (*matrix)->data = malloc(sizeof(int) * h);
    for (int i=0; i<h; i++) {
        (*matrix)->data[i] = malloc(sizeof(int) * w);
        for (int j=0; j<w; j++)
            ((int*)((*matrix)->data[i]))[j] = 1;
    }
}

void randomSquareMatrix (Matrix **matrix, int x, int top) {
    (*matrix) = malloc(sizeof(Matrix));
    (*matrix)->h = x;
    (*matrix)->w = x;
    (*matrix)->data = malloc(sizeof(int) * x);
    for (int i=0; i<x; i++) {
        (*matrix)->data[i] = malloc(sizeof(int) * x);
        for (int j=0; j<x; j++)
            ((int*)(*matrix)->data[i])[j] = rand() % top;
    }
}

void matrixAddition(Matrix *m1, Matrix *m2, Matrix **result) {
    if (m1 == NULL || m2 == NULL)
        return;

    int hResult = (m1->h > m2->h) ? m2->h : m1->h;
    int wResult = (m1->w > m2->w) ? m2->w : m1->w;

    zeroMatrix(result, hResult, wResult);
    if ((*result) == NULL)
        return;

    for (int i=0; i<hResult; i++)
        for (int j=0; j<wResult; j++)
            ((int*)(*result)->data[i])[j] = ((int*)m1->data[i])[j] + ((int*)m2->data[i])[j];
}

void matrixSub(Matrix *m1, Matrix *m2, Matrix **result) {
    if (m1 == NULL || m2 == NULL)
        return;

    int hResult = (m1->h > m2->h) ? m2->h : m1->h;
    int wResult = (m1->w > m2->w) ? m2->w : m1->w;

    zeroMatrix(result, hResult, wResult);
    if ((*result) == NULL)
        return;

    for (int i=0; i<hResult; i++)
        for (int j=0; j<wResult; j++)
            ((int*)(*result)->data[i])[j] = ((int*)m1->data[i])[j] - ((int*)m2->data[i])[j];
}

void matrixDiv(Matrix *m1, Matrix *m2, Matrix **result) {
    if (m1 == NULL || m2 == NULL)
        return;

    int hResult = (m1->h > m2->h) ? m2->h : m1->h;
    int wResult = (m1->w > m2->w) ? m2->w : m1->w;

    zeroMatrix(result, hResult, wResult);
    if ((*result) == NULL)
        return;

    for (int i=0; i<hResult; i++)
        for (int j=0; j<wResult; j++)
            ((int*)(*result)->data[i])[j] = ((int*)m1->data[i])[j] / ((int*)m2->data[i])[j];
}

void matrixMultiplication(Matrix *m1, Matrix *m2, Matrix **result) {
    if (m1 == NULL || m2 == NULL)
        return;

    zeroMatrix(result, m1->h, m2->w);
    if ((*result) == NULL)
        return;

    for (int i=0; i<m1->h; i++) {
        for (int j=0; j<m2->w; j++) {
            int s = 0;
            for (int k=0; k<m1->w; k++) {
                s += ((int*)(m1->data[i]))[k] * ((int*)(m2->data[k]))[j];
            }
            ((int*)((*result)->data[i]))[j] = s;
        }
    }
}

void matrixTranspose(Matrix *matrix, Matrix **result) {
    zeroMatrix(result, matrix->w, matrix->h);
    if ((*result) == NULL)
        return;

    for (int i=0; i<matrix->w; i++)
        for (int j=0; j<matrix->h; j++)
            ((int*)(*result)->data[i])[j] = ((int*)matrix->data[j])[i];
}

int getDeterminant(Matrix *matrix) {
    if (matrix->w == 2 && matrix->h == 2) {
        return ((int*)matrix->data[0])[0] * ((int*)matrix->data[1])[1] -
                ((int*)matrix->data[0])[1] * ((int*)matrix->data[1])[0];
    } else {
        int sum = 0;
        for (int i=0; i<matrix->w; i++) {
            Matrix *subMatrix;
            zeroMatrix(&subMatrix, matrix->h - 1, matrix->w - 1);

            int x = 0;
            for (int j=0; j<(matrix->w - 1); j++) {
                for (int k=0; k<(matrix->w - 1); k++) {
                    if (k == i) {
                        x = 1;
                    }
                    ((int*)subMatrix->data[j])[k] = ((int*)matrix->data[j + 1])[k + x];
                }
                x = 0;
            }

            if (i % 2 != 0)
                sum -= (((int*)matrix->data[0])[i] * getDeterminant(subMatrix));
            else
                sum += (((int*)matrix->data[0])[i] * getDeterminant(subMatrix));
        }
        return sum;
    }
}

void adjointMatrix(Matrix *matrix, Matrix **adj) {
    zeroMatrix(adj, matrix->h, matrix->w);
    if ((*adj) == NULL)
        return;

    for (int i=0; i<matrix->w; i++) {
        for (int j=0; j<matrix->w; j++) {
            Matrix *subMatrix;
            zeroMatrix(&subMatrix, matrix->w - 1, matrix->h - 1);

            // get sub
            int x = 0, y = 0;
            for (int k=0; k<(matrix->w - 1); k++) {
                if (k == i)
                    x = 1;
                for (int l=0; l<((matrix)->w - 1); l++) {
                    if (l == j)
                        y = 1;
                    ((int*)subMatrix->data[k])[l] = ((int*)matrix->data[k + x])[l + y];
                }
                y = 0;
            }

            if ((i + j) % 2 == 0)
                ((int*)(*adj)->data[j])[i] = getDeterminant(subMatrix);
            else
                ((int*)(*adj)->data[j])[i] = -1 * getDeterminant(subMatrix);
        }
    }

}

void getInverse(Matrix *matrix, Matrix **inverse) {
    if (matrix->w != matrix->h)
        return;

    // Following steps are from wikiHow: How to get inverse matrix =)
    // step 1: check determinant
    if (getDeterminant(matrix) == 0)
        return;

    // step 2: get transpose
    Matrix *transpose;
    matrixTranspose(matrix, &transpose);

    // step 3: get adjoint
    Matrix *mAdj;
    adjointMatrix(transpose, &mAdj);

    // step 4: adj / det (mat)
    Matrix *mDet;
    int determinant = getDeterminant(matrix);
    zeroMatrix(&mDet, matrix->w, matrix->h);
    for (int i=0; i<matrix->w; i++) {
        for (int j=0; j<matrix->w; j++) {
            ((int*)mDet->data[i])[j] = determinant;
        }
    }
    matrixDiv(mAdj, mDet, inverse);
}

void rotateMatrix() {
    //.........
}

void translate() {
    // ........
}

void printMatrix(Matrix *matrix) {
    if (matrix == NULL)
        return;

    printf("%dx%d\n", matrix->h, matrix->w);
    for (int i=0; i<matrix->h; i++) {
        for (int j=0; j<matrix->w; j++)
            printf("%d ", ((int*)(matrix->data[i]))[j]);
        printf("\n");
    }
    printf("\n");
}

#endif // MATRIX_H_INCLUDED
