// // char* infix2postfix_sf(char *infix) {
// //     int length = strlen(infix);
// //     // int num_punct = 0;
// //     // int num_alnum = 0;
// //     // for(int i = 0; i < length; i++){
// //     //     if(ispunct(infix[i]))// if it is a punct 
// //     //     {
// //     //         num_punct ++;
// //     //         continue;
// //     //     }
// //     //     if(isalnum(infix[i])){
// //     //         num_alnum++;
// //     //     }
// //     // }
// //     // char* post_fix = (char*)malloc(length*sizeof(char));
// //     // char* temp = (char*)malloc(length*sizeof(char));
// //     // strcpy(temp, infix);
// //     // int count_loop = 0;
// //     // char* temp_ptr = temp;
// //     // while(*temp_ptr != '\0' && *temp_ptr != '\n')
// //     // {   
// //     //     if(*temp_ptr == '('){
// //     //         ++temp_ptr;
// //     //         for(int i = 0; *(temp_ptr + i) != ')'; i++){

// //     //         }
// //     //     }
// //     //     count_loop++;
// //     //     temp_ptr++;
// //     // }
// //     return infix;
// // }


// // matrix_sf* find_cursor(char name, bst_sf* cursor){
// //     find_bst_sf(name,cursor->left_child);
// //     find_bst_sf(name,cursor->right_child);
// //     if(cursor->mat->name == name){
// //         return cursor->mat;
// //     }
// // }


// matrix_sf *execute_script_sf(char *filename) {
//     // need to restructure this code, think about it. 
//     FILE* input = fopen(filename, "r+");
//     int matrix_count = 0;
//     int expression_count = 0;
//     int num_of_lines = 0;
//     while(1){
//         size_t bytes_read;
//         size_t size = MAX_LINE_LEN;
//         char *string = NULL;
//         string = (char *) malloc (size * sizeof(char));
//         bytes_read = getline (&string, &size, input); 
//         num_of_lines++;
//         if (bytes_read == EOF){
//             free(string);
//             break;
//         }    
//         if(bytes_read == 0){
//             free(string);
//             break;
//         } 
//         if(strstr(string, "[") != 0) // if found bracket
//         {
//             matrix_count++;
//         }
//         else
//         {
//             expression_count++;
//         }
//     }
//     // char* matrixs[MAX_LINE_LEN] = (char**)malloc(sizeof(matrixs[MAX_LINE_LEN]) * matrix_count);
//     // char* expression[MAX_LINE_LEN] = (char**)malloc(sizeof(expression[MAX_LINE_LEN]) * expression_count);
//     // int which_matrix = 0;
//     // int which_expression = 0;
//     // for(int i = 0; i < num_of_lines; i++)
//     // {
//     //     size_t bytes_read;
//     //     size_t size = MAX_LINE_LEN;
//     //     char *string = NULL;
//     //     string = (char *) malloc (size * sizeof(char));
//     //     bytes_read = getline (&string, &size, input); 
//     //     if (bytes_read == EOF){
//     //         free(string);
//     //         break;
//     //     }    
//     //     if(bytes_read == 0){
//     //         free(string);
//     //         break;
//     //     } 
//     //     if(strstr(string, "[") != 0) // if found bracket
//     //     {
//     //         matrixs[which_matrix] = string;
//     //         which_matrix++;
//     //     }
//     //     else
//     //     {
//     //         expression[which_expression] = string;
//     //         which_expression++;
//     //     }
//     // }
//     // free(matrixs);
//     // free(expression);
//     return NULL;
// }
