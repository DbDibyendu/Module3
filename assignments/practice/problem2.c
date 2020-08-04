/** @file problem2.c
 *  @brief Barcode reader
 *  
 *  Reading the barcode and printing it
 *  
 *  @author Dibyendu 
 *  @bug I didn't find any  
 */

/*
 *#####################################################################
 *  Initialization block
 *  ---------------------
 *  This block contains initialization code for this particular file.
 *  It typically contains Includes, constants or global variables used
 *  throughout the file.
 *#####################################################################
 */

/* --- Standard Includes --- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
/* --- Project Includes --- */

/* Global Variables */
 char api_key[100]= "";                      // https://upcdatabase.org/
 char ss[100]="";

/************************** 
 * Error-handling functions
 **************************/
/* $begin errorfuns */
/* $begin unixerror */
void unix_error(char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
/* $end unixerror */

void posix_error(int code, char *msg) /* posix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

void app_error(char *msg) /* application error */
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}
/* $end errorfuns */

/******************************************
 * Wrappers for the Standard I/O functions.
 ******************************************/
void Fclose(FILE *fp) 
{
    if (fclose(fp) != 0)
    unix_error((char*)"Fclose error");
}

FILE *Fdopen(int fd, const char *type) 
{
    FILE *fp;

    if ((fp = fdopen(fd, type)) == NULL)
    unix_error((char*)"Fdopen error");

    return fp;
}

char *Fgets(char *ptr, int n, FILE *stream) 
{
    char *rptr;

    if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream))
    app_error((char*)"Fgets error");

    return rptr;
}

FILE *Fopen(const char *filename, const char *mode) 
{
    FILE *fp;

    if ((fp = fopen(filename, mode)) == NULL)
    unix_error((char*)"Fopen error");

    return fp;
}

void Fputs(const char *ptr, FILE *stream) 
{
    if (fputs(ptr, stream) == EOF)
    unix_error((char*)"Fputs error");
}

size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t n;

    if (((n = fread(ptr, size, nmemb, stream)) < nmemb) && ferror(stream)) 
    unix_error((char*)"Fread error");
    return n;
}

void Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    if (fwrite(ptr, size, nmemb, stream) < nmemb)
    unix_error((char*)"Fwrite error");
}


/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */

/** 
 *  @brief Barcode Reader
 *  
 *  Full description of the function
 *
 *  @return List all Function returns 
 */

  char *barcode_reader(){
      char hid[52][2] = { 4,'a', 5, 'b', 6, 'c', 7, 'd', 8, 'e', 9, 'f', 10, 'g', 11, 'h', 12, 'i', 13, 'j', 14, 'k', 15, 'l', 16, 'm',
           17, 'n', 18, 'o', 19, 'p', 20, 'q', 21, 'r', 22, 's', 23, 't', 24, 'u', 25, 'v', 26, 'w', 27, 'x', 28, 'y',
           29, 'z', 30, '1', 31, '2', 32, '3', 33, '4', 34, '5', 35, '6', 36, '7', 37, '8', 38, '9', 39, '0', 44, ' ',
           45, '-', 46, '=', 47, '[', 48, ']', 49, '\\', 51, ';', 52, '\'', 53, '~', 54, ',', 55, '.', 56, '/'};

      char  hid2[52][2] = {4, 'A', 5,'B', 6,'C', 7 ,'D', 8, 'E', 9, 'F', 10, 'G', 11, 'H', 12, 'I', 13, 'J', 14, 'K', 15, 'L', 16, 'M',
            17, 'N', 18, 'O', 19, 'P', 20, 'Q', 21, 'R', 22, 'S', 23, 'T', 24, 'U', 25, 'V', 26, 'W', 27, 'X', 28, 'Y',
            29, 'Z', 30, '!', 31, '@', 32, '#', 33, '$', 34, '%', 35, '^', 36, '&', 37, '*', 38, '(', 39, ')', 44, ' ',
            45, '_', 46, '+', 47, '{', 48, '}', 49, '|', 51, ',', 52, '"', 53, '~', 54, '<', 55, '>', 56, '?'};
        
        FILE *fp= Fopen("/dev/hidraw0","rb");
        bool shift = false;
        bool done = false;
        while(!done){
            // Get character from the HID
            char buffer[100];
            Fgets(buffer,8,fp);
            int l=strlen(buffer);
            for(int i=0;i<l;i++){
                if(buffer[i]>0){
                    // 40 is carriage return which signifies
                    // we are done looking for characters
                    if(buffer[i]==40){
                        done =true;
                        break;
                    }
                    // If we are shifted then we have to 
                    // use the hid2 characters.
                    if (shift){
                        // If it is a '2' then it is the shift key
                        if(buffer[i]==2){
                            shift = true;
                        }
                        else
                        {
                            strcat(ss,hid2[buffer[i]][1]);
                            shift = false;
                        }
                    }
                    // if we are not shifted then use   
                    // the hid characters

                    else{

                        // if it is a '2 then it is the shift key      
                        if(buffer[i]==2){
                            shift =true;
                        }
                        // if not 2 then lookup in the map
                        else
                        {
                            strcat(ss,hid[buffer[i]][1]);
                        }

                        
                    }      
                }
            }
        }
    return ss;
}
/** 
 *  @brief Barcode Reader
 *  
 *  Full description of the function
 *
 *  @return List all Function returns 
 */

void UPC_Lookup(char *api_key,char *upc){

}

/** 
 *  @brief Description on main
 *  
 *  Full description of the function
 *
 *  @return List all Function returns 
 */

int main (void)
{
      char buffer[100]="dibyendu";
      strcpy(buffer,barcode_reader());
      int l=strlen(buffer);
            for(int i=0;i<l;i++){
                printf("%c",buffer[i]);
            }
              for(int i=0;i<l;i++){
                if(buffer[i]>0){
                    printf("%d ",buffer[i]);
                    
                }

            }


        /*Make sure you comment every line */
        return 0;
        
}
