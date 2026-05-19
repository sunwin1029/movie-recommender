CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
TARGET = movie_recommender
SRCS = src/main.cpp src/Movie.cpp src/User.cpp src/Rating.cpp src/UserInterface.cpp src/Manager.cpp src/MovieManager.cpp src/UserManager.cpp src/RatingManager.cpp src/SimilarityCalculator.cpp src/Recommender.cpp
OBJS = obj/main.o obj/Movie.o obj/User.o obj/Rating.o obj/UserInterface.o obj/Manager.o obj/MovieManager.o obj/UserManager.o obj/RatingManager.o obj/SimilarityCalculator.o obj/Recommender.o
HEADERS = include/Movie.h include/User.h include/Rating.h include/UserInterface.h include/Manager.h include/BaseManager.h include/MovieManager.h include/UserManager.h include/RatingManager.h include/SimilarityCalculator.h include/Recommender.h

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
