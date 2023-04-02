#include "hw7.h"

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
    while((*expr != '\n') && (*expr != '\0'))
    {
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
    // printf("%s \n", new_string);

    // create the matrix_sf struct. 
    char* matrix_ptr = new_string;
    while (isdigit (*matrix_ptr) == 0)
    {   // find first number
        matrix_ptr++;
    }
    int num_rows = atoi(matrix_ptr);
    while(isspace(*matrix_ptr) == 0){
        matrix_ptr++;
    }
    while (isdigit (*matrix_ptr) == 0)
    {   // find second number
        matrix_ptr++;
    }
    int num_columns = atoi(matrix_ptr); // find second number 
    while(*matrix_ptr != '['){
        matrix_ptr++;
    } // now point to left bracket [
    int* values = (int*) malloc(sizeof(int) * num_rows * num_columns);
    int* value_ptr = values;
    while(*matrix_ptr != ']')
    { // fill the matrix until right bracket being found. 
        if(isdigit(*matrix_ptr) || (*matrix_ptr == '-'))
        {   // fill one element once find a space.
            *value_ptr = atoi(matrix_ptr);
            value_ptr++;
            while (isdigit(*matrix_ptr) || (*matrix_ptr == '-'))
            {
                matrix_ptr++;
            }
            
        }
        matrix_ptr++;
    } 
    // value_ptr = 0;

    // store values into matrix and return. 
    matrix_sf* struct_matrix = copy_matrix(num_rows, num_columns, values);
    // for(int i = 0; i < (num_columns * num_rows); i++){

    // }
    free(values);
    struct_matrix->name = name;
    free(new_string);
    
    return struct_matrix;
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
