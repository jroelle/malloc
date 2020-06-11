export LD_LIBRARY_PATH=.
gcc -I inc/ main.c -L. -lft_malloc
if [ "$(uname)" == "Darwin" ]; then
    ARG=-l
else
	ARG=-v
fi
\time $ARG ./a.out
rm -f a.out
