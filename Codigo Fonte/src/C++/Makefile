CXX = g++
CXXFLAGS = -O2 -pthread
TARGET = benchmark
SRCS = main.cpp mergesort.cpp parallelmergesort.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)