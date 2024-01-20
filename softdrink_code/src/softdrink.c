/* ****************************************************
* Author    : Rahul Singh 
* URL       : https://github.com/codecliff/softdrink
* License   : MIT 
* email     : codecliff@users.noreply.github.com
* Disclaimer: No warranties, stated or implied.   
* Description : 
*   This File is part of softdrink project
*   A personal attempt to create directory shortcuts 
*   for Gnome and Nautilus file browser 
*   (Acknowledgment: This project has heavily used LLMs 
*                    viz. Phind, Bard and ChatGPT )
* ****************************************************/


/* ***************************************************
0. Call this executable with argument being a file with following requisites:
    0.1) File is a plain text
    0.2) its name ends in the extension .jump
    0.3) its content is just a single line of text
    0.4) which is path to a directory you want to launch
        0.4.1) path preferably be absolute
    Note: We are not trimming the string.    
1. read argv , 
2. make sure it is path to an existing, valid  file
3. read the file, make sure it has only one line, return line
4. ensure that this line is a valid directory 
5. open that direcotry in nautilus for browsing
6. Done
*************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <libgen.h>
#include <wordexp.h>
#include "trimstr.h"
#include "appstrings.h"



void showErrorMessageBox(const char *errorMessage);
char* expand_tilde(const char* dir_path);



/* 
    get system specific constraints
*/
long get_max_path_length()
{
    // PATH_MAX might not be diefined, so query it
    long max_path_len = pathconf("/", _PC_PATH_MAX);
    if (max_path_len == -1)
    {
        max_path_len = 4096;
    }
    printf("ok...\n");
    return max_path_len;
}

#define MAX_LINE_LENGTH get_max_path_length()

/* 
    check that a string ends in .jump 
*/
int ends_with_jump(const char *mystring)
{
    /* Get the lengths of the string and substring */
    size_t string_length = strlen(mystring);
    size_t substring_length = strlen(".jump");

    /* Check if the string is long enough to contain the substring */
    if (string_length < substring_length)
    {
        return 0; // Not long enough
    }

    // Compare the last four characters, return 1 for match, 0 for mismatch.
    // Note: strcmp returns 0 for equlity

    return strcmp(mystring + string_length - substring_length, ".jump") == 0;
}

/* 
    Read a given file and if it contains a single line, return that line. 
    Else return NULL 
*/
char *readSingleLine(const char *filename)
{
    // Check if the path is not NULL
    if (filename == NULL)
    {
        showErrorMessageBox("Error: Filename is NULL\n");
        return NULL;
    }

    if (!ends_with_jump(filename))
    {
        showErrorMessageBox("Error: Bad extension\n Softdrink handles .jump files only");
        return NULL;
    }

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        showErrorMessageBox("Error opening input file \n");
        perror("Exact error is: ");
        return NULL;
    }

    // Read the first line from the file
    char line[MAX_LINE_LENGTH];

    if (fgets(line, MAX_LINE_LENGTH, file) == NULL)
    {
        showErrorMessageBox("Error reading from .jump file\n");
        fclose(file);
        return NULL;
    }

    // Remove newline character from the end of the line
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
    }

    //trim the line
    char *line2=  trimString(line);

    // Check if the line is empty
    if (strlen(line2) == 0)
    {
        showErrorMessageBox("Error: Empty line in .jump file!\n");
        fclose(file);
        return NULL;
    }

    // Check if there is more than one line in the file
    if (fgets(line2, MAX_LINE_LENGTH, file) != NULL)
    {
        showErrorMessageBox("Error: Multiple lines in .jump file!\n");
        fclose(file);
        return NULL;
    }

    // Close the file
    fclose(file);

    // Allocate memory for the string and copy the line
    char *result = strdup(line2);
    if (result == NULL)
    {
        showErrorMessageBox("Error allocating memory");
        perror("Error allocating memory");
        return NULL;
    }
    
    free(line2);

    return result;
}

/* 
    Convert relative paths to absolute
    @abspath_jump: .jump file location  
    @relpath:  content of .jump file, relative path w.r.t. its parent directory 
*/
char *processRelativePaths(const char *abspath_jump, const char *relpath_jump)
{
    
    
    // Find the parent directory of the absolute path
    char *parDir = strdup(abspath_jump);
    char *parentDir = dirname(parDir);

    long max_path_len = 4096; //get_max_path_length();
    printf("max_path_len %ld\n", max_path_len);

    // Combine parent directory and relative path to get absolute target path
    char absTargetPath[max_path_len];

    // printf("parentDir: %s\n",parentDir);
    if (realpath(parentDir, absTargetPath) == NULL)
    {
        perror("Error converting parent directory to absolute path");
        free(parDir);
        return NULL;
    }

    //trim file content 
    char *relpath = trimString(relpath_jump);

    // Append the relative path to the absolute target path
    if (relpath[0] != '/')
    {
        // If relpath is not an absolute path, append it to the absolute parent directory
        strcat(absTargetPath, "/");
        strcat(absTargetPath, relpath);
    }
    else
    {
        // If relpath is an absolute path, use it as is
        strncpy(absTargetPath, relpath, max_path_len - 1);
    }

    // Print if absTargetPath exists or not
    if (access(absTargetPath, F_OK) == 0)
    {
        printf("The absolute target path '%s' exists.\n", absTargetPath);
    }
    else
    {
        printf("The absolute target path '%s' does not exist.\n", absTargetPath);
    }

    // Free the allocated memory
    free(parDir);
    free(relpath);

    // Return the absolute target path
    return strdup(absTargetPath);
}

