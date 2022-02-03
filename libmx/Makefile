#directories
IDIR = inc
ODIR = obj
SDIR = src
#compiler settings
CC=clang
CFLAGS=-I $(IDIR)
CCFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I $(IDIR)
#dependencies
NAME = libmx.a
TEST = test
#headers
_DEPS = libmx.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#sources
SRCS := $(wildcard $(SDIR)/mx_*.c)
#objects
_OBJS = $(SRCS:.c=.o)
OBJS = $(subst $(SDIR),$(ODIR),$(_OBJS))

all: $(NAME)

#make objects
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@mkdir -p obj
	@$(CC) -c -o $@ $< $(CCFLAGS)
#make library
$(NAME): $(OBJS)
	@ar -rc $@ $^
#executable for tests
$(TEST): $(NAME)
	@$(CC) $(CCFLAGS) -Wno-nonnull $(SDIR)/$(TEST).c $< -o $@ 

.PHONY: clean uninstall reinstall
#delete all files
uninstall: clean
	@rm -f $(NAME) $(TEST)
	@rm -f *.a
#remove all temporary files
clean:
	@rm -rf $(ODIR)
#rebuild project
reinstall: uninstall all