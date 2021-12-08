/* TournamentDeme implementation
*/

#include "tournament_deme.hh"

#include <algorithm>

#include "constant.hh"

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate, unsigned p)
: Deme(cities_ptr, pop_size, mut_rate), p_(p) {}

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


	// Sanity check: uncomment this and lines ??? to compare select_parents()'s method
	// of getting the hightest fitness with this funcion
	// max_element() lambda is from Eitan's previous homework solutions

	// Chromosome* true_max = *std::max_element(p_parents.begin(), p_parents.end(), [](auto cp1, auto cp2){
  	//   return cp1->get_fitness() < cp2->get_fitness(); });
	// if (verbose){std::cout<<"just declared true_max"<<std::endl;}

	// Keep track of which indicies to remove to avoid data races
	std::vector<Chromosome*> winners;
	winners.reserve(p_/2);
	//std::cout<<"winners declared"<<std::endl;
	if (verbose){std::cout<<"just declared to_remove"<<std::endl;}

	// While there are still parents left to compete
	while (p_parents.size() > 1){

		//std::cout<<"starting while loop"<<std::endl;
		//std::cout<<"p_parents size = "<<p_parents.size()<<std::endl;
	// Iterate through the remaining population
	for (unsigned i = 0; i<p_parents.size()/2; i+=2){

		// Get the fitnesses of both selected parents
		double fitness_1 = p_parents[i]->get_fitness();
		double fitness_2 = p_parents[i+1]->get_fitness();

		// If one parent is fitter than another
		if (fitness_1 > fitness_2){
			if (verbose){std::cout<<"passed if check in tournament_deme.cc"<<std::endl;}
			winners.push_back(p_parents[i]);
			if (verbose){std::cout<<"just pushed back on to_remove"<<std::endl;}

		}

		else if (fitness_1 < fitness_2){
			if (verbose){std::cout<<"passed else if check in tournament_deme.cc"<<std::endl;}
			winners.push_back(p_parents[i+1]);
			if (verbose){std::cout<<"just pushed back on to_remove"<<std::endl;}
		}

		// If equal fitness, remove the first one
		else {
			if (verbose){std::cout<<"passed else check in tournament_deme.cc"<<std::endl;}
			winners.push_back(p_parents[i]);
			if (verbose){std::cout<<"just pushed back on to_remove"<<std::endl;}
		}
	}
	//if (verbose){std::cout<<"printing everything in to_remove"<<std::endl;}
	//for (auto i: to_remove){
	//	std::cout<<i<<std::endl;

	//if (verbose){std::cout<<"\n\n\n\n\n\ndid while loop\n\n\n\n\n\n";}
	assert(winners.size() < p_parents.size());
	p_parents = winners;
	winners.clear();
	//std::cout<<"swaped"<<std::endl;

	if (verbose){std::cout<<"\n\n\n\n\n\ndid while loop\n\n\n\n\n\n";}

	std::swap(winners, p_parents);

	}

	return winners[0]; }
