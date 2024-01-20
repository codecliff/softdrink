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

// Version and help args
    const char *versionStr = "0.9";
    const char *helpStr = "This applicaiton processes a .jump file \n\
    and opens the directory mentioned in it \n\
    Args availabe on console : \n\
        -h, -v, /path/to/a/valid/.jump/file \n\n\
    A jump file is like a directory shortcut.\n\
     In essence, it is a one line text file \n\
     containing path to a target directory \n\
     and named with extension .jump  \n\
     Example:\n\
     echo ~/Documents > myname.jump \n\
     Double-click on myname.jump to open ~/Documents \n\n "   ;
