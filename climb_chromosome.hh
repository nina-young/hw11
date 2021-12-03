// implementation for climb chromosome Class

#pragma once
#include "chromosome.hh"
#include "deme.hh"

class ClimbChromosome : public Chromosome {
  public:

  ClimbChromosome(const Cities *cities_ptr) : Chromosome(cities_ptr) {}
  virtual void mutate() override;

  virtual Chromosome* clone() const override;

};
