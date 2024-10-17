RUN = g++ -Wall -Werror -Wextra -O2 --pedantic -std=c++17 -g
ifeq ($(shell uname),Linux)
	OS = -lm -lrt -lpthread -lsubunit
else
	OS = -lm -lpthread
endif
all:	clean uninstall install
gamebox.a:	gamebox.o
	ar rcs gamebox.a *.o
	ranlib gamebox.a
gamebox.o:	*.cpp *.h
	$(RUN) *.cpp -cpp
clean:
	rm -rf *.gcda *.gcno *.o *.info *.a *.tar.gz docs/html docs/latex report
gamebox_install.o:	*.cpp *.h
install:
	 mkdir Tetris_and_Snake && mkdir tmp && install *.cpp *.h *.pro *.pro.* Tetris_and_Snake
	 echo "" > tmp/Makefile && cp -rf Makefile tmp/Makefile
	 qmake -o Makefile Tetris_and_Snake/gamebox.pro && make
	 mv ./gamebox Tetris_and_Snake && cp -rf tmp/Makefile Makefile
	 rm -rf tmp && ./Tetris_and_Snake/gamebox
uninstall:	clean
	rm -rf Tetris_and_Snake .qmake.* *.txt
dist:
	tar czvf Teris_Snake.tar.gz --ignore-failed-read *.cpp *.h *.pro.* *.pro Makefile readme.md
dvi:
	$(shell which firefox || which xdg-open || which open || which x-www-browser) docs/html/index.html
