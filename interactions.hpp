//
//  interactions.hpp
//  FAB
//
//  Created by Pierre Cristofari on 09/04/2017.
//  Copyright © 2017 Pierre Cristofari. All rights reserved.
//

#ifndef interactions_hpp
#define interactions_hpp

#include <stdio.h>

#include "island.hpp"
using namespace std;


void define_TIME_grid ( vector <double> &TIME, double begin, double end, int step );
void set_type_vector_multiple_island (std::vector < vector<Island> > & ISLANDS, std::vector<double> & MAXIMUM_CAPA); 

void island_to_island_interaction(vector < vector <double> > MATRIX_PROBA , Island & D1, Island & D2, double timing);
void island_to_island_interaction_TEST(Island & D1, Island & D2, double timing);

void clean_one_island (vector <double> LEVEL_CLEAN, Island &D1, double temps);

void one_day_interaction(vector < vector<Island> > &ISLANDS,  vector < vector <double> > MATRIX_PROBA , vector < vector <double> > &MATRIX_INTER, vector <double> &CLEAN,vector <double> LEVEL_CLEAN,vector<double> TIME_DISTRIB , int number_day );


void N_days_interactions (int N, vector < vector<Island> > &ISLANDS, vector < vector <double> > MATRIX_PROBA, vector < vector <double> > MATRIX_INTER, vector <double> &CLEAN,vector <double> LEVEL_CLEAN,vector<double> TIME_DISTRIB);


void define_MATRIX_EFFECTIVE_INTERACTIONS (vector < vector< double> > MATRIX_NUMBER, vector < vector< double> > &MATRIX , vector < vector <Island> > &ISLANDS );

void define_MATRIX_EFFECTIVE_CLEAN ( vector<double > NUMBER_CLEAN, vector < double > &CLEAN, vector < vector <Island> > &ISLANDS, vector<double > &TIME_DISTRIB, vector<double > &TIME_DISTRIB_WALL); 

void show_2D_vector_matrix ( vector < vector< double> > &MATRIX);
void show_1D_vector (   vector< double> &MATRIX);
void print_in_file ( vector <double > &TIME, vector <vector <Island> > & ISLANDS , char filename0[] );
void print_docs_in_file ( vector <double > &TIME, vector <vector <Island> > & ISLANDS , char filename0[] ); 



#endif /* interactions_hpp */

