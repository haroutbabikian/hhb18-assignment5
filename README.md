In order to compile the files:

    ```bash
    gcc -o <output_file_name> <input_file_name.c> <additional_flags>
    ```
Replace `<output_file_name>` with the desired name for the compiled executable, `<input_file_name.c>` with the name of the .c file you want to compile, and `<additional_flags>` with any additional flags you want to pass to the compiler (e.g., `-pthread` for enabling pthread library).
Repeat this step for each C file you want to compile, changing the `<input_file_name.c>` and `<output_file_name>` accordingly.

Here's an example command to compile a file named `count_cache.c` with the `-pthread` flag and output the executable as `count_cache`:
`gcc -o count_cache count_cache.c -pthread`