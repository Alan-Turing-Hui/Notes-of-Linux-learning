# Treasure Trove of Linux

## The `exec` family of functions

> The `exec` family of functions in C is used to execute a new program, *replacing the current process image with a new process image*. They are commonly used after a `fork()` to replace the child process's image with a new program.

1. **`execl`**
   - **Prototype:**
     ```c
     int execl(const char *path, const char *arg0, ..., NULL);
     ```
   - **Parameters:**
     - `path`: Path to the executable file.
     - `arg0`: The first argument (usually the name of the program).
     - Subsequent arguments (`arg1`, `arg2`, ..., `NULL`): Arguments to the program, ending with `NULL`.
   - **Return Value:** Returns `-1` on error; does not return on success (the process image is replaced).
   
   -**Example:**
    ```c
    else if (pid == 0) {
        // The child process gets a new process image to execute "ls -l" command
        if (execl("/bin/ls", "ls", "-l", NULL) == -1) {
            perror("Execl failed");
            return 2;
        }
    }
    ```
