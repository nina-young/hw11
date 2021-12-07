// comments


#include "climb_chromosome.hh"

ClimbChromosome::ClimbChromosome(const Cities *cities_ptr) : Chromosome(cities_ptr) {
    assert(!order_.empty());
  }

ClimbChromosome::~ClimbChromosome(){};

// Using "local hill method"
void ClimbChromosome::mutate() {
  std::uniform_real_distribution<double> unif(0, order_.size() - 1);
  double p = unif(generator_);
  //swap with the city at index N-1 instead of at index -1
  Cities::permutation_t permutation_1 = order_; // save the first order
  Cities::permutation_t permutation_2;
  Cities::permutation_t permutation_3;
  double fitness_1 = get_fitness(); //find fitness of permutation 1
  double fitness_2;
  double fitness_3;
  //first recombination
  if (p==0){
    permutation_2 = permutation_1; //save new reordering
    std::swap(permutation_2[p], permutation_2[permutation_2.size()-1]);
    std::swap(permutation_2, order_);
    assert(is_valid());
    fitness_2 = get_fitness(); //get fitness of this permutation
    std::swap(permutation_2, order_);
    assert(is_valid());
  } else {
    permutation_2 = permutation_1; //save new reordering
    std::swap(permutation_2[p], permutation_2[p - 1]);
    std::swap(permutation_2, order_);
    fitness_2 = get_fitness(); // get fitness of perm 2
    std::swap(permutation_2, order_);
    assert(is_valid());
  }
  //second recombination
  if (p == permutation_1.size()-1){
    permutation_3 = permutation_1; //save new reordering
    std::swap(permutation_3[0], permutation_3[p]);
    std::swap(permutation_3, order_);
    fitness_3 = get_fitness();
    std::swap(permutation_3, order_);
    assert(is_valid());
  } else {
    assert(is_valid());
    permutation_3 = permutation_1; //save new reordering
    std::swap(permutation_3[p], permutation_3[p + 1]);
    assert(is_valid());
    std::swap(permutation_3, order_);
    assert(is_valid());
    fitness_3 = get_fitness();
    std::swap(permutation_3, order_);
    assert(is_valid());
  }
  //find the highest total fitness between the three chromosomes)
  if (fitness_1 > fitness_2) {
    order_ = permutation_1;
    assert(is_valid());
  }
  if (fitness_2 > fitness_1) {
    order_ = permutation_2;
    assert(is_valid());
  }
  if (get_fitness() < fitness_3) {
    order_ = permutation_3;
    assert(is_valid());
  }
    assert(is_valid());
}

Chromosome* ClimbChromosome::clone() const {
  return new ClimbChromosome(cities_ptr_);
}
