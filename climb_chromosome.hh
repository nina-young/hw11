// implementation for climb chromosome Class

#pragma once
#include "chromosome.hh"
#include "deme.hh"

class ClimbChromosome : public Chromosome {

  public:



  ClimbChromosome(const Cities *cities_ptr); //: Chromosome(cities_ptr) {
    //assert(!order_.empty());
  // }

  virtual ~ClimbChromosome();

  virtual void mutate() override;
  virtual Chromosome* clone() const override;

/*
protected:
  ClimbChromosome(const ClimbChromosome&) = delete;
  ClimbChromosome(ClimbChromosome&&) = delete;
  ClimbChromosome& operator=(const ClimbChromosome&) = default;
  ClimbChromosome& operator=(ClimbChromosome&&) = default;
  */
};
