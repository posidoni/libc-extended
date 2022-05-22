CC=gcc
CFLAGS:=-Wall -Werror -Wextra -std=c11 #$(ASAN)

ifeq ($(shell uname), Mac)
ASAN=-g -fsanitize=address
endif

TARGET=s21_matrix.a

INC:=$(shell find . -name "*.h")
SRC:=$(shell find . -name "s21*.c")
OBJS:=$(SRC:%.c=%.o)

# s21_matrix.a
all: $(TARGET)

$(TARGET): $(OBJS)
	ar rc $(TARGET) $(OBJS)
	ranlib $(TARGET)

$(OBJS): $(SRC) $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

# TESTS & COVERAGE
GCOV_FLAGS:=$(CFLAGS) -fprofile-arcs -ftest-coverage $(ASAN)
TEST_LIBS:=$(shell pkg-config --cflags --libs check)

TARGET_TEST=test
TARGET_TEST_LIB=s21_matrix_test.a
TEST_DIR=./tests

TEST_INC:=$(shell find $(TEST_DIR) -name "*.h")
TEST_SRC:=$(shell find $(TEST_DIR) -name "*.c")

GCOV_OBJS:=$(SRC:%.c=%.o)
TEST_OBJS:=$(TEST_SRC:%.c=%.o)

# GENERATE TEST.EXE FOR GCOV
$(TARGET_TEST): $(TEST_OBJS) $(TARGET_TEST_LIB)
	$(CC) $(GCOV_FLAGS) $(CFLAGS) main.c $(TARGET_TEST_LIB) -o $@ $< $(TEST_LIBS)
	./test
	
# GET ALL OBJS FROM TEST_DIR
$(TEST_OBJS): $(TEST_SRC) $(TEST_INC)
	$(CC) $(GCOV_FLAGS) $(CFLAGS) -o $@ -c $<

# BUILD THE LIB AGAIN FOR TESTS
$(TARGET_TEST_LIB): $(GCOV_OBJS) $(INC)
	ar rc $(TARGET_TEST_LIB) $(GCOV_OBJS)
	ranlib $(TARGET_TEST_LIB)

# OBJS FOR LIB AGAIN
$(GCOV_OBJS): $(SRC) $(TEST_INC)
	$(CC) $(GCOV_FLAGS) $(CFLAGS) -o $@ -c $<

gcov: $(TARGET_TEST)
	gcov $(TEST_SRC) $(SRC)

coverage.info: gcov
	lcov --capture --directory . --output-file coverage.info

report: coverage.info
	genhtml coverage.info --output-directory coverage

open:
	open coverage/index.html

clean:
	@rm -rf $(TEST_DIR)/*.gcno $(TEST_DIR)/*.gcda $(TEST_DIR)/*.o *.gcno *.gcda *.o coverag* *.gcov

fclean: clean
	@rm -rf $(TARGET) $(TARGET_TEST_LIB) $(TARGET_TEST)

re: fclean all

.PHONY: all clean fclean open
