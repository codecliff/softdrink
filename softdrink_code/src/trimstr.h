/* ****************************************************
* Author    : Rahul Singh 
* URL       : https://github.com/codecliff/softdrink
* License   : LGPL 
* email     : codecliff@users.noreply.github.com
* Disclaimer: No warranties, stated or implied.   
* Description : 
*   This File is part of softdrink project
*   A personal attempt to create directory shortcuts 
*   for Gnome and Nautilus file browser 
*   (Acknowledgment: This project has heavily used LLMs 
*                    viz. Phind, Bard and ChatGPT )
* ****************************************************/

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// a C implementation of strtrim() 
char* trimString(const char *strin) {
    
    char* str;
    str = strdup(strin);  
   
   // Trim leading spaces
   while (isspace((unsigned char)str[0]))
       memmove(str, str + 1, strlen(str));  

   // Trim trailing spaces
   while (isspace((unsigned char)str[strlen(str) - 1]))
       str[strlen(str) - 1] = '\0';
    
   //fprintf(stderr, "trimmed: |%s|\n", str);  
   return str; 
}


