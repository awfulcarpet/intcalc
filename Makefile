WARNING = -Wall -Wextra -Wpedantic -Wno-unused-result -Wno-all
CFLAGS = -std=c99 -O0 $(WARNING) -pipe -ggdb -Iinclude -I/usr/local/include
LDLIBS = -lraylib -lGL -lm -lX11 -lpthread -ldl -lrt
EMCCFLAGS = lib/libraylib.a -s USE_GLFW=3 --shell-file minshell.html -s ASYNCIFY
PLATFORM ?= PLATFORM_DESKTOP

ifeq ($(PLATFORM),PLATFORM_WEB)
	CC=emcc
	LDLIBS = $(EMCCFLAGS)
	EXT = .html
endif

LDFLAGS = #-static
PREFIX = /usr/local/bin
NAME = intcalc
OUTDIR = .build
OBJ = \
      $(OUTDIR)/main.o \
      $(OUTDIR)/inputbox.o \
      $(OUTDIR)/equation.o \
      $(OUTDIR)/graph.o \

all: $(NAME)

debug:
	tmux new-window "gdbserver :12345 $(OUTDIR)/$(NAME)"
	tmux selectw -t 1
	~/opt/gf/gf2 -x debug.gdb -c core

checkleak:
	valgrind --leak-check=full --show-leak-kinds=all --log-file=log $(OUTDIR)/$(NAME)

run: $(NAME)
	$(OUTDIR)/$(NAME)


$(OUTDIR)/%.o: src/%.c
	@mkdir -p $(OUTDIR)
	$(CC) -c $(CFLAGS) -o $@ $<


$(NAME): $(OBJ)
	@echo "linking"
	@$(CC) -o $(OUTDIR)/$@$(EXT) $^ $(LDLIBS) $(LDFLAGS)

release: $(NAME)
	strip $(OUTDIR)/$(NAME)

web-release: clean $(NAME)
	@rm -rf pub index.html
	@mkdir -p pub
	mv -f .build/$(NAME).* pub/
	sed "s/$(NAME).js/pub\/$(NAME).js/g" pub/$(NAME).html > index.html

install: $(release)
	cp .build/$(NAME) $(PREFIX)/$(NAME)

uninstall:
	rm $(PREFIX)/$(NAME)

clean:
	rm -rf .build/ log core
