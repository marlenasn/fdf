NAME				= fdf


CC				= gcc
CFLAGS				= -Wall -Werror -Wextra 
RM				= rm -f

# Source Files
SOURCES =\
	ft_strlcpy.c ft_split.c get_next_line_utils.c get_next_line.c parse_to_array.c main.c 


OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lmlx -lX11 -lXext -o fdf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug:
	printf "$(OBJECTS)" 

.PHONY: re
