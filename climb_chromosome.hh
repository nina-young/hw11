// implementation for climb chromosome Class


#include "chromosome.hh"
#include "deme.hh"

class ClimbChromosome : public Chromosome {
  public:
  ClimbChromosome(const Cities *cities_ptr) : Chromosome(cities_ptr) {}
  void mutate() override;

  Chromosome::Chromosome* clone() override;

  private:

};
