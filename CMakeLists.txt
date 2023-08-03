cmake_minimum_required(VERSION 3.5)

project(cmd)

# Set the source file for your program
set(SOURCE_FILES main.c commands.c)

# Create an executable 
add_executable(cmd ${SOURCE_FILES})