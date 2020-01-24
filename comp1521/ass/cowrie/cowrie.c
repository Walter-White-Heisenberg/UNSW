// cowrie.c a simple shell


// PUT YOUR HEADER COMMENT HERE

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <spawn.h>
#include <glob.h>
#include <ctype.h>

// PUT EXTRA `#include'S HERE


#define MAX_LINE_CHARS 1024
#define INTERACTIVE_PROMPT "cowrie> "
#define DEFAULT_PATH "/bin:/usr/bin"
#define WORD_SEPARATORS " \t\r\n"
#define DEFAULT_HISTORY_SHOWN 10

// These characters are always returned as single words
#define SPECIAL_CHARS "!><|"

// PUT EXTRA `#define'S HERE


static void execute_command(char **words, char **path, char **environment, char *file);
static void do_exit(char **words);
static int is_executable(char *pathname);
static char **tokenize(char *s, char *separators, char *special_chars);
static void free_tokens(char **tokens);


//turn file to a 2d char array line by line
static char **file_to_strings(char *where, int *line);
//write command to file as a line
static void comm_to_file(char *file_name, char *comm[MAX_LINE_CHARS]);
//check is there only digit in a string
static int only_digit(char *string);

int main(void) {
    //ensure stdout is line-buffered during autotesting
    setlinebuf (stdout);
    // Environment variables are pointed to by `environ', an array of
    // strings terminated by a NULL value -- something like:
    //     { "VAR1=value", "VAR2=value", NULL }
    extern char **environ;

    // grab the `PATH' environment variable;
    // if it isn't set, use the default path defined above
    char *pathp;
    if ((pathp = getenv("PATH")) == NULL) {
        pathp = DEFAULT_PATH;
    }
    char **path = tokenize(pathp, ":", "");

    char *prompt = NULL;
    // if stdout is a terminal, print a prompt before reading a line of input
    if (isatty(1)) {
        prompt = INTERACTIVE_PROMPT;
    }
    
    // main loop: print prompt, read line, execute command
    while (1) {
        if (prompt) {
            fputs(prompt, stdout);
        }

        char line[MAX_LINE_CHARS];
        if (fgets(line, MAX_LINE_CHARS, stdin) == NULL) {
            break;
        }
            
        //find where the history file should be
        char past_path[MAX_LINE_CHARS];
        strcpy(past_path ,getenv("HOME"));
        strcat(past_path,"/.cowrie_history");

        // find out the number of command, for subset 4
        int n_comm = 0;
        char **command_words = tokenize(line, WORD_SEPARATORS, SPECIAL_CHARS);
        while(path[n_comm] != NULL){
            n_comm++;
        }
             
        //identify history and "!" for subset 2
        if ((strcmp(command_words[0],"!") == 0 || strcmp(command_words[0],"history") == 0)) {
        
            //Nline's value will be changed after file_to_string function
            int Nline = 0;
            char **past = file_to_strings(past_path,&Nline);
            
            
            //to check is there any operation before history
            if (command_words[1] != NULL && command_words[2] != NULL) 
                fprintf (stderr,"history: too many arguments\n");
                              
            //to check is there too many arguments
            else if (past[0] == NULL)
                fprintf (stderr,"history: nonnumber: numeric argument required\n");
               
            //history case
            else if (command_words[0][0] == 'h') {               
                FILE *history = fopen(past_path,"a+");

                //case for no trailing number, if Nline is smaller than 10, set it to zero
                if (command_words[1] == NULL) 
                    Nline -= (Nline < 10) ? Nline : 10;                
                else {                    
                    //the second argument contains something not a digit
                    if (only_digit(command_words[1]) == 0)
                        fprintf (stderr,"history: nonnumber: numeric argument required\n");
            
                    int which_comm = atoi(command_words[1]);
                    
                    //check if the number in the range
                    if (which_comm < 0)
                        fprintf(stderr,"histpry: %d: invalid option\n", which_comm);
                    else  if(which_comm > Nline)
                        fprintf(stderr,"history: %d: numeric argument required\n", which_comm);
                     
                    //goes back to nth newest command    
                    Nline -= which_comm;
                } 
                
                //then print from the old to new
                for(int i = 0; past[Nline + i] != NULL && i < 10;i++)
                    printf ("%d: %s\n",Nline + i,past[Nline + i]);    
                fclose(history); 
                
                //write a history command to the file
                comm_to_file(past_path, command_words);  
                
            //case for "!"   
            } else { 
                int which_comm;              
                //no second command, find the last line
                if (command_words[1] == NULL)             
                    which_comm = Nline - 1;                
                //or use atoi find the particular line
                else {
                    which_comm = atoi(command_words[1]);                                                       
                    //check if Nline is in the range
                    if (which_comm > Nline && which_comm < 0) 
                        fprintf(stderr,"the number is out of range\n");
                }
                printf ("%s\n",past[which_comm]);
                 //generate history commands and pass it in the function 
                char **past_comm = tokenize(past[which_comm], WORD_SEPARATORS, SPECIAL_CHARS);
                execute_command(past_comm, path, environ, past_path);
                free_tokens(past_comm); 
            }
            free_tokens(past);
        } else {    
            //normal case (without history and !)
            execute_command(command_words, path, environ, past_path);
        }
        free_tokens(command_words);   
    }
    free_tokens(path);
    return 0;
}