/* 
    Ensure that arg is a directory and launch it 
*/
int launchNautilus(const char *fpath)
{
    // Check if the path is not NULL
    if (fpath == NULL)
    {
        showErrorMessageBox("Error: Path is NULL");
        fprintf(stderr, "Error: Path is NULL\n");
        return EXIT_FAILURE;
    }

    printf("launching -%s\n", fpath);

    // Use stat to get information about the file/directory
    struct stat path_stat;
    if (stat(fpath, &path_stat) == -1)
    {
        showErrorMessageBox("Error getting directory. Does it exist?");
        perror("Error getting directory information");
        return EXIT_FAILURE;
    }

    // Check if the path corresponds to a directory
    if (!S_ISDIR(path_stat.st_mode))
    {
        showErrorMessageBox("Error: Not a directory!");
        fprintf(stderr, "Error: %s is not a directory\n", fpath);
        return EXIT_FAILURE;
    }

    // Check if the directory is readable
    if (!(path_stat.st_mode & S_IRUSR))
    {
        showErrorMessageBox("Directory not readable!");
        fprintf(stderr, "Error: Directory %s is not readable\n", fpath);
        return EXIT_FAILURE;
    }

    // Launch Nautilus using the system command with sh
    //using sh will allow spaces and special characters in file path
    char command[256];
    snprintf(command, sizeof(command), "sh -c 'nautilus \"%s\"'", fpath);
    if (system(command) == -1)
    {
        showErrorMessageBox("Error Launching File Browser!");
        perror("Error launching Nautilus");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* 
    Zenity based UI Message Delivery 
*/

void showErrorMessageBox(const char *errorMessage)
{
    char command[256];
    //print error
    fprintf(stderr, "%s \n", errorMessage);

    //gui error display
    snprintf(command, sizeof(command), "zenity --error --no-wrap --title=\"Softdrink Error!\" --text=\"%s\"", errorMessage);

    // Use system() to execute the command
    int result = system(command);

    // Check the result of the system() call
    if (result == -1)
    {
        fprintf(stderr, "Error: %s", errorMessage);
        perror("Error showing zenity messagebox");
        return;
    }
}

/* Expand paths starting with tilde */
char* expand_tilde(const char* dir_path) {
   wordexp_t exp_result;
   wordexp(dir_path, &exp_result, WRDE_UNDEF);

   // return  expanded path
   if (exp_result.we_wordc > 0) {
       return exp_result.we_wordv[0];
   }

   // else return original path
   return strdup(dir_path);
}

/********************** main  **********************/
int main(int argc, char *argv[])
{

    // Prevent invokation by root user
    if (getuid() == 0) {
       printf("This program cannot be  run by root user!\n");
       return EXIT_FAILURE;
    }

    // Check if the correct number of command line arguments is provided
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        showErrorMessageBox("Not to be executed directly!\n \
         For help, try 'softdrink -h' in console\n");
        return EXIT_FAILURE;
    }


    //handle version or help args 

    int opt;

    while ((opt = getopt(argc, argv, "vh")) != -1) {
        switch (opt) {
            case 'v':
                printf("Version: %s\n", versionStr);
                exit(0);
            case 'h':
                printf("%s", helpStr);
                exit(0);
            default:
                fprintf(stderr, "Unknown option: %c\n", opt);
                fprintf(stderr, "%s", helpStr);
                exit(1);
        }
    }                    

    

    char *path_arg = strdup(argv[1]);
    //printf("path_arg: %s\n", path_arg);
    

    // read single line
    char *line = readSingleLine(argv[1]);
    if (line != NULL)
    {
        printf("Read line: %s\n", line);
    }
    else
    {   
        free(path_arg);
        return EXIT_FAILURE;
    }

    //if line is relative path, convert to absolute
    char *line2 = NULL;
    printf("path_arg= %s\n", path_arg);
    if (line[0] == '/')
    {
        line2 = strdup(line);
    }
    else if (line[0] == '~')
    {
        line2 = expand_tilde(line);
    }
    else
    {
        line2 = processRelativePaths(path_arg, line);
    }

    if (line2 == NULL)
    {
        showErrorMessageBox("Error with relative path!");
        free(path_arg);
        return EXIT_FAILURE;
    }

    //ensure it is a directory path and launch it
    launchNautilus(line2);

    free(line);
    free(line2);
    free(path_arg);

    return EXIT_SUCCESS;
}
