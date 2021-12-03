// comments


#include "climb_chromosome.hh"



// Using "local hill method"
void mutate() override {
  // evaluate the fitness of the current (original) chromosome.
  //   Pick a random point
  //   Swap the city at index p with the city at index p-1 and evaluate the resulting chromosome's fitness. If p==0, swap with the city at index N-1 instead of at index -1
  //   Swap the city at index p (from the original chromosome) with the city at index p+1 and evaluate the resulting chromosome's fitness. If p==N-1, swap with the city at index 0 instead of at index N.
  //   Find which of the three chromosomes produced the fittest ordering and choose that fittest chromosome as the resulting mutated chromosome.
  double fitness = this.get_fitness();
  std::uniform_real_distribution<double> unif(0, order_.size() - 1);
  double p = unif(generator_);
  //swap with the city at index N-1 instead of at index -1
  double fitness_2;
  double fitness_3;
  double best_fitness;
  if (p==0){
    std::swap(order_[p], order_[order.size()-1]);
    fitness_2 = this.get_fitness();
  } else {
    std::swap(order_[p], order_[p - 1]);
    fitness_2 = this.get_fitness();
  }
  if (p == order_.size()-1){
    std::swap(order_[0], order_[p]);
    fitness_3 = this.get_fitness();
  } else {
    std::swap(order_[p], order_[p + 1]);
    fitness_3 = this.get_fitness();
  }
  //find the highest total fitness between the three chromosomes)
  if (fitness > fitness_2) {
    best_fitness = fitness;
  }
  if (fitness_2 < fitness) {
    best_fitness = fitness_2;
  }
  if (best_fitness < fitness_3) {
    best_fitness = fitness_3;
  }
  return best_fitness;
}

Chromosome::Chromosome* clone(){
  return new ClimbChromosome(cities_ptr_);
}
