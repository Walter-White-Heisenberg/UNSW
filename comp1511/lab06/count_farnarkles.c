int count_farnarkles(int tiles1[], int tiles2[]) {
    int x,i;
    x=0;
    i=0;
    while(x<4){
        if(tiles1[x]==tiles2[x]){
            i++;
        }
        x++;
    }

    return i;
}

