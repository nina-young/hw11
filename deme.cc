/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */


#include "deme.hh"

// Generate a Deme of the specified size with all-random Chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
  : pop_(pop_size), mut_rate_(mut_rate)
{
  // Add new Chromosomes to the population
  // Not sure if this is random (?)
  for (unsigned i = 0; i < pop_size; i++){
    pop_[i] = new ClimbChromosome(cities_ptr); //make sure that this is allocated corrrectly?
  }
}

// Deconstruct by deleting each Chromosome in the population
Deme::~Deme() {for (auto c : pop_){ delete c;}}

// Return a copy of the Chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  // Set to first Chromosome arbitrarily
  Chromosome* highest = pop_[0];

  // Check highest against every other Chromosome in pop_
  // (?) find a way to skip the first one with this syntax
  for (auto c : pop_){
   if (c->get_fitness() > highest->get_fitness()){
    highest = c;
   }
  }
  return highest;
}
// Randomly select a Chromosome in the population based on fitness and
// return a pointer to that Chromosome.
// Using Fitness Proportionate selection
Chromosome* Deme::select_parent()
{
  // Get the sum of all the fitness
  double S = 0;
  for (auto c : pop_){
    S += c->get_fitness();
  }

  // Generate a random number
  double lower_bound = 0;
  double upper_bound = S;
  std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
  double rand_num = unif(generator_);

  // Initialize partial sum
  double P = 0;
  for (auto c : pop_){
    P += c->get_fitness();
    if (P>rand_num){
      return c;
    }
  }
  return nullptr; //should never happen but just to please the compiler
}

// Evolve a single generation of new Chromosomes, as follows:
// We select pop_size/2 pairs of Chromosomes (using the select() method below).
// Each Chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the Chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of Chromosomes, which are stored in the Deme.
// After we've generated pop_size new Chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  std::vector<Chromosome*> new_pop;
  for (unsigned long i=0; i<pop_.size()/2; i++){
    // Select two parents at random // What if they are the same?
    Chromosome* p1 = select_parent();
    Chromosome* p2 = select_parent();

    // Mutate parents if random number less than mut_rate_
    double lower_bound = 0;
    double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    double mutation = unif(generator_);
    if (mutation<mut_rate_){
      p1->mutate();
    }

    auto mutation2 = unif(generator_);

    if (mutation2<mut_rate_){
      p1->mutate();
    }
    // store two children
    auto children = p1->recombine(p2);
    new_pop.push_back(children.first);
    new_pop.push_back(children.second);

  }
  pop_ = new_pop;
}
