// char* infix2postfix_sf(char *infix) {
//     int length = strlen(infix);
//     // int num_punct = 0;
//     // int num_alnum = 0;
//     // for(int i = 0; i < length; i++){
//     //     if(ispunct(infix[i]))// if it is a punct 
//     //     {
//     //         num_punct ++;
//     //         continue;
//     //     }
//     //     if(isalnum(infix[i])){
//     //         num_alnum++;
//     //     }
//     // }
//     // char* post_fix = (char*)malloc(length*sizeof(char));
//     // char* temp = (char*)malloc(length*sizeof(char));
//     // strcpy(temp, infix);
//     // int count_loop = 0;
//     // char* temp_ptr = temp;
//     // while(*temp_ptr != '\0' && *temp_ptr != '\n')
//     // {   
//     //     if(*temp_ptr == '('){
//     //         ++temp_ptr;
//     //         for(int i = 0; *(temp_ptr + i) != ')'; i++){

//     //         }
//     //     }
//     //     count_loop++;
//     //     temp_ptr++;
//     // }
//     return infix;
// }


// matrix_sf* find_cursor(char name, bst_sf* cursor){
//     find_bst_sf(name,cursor->left_child);
//     find_bst_sf(name,cursor->right_child);
//     if(cursor->mat->name == name){
//         return cursor->mat;
//     }
// }