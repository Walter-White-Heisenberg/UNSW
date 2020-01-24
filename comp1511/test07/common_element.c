// copy all of the values in source1 which are also found in source2 into destination
// return the number of elements copied into destination

int common_elements(int length, int source1[length], int source2[length], int destination[length]) {
    int destination[length] = {0};
    int source[length];
    int i = 0;
    int counter = 0;
    while(i < length){ 
        int a = 0;   
        while(a < length){
            if (source1[i] == source2[a]){
                destination[i] == source1[i];
                counter++;
                a = a + length;
            }
            a++;    
        }
        int b = 0;
        while(b < length){
            if(destination[b] = destination[i] && b != i && b*i != 0){
                destination[b] = 0;
            }
            b++;
        }
        i++;
    }
    return counter;
}

// You may optionally add a main function to test your common_elements function.
// It will not be marked.
// Only your common_elements function will be marked.

