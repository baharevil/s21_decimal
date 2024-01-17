OS 				:= $(shell uname -s)
CC 				= gcc
# Отключил -pedantic. Компилятор с ним не хотел компилиться
CFLAGS 			= -Wall -Werror -Wextra -std=c11 -I.
DEBUG 			= -g
LDFLAGS 		:= $(if $(filter Linux, $(OS)),$(shell pkg-config --libs check),-lcheck)
OPEN_CMD 		:= $(if $(filter Linux, $(OS)),xdg-open,open)

project_name 	= s21_decimal
report_dir		= gcovr-report
func_dir 		= function
test_dir 		= tests

lib_name 		:= $(addsuffix .a, $(project_name))
test_lib_name	:= $(addprefix  $(test_dir)/, $(addsuffix _test.a, $(project_name)))
dirs_for_obj	:= $(func_dir) $(test_dir)
obj_list 		:= $(patsubst %.c, %.o, $(wildcard $(addsuffix /*.c, $(dirs_for_obj))))

all: $(lib_name)

.PHONY: test
test: $(test_lib_name) $(lib_name) 
	$(CC) -o $@ -pipe -L. $(addprefix -l:, $^) $(LDFLAGS)
	@$(if $(filter valgrind, $(val)), $(val) --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s) ./$@

$(lib_name): $(filter $(func_dir)/%.o, $(obj_list))
	ar crs $@ $^

$(test_lib_name): $(filter $(test_dir)/%.o, $(obj_list))
	ar csr $@ $?

%.o: %.c
	$(CC) $(CFLAGS) $(if $(filter $(func_dir)/%.c, $^),$(GCOVFLAGS)) $(DEBUG) -c $^ -o $@

gcov_report: GCOVFLAGS = -fprofile-arcs -ftest-coverage
gcov_report: LDFLAGS += -lgcov
gcov_report: clean_gcov test
	@mkdir $(report_dir)
	~/.local/bin/gcovr --exclude-branches-by-pattern * --html-nested --output $(report_dir)/$(project_name).html

gcov_open:
	$(OPEN_CMD) $(report_dir)/$(project_name).html

deps:
	pip install gcovr

valgrind: val = valgrind
valgrind: test

.PHONY: clang-n
clang-n:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -n -style=file:../materials/linters/.clang-format

.PHONY: clang-i
clang-i:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i -style=file:../materials/linters/.clang-format

.PHONY: clean
clean:
	@rm -rf $(lib_name) $(test_lib_name) test
	@rm -rf $(report_dir)
	@rm -rf $(obj_list) $(addsuffix /*.gcda, $(func_dir)) $(addsuffix /*.gcno, $(func_dir))

.PHONY: clean_gcov
clean_gcov:
	@rm -rf $(report_dir) 
	@rm -rf $(filter $(func_dir)/%.o, $(obj_list)) $(addsuffix /*.gcda, $(func_dir)) $(addsuffix /*.gcno, $(func_dir))

.DEFAULT_GOAL := man
man:
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##//'

##
##		Pproject's Makefile manual
##
##Usage: make [TARGET]
##Runs GNU Make with the selected TARGET
##Example: make all
##
##Tasrgets:
##Required targets:
##	all		launches targets s21_string.a
##	clean		clean up the created files 
##	test		testing lib's function	
##	s21_decimal.a	compiling static lib
##	gcov_report	generate a gcov report 
##			in the form of an html page.
##
##Supporting targets:
##	deps		install gcovr
##	gcov_open	open a gcov report in the browser
##	clang-n		style check
##
##Report bugs to: ladonnah@student.21-school.ru
##		melonieh@student.21-school.ru
##		roninsha@student.21-school.ru
##Home page: https://repos.21-school.ru/students/C5_s21_decimal.ID_353529/Team__TL__ladonnah_student.21_school.ru_.a5Yy2emvSCWs59HTPicuIQ/C5_s21_decimal-1
