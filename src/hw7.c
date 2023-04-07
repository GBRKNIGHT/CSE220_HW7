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
    // char name = mat->name;
    // int NR = mat->num_rows;
    // int NC = mat->num_cols;
    // int* values = mat->values;
    if(root == NULL){
        bst_sf* new_tree = (bst_sf*)malloc(sizeof(bst_sf*) * 2 + sizeof(matrix_sf*));
        new_tree->mat = mat;
        new_tree->left_child = NULL;
        new_tree->right_child = NULL;
        return new_tree;
    }
    if((root->mat->name) < (mat->name) && root->right_child == NULL)
    {
        bst_sf* right_tree = (bst_sf*)malloc(sizeof(bst_sf*) * 2 + sizeof(matrix_sf*));
        right_tree->mat = mat;
        right_tree->left_child = NULL;
        right_tree->right_child = NULL;
        root->right_child = right_tree;  
        return root;
    }
    else if((root->mat->name) > mat->name && root->left_child == NULL)
    {
        bst_sf* left_tree = (bst_sf*)malloc(sizeof(bst_sf*) * 2 + sizeof(matrix_sf*));
        left_tree->mat = mat;
        left_tree->left_child = NULL;
        left_tree->right_child = NULL;
        root->left_child = left_tree;  
        return root;
    }
    if(mat->name < root->mat->name){
        insert_bst_sf(mat,root->left_child);
    }
    else
    {
        insert_bst_sf(mat,root->right_child);
    }
    return root; 
}



matrix_sf* find_bst_sf(char name, bst_sf *root) {
    // printf("IN BST: %p\n", root);
    // printf("Left Child: %p\n", root->left_child);
    // printf("Right Child: %p\n", root->right_child);
    // printf("IN BST looking for: %c\n", name);
    // printf("IN BST Current name: %c\n", root->mat->name);
    if(root == NULL){
        return NULL;
    }
    if(root->mat->name == name){
        return root->mat;
    }
    if(name < root->mat->name){
        return find_bst_sf(name, root->left_child);
    }else{
        return find_bst_sf(name, root->right_child);
    }
    return NULL;
}



void free_cursor(bst_sf* cursor){
    if (cursor)
    {
        free_cursor(cursor->left_child);
        free_cursor(cursor->right_child);
        free(cursor->mat);
        free(cursor);
    }
}

void free_bst_sf(bst_sf *root) {
    bst_sf* cursor = root;
    free_cursor(cursor);
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


// This code is inspired by the provided instruction.
// https://www.geeksforgeeks.org/convert-infix-expression-to-postfix-expression/

// show the precedence of each operators, parenthesis has highest. And + has lowest. 
int precedence(char operator)
{
    if(operator == '+'){
        return 1;
    }
    if(operator == '*'){
        return 2;
    }
    if(operator == '\''){
        return 3;
    }
    else{
        return -1;
    }
}


int isoprea(char cursor){
    if(cursor == '+' || cursor == '*' || cursor == '\'' || cursor == '(' || cursor == ')')\
    {
        return 1;
    }
    else{
        return 0;
    }
}


char* infix2postfix_sf(char* infix)
{
    int length = strlen(infix);
    char* postfix = (char*)malloc(sizeof(char) * MAX_LINE_LEN);
    char* stack = (char*)malloc(sizeof(char) * MAX_LINE_LEN);
    int top = -1;
    int i= 0, j = 0;

    while (i < length) {
        if (isalnum(infix[i])) {
            postfix[j] = infix[i];
            j++;
        } 
        // we need to make sure the parenthesis has the highest precedency.
        if (infix[i] == '(') 
        {// if left, push it into stack
            top++;
            stack[top] = infix[i];
        } 
        else if (infix[i] == ')') 
        {// right exist only if left exist
            while (top > -1 && stack[top] != '(') 
            {   //move to post fix 
                postfix[j] = stack[top];
                j++;
                top--;
            }
                top--;
        } 
        else if (isoprea(infix[i])) {
            while (top > -1 && precedence(stack[top]) >= precedence(infix[i])) 
            {
                postfix[j] = stack[top];
                j++;
                top--;
            }
            top++;
            stack[top] = infix[i];
        }      
        i++;
    }
    while (top != -1) {
        postfix[j] = stack[top];
        j++;
        top--;
    }
    postfix[j] = '\0';
    free(stack);
    return postfix;
}


matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    if(root == NULL || expr == NULL){
        return NULL;
    }
    // printf("BST: %p\n", root);
    char* pos_expr = infix2postfix_sf(expr);
    int exp_len = strlen(pos_expr);
    matrix_sf** matrix_stack = (matrix_sf**)malloc(sizeof(matrix_sf**) * (exp_len));
    int stack_counter = 0;
    for(int i = 0; i < exp_len; i++){
        if(isalnum(pos_expr[i])){
            printf("Found: %c\n", pos_expr[i]);
            matrix_sf* found_matrix = find_bst_sf(pos_expr[i], root);
            // printf("Matrix Address: %p\n", found_matrix);
            matrix_sf* this_matrix = (copy_matrix(found_matrix->num_rows, found_matrix->num_cols, found_matrix->values));
            matrix_stack[stack_counter] = this_matrix;
            stack_counter++;
            // push a element to the stack 
        }
        else if(pos_expr[i] == '\''){
            matrix_sf* being_trans = matrix_stack[stack_counter - 1];
            matrix_sf* transposed = transpose_mat_sf(being_trans);
            free(being_trans);
            matrix_stack[stack_counter - 1] = transposed;
            continue;
        }
        else if(pos_expr[i] == '*'){
            matrix_sf* being_mul1 = matrix_stack[stack_counter - 2];
            matrix_sf* being_mul2 = matrix_stack[stack_counter - 1];
            matrix_sf* product = mult_mats_sf(being_mul1, being_mul2);
            free(being_mul1);
            free(being_mul2);
            stack_counter -= 2;
            matrix_stack[stack_counter] = product;
            stack_counter += 1;
            continue;
        }
        else if(pos_expr[i] == '+'){
            matrix_sf* being_add1 = matrix_stack[stack_counter - 2];
            matrix_sf* being_add2 = matrix_stack[stack_counter - 1];
            matrix_sf* sum = add_mats_sf(being_add1, being_add2);
            free(being_add1);
            free(being_add2);
            stack_counter -= 2;
            matrix_stack[stack_counter] = sum;
            stack_counter += 1;
            continue;
        }
        else{
            printf("error! \n");
        }
    }
    int NR = matrix_stack[0]->num_rows;
    int NC = matrix_stack[0]->num_cols;
    int* value = matrix_stack[0]->values;
    matrix_sf* top = copy_matrix(NR, NC, value);
    free(matrix_stack[0]);
    free(matrix_stack);
    free(pos_expr);
    top->name = name;
    return top;
}

