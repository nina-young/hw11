/* TournamentDeme header file
*/

// This class inherits from the Deme class and overrides whatever is necessary in your judgement for your 
// class to replace the parent selection algorithm. 
// (It can use either Chromosome or ClimbChromosome: experiment with both when you're done and pick the best one.) 
// The new selection operator we’ll try is called “tournament selection” 
// because it pits candidate parents against each other to determine which parent gets to recombine. 
// It works as follows: * Select P parents at random, where P is some constant power of two that you choose 
// (no bigger than the population size). * Take the first pair in the set of P parents and discard the parent 
// with the lower fitness of the two. * Do the same for the next pair, and so forth. You should have P/2 parents
//  in the resulting set. * Repeat the last two steps until you’re left with only one parent. * Now modify tsp.cc
//   to use your new TournamentDeme class instead of Deme. Compile the program, run it, and observe the quality 
//   and speed of the solutions. Note that you may need to experiment with the size of to get good results. Once 
//   you’re satisfied with the results, run the program and save the results into “tournament.tsv”.
