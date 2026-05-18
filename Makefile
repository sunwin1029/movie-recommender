CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
TARGET = movie_recommender
SRCS = src/main.cpp src/Movie.cpp src/User.cpp src/Rating.cpp src/UserInterface.cpp src/Manager.cpp
OBJS = obj/main.o obj/Movie.o obj/User.o obj/Rating.o obj/UserInterface.o obj/Manager.o
HEADERS = include/Movie.h include/User.h include/Rating.h include/UserInterface.h include/Manager.h

$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp $(HEADERS) | obj
		$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run

obj:
		mkdir -p obj

clean:
		rm -f $(OBJS) $(TARGET)
run: $(TARGET)
		./$(TARGET)
