# Compiler config
CC 				:=	gcc

# Compilation flags configuration
ALL_TARGETS 	?= $(TARGET) test # gcov_report 
ASAN 			:= 	#-fsanitize=address
UBSAN			:=	#-fsanitize=undefined
STDFLAGS 		:=	-g -c -Wall -Wextra -std=c11 #-Werror


# Linking flags configuration
LIBS 			?=	$(CHECK_LIB) $(GMP_LIB)
CHECK_LIB 		:= 	$(shell pkg-config --libs --cflags check)
GMP_LIB 		:= 	$(shell pkg-config --libs --cflags gmp)

# Names config
TARGET 			?=	s21_decimal.a
TEST_TARGET		?=	test_s21_decimal.a
TEST_EXE 		?=	test
TEST_GCOV_EXE	?=	test_gcov
GCOV_TARGET		 =	./coverage
GCOV_INFO		 =	coverage.info

# Modules - dirs with source code. Grep'ed dirs are excluded from search.
MODULES 		:=	$(shell find . -maxdepth 1 -type d | grep -v -E "docker|objs|tests")
TEST_MODULES 	:=	$(shell find tests -maxdepth 1 -type d | grep -v -E "objs")

# Dirs configuration
SRC_DIR 		?=	$(MODULES)
TEST_SRC_DIR	?=	$(TEST_MODULES)
OBJ_DIR 		:=	./objs
GCOV_OBJ_DIR	:=	./tests/gcov_obj

# Source code files configuration
SRC 			:=	$(shell find $(SRC_DIR) -maxdepth 1 -name "s21_*.c")
TEST_SRC 		:=  $(shell find $(TEST_SRC_DIR) -maxdepth 1 -name "*.c")
INC 			:=	$(shell find $(SRC_DIR) -maxdepth 1 -name "s21_*.h")
TEST_INC		:=	$(shell find $(TEST_SRC_DIR) -maxdepth 1 -name "*.h")

# Objects configuration
ALL_OBJS		:=	$(shell find . -name "*.o")
OBJS 			:=	$(notdir $(SRC:.c=.o))
TEST_OBJS 		:=	$(notdir $(TEST_SRC:.c=.o))

# GCOV-specific objects configuration
GCOV_OBJS		:=	$(addprefix $(GCOV_OBJ_DIR)/gcov_, $(notdir $(SRC:.c=.o)))
GCOV_TEST_OBJS 	:=	$(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o)))

# GCOV configuration
GCDA 			:= 	$(shell find . -name "*.gcda")
GCNO 			:= 	$(shell find . -name "*.gcno")
GCOV_FLAGS 		:=	-fprofile-arcs -ftest-coverage

# VPath configuration. Order of args is their priority. 
vpath %.c $(MODULES) : $(TEST_MODULES)
vpath %.o $(OBJ_DIR) : $(GCOV_OBJ_DIR)


# Default system utilities
AR 	:=	ar rc
RAN :=	ranlib
RM 	:= 	rm -f
MK 	:=	mkdir -p

# Assignment of configured flags
CFLAGS 		?= 	$(STDFLAGS) $(ASAN) $(UBSAN)
TST_CFLAGS 	:= 	$(STDFLAGS) #$(shell pkg-config --cflags check)

all 			: 	$(ALL_TARGETS)

debug: 
	echo $(GCOV_OBJ_DIR)
	echo $(GCOV_OBJS)
	echo $(GCOV_TEST_OBJS)

# General compilation rule
%.o 			: %.c $(INC) 
				@$(MK) $(OBJ_DIR)
				$(CC) $(CFLAGS) -o $(OBJ_DIR)/$(notdir $@) -c $<


# Building static library
$(TARGET) 		: $(OBJS) Makefile
				$(AR) $(TARGET) $(OBJ_DIR)/*
				$(RAN) $(TARGET)

$(TEST_TARGET)	: $(GCOV_OBJS) $(INC)
				$(AR) $(TEST_TARGET) $(GCOV_OBJ_DIR)/*
				$(RAN) $(TEST_TARGET)

test 			: $(TARGET) $(TEST_OBJS) $(TEST_INC) Makefile
				$(CC) $(OBJ_DIR)/* $(ASAN) $(UBSAN) $(GCOV_FLAGS) -o $(TEST_EXE) $(LIBS) -L. $(TARGET)
				./test

# GCOV stage
gcov_report: $(GCOV_TARGET)

# GCOV sets GCOV-specific variables & generates separate set of objects
$(GCOV_TARGET) 	: OBJ_DIR=$(GCOV_OBJ_DIR)
$(GCOV_TARGET) 	: CFLAGS += $(GCOV_FLAGS)
$(GCOV_TARGET) 	: $(GCOV_INFO)
				genhtml $(GCOV_INFO) -o $(GCOV_TARGET)

# GCOV objects compilation rule
$(GCOV_OBJ_DIR)/gcov_%.o : %.c $(INC) 
				@$(MK) $(OBJ_DIR)
				$(CC) $(CFLAGS) -o $(GCOV_OBJ_DIR)/$(notdir $@) -c $<

# Linking of GCOV objects
test_gcov 		: $(TEST_TARGET) $(GCOV_OBJS) $(GCOV_TEST_OBJS) Makefile
				$(CC) $(GCOV_OBJS) $(GCOV_TEST_OBJS) $(GCOV_FLAGS) -o $(TEST_GCOV_EXE) $(LIBS) -L. $(TEST_TARGET)

# Launching of executable & generating HTML report
$(GCOV_INFO) 	: test_gcov
				./$(TEST_GCOV_EXE)
				geninfo $(GCOV_OBJ_DIR) -b . -o ./$(GCOV_INFO)
				
# Utility targets

open 			:
				open coverage/index.html

clean 			:
				$(RM) $(ALL_OBJS)
				$(RM) $(GCDA)
				$(RM) $(GCNO)

fclean 			: clean
				$(RM) $(TARGET)
				$(RM) $(TEST_TARGET)
				$(RM) $(TEST_EXE)
				$(RM) $(TEST_GCOV_EXE)
				$(RM) $(GCOV_INFO)
				$(RM) -r $(GCOV_TARGET)

lint 			: Makefile
				-cp ../materials/linters/CPPLINT.cfg .
				-find . -type f -name "*.c" | xargs python3 ../materials/linters/cpplint.py --extensions=c
				-find . -type f -name "*.h" | xargs python3 ../materials/linters/cpplint.py --extensions=c
				-find . -type f -name "*.c" | xargs cppcheck --enable=all --suppress=missingIncludeSystem
				rm -f CPPLINT.cfg

re 				: fclean all

.PHONY 			: all clean fclean re open lint
