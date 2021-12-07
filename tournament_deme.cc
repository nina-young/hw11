/* TournamentDeme implementation
*/

#include "tournament_deme.hh"

#include <algorithm>

#include "constant.hh"
// Might change to climbchromosome later (?)

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate, unsigned p)
: Deme(cities_ptr, pop_size, mut_rate), p_(p) {}

int TournamentDeme::get_p(){
	if (verbose){std::cout<<"running get_p"<<std::endl;}
	return p_;
}

Chromosome* TournamentDeme::select_parent(){
	if (verbose){std::cout<<"select_parent in tournament_deme.cc"<<std::endl;}
	// p cannot be larger than the population size of the deme
	if (pop_.size()<p_) {
    std::cerr << "The number of random parents you want to compete is greater than the population size.\n";
    assert(false);}

	// Make container for parents to compete
	std::vector<Chromosome*> p_parents;
	if (verbose){std::cout<<"just declared p_parents"<<std::endl;}

	// Select a random sample of size p
    std::sample(pop_.begin(), pop_.end(), std::back_inserter(p_parents),
                p_, generator_);
    if (verbose){std::cout<<"just did std::sample to get p_parents"<<std::endl;}
    assert(!p_parents.empty());
    assert(p_parents.size() == p_); // Make sure that the right amount of parents were chosen


	// Find the maximum of p_parents
	// from eitan
	
	 Chromosome* true_max = *std::max_element(p_parents.begin(), p_parents.end(), [](auto cp1, auto cp2){
      return cp1->get_fitness() < cp2->get_fitness(); });
	 if (verbose){std::cout<<"just declared true_max"<<std::endl;}

	// Keep track of which indicies to remove to avoid data races
	std::vector<int> to_remove;
	if (verbose){std::cout<<"just declared to_remove"<<std::endl;}

	// While there are still parents left to compete
	while (p_parents.size() > 1){
		if (verbose){std::cout<<"starting while loop"<<std::endl;}

	// Iterate through the remaining population
	for (unsigned i = 0; i<p_parents.size(); i+=2){

		// Get the fitnesses of both selected parents
		double fitness_1 = p_parents[i]->get_fitness();
		double fitness_2 = p_parents[i+1]->get_fitness();

		// If one parent is fitter than another
		if (fitness_1 > fitness_2){
			if (verbose){std::cout<<"passed if check in tournament_deme.cc"<<std::endl;}


			to_remove.push_back(i+1);
			if (verbose){std::cout<<"just pushed back on to_remove"<<std::endl;}

		}
		else if (fitness_1 < fitness_2){ 
			if (verbose){std::cout<<"passed else if check in tournament_deme.cc"<<std::endl;}
			to_remove.push_back(i);
			if (verbose){std::cout<<"just pushed back on to_remove"<<std::endl;}
		}

		// If equal fitness, remove the first one
		else {
			if (verbose){std::cout<<"passed else check in tournament_deme.cc"<<std::endl;}
			to_remove.push_back(i);
			if (verbose){std::cout<<"just pushed back on to_remove"<<std::endl;}
		}
	}

	if (verbose){std::cout<<"printing everything in to_remove"<<std::endl;}
	for (auto i: to_remove){
		std::cout<<i<<std::endl;
	}

	if (verbose){std::cout<<"about to do std::reverse"<<std::endl;}
	std::reverse(to_remove.begin(), to_remove.end());
	if (verbose){std::cout<<"just did std::reverse"<<std::endl;}
	// Remove parents that lost
	for (auto i : to_remove){
		std::cout<<"size of p parents = "<<p_parents.size()<<std::endl;
		std::cout<<"index = "<<i<<std::endl;
		p_parents.erase(p_parents.begin()+i);
	}

	// Reset to_remove for the next tournament round
	to_remove.clear();
	assert(to_remove.empty());
}

std::cout<<"Finished while loop"<<std::endl;
assert(p_parents.size() == 1);
// std::cout<<"printing true max: ";
// for (int i = 0; i<true_max->size(); i++){
// 	std::cout<<true_max[i]<<' ';
// }
// std::cout<<std::endl;

// std::cout<<"printing true max: ";
// for (int i : *(p_parents[0])){
// 	std::cout<<i<<' ';
// }
//std::cout<<std::endl;
//std::cout<<*true_max<<std::endl;
//std::cout<<*(p_parents[0])<<std::endl;

return p_parents[0];
}