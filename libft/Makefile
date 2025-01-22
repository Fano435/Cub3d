#Nom de la bibliotheque
NAME = libft.a

#ficher d'en-tete
HEAD = libft.h

#Compilateur et option de compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra

red             = /bin/echo -e "\x1b[31m\#\# $1\x1b[0m"
green           = /bin/echo -e "\x1b[32m\#\# $1\x1b[0m"
yellow          = /bin/echo -e "\x1b[33m\#\# $1\x1b[0m"
blue            = /bin/echo -e "\x1b[34m\#\# $1\x1b[0m"
purple          = /bin/echo -e "\x1b[35m\#\# $1\x1b[0m"

#listes des fichier sources
SRC = ft_atoi.c \
	ft_bzero.c \
	ft_strlen.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_memset.c \
	ft_strdup.c \
	ft_strlcpy.c\
       	ft_strlen.c \
	ft_strncmp.c\
       	ft_tolower.c\
       	ft_toupper.c\
       	ft_memcpy.c\
       	ft_memmove.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_calloc.c\
	ft_itoa.c\
	ft_putstr_fd.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_substr.c\
	ft_strnstr.c\
	ft_striteri.c\
	ft_strmapi.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_strlcat.c\
	ft_split.c\
	ft_lstdelone_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstmap_bonus.c \
	ft_strcmp.c \
	ft_strcpy.c \

SRCBONUS = ft_lstnew_bonus.c\
	   ft_lstadd_front_bonus.c\
	   ft_lstsize_bonus.c\
	   ft_lstlast_bonus.c\
	   ft_lstadd_back_bonus.c\
	   ft_lstdelone_bonus.c

# Liste des fichiers objets (générés automatiquement à partir des fichiers sources)
OBJ = $(SRC:.c=.o)

OBJBONUS = $(SRCBONUS:.c=.o)

# Options pour l'archiveur
AR = ar		#archiver
ARFLAGS = -rc	#-r inserer les fichier dans l'archive /   -c cree larchive si elle nexiste pas

# Création de la bibliothèque
all: $(NAME)

# Cible par défaut
$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $(NAME) $^
	@$(call blue,"✅ $< compiled!")

# Règle pour compiler les fichiers objets
%.o: %.c
	@$(CC) -c $< -o $@
	@$(call blue,"✅ $< compiled!")

# Suppression des fichiers objets
clean :
	@rm -f $(OBJ)

# Suppression des fichiers objets et de la bibliothèque
fclean : clean
	@rm  -f $(NAME)

# Reconstruction complète
re :	fclean all

bonus : $(OBJ) $(OBJBONUS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ) $(OBJBONUS)

# Indiquer à make que ces cibles ne sont pas des fichiers
.PHONY : all bonus clean fclean re
