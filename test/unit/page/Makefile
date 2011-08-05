.SUFFIXES:
.SUFFIXES: .c.o

TARGET= test_page

TOP_DIR=../../..

INC_DIR=-I$(TOP_DIR)/include \
  -I/usr/include/apache2 \
  -I/usr/include/apr-1.0 \
  -I$(TOP_DIR)/include

all:test



test: $(TARGET)
	./$(TARGET)

$(TARGET): $(TARGET).c
	gcc -g -o $@ -Wall -lcunit $< $(INC_DIR) -DLINUX=2 -D_REENTRANT -D_GNU_SOURCE -D_LARGEFILE64_SOURCE  -lapr-1 -laprutil-1  $(TOP_DIR)/src/.libs/libscss.a


clean:
	rm -f ./$(TARGET)
