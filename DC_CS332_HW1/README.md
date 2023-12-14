# Compiling & Running
  **To compile, run the following command**
  
    gcc hw1.c -o hw1
  **To Run, follow this format**
  
    ./hw1 [keywords] < [input_file]
    Where:
     - keywords is all the keywords to search for, separated by whitespace
        - Ex: a as the before
     - input_file is the name of the file to search in
        - Ex: input.txt
# How it Works
  Using a method called Lexical Analysis, it is possible to recognize a sequence of words (Separated by a delimiter).
  - For recognizing keywords in an entire file, we just repeat the process below for every line in the file.
  
  **The Process for lexical analysis flows as follows**
  1. Get a line to analyze.
  2. Starting at the beginning, get a character from the line.
  3. Add that character to a temporary string if it is not whitespace
  4. Move to the next character in the line
  5. Repeat steps 3&4 until you encounter a whitespace character
  6. Check to see if the current word (stored in the temporary string) matches the keyword
    a. If the current word matches the keyword, we run the code we want to run when we encounter a keyword.
       This could be incrementing a count variable, or tokenizing the word, etc.
  7. Clear out the temporary string, and move to the next character
  8. Repeat steps 3 through 7 until you reach the end of the line
  
