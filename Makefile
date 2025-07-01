all: prod_cons

prod_cons: prod_cons.c buffer.c assert.c
	gcc -o $@ $^ -pthread

clean: prod_cons
	rm $<