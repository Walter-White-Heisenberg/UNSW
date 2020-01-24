int remove_duplicates(int length, int source[length], int destination[length]){
    int p,w,i,c;
    i = 0;
    while(i < length){
        destination[i] = 0;
        i++;
    }
    i = 0;
    p = 0;
    while(i < length){
        w = 0;
        c = 0;       
        while(w < length){
            if(source[i] == destination[w] && i != w && source[i] != 0){
                c++;
            }
            w++;
        }if(c == 0){
            destination[p] = source[i];
            p++;
        }        
        i++;
    }
    return p;
}
