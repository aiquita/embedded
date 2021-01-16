# Steps to recreate

1. Compile esterel
    ```sh
    esterel trivial.strl
    ```
2. Compile Program
    ```sh
    gcc main.c trivial.c -o triv.o
    ```
3. Run
    ```
    ./triv.o
    ```
Should output Print 5 times ca. every Second.