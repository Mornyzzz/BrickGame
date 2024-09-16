CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wswitch -Wunused -std=c++17
TFLAGS = $(shell pkg-config --libs gtest)
SOURCE_DEC = tests/test.cpp brick_game/brickgame.cpp brick_game/snake/*.cpp
TARGET := BrickGamev2

ifeq ($(shell uname), Linux)
	TST_LIBS := -lgtest -lm
	LSTDC := -lstdc++ --coverage
	OPEN_CMD := xdg-open
endif

all: clean install

tests: clean
	@echo "┏=========================================┓"
	@echo "┃                 Tests                   ┃"
	@echo "┗=========================================┛"
	@$(CC) $(CFLAGS) $(SOURCE_DEC) $(TFLAGS) -o test $(TST_LIBS) $(LSTDC) \
	-lcheck $(shell pkg-config --cflags --libs check) \
	$(TST_LIBS) --coverage
	@./test

cli_game:
	@gcc brick_game/**/*.cpp gui/cli/cli.cpp brick_game/brickgame.cpp -lncurses -lstdc++ -o cli.exe
	@./cli.exe

install:
	@echo "Start installation"
	@mkdir -p ../build
	@cd gui/desktop && qmake && make && make clean && rm -rf Makefile && mv BrickGameQt ../../../build/$(TARGET).app
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃              build folder.              ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf ~/Desktop/BrickGame.exe ../build
	@echo "Uninstall completed successfully"

dvi:
	@open ../README_RUS.md

dist: install
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v1.0.tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md
	@echo "The build was successfully archived"

clean:
	@echo "Deleting unnecessary files..."
	@rm -rf *.gcno *.o *.h.gch *.a *.dSYM **/*.dSYM *.log **/*.log report matrix_tests.info test_report.txt test *.gcno \
    *.info test_output report *.exe *.gcda **/**/*.o **/**/ui_mainwindow.h **/**/Makefile **/**/.qmake.stash

gcov_report: tests
	@echo "┏=========================================┓"
	@echo "┃               HTML Report               ┃"
	@echo "┗=========================================┛"
	@lcov --no-external -t "test" -o test.info -c -d .
	@lcov --extract test.info "*/brickgame.cpp" "*/snake/*.cpp" -o filtered_test.info
	@genhtml -o test_output filtered_test.info

style_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -n **/*.h **/*.cpp **/**/*.h **/**/*.cpp
	@rm ./.clang-format

style_fix:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -i **/*.h **/*.cpp **/**/*.h **/**/*.cpp
	@rm ./.clang-format

valgrind_check: tests
	@CK_FORK=no valgrind --leak-check=full \
	--show-leak-kinds=all --track-origins=yes -s ./test
	@echo "┏=========================================┓"
	@echo "┃        Valgrind check is over           ┃"
	@echo "┃       logs have been generated          ┃"
	@echo "┗=========================================┛"

fonts:
	open view/fonts/.

.PHONY: all install uninstall dvi dist test gcov_report valgrind_check style_check format_style fonts clean fclean