//
// Execute a command, and wait until it finishes.
//
//  * `words': a NULL-terminated array of words from the input command line
//  * `path': a NULL-terminated array of directories to search in
//  * `environment': a NULL-terminated array of environment variables
//
static void execute_command(char **words, char **path, char **environment, char *file) {
    assert(words != NULL);
    assert(path != NULL);
    assert(environment != NULL);

    char *program = words[0];

    if (program == NULL) {
        // nothing to do
        return;
    }

    if (strcmp(program, "exit") == 0) {
        do_exit(words);
        // do_exit will only return if there is an error
        return;
    }
    //generate new 2d array by globbing, I used the globbed command to execute 
    //but write original commands in the history file
    glob_t matches;
    glob(words[0], GLOB_NOCHECK|GLOB_TILDE, NULL, &matches);
    for(int i = 1; words[i] != NULL; i++)
        glob(words[i], GLOB_NOCHECK|GLOB_TILDE|GLOB_APPEND, NULL, &matches);
      
    //after keep appending, the new 2d array is generalized    
    char **new_words = matches.gl_pathv;
    
    //case for cd
    if (strcmp(new_words[0],"cd") == 0) {
        if (new_words[1] != NULL && chdir(new_words[1]) != 0) { 
            fprintf (stderr,"cd: %s: No such file or directory\n",new_words[1]);
        } else if (new_words[1] == NULL) {
            char *tmp = getenv("HOME");
            //change path to the home directory
            if (chdir(tmp) != 0)  
                perror("chdir");
            
        }
        comm_to_file(file, words);
        globfree(&matches);
        return;
        
    //case for pwd
    } else if (strcmp(new_words[0],"pwd") == 0) {
        char pathname[PATH_MAX];
        
        if (getcwd(pathname, sizeof pathname) == NULL) 
            perror("getcwd");
            
        printf ("current directory is '%s'\n", pathname);
        comm_to_file(file, words);   
        globfree(&matches);  
        return;
    }  

    pid_t pid = 0;
    int status;
    
    //if path is already contained in the words
    if (strrchr(new_words[0], '/') != NULL) {
        
        if (is_executable(program)) {
            posix_spawn(&pid, new_words[0], NULL, NULL, new_words, environment);
            waitpid(pid, &status,0);
            printf ("%s exit status = %d\n",new_words[0],WEXITSTATUS(status));
            
            //write to history file
            comm_to_file(file, words);
            globfree(&matches);
            return ;
        }
        fprintf (stderr, "%s: command not found\n",new_words[0]);
        
    //normal case
    } else {
        for(int i = 0; path[i] != NULL; i++) {
            int length = strlen(path[i]) + 2 + strlen(new_words[0]);
            char* x = malloc(length);
            
            //build the new path by command  and the path
            snprintf (x, length, "%s/%s", path[i], new_words[0]);
            if (is_executable(x)) {
                posix_spawn(&pid, x, NULL, NULL, new_words, environment);
                waitpid(pid, &status,0);
                printf ("%s exit status = %d\n",x,WEXITSTATUS(status));
                free(x);
                
                //write to history file
                comm_to_file(file, words);
                globfree(&matches);
                return ;    
            }
            free(x);
        }
        fprintf (stderr, "%s: command not found\n",new_words[0]);
    }
}



