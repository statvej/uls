IDIR = inc
ODIR = obj
SDIR = src
LDIR = libmx
#compiler settings
CC = clang
CFLAGS = -std=c11 -g -Og -g3 -fsanitize=address
CCFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
FLAGS = $(CFLAGS) -I $(IDIR) -I $(LDIR)/$(IDIR)
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
	@printf "\33[2KCompiling \33[0;32m$<\33[m\n"
	@$(CC) $(FLAGS) -c $< -o $@


#make excecutable
$(NAME): $(OBJS) $(LDIR)/$(LIB)
	@$(CC) $(FLAGS) $^ -o $@
	@printf "\r\33[2KExcecutable for \33[0;32m$@\33[m done!\n"
	@printf "Usage: ./$@ [filename]\n"

.PHONY: clean uninstall reinstall

#delete all files
uninstall: clean
	@printf "\r\33[2K\33[0;33mUninstalling $(NAME)...\33[m\n"
	@rm -f $(NAME)
	@make $@ -C $(LDIR)

#remove all temp files
clean:
	@rm -rf $(ODIR)
	@printf "\r\33[2K\33[0;33mRemoving temporary $(NAME) files...\33[m\n"
	@make $@ -C $(LDIR)

#rebuild project
reinstall: uninstall all