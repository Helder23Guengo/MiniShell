cc -g *.c -lreadline ;
valgrind --leak-check=full ./a.out ;