matrix_sf *execute_script_sf(char *filename) {
    // need to restructure this code, think about it. 
    FILE* input = fopen(filename, "r");
    int matrix_count = 0;
    int expression_count = 0;
    int num_of_lines = 0;
    bst_sf* binary_search_tree = NULL;
    if(input == NULL){
        return NULL;
    }
    size_t bytes_read = 0;
    size_t size = MAX_LINE_LEN;
    char *string = NULL;
    string = (char *) malloc (size * sizeof(char));
    bytes_read = getline(&string, &size, input);
    while(1){
        if (bytes_read == EOF){
            free(string);
            break;
        }    
        if(bytes_read == 0){
            free(string);
            break;
        } 
        num_of_lines++;
        if(strstr(string, "[") != 0) 
        // if found bracket, this is a matrix, need to create a matrix, then
        // insert it into the current binary tree. 
        {
            
            char* equal_sign  = strchr(string, '=');
            int index_equal = (int)(equal_sign - string);
            // char* matrix = (char*)malloc(sizeof(char)*(strlen(string) - index_equal));
            // for(int i = 0; i < strlen(string) - index_equal + 1; i++){
            //     matrix[i] = string[i + index_equal];
            // }
            // matrix[strlen(matrix)] = '\0';
            matrix_sf* new_matrix_matrix = create_matrix_sf(string[0], string+index_equal);
            binary_search_tree = insert_bst_sf(new_matrix_matrix, binary_search_tree);
            matrix_count++;
        }
        else
        {
            // if this is an expression, we need to perform calculations and add the result 
            // to the binary tree. 
            char new_name = string[0];
            char* equal_sign  = strchr(string, '=');
            int index_equal = (int)(equal_sign - string);
            // char* expression = (char*)malloc(sizeof(char)*(strlen(string) - index_equal));
            // for(int i = 0; i < strlen(string) - index_equal + 1; i++){
            //     expression[i] = string[i + index_equal];
            // }
            // expression[strlen(expression)] = '\0';
            matrix_sf* new_matrix_eva = evaluate_expr_sf(new_name, string+index_equal, binary_search_tree);
            binary_search_tree = insert_bst_sf(new_matrix_eva, binary_search_tree);
            expression_count++;
        }
        bytes_read = getline (&string, &size, input); 
    }
    string = NULL;
    if(binary_search_tree != NULL && binary_search_tree->mat != NULL){
        char result_name = binary_search_tree->mat->name;
        unsigned int result_NR = binary_search_tree->mat->num_rows;
        unsigned int result_NC = binary_search_tree->mat->num_cols;
        int* result_value = binary_search_tree->mat->values;
        matrix_sf* result = copy_matrix(result_NR, result_NC, result_value);
        result->name = result_name;
        free_bst_sf(binary_search_tree);
        fclose(input);
        free(string);
        return result;
    }
    else{
        free_bst_sf(binary_search_tree);
        fclose(input);
        free(string);
        return NULL;
    }
    
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

// void inorder_sf(bst_sf *root, char *output) {
//     if (!root) return;
//     inorder_sf(root->left_child, output);
//     char s[2] = {root->mat->name};
//     strcat(output, s);
//     inorder_sf(root->right_child, output);
// }
// int compare_chars_sf(const void* a, const void* b) { return (*(char*)a - *(char*)b); }
// void sort_string_sf(char* str) { qsort(str, strlen(str), sizeof(char), compare_chars_sf); }

// bst_sf* build_bst() {
//     matrix_sf *A = copy_matrix(3, 5, (int[]){-4, 18, 6, 7, 10, -14, 29, 8, 21, -99, 0, 7, 5, 2, -9});
//     A->name = 'A';
//     matrix_sf *B = copy_matrix(3, 5, (int[]){10, 9, -2, -33, 22, 44, 10, 12, 72, 52, -88, 17, 16, 14, -9});
//     B->name = 'B';
//     matrix_sf *C = copy_matrix(1, 4, (int[]){-123, 47, -4, 140});  
//     C->name = 'C';
//     matrix_sf *D = copy_matrix(1, 4, (int[]){-16, 122, 135, 107});
//     D->name = 'D';
//     matrix_sf *E = copy_matrix(6, 4, (int[]){83, -22, 56, -1, 97, 94, 135, -10, 84, 40, -83, -4, 79, 28, 52, -101, 138, 146, 99, 0, -23, -73, -39, -47});
//     E->name = 'E';
//     matrix_sf *F = copy_matrix(4, 7, (int[]){-77, -20, 111, -2, 41, 117, 118, 21, -29, -45, 135, 98, 54, 131, 54, 1, 80, 143, -127, 148, 114, -81, 87, -33, -2, -6, 115, 59});
//     F->name = 'F';
//     matrix_sf *G = copy_matrix(7, 1, (int[]){-38, 4, 46, -14, -102, -72, -27});
//     G->name = 'G';
//     matrix_sf *H = copy_matrix(1, 5, (int[]){52, 65, -94, -73, -48});
//     H->name = 'H';
//     matrix_sf *I = copy_matrix(4, 4, (int[]){-7, 78, -87, -113, -144, -94, 22, -75, -137, -130, -113, -106, 85, -120, 50, 55});
//     I->name = 'I';
//     matrix_sf *J = copy_matrix(6, 3, (int[]){121, -1, 128, 78, -138, 138, -61, 51, -35, -84, 125, -83, -78, 138, 2, 81, -5, -36});
//     J->name = 'J';
//     bst_sf* Anode = malloc(sizeof(bst_sf));
//     Anode->mat = A;
//     Anode->left_child = NULL;
//     Anode->right_child = NULL;
//     bst_sf* Cnode = malloc(sizeof(bst_sf));
//     Cnode->mat = C;
//     Cnode->left_child = NULL;
//     Cnode->right_child = NULL;
//     bst_sf* Hnode = malloc(sizeof(bst_sf));
//     Hnode->mat = H;
//     Hnode->left_child = NULL;
//     Hnode->right_child = NULL;
//     bst_sf* Jnode = malloc(sizeof(bst_sf));
//     Jnode->mat = J;
//     Jnode->left_child = NULL;
//     Jnode->right_child = NULL;
//     bst_sf* Bnode = malloc(sizeof(bst_sf));
//     Bnode->mat = B;
//     Bnode->left_child = Anode;
//     Bnode->right_child = Cnode;
//     bst_sf* Fnode = malloc(sizeof(bst_sf));
//     Fnode->mat = F;
//     Fnode->left_child = NULL;
//     Fnode->right_child = NULL;
//     bst_sf* Inode = malloc(sizeof(bst_sf));
//     Inode->mat = I;
//     Inode->left_child = Hnode;
//     Inode->right_child = Jnode;
//     bst_sf* Dnode = malloc(sizeof(bst_sf));
//     Dnode->mat = D;
//     Dnode->left_child = Bnode;
//     Dnode->right_child = NULL;
//     bst_sf* Gnode = malloc(sizeof(bst_sf));
//     Gnode->mat = G;
//     Gnode->left_child = Fnode;
//     Gnode->right_child = Inode;
//     bst_sf* Enode = malloc(sizeof(bst_sf));
//     Enode->mat = E;
//     Enode->left_child = Dnode;
//     Enode->right_child = Gnode;
//     return Enode;
// }

// static char test_log_outfile[100];

// #define TEST_TIMEOUT 10
// #define TEST_INPUT_DIR "tests.in"
// #define TEST_OUTPUT_DIR "tests.out"


// void run_script_without_valgrind(char *script_file) {
//     char executable[100];
//     sprintf(executable, ".bin/execute_script");
//     assert(access(executable, F_OK) == 0);
//     char cmd[500];
//     sprintf(test_log_outfile, "%s/%s.txt", TEST_OUTPUT_DIR, script_file);
//     sprintf(cmd, "ulimit -f 300; ulimit -t 5; ./bin/execute_script %s > %s 2>&1",
//         script_file, test_log_outfile);
//     system(cmd);
//     // expect_outfile_matches(script_file);
// }

// int main(){
//     run_script_without_valgrind("script01"); 
//     return 0;
// }
