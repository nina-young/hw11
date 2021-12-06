/* tests
*/

#include <iostream>

#include "tournament_deme.hh"

void test_select_parent(TournamentDeme* t){
 std::cout<<"p is set to: "<<t->get_p()<<std::endl;

}


int main(){
	// need to read things in and put args in line 16
	TournamentDeme* t = new TournamentDeme();
	test_select_parent(t);
	return 0;
}