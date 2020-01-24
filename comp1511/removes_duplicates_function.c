int remove_duplicates(int length, int source[length], int destination[length]){
    int p,w,i,x,c;
    char destination[length] = {0};
    i = 0;
    p = 0;    
    while(i < length){
        w = 0;
        c = 0;    
        while(w <= p){
            if(destinations[w] == source[i]){
                c++;
            }
            w++;
        }
        if(destinations[p] == source[i] && c == 0){
            destinations[p] = source[i];
            p++;
        }
        i++;
    }
    return p+1;
}
