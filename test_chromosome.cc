/*
 * Tests for chromosome
 */

#include "chromosome.hh"
#include <fstream>

// Testing mutate
bool test_mutate(Chromosome chrom){
  assert(chrom.is_valid());

  // Save previous ordering
  Cities::permutation_t prev_order;
  copy(chrom.get_ordering().begin(), chrom.get_ordering().end(), back_inserter(prev_order));
  assert(not prev_order.empty());

  chrom.mutate();

  return prev_order != chrom.get_ordering();
}

int main(){
  Cities cities1 = Cities();
  std::ifstream cities_file;
  cities_file.open("five.tsv");
  cities_file >> cities1;
  assert(test_mutate(Chromosome(&cities1)));
	return 0;
  }
