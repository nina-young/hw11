/* Implementation for Chromosome class
 */

#include "chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(rand())
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{
  // Make sure chromosome is valid before mutating it
  assert(is_valid());

  // Get two random iterators
  std::uniform_int_distribution<int> distribution(0, order_.size()-1);
  auto i = distribution(generator_);
  auto j = distribution(generator_);

  // Swap something in the permutation
  std::swap(order_[i], order_[j]);

  // Check that this new arrangement is valid
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  // Check that both original and other are valid
  assert(is_valid());
  assert(other->is_valid());

  std::pair<Chromosome*, Chromosome*> ptr_pair;

  std::uniform_int_distribution<> random(0, order_.size()-1);
 unsigned l = random(generator_);

 std::uniform_int_distribution<> random2(0, order_.size()-l-1);
 unsigned b = random2(generator_);
 unsigned e = b+l;
 assert(b <= e);
  // Create crossover children
  ptr_pair.first = create_crossover_child(this, other, b, e);
  ptr_pair.second = create_crossover_child(other, this, b, e);

  return ptr_pair;
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
      }
      assert(j < p2->order_.size());
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  auto score = cities_ptr_->total_path_distance(order_);
  auto fitness = score*-1 + offset_;
  return fitness;
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
// We implement this check with a sort, which is a bit inefficient, but simple
bool
Chromosome::is_valid() const
{

  // Check that the permutation is not empty
  assert(not order_.empty());

  //assert that there are no duplicates
  Cities::permutation_t copy = order_;
  std::sort(copy.begin(), copy.end());
  return std::adjacent_find(copy.begin(), copy.end()) == copy.end() && copy.back() < cities_ptr_->size();
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  return std::find(order_.begin() + begin, order_.begin() + end, value) != order_.begin() + end;
}
