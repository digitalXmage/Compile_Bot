# Dev_Buddy prototype.1
A Bot which automatically compiles your Programs for you. Launch the bot in your working environment and provide the compilation script for the project. So whenever you Write any changes, such as Writing to file in Vim, the bot will automatically compile the code for you.

# Start
       ./bot <compile_script.sh>
       
   
# Terminate
        ./bot -k
        
# If compile.sh script has been updated
        ./bot -k
        ./bot <compile_script.sh>
        
        
# Misc
call THe bot program in the directory your dev working directory is, and provide the compile.sh script so the bot can automatically compile the code for you
      
      
# Todo
1. Clean up code, annotate , seperate .c .h files
2. Ability to recheck compile.sh script for changes, so no need to kill and restart the program if the compile.sh scirpt has been updated
3. Create a logging function to log output to a textfile, as the bot is a daemon process
4. Allow user's to specify what language they are writing in, at the moment only works with .C files
5. ALlow the option to provide makeFiles instead of a bash compilation script
6. Get rid of global data structures!!! This is only a first quick prototype.
