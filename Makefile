VERSION=1.0.0

TOOLS_DIR	=
NAME_MODULE	= ipc-app
NAME_LIB	= 
OPTIMIZE	= -Wall -O2 
PROJECT_DIR = $(PWD)
OBJ_DIR=${PROJECT_DIR}/build
OUT_DIR=${PROJECT_DIR}/output

include $(PROJECT_DIR)/Makefile.conf

# linux
CROSS_COMPILE=

CXX	  =$(CROSS_COMPILE)g++
CC	  =$(CROSS_COMPILE)gcc
AR	  =$(CROSS_COMPILE)ar
STRIP =$(CROSS_COMPILE)strip


CFLAGS += $(OPTIMIZE)

# sources include  
CFLAGS += -I$(PROJECT_DIR)/sources
CFLAGS += -I$(PROJECT_DIR)/sources/utils

# dependencies
CFLAGS += -I
CFLAGS += -L
LIBS +=

# add path sources c
CSRCS += $(wildcard sources/*.c)
CSRCS += $(wildcard sources/utils/*.c)
OBJS  += $(patsubst %.c, $(OBJ_DIR)/%.o, $(CSRCS))

CFLAGS += -g -lpthread -lrt -ldl

.PHONY : create all clean flash

$(OBJ_DIR)/%.o: %.c
	@echo "build $<"
	@mkdir -p $(shell dirname $@)
	@$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

$(OBJ_DIR)/$(NAME_MODULE): $(OBJS)
	@$(CC) -o $(OBJ_DIR)/$(NAME_MODULE) $^  $(CFLAGS) ${LIBS}
	@echo "---------- build $(NAME_MODULE) release ----------"

all: create $(OBJ_DIR)/$(NAME_MODULE)

create:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OUT_DIR)

clean:
	@rm -rf $(OUT_DIR)
	@rm -rf $(OBJ_DIR)
flash:
	@sudo cp -r $(OBJ_DIR)/$(NAME_MODULE) $(OUT_DIR)
	@sudo cp -r $(OBJ_DIR)/$(NAME_MODULE) $(NFS_DIR)
