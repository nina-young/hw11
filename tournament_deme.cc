/* TournamentDeme implementation
*/

#include "tournament_deme.hh"

#include <algorithm>

#include "constant.hh"
// Might change to climbchromosome later (?)

//Now modify tsp.cc
//   to use your new TournamentDeme class instead of Deme. Compile the program, run it, and observe the quality 
//   and speed of the solutions. Note that you may need to experiment with the size of to get good results. Once 
//   you’re satisfied with the results, run the program and save the results into “tournament.tsv”.

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate, unsigned p)
: Deme(cities_ptr, pop_size, mut_rate), p_(p) {}

int TournamentDeme::get_p(){
	if (verbose){std::cout<<"running get_p"<<std::endl;}
	return p_;
}

Chromosome* TournamentDeme::select_parent(){
	if (verbose){std::cout<<"select_parent in tournament_deme.cc"<<std::endl;}
	// p cannot be larger than the population size of the deme
	assert(pop_.size()>p_);
	//more prints
	// Make container for parents to compete
	std::vector<Chromosome*> p_parents;

	// Find the maximum of p_parents
	// from eitan
	auto true_max = *std::max_element(p_parents.cbegin(), p_parents.cend(), [](auto cp1, auto cp2){
      return cp1->get_fitness() < cp2->get_fitness(); });

	// Select a random sample of size p
    std::sample(pop_.begin(), pop_.end(), std::back_inserter(p_parents),
                p_, generator_);
	assert(p_parents.size() == p_); // Make sure that the right amount of parents were chosen
	
	// Keep track of which indicies to remove to avoid data races
	std::vector<int> to_remove;

	// While there are still parents left to compete
	while (p_parents.size() > 1){

	// Iterate through the remaining population
	for (unsigned i = 0; i<p_parents.size(); i+=2){

		// Get the fitnesses of both selected parents
		double fitness_1 = p_parents[i]->get_fitness();
		double fitness_2 = p_parents[i+1]->get_fitness();

		// If one parent is fitter than another
		if (fitness_1 > fitness_2){ to_remove.push_back(i+1);}
		else if (fitness_1 < fitness_2){ to_remove.push_back(i);}

		// If equal fitness, remove the first one
		else {to_remove.push_back(i);}
	}

	for (auto i: to_remove){
		std::cout<<i<<std::endl;
	}

	std::reverse(to_remove.begin(), to_remove.end());

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
assert(true_max == p_parents[0]);
return p_parents[0];
}