# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ncornacc <ncornacc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/03/19 13:31:45 by ncornacc      #+#    #+#                  #
#    Updated: 2024/04/10 10:52:29 by ncornacc      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo

CC		:=	gcc
HEADER	:=	philosophers.h
FLAGS	:=	-Wall -Werror -Wextra -g -fsanitize=thread

RM		:=	rm	-rf

############################SOURCES##########################

OBJ_DIR	:=	obj/
SRC_DIR	:=	src/

FILE	:=	main initialize loop free arguments misc monitor utils actions

SRC		:=	${addprefix ${SRC_DIR}, ${addsuffix .c, ${FILE}}}
OBJ		:=	${addprefix ${OBJ_DIR}, ${addsuffix .o, ${FILE}}}


#############################RULES############################

all: ${NAME}

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${HEADER}
	@mkdir -p ${OBJ_DIR}
	@${CC} ${FLAGS} -o $@ -c $< && printf "${YELLOW} Compiling: $(notdir $<) ${DEF_COLOR}"

${NAME}: ${OBJ}
	@${CC} ${FLAGS} ${OBJ} -o ${NAME}
	@echo "${GREEN} philosophers compiled!${DEF_COLOR}"

clean:
	${RM} ${OBJ_DIR}
	@echo "${MAGENTA} Object files cleaned!${DEF_COLOR}"

fclean: clean
	${RM}	${NAME}
	@echo  "${MAGENTA} executable/archive files cleaned!${DEF_COLOR}"

re:	fclean all
	@echo	"${GREEN} Cleaned and rebuild everything for so_long!${DEF_COLOR}:"

mem:
	memdetect.sh ${SRC} ${FLAGS} ${HEAD} ${1}

.PHONY:	re, all, clean, fclean, libs, mem

##############################################################
#############################COLORS###########################

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
