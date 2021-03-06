// pathname is the pathname component of a URL
// if a corresponding file exists the client is sent
// a 200 header assuming file contains HTML
// followed by the file contents
// if a the file can't be opened
// a 404 header is sent with no body


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "serve_web_page.h"
#include <fcntl.h>
#include <sys/stat.h>


void serve_web_page(char *pathname, FILE *client_stream) {
    
    printf("%s\n",pathname);
    FILE *serve = fopen(pathname, "r+");
    if(serve != NULL){
        fprintf(client_stream, HEADER_200);
        char x[BUFSIZ];
    while(fgets(x, BUFSIZ, serve) != NULL){
        fputs(x, client_stream);
    }
    }else{
        fprintf(client_stream, HEADER_404);
    }
}
