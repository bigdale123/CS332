# Compiling & Running
## Compiling
- To compile, run the following command:

        make

- To run, use the following command:

        ./hw2 [-S] [-s <file_size>] [-f <pattern>] <abs_path>

# Optional Flags Explained
All the flags used with this program are completely optional, and hw2 can be run independently. Like so:

        ./hw2
- - -
- `-S` flag displays file size next to each file name when printing the file tree.
    - Note that directories will all have the same size of 4KB.
- `-s <size>` flag only displays files that have a size equal or greater to the provided size, `<size>`.
- `-f <name>` flag only displays files whose filename contains the substring provided, `<name>`.
