CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = movie_recommender
OBJS = main.o Movie.o User.o Rating.o UserInterface.o Manager.o

$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Movie.h
		$(CXX) $(CXXFLAGS) -c $<

Movie.o: Movie.cpp Movie.h
		$(CXX) $(CXXFLAGS) -c $<

User.o: User.cpp User.h
		$(CXX) $(CXXFLAGS) -c $<

Rating.o: Rating.cpp Rating.h
		$(CXX) $(CXXFLAGS) -c $<

UserInterface.o: UserInterface.cpp UserInterface.h
		$(CXX) $(CXXFLAGS) -c $<

Manager.o: Manager.cpp Manager.h
		$(CXX) $(CXXFLAGS) -c $<


.PHONY: clean run

clean:
		rm -f $(OBJS) $(TARGET)
run: $(TARGET)
		./$(TARGET)