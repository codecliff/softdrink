#!/bin/bash

# Place this file in  Nautilus scripts folder if you want context-menu ease
# ~/.local/share/nautilus/scripts/

# A nautilus script to create a jump file pointing to current directory
# you can later copy this jump file to anywhere and use as shortcut to this directory
# https://github.com/codecliff/softdrink
# Copyright : Rahul Singh (Acknowledgment- Phind)
# Disclaimer: No warranties, stated or implied.   


# nautilus scripts expose  paths of all selected files
file_paths=$NAUTILUS_SCRIPT_SELECTED_FILE_PATHS

# get first such file : 

# Split  paths into  array, set internal field separator to a newline character
IFS=$'\n' read -rd '' -a paths <<<"$file_paths"

# Get the path of the first selected file
first_file=${paths[0]}


# Get  parent directory
parent_dir=$(dirname "$first_file")


# Create a .jump file there:
output_file="$parent_dir/$(basename "$parent_dir").jump"

# Check  write access 
if [ ! -w "$parent_dir" ]; then
    zenity --error --text="Error: No write access to the parent directory."
    exit 1
fi

# write parent path to output file 
echo "$parent_dir" > "$output_file"

zenity --info --no-wrap --text="File created: $output_file"
