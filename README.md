# HW 11: Advanced GA

## Overview

This is a continuation of the traveling salesperson problem that uses a more advanced GA search function.

## To fix!!!!

we need to fix the offset in chromosome.hh eventually

need some way to assert that p is a power of 2

make it actually print as it goes like in previous homework

talk somewhere about what the cities files are called

**make a tsv challenge and linear separate files**


for whatever reason it doesnt print as it goes, how to we fix this?

## ClimbChromosome Class

## TournamentDeme Class

## Testing

This repository contains `constant.hh` which sets a variable `verbose` to `false`. Go into this file and reset it to `true`, then uncomment any lines in the rest of the files that have an `if (verbose){}` statement to see more print statements. To disable, comment out the lines again or set `verbose` to be `false` again in `constant/hh`. Note that in order for this method to work, you must use `g++`.

Tests for `ClimbChromosome` and `TournamentDeme` classes are inlcluded in their implimentation (spelling?). The test files are for the Makefile.

## Running the code

The arguments needed are:
* `filename.tsv` *a file of city coordinates*
* `pop_size` *the population size*
* `mut_rate` *the mutation rate*
* `p` *the number of `Chromosome` objects in a `TournamentDeme` that will compete with each other*

*Note that `p` must be a power of 2* 

To run the code type
	
	make
	./tsp filename.tsv pop_size mut_rate p

The ordering of shortest path as calculated by the advanced ga search will be saved in `tournament.tsv`. To test the results of the other algorithms, uncomment the lines before _______(?) and change the destination in line ______.

## Results

The best orderings for `challenge.tsv` and for `five.tsv` are in the files _____ and _____ respectively. Note that when this is run, your results will still end up in `tournament.tsv`. 

Now, create a combined graph from “baseline-ga.tsv”, “local.tsv”, and “tournament.tsv”. Save the graph into “comparison.gif” and upload it with your source code in one zip file. The procedure should be nearly identical to what you did on the last assignment to compare “randomized.tsv” and “ga.tsv”.