//check if a string only contains digit
static int only_digit(char *string) {
    for(int i = 0; string[i] != '\0'; i++)
        if (isdigit(string[i]) == 0) return 0;
    return 1;
}

//convert a file to 2d array of string, opening and closing during the function
static char **file_to_strings(char *where, int *line) {
    FILE *file = fopen(where,"a+");
    int c = fgetc(file), i = 1, j = 2, total = 1;
    char **product = NULL;
    //purpose for tmp is to save a single line and insert it into 2d array
    char *tmp = NULL;
    while (c != EOF) {
        //scan char by char when its not new line character
        if (c != '\n') {
            tmp = realloc(tmp, j);
            tmp[j-2] = c;
            j++;
        } else {
            //when a line is scaned, insert tmp into 2d array re-initialize the tmp
            tmp[j-2] = 0;
            product = realloc(product, i * sizeof (char *));
            product[i-1] = tmp;
            j = 2;
            tmp = NULL;
            i++;
        }
        total++;
        c = fgetc(file); 
    }
    //make last line be NULL for convienience
    product = realloc(product, i * sizeof (char *));
    product[i-1] = NULL;
    *line = i - 1;
    fclose(file);
    return product;
}

//append command in file line by line, opening and closing during the function
static void comm_to_file(char *file_name, char **comm) {
    FILE *file = fopen(file_name,"a+");
    for(int i = 0; comm[i] != NULL; i++) {
        fputs(comm[i],file);
    //not writing space for last word
        if (comm[i+1] != NULL)
            fputc(' ',file);
    }
    fputc('\n',file);
    fclose(file);
}

//
// Implement the `exit' shell built-in, which exits the shell.
//
// Synopsis: exit [exit-status]
// Examples:printf printf_lives_in_/usr/bin
//     % exit
//     % exit 1
//
static void do_exit(char **words) {
    int exit_status = 0;

    if (words[1] != NULL) {
        if (words[2] != NULL) {
            fprintf (stderr, "exit: too many arguments\n");
        } else {
            char *endptr;
            exit_status = (int)strtol(words[1], &endptr, 10);
            if (*endptr != '\0') {
                fprintf (stderr, "exit: %s: numeric argument required\n",words[1]);
            }
        }
    }
    exit(exit_status);
}


//
// Check whether this process can execute a file.
// Use this function when searching through the directories
// in the path for an executable file
//
static int is_executable(char *pathname) {
    struct stat s;
    return
        // does the file exist?
        stat(pathname, &s) == 0 &&
        // is the file a regular file?
        S_ISREG(s.st_mode) &&
        // can we execute it?
        faccessat(AT_FDCWD, pathname, X_OK, AT_EACCESS) == 0;
}


//
// Split a string 's' into pieces by any one of a set of separators.
//
// Returns an array of strings, with the last element being `NULL';
// The array itself, and the strings, are allocated with `malloc(3)';
// the provided `free_token' function can deallocate this.
//
static char **tokenize(char *s, char *separators, char *special_chars) {
    size_t n_tokens = 0;
    // malloc array guaranteed to be big enough
    char **tokens = malloc((strlen(s) + 1) * sizeof *tokens);


    while (*s != '\0') {
        // We are pointing at zero or more of any of the separators.
        // Skip leading instances of the separators.
        s += strspn(s, separators);

        // Now, `s' points at one or more characters we want to keep.
        // The number of non-separator characters is the token length.
        //
        // Trailing separators after the last token mean that, at this
        // point, we are looking at the end of the string, so:
        if (*s == '\0') {
            break;
        }

        size_t token_length = strcspn(s, separators);
        size_t token_length_without_special_chars = strcspn(s, special_chars);
        if (token_length_without_special_chars == 0) {
            token_length_without_special_chars = 1;
        }
        if (token_length_without_special_chars < token_length) {
            token_length = token_length_without_special_chars;
        }
        char *token = strndup(s, token_length);
        assert(token != NULL);
        s += token_length;

        // Add this token.
        tokens[n_tokens] = token;
        n_tokens++;
    }

    tokens[n_tokens] = NULL;
    // shrink array to correct size
    tokens = realloc(tokens, (n_tokens + 1) * sizeof *tokens);

    return tokens;
}

//
// Free an array of strings as returned by `tokenize'.
//
static void free_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
