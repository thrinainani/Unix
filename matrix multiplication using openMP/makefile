export GCC=gcc && make
GCC = gcc

TARGET = mmatrix_mp

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(GCC) -fopenmp -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
