
BIN_DIR		=	bin
SRC_DIR		=	src
INC_DIR		=	inc
SUBMODULE_DIR	=	submodules

RM	=	rm
AR	=	ar
AS	=	nasm
CC	=	cc
CXX	=	c++
LD	=	ld

RMFLAGS		:=	-rf
ARFLAGS		:=	rcs
ASFLAGS		:=	-felf64
CCFLAGS		:=	-Wall -Wextra -Werror -MMD
CXXFLAGS	:=	-Wall -Wextra -Werror -MMD
LDFLAGS		:=	

LIBFT_DIR	=	$(SUBMODULE_DIR)/libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SUBMODULE	=	$(LIBFT_DIR)
LIBS		=	$(LIBFT)

CINC		:=	-I$(BIN_DIR)
CINC		+=	-I$(INC_DIR)
CINC		+=	-I$(SRC_DIR)
CINC		+=	-I$(LIBFT_DIR)/inc
CXXFLAGS	+=	$(CINC)
CCFLAGS		+=	$(CINC)

CDEBUG		:=	-g
CXXFLAGS	+=	$(CDEBUG)
CCFLAGS		+=	$(CDEBUG)

NAME	=	ft_ls

OBJ	:=	main.o		\
				\
		parse_args.o	\
				\
		print_pathv.o	\
				\
		print_file.o	\
		print_dir.o	\
				\
		ft_lstsort.o	\
		ft_lst_to_arr.o	\
		free_arr.o	\
		arr_len.o	\
		arr_map.o	\

OBJ		:=	$(addprefix $(BIN_DIR)/, $(OBJ))

DEP		:=	$(OBJ:.o=.d)

VPATH	+=	$(SRC_DIR)
VPATH	+=	:$(SRC_DIR)/utils

all:		$(BIN_DIR) $(NAME) Makefile

$(NAME):	$(LIBS) $(OBJ) Makefile
	$(CC) $(CCFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(BIN_DIR)/%.o:	%.c Makefile
	$(CC) $(CCFLAGS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $@

$(LIBFT):
	@if [ ! -f $(LIBFT_DIR)/Makefile ]; then \
		git submodule init ; \
		git submodule update ; \
	fi
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(RMFLAGS) $(BIN_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean tclean
	$(RM) $(RMFLAGS) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

test:
	@bash test.sh

tclean:
	$(RM) $(RMFLAGS) test_diff

-include $(DEP)

.PHONY:	all clean fclean re test tclean
