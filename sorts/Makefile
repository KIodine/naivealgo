AR := ar
ARFLAGS := rcs

CC := cc
CFLAGS := -Wall -Wextra
WARNS := -Wno-unused-but-set-variable

VG := valgrind
VFLAG := --leak-check=full --show-leak-kinds=all --verbose

# TODO: Change this makefile to adapt to `libsort`!

# TODO: conditional debug
ifdef DEBUG
	CFLAGS += -g -O0
else
	CFLAGS += -O2 -DNDEBUG $(WARNS)
endif

PROJ_NAME = sorts
# TODO: more complete project layout.
INCDIR = include src
SRCDIR = src
TSTDIR = test
OBJDIR = obj
LIBDIR = lib
BINDIR = bin

CFLAGS += $(addprefix -I,$(INCDIR))


SRCNAMES := shuffle.c bubble.c selection.c insertion.c \
	# merge.c quicksort.c
SRCFILES := $(addprefix $(SRCDIR)/,$(SRCNAMES))
INCNAMES := sorts.h # Currently not used.
INCFILES := $(addprefix $(INCDIR)/,$(INCNAMES))
# > For each test generate a binary with same name?
TSTNAMES := sort-test.c
TSTFILES := $(addprefix $(TSTDIR)/,$(TSTNAMES))

# > Add `SHAREDDST` `STATICDST` `TSTDST`?
OBJDST = $(addprefix $(OBJDIR)/,$(SRCNAMES:.c=.o))
TSTDST = $(addprefix $(OBJDIR)/,$(TSTNAMES:.c=.o))

.PHONY: all static shared testbin runtest runcheck clean clean_all


# --- build rules.
# > How to make dirs once and only once?
# > Order-only prerequisites: rebuild won't propagate?
init: | mk_dirs
mk_dirs: $(OBJDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR) $(LIBDIR) $(BINDIR)

# > Make sure OBJDIR is order-only so make won't "rebuild" it everytime.
# > Static pattern rule.
$(OBJDST): $(OBJDIR)/%.o: $(SRCDIR)/%.c |$(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TSTDST): $(OBJDIR)/%.o: $(TSTDIR)/%.c |$(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# TODO: build test objects separately.
$(LIBDIR)/lib$(PROJ_NAME).a: $(OBJDST)
	$(AR) $(ARFLAGS) $@ $(OBJDST)
static: $(LIBDIR)/lib$(PROJ_NAME).a

$(LIBDIR)/lib$(PROJ_NAME).so: $(OBJDST)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJDST)
# > Target-specific variable.
shared: CFLAGS += -fPIC
shared: $(LIBDIR)/lib$(PROJ_NAME).so
# > !phony targets always need update.

$(BINDIR)/$(PROJ_NAME)-test: $(LIBDIR)/lib$(PROJ_NAME).so $(TSTDST)
	$(CC) $(CFLAGS) -o $@ \
	-L$(LIBDIR) -Wl,-rpath,$(LIBDIR) $(TSTDST) -l$(PROJ_NAME) 
testbin: $(BINDIR)/$(PROJ_NAME)-test

# --- production rules.
all: static shared testbin

runtest: testbin
	./$(BINDIR)/$(PROJ_NAME)-test

runcheck: testbin
	$(VG) $(VFLAG) ./$(BINDIR)/$(PROJ_NAME)-test

clean:
	rm -f $(OBJDIR)/*

clean_all: clean
	rm -f $(BINDIR)/* $(LIBDIR)/*

# --- header dependencies, use `gcc -MM -I<incdir> <src>` to generate.
gen_deplist:
	$(CC) -MM $(addprefix -I,$(INCDIR)) $(SRCDIR)/*.c $(TSTDIR)/*.c

# --- DO NOT MODIFY MANUALLY ---
bubble.o: src/bubble.c include/sorts.h src/routines.h
#insertion.o: src/insertion.c include/sorts.h src/routines.h
#merge.o: src/merge.c
#quicksort.o: src/quicksort.c
shuffle.o: src/shuffle.c include/sorts.h src/routines.h
sort-test.o: test/sort-test.c include/sorts.h
