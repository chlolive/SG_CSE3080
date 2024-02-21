CC=gcc
target1=hw1_naive 
target2=hw1_kmp
object1=hw1_naive.o 
object2=hw1_kmp.o

$(target1) $(target2) : $(object1) $(object2)
	$(CC) -o $(target1) $(object1)
	$(CC) -o $(target2) $(object2)

%.o : %.c
	$(CC) -c -o $@ $<

.PHONY : clean
clean :
	rm $(target1) $(target2) $(object1) $(object2)
