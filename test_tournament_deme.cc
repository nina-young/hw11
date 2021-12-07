/* tests
*/

//#include <iostream>

//#include "tournament_deme.hh"

/*
void test_select_parent(TournamentDeme* t){
 std::cout<<"p is set to: "<<t->get_p()<<std::endl;
 // result = run the function
 //highest = get max elelment in p_parents
 // assert()

}

*/

/*
int main(int argc, char** argv)
{
  if (argc != 4) {
    std::cerr << "Required arguments: filename for cities, population size, and mutation rate\n";
    return -1;
  }

  const auto cities = Cities(argv[1]);
  const auto pop_size = atoi(argv[2]);
  const auto mut_rate = atof(argv[3]);
  constexpr unsigned NUM_ITER = 100000;
  assert(cities.size() > 0 && "Did you actually read the input file successfully?");


 //const auto best_ordering = exhaustive_search(cities);
 //const auto best_ordering = randomized_search(cities, NUM_ITER);
  const auto best_ordering = ga_search(cities, NUM_ITER, pop_size, mut_rate);

  auto out = std::ofstream("shortest.tsv");
  if (!out.is_open()) {
    std::cerr << "Can't open output file to record shortest path!\n";
    return -2;
  }

  out << cities.reorder(best_ordering);

  return 0;
}

?
*/


// int main(){
// 	// need to read things in and put args in line 16
// 	TournamentDeme* t = new TournamentDeme();
// 	test_select_parent(t);
// 	return 0;
// }
