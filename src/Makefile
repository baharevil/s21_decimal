OS 							:= $(shell uname -s)
CC 							 = gcc
CFLAGS 					 = -Wall -Werror -Wextra -std=c11 -I. -pedantic
DEBUG 					 = -g
VALFLAGS				 = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s
LDFLAGS 				:= $(if $(filter Linux, $(OS)),$(shell pkg-config --libs check),-lcheck)
OPEN_CMD 				:= $(if $(filter Linux, $(OS)),xdg-open,open)

project_name 		 = s21_decimal
report_dir			 = gcovr-report
func_dir 				 = function
test_dir 				 = tests

lib_name 				:= $(addsuffix .a, $(project_name))
test_lib_name		:= $(addprefix  $(test_dir)/, $(addsuffix _test.a, $(project_name)))
import					 = $(test_lib_name) $(lib_name)

find_command		 = find $(1) -iname "*.c"
depenc_command	 = $(filter $(1)/%.o, $(obj_list))

func_source			:= $(shell $(call find_command, $(func_dir)))
test_source_1		 = $(shell $(call find_command, $(test_dir)))
test_source_2		:= $(filter-out $(test_dir)/$(func_dir)/%.c $(test_dir)/tests/%.c, $(shell $(call find_command, $(test_dir))))
obj_list 				:= $(patsubst %.c, %.o, $(func_source) $(if $(filter ., $(test_dir)), $(test_source_2), $(test_source_1)))


all: $(lib_name)


#---- BASIC ----#
.PHONY: test
test: $(import)
	$(CC) -o $@ -pipe -L. $(addprefix -l:, $^) $(LDFLAGS)
	@$(if $(filter valgrind, $(val)), CK_FORK=no $(val) $(VALFLAGS)) ./$@

$(lib_name): $(call depenc_command, $(func_dir))
$(test_lib_name): $(call depenc_command, $(test_dir))
%.a:
	ar csr $@ $?

%.o: %.c
	$(CC) $(CFLAGS) $(if $(filter $(func_dir)/%.c, $^),$(GCOVFLAGS)) $(DEBUG) -c $^ -o $@

valgrind: val = valgrind
valgrind: test


#---- REPORT ----#
.PHONY: doc
gcov_report: GCOVFLAGS = -fprofile-arcs -ftest-coverage
gcov_report: LDFLAGS += -lgcov
gcov_report: clean_gcov test
	@mkdir $(report_dir)
	~/.local/bin/gcovr --exclude-branches-by-pattern * --html-nested --output $(report_dir)/$(project_name).html

gcov_open:
	$(OPEN_CMD) $(report_dir)/$(project_name).html

deps:
	pip install gcovr

doc:
#	~/Downloads/doxygen-1.10.0/bin/doxygen doc/doc_config
	doxygen doc/doc_config
	$(OPEN_CMD) doc/html/index.html


#---- CLANG-FORMAT ----#
.PHONY: clang-n clang-i
clang-n:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -n -style=file:../materials/linters/.clang-format

clang-i:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i -style=file:../materials/linters/.clang-format


#---- CLEAN ----#
.PHONY: clean clean_gcov
clean: clean_doc
	@rm -rf $(report_dir)
	@rm -rf $(lib_name) $(test_lib_name) test
	@rm -rf $(obj_list) $(addsuffix /*.gcda, $(func_dir)) $(addsuffix /*.gcno, $(func_dir))

clean_gcov:
	@rm -rf $(report_dir) 
	@rm -rf $(filter $(func_dir)/%.o, $(obj_list)) $(addsuffix /*.gcda, $(func_dir)) $(addsuffix /*.gcno, $(func_dir))

clean_doc:
	@rm -rf doc/html doc/latex

#---- MAN ----#
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
