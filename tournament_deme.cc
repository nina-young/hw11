/* TournamentDeme implementation
*/

#include "tournament_deme.hh"
#include "constant.hh"

#include <algorithm>
#include <cassert>

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate, unsigned p)
: Deme(cities_ptr, pop_size, mut_rate), p_(p) {assert(p%2 == 0);}

// Get the number of parents to select in select_parents
int TournamentDeme::get_p(){
	if (verbose){std::cout<<"running get_p"<<std::endl;}
	return p_;
}

Chromosome* TournamentDeme::select_parent(){
	if (verbose){std::cout<<"select_parent in tournament_deme.cc"<<std::endl;}

	if (pop_.size()<p_) {
    std::cerr << "The number of random parents you want to compete is greater than the population size.\n";
    assert(false);}

	// Make container for parents to compete
	std::vector<Chromosome*> p_parents;
	p_parents.reserve(p_);
	if (verbose){std::cout<<"just declared p_parents"<<std::endl;}

	// Select a random sample of size p
    std::sample(pop_.begin(), pop_.end(), std::back_inserter(p_parents),
                p_, generator_);
    if (verbose){std::cout<<"just did std::sample to get p_parents"<<std::endl;}
    assert(p_parents.size() == p_); // Make sure that the right amount of parents were chosen


	// Sanity check: uncomment this and lines 42 and 43 to compare select_parents()'s method
	// of getting the hightest fitness with this funcion
	// max_element() lambda is from Eitan's previous homework solutions

	// Chromosome* true_max = *std::max_element(p_parents.begin(), p_parents.end(), [](auto cp1, auto cp2){
  	//   return cp1->get_fitness() < cp2->get_fitness(); });

	// Keep track of winners for each round
	std::vector<Chromosome*> winners;
	winners.reserve(p_/2);

	// While there are still parents left to compete
	while (p_parents.size() > 1){
	winners.clear();
	// Iterate through the remaining population
	for (unsigned i = 0; i<p_parents.size()/2; i+=2){

		// Get the fitnesses of both selected parents
		double fitness_1 = p_parents[i]->get_fitness();
		double fitness_2 = p_parents[i+1]->get_fitness();

		// If one parent is fitter than another
		if (fitness_1 > fitness_2){
			winners.push_back(p_parents[i]);
		}

		else if (fitness_1 < fitness_2){
			winners.push_back(p_parents[i+1]);
		}

		// If equal fitness, remove the first one
		else {
			winners.push_back(p_parents[i]);
		}
	}
	assert(winners.size() < p_parents.size());
	p_parents = winners;
	}
	return winners[0]; }
