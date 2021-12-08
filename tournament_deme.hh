/* Declarations for TournamentDeme class
*/
#include <algorithm>
#include <cassert>

#include "deme.hh"

class TournamentDeme : public Deme {

public: 
	TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate, unsigned p);
	virtual Chromosome* select_parent() override;
	int get_p();

private:
	const unsigned p_; // To be used in select_parent()
};