CC:=g++ --std=c++11 -Werror
INCLUDE:=-I ./include/
SRC_DIR:=./src
OBJ_DIR:=./obj
EXE:=elf_vs_orcs

.PHONY: test all clean

default:
	${CC} ${SRC_DIR}/*.cpp ${INCLUDE} -o ${EXE}

clean:
	rm ${EXE}

