gcc -I inc/ main.c -L. -lft_malloc
LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./a.out
rm -f a.out
