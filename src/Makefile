OBJS = simpleUI.o tokenizer.o history.o

all: out

out: $(OBJS)

	cc -o out $(OBJS)

$(OBJS): tokenizer.h history.h

clean:

	-rm *.o
	-rm *~
	-rm out

run: out

	./out
