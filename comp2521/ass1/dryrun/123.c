static char *starANDline(char *original,int from){
    int firstStar = -1, firstLine = -1, secondStar = -1, secondLine = -1,starN = 0,lineN = 0;
    for(int i = from; original[i] != 0; i++){     //loop to get the position of first pair
        if(secondStar != -1 && secondLine != -1){//quit when there are already pairs of * and _
            i = strlen(original)-1;
        }else if(original[i] == '*'){//only count for the original after point from
            if(firstStar != -1 && starN == 1){
                secondStar = i;
                starN++;
            }else if(original[i + 1] != '*' && starN == 0){
                firstStar = i;
                starN++;
            }    
        }else if(original[i] == '_'){
            if(firstLine != -1 && lineN == 1){
                secondLine = i;
                lineN++;
            }else if(original[i + 1] != '_' && lineN == 0){
                firstLine = i;
                lineN++;   
            }     
        }
    }
    
    if(secondStar != -1 || secondLine != -1){
        int smaller = (secondLine == -1 ||(( firstStar < firstLine ) && (secondStar != -1))) ? firstStar : firstLine;
        int bigger = (smaller == firstStar) ? secondStar :secondLine; 
        char *final = malloc(strlen(original) + 6);
        int m = 0;
        for(int i = 0; original[i] != 0; i++){
            if(i == smaller){
                final[m] = '<';
                final[m+1] = (smaller == firstStar) ? 'b':'i';
                final[m+2] = '>';
                m = m + 3;
            }else if(i == bigger){
                final[m] = '<';
                final[m+1] = 47;
                final[m+2] = (smaller == firstStar) ? 'b':'i';
                final[m+3] = '>';
                m = m + 4;
                if(secondStar != -1 && secondLine != -1 && (bigger < firstStar + firstLine - smaller)){
                    final = realloc(final,strlen(original) + 11);
                    smaller = firstStar + firstLine - smaller;
                    bigger = secondStar +secondLine - bigger;
                }                      
            }else{
                final[m] = original[i];
                m++;
            }
        }
        from = bigger;
        free(original);
        final[m] = 0;
        return starANDline(final,from);//the new string will be returned until all qualified * and _ is replaced
    }else{
        return original;
    } 
}

void formRichText (TB tb) {
    char *original = NULL;
    for(textnode *n = tb->first; n != NULL; n = n->next){
        original = n->text;
        if(original[0] == '#' && strlen(original) > 1){//when '#' is at beginning 
            char *end = "</h1>";
            char *start = "<h1";
            char *tmp = NULL;
            tmp = realloc(tmp,strlen(original) + strlen(start) + strlen(end) + 1);
            strcpy(tmp,start);
            strcat(tmp,original);
            tmp[3] = '>';
            strcat(tmp,end);
            n->text = tmp;
            free(original);
        }else{
            n->text = starANDline(original,0);//when # is not at beginning
        }       
    }   
}

//turn tb1 into tb2
char *diffTB (TB tb1, TB tb2) {
    int line = 1,length = 0;    
    textnode *original = tb1->first;
    textnode *final = tb2->first;
    char *diff = malloc(1);
    char *str = NULL;
    strcpy(diff, "");
    while(original != NULL || final != NULL){
        length = snprintf( NULL, 0, "%d", line);
        if(original == NULL){
            diff = realloc(diff, strlen(diff) + 5 + strlen(final->text) + length);
            str = malloc(length + 1 + 3);
            snprintf(str, length + 4, "+,%d,", line);
            strcat(diff,str);
            strcat(diff,final->text);
            final = final->next;
            line = line + 1;
            strcat(diff,"\n");
            free(str);
        }else if(final == NULL){
            diff = realloc(diff, strlen(diff) + 4 + length);
            str = malloc(length + 1 + 2);
            snprintf(str, length + 3, "-,%d", line);
            strcat(diff,str);
            original = original->next;
            strcat(diff,"\n");
            free(str);
        }else{
            if(strcmp(original->text,final->text) != 0){
                if(final->next != NULL && strcmp(final->next->text, original->text) == 0){
                    diff = realloc(diff, strlen(diff) + 4 + length);
                    str = malloc(length + 3);
                    snprintf(str, length + 3, "-,%d", line);
                    strcat(diff,str);
                    strcat(diff,"\n");
                    free(str); 
                    final = final->next;
                }else if(original->next != NULL && strcmp(original->next->text, final->text) == 0){
                    diff = realloc(diff, strlen(diff) + 5 + strlen(final->text) + length);
                    str = malloc(length + 1 + 3);
                    snprintf(str, length + 4, "+,%d,", line);
                    strcat(diff,str);
                    strcat(diff,final->text);
                    strcat(diff,"\n");
                    free(str);
                    original = original->next;
                }else{
                    diff = realloc(diff, strlen(diff) + 4 + length);
                    str = malloc(length + 3);
                    snprintf(str, length + 3, "-,%d", line);
                    strcat(diff,str);
                    strcat(diff,"\n");
                    free(str);                
                    diff = realloc(diff, strlen(diff) + 5 + strlen(final->text) + length);
                    str = malloc(length + 1 + 3);
                    snprintf(str, length + 4, "+,%d,", line);
                    strcat(diff,str);
                    strcat(diff,final->text);
                    strcat(diff,"\n");
                    free(str);
                }    
            }
            original = original->next;
            final = final->next;
            line = line + 1;
        }    
    }
	return diff;
}
