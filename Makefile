#directories
IDIR = inc
ODIR = obj
SDIR = src
LDIR = libmx
#compiler settings
CC = gcc
CFLAGS = -std=c11
CCFLAGS = -std=c11 -g -Wall -Wextra -Werror -Wpedantic# -Og -g3 -fsanitize=address
FLAGS = $(CCFLAGS) -I $(IDIR) -I $(LDIR)/$(IDIR)
#dependencies
NAME = uls
LIB = libmx.a
#headers
DEPS := $(wildcard $(IDIR)/*.h)
#sources
SRCS := $(wildcard $(SDIR)/*.c)
#objects
_OBJS = $(SRCS:.c=.o)
OBJS = $(subst $(SDIR),$(ODIR),$(_OBJS))

#TARGETS
all: $(NAME)

#make library
$(LDIR)/$(LIB):
	@make -C $(LDIR)

#make objects
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $< -o $@


#make excecutable
$(NAME): $(OBJS) $(LDIR)/$(LIB)
	@$(CC) $(FLAGS) $^ -o $@


.PHONY: clean uninstall reinstall

#delete all files
uninstall: clean
	@rm -f $(NAME)
	@make $@ -C $(LDIR)

#remove all temp files
clean:
	@rm -rf $(ODIR)
	@make $@ -C $(LDIR)

#rebuild project
reinstall: uninstall all
