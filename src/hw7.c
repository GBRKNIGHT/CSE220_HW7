#include "hw7.h"

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    return NULL;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    return NULL;
}

void free_bst_sf(bst_sf *root) {
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    return NULL;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
   return NULL;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    return NULL;
}

// create a new string to make sure the number of spaces between each 
// operator/ bracket/ number equal to 1. 
// Then separate into a matrix, and return in this standard form. 
matrix_sf* create_matrix_sf(char name, const char *expr) 
{
    char* new_string = (char*)malloc(MAX_LINE_LEN * sizeof(char)); // max = 128
    int previous_char = 0; // 
    char* new_str_ptr = new_string;
    while(*expr != '\n'){
        if (isspace(*expr))// if this char is a space
        {
            if(previous_char != 1)
            {   // if there is no space and this is not first char, add this space to 
                // the new string. 
                *new_str_ptr = *expr;
                new_str_ptr++;
            }
            previous_char = 1;
            expr++;
            continue;
        }
        if(ispunct(*expr) || *expr == '=') // if this char is a punct or = 
        {
            if(previous_char != 1){
                *new_str_ptr = ' ';
                new_str_ptr++;
            }
            *new_str_ptr = *expr;
            new_str_ptr++;
            previous_char = 2;
            expr++;
            continue;
        }
        if(isdigit(*expr)) // if this char is a number
        {
            if(((previous_char == 2) || (previous_char == 4)) && (*(expr - 1) != '-'))
            {
                *new_str_ptr = ' ';
                new_str_ptr++;
                
            }
            *new_str_ptr = *expr;
            previous_char = 3;
            new_str_ptr++;
            expr++;
            continue;
        }
        if(isalnum(*expr))// if this char is a alphaberical char
        {
            // assume this alphaberical char will appear at position 0 only. 
            *new_str_ptr = *expr; 
            new_str_ptr++;
            previous_char = 4;
            expr++;
            continue;
        }
    }
    printf("%s \n", new_string);
    return NULL;
}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
