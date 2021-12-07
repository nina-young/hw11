CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -O3 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)
#clang


#including test_cities here in case we update the interface
#for later: fix the scaling thing
all:  test_cities tsp test_chromosome test_climb_chromosome test_tournament_deme

test_cities: cities.o test_cities.o constant.hh
	$(CXX) $(LDFLAGS) -o $@ $^

test_chromosome: chromosome.o test_chromosome.o cities.o constant.hh
	$(CXX) $(LDFLAGS) -o $@ $^

test_climb_chromosome: chromosome.o cities.o deme.o test_climb_chromosome.o climb_chromosome.o constant.hh
	$(CXX) $(LDFLAGS) -o $@ $^

test_tournament_deme: chromosome.o cities.o deme.o  tournament_deme.o climb_chromosome.o test_tournament_deme.o constant.hh
	$(CXX) $(LDFLAGS) -o $@ $^

tsp: tsp.o chromosome.o deme.o cities.o climb_chromosome.o tournament_deme.o constant.hh
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o test_cities test_chromosome tsp test_climb_chromosome test_tournament_deme
