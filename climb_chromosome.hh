// implementation for climb chromosome Class


#include "chromosome.hh"
#include "deme.hh"

class ClimbChromosome:Chromosome {
  public:
  void mutate() override;

  Chromosome::Chromosome* clone() override;

  private:

};
