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
    if(root->mat->name == name){
        return root->mat;
    }
    bst_sf* cursor = root;
    find_bst_sf(name,cursor->left_child);
    if(cursor->mat->name == name){
        return cursor->mat;
    }
    else{
        return NULL;
    }
    find_bst_sf(name,cursor->right_child);
}


void free_cursor(bst_sf* cursor){
    free_cursor(cursor->left_child);
    free_cursor(cursor->right_child);
    free(cursor);
}

void free_bst_sf(bst_sf *root) {
    bst_sf* cursor = root;
    free_cursor(cursor);
    free(root);
}



matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    int NR = mat1->num_rows;
    int NC = mat1->num_cols;
    int product = NR * NC;
    int* value_1 = mat1->values;
    int* value_2 = mat2->values;
    int* new_value = (int*)malloc(NR * NC * sizeof(int));
    for(int i = 0; i < product; i++){
        *(new_value+i) = value_1[i] + value_2[i];
    }
    matrix_sf* add_result = copy_matrix(NR, NC, new_value);
    free(new_value);
    return add_result;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    int NR = mat1->num_rows; // how many elements in one column
    int NC = mat2->num_cols; // how many elements in one row
    int inter = mat1->num_cols;
    int total_elements = NR * NC;
    int* mat1_value = mat1->values;
    int* mat2_value = mat2->values;
    int* new_value = (int*)malloc(NR * NC* sizeof(int));
    for(int i = 0; i < NR; i++){
        for(int j = 0; j < NC; j++){
            int this_element = 0;
            for(int k = 0; k < inter; k++){
                this_element+= (mat1_value[inter * i + k] * mat2_value[NC * k + j]);
            }
            new_value[i*NC + j] = this_element;
        }
    }
    matrix_sf* multi_result = copy_matrix((unsigned int)NR,(unsigned int) NC, new_value);
    free(new_value);
    return multi_result;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    int NR = mat->num_cols;// how many elements in one column
    int NC = mat->num_rows;// how many elements in one row
    int total_elements = NR * NC;
    int* new_value = (int*)malloc(NR * NC * sizeof(int));
     // size remain unchanged after transpose
    int* old_value = mat->values;
    for(int i = 0; i < total_elements; i++){
        int row_new = i / NC;
        int col_new = i % NC;
        int row_origin = col_new;//switch position
        int col_origin = row_new;
        new_value[i] = old_value[row_origin * NR + col_origin];// put in
    }
    matrix_sf* trans_result = copy_matrix(NR, NC, new_value);
    free(new_value);
    return trans_result;
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
    int length = strlen(infix);
    int num_punct = 0;
    int num_alnum = 0;
    for(int i = 0; i < length; i++){
        if(ispunct(infix[i]))// if it is a punct 
        {
            num_punct ++;
            continue;
        }
        if(isalnum(infix[i])){
            num_alnum++;
        }
    }
    
    return infix;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
    // FILE* input = fopen(filename, "r+");
    // int matrix_count = 0;
    // int expression_count = 0;
    // int num_of_lines = 0;
    // while(1){
    //     size_t bytes_read;
    //     size_t size = MAX_LINE_LEN;
    //     char *string = NULL;
    //     string = (char *) malloc (size * sizeof(char));
    //     bytes_read = getline (&string, &size, input); 
    //     num_of_lines++;
    //     if (bytes_read == EOF){
    //         free(string);
    //         break;
    //     }    
    //     if(bytes_read == 0){
    //         free(string);
    //         break;
    //     } 
    //     if(strstr(string, "[") != 0) // if found bracket
    //     {
    //         matrix_count++;
    //     }
    //     else
    //     {
    //         expression_count++;
    //     }
    // }
    // char* matrixs[MAX_LINE_LEN] = malloc(sizeof(matrixs[MAX_LINE_LEN]) * matrix_count);
    // char* expression[MAX_LINE_LEN] = malloc(sizeof(expression[MAX_LINE_LEN]) * expression_count);
    // int which_matrix = 0;
    // int which_expression = 0;
    // for(int i = 0; i < num_of_lines; i++)
    // {
    //     size_t bytes_read;
    //     size_t size = MAX_LINE_LEN;
    //     char *string = NULL;
    //     string = (char *) malloc (size * sizeof(char));
    //     bytes_read = getline (&string, &size, input); 
    //     if (bytes_read == EOF){
    //         free(string);
    //         break;
    //     }    
    //     if(bytes_read == 0){
    //         free(string);
    //         break;
    //     } 
    //     if(strstr(string, "[") != 0) // if found bracket
    //     {
    //         matrixs[which_matrix] = string;
    //         which_matrix++;
    //     }
    //     else
    //     {
    //         expression[which_expression] = string;
    //         which_expression++;
    //     }
    // }
    // free(matrixs);
    // free(expression);
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
