NAME = bomberman

CC = g++

## ========================================================================== ##
SRC	= main.cpp \
      src/Map/Map.cpp \
      src/Blocks/ABlock.cpp \
      src/GUI/EventReceiver.cpp \
      src/APlayers/APlayers.cpp \
      src/Characters/Mario/Mario.cpp \
      src/Characters/Luigi/Luigi.cpp \
      src/Characters/Yoshi/Yoshi.cpp \
      src/Characters/Wario/Wario.cpp \
      src/Properties/Properties.cpp \
      src/Bomb/Bomb.cpp \
      src/GUI/MainMenu.cpp \
      src/Window/Window.cpp \
      src/PowerUp/APowerUp.cpp \
      src/PowerUp/Speed.cpp \
      src/PowerUp/Stock.cpp \
      src/PowerUp/Power.cpp \
      src/GUI/Settings.cpp \
      src/GUI/MenuButton.cpp \
      src/GUI/Credits.cpp \
      src/GUI/SelectingEvent.cpp \
      src/splashscreen/Splash.cpp \
      src/GUI/InGameMenu.cpp \
      src/Game/Game.cpp \
      src/Exception/Error.cpp \
    	src/GUI/LoadGame.cpp \
      src/AI/AAi.cpp \

## ========================================================================== ##
OBJ	=	$(SRC:.cpp=.o)

CFLAGS = -D_GNU_SOURCE -W -Werror -Wall -Wextra -std=c++17 -lsfml-system -lsfml-audio -lIrrlicht

## ========================================================================== ##
all:	$(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)


## ========================================================================== ##
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f *~
	@rm -f $(NAME)

re: fclean all

.PHONY: all rc clean fclean re

## ========================================================================== ##

%.o:	%.c
	@gcc $(CFLAGS) -o $@ -c $<

## ========================================================================== ##
