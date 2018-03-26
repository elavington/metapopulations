//
//  main.cpp
//  FAB
//
//  Created by Pierre Cristofari on 09/04/2017.
//  Copyright © 2017 Pierre Cristofari. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>   // for std::string


#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include "constants.h"
#include "island.hpp"
#include "random.hpp"
#include "interactions.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <typeinfo>

using namespace std;
using std::vector;


int main (int argc, char * const argv[]) {
    // In the executable file= we pass:
    // 1) Parameters_X.txt
    // 2) X -> number of folder where we put the results
    
    
    /**************************************************************************/
 // test reading from file and writing files - GOOOD STUFF
    /**************************************************************************/
    cout << " ----------------------------" <<endl;
    cout << " Hello Friend! Let's go! " << endl;
    cout << " ----------------------------" <<endl;

    
    /*******************************************/
    //Declare parameters:
    /*******************************************/
    int number_type_islands=5;
    int N=0;
    int number_of_days=0;
    int number_docs=0;
    int number_nurses=0;
    int number_patients=0;
    int number_trays=0;
    int number_walls=0;
    int bin_time=8;
    
    vector <double> NUMBER_CLEAN_8H(number_type_islands);
    vector <double> LEVEL_CLEAN_8H(number_type_islands);
    vector <vector <double> > MATRIX_PROBA_8H (number_type_islands, std::vector<double> (number_type_islands,0.));
    vector <vector <double> > MATRIX_NUMBER_INTER_8H (number_type_islands, std::vector<double> (number_type_islands,0.));
    vector <double> CARRYING_CAPA_READ(number_type_islands);
    vector <double > TIME_DISTRIB(bin_time, 0.);

    
    /*******************************************/
    //Read Parameters:
    /*******************************************/
    ifstream fichier(argv[1], ios::in);
    if(fichier){
        string chaine1, delimiter;
        fichier >> chaine1 >> N;
        fichier >> chaine1 >> number_of_days;
        fichier>> chaine1 >> number_docs;
        fichier>> chaine1 >> number_nurses;
        fichier>> chaine1 >> number_patients;
        fichier>> chaine1 >> number_trays;
        fichier>> chaine1 >> number_walls;
        //Read CARRYING_CAPA_READ:
        fichier>> delimiter;
        fichier>> chaine1;
        for(int j=0; j<number_type_islands; j++){
            fichier>> CARRYING_CAPA_READ[j];}

    // Read MATRIX_NUMBER:
        fichier >> delimiter;
        for(int j=0; j<number_type_islands; j++){
        fichier >> chaine1;
        for(int i=0; i<number_type_islands; i++){
            fichier>> MATRIX_NUMBER_INTER_8H[j][i];      }}
        
        // Read MATRIX_PROBA:
        fichier >> delimiter;
        for(int j=0; j<number_type_islands; j++){
            fichier >> chaine1;
            for(int i=0; i<number_type_islands; i++){
                fichier>> MATRIX_PROBA_8H[j][i];      }}
        
        fichier>> delimiter;
        fichier>> chaine1;
        for(int i=0; i<number_type_islands; i++){
            fichier>> NUMBER_CLEAN_8H[i]; }
        fichier>> chaine1;
        for(int i=0; i<number_type_islands; i++){
            fichier>> LEVEL_CLEAN_8H[i]; }
        
        fichier>> chaine1;
        for(int i=0; i<bin_time; i++){
            fichier>>TIME_DISTRIB[i]; }


        fichier.close();
    }
    else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
    
    
    
    
//     Making directory for results
//
//        const std::string baseFolderName = "Results";
//        int k= 0
//        std::ostringstream FolderName;
//        FolderName << baseFolderName << k;
//        const char * FolderNamechar=FolderName.str().c_str(); // convert stremstring to string, then to char.
//        mkdir(FolderNamechar,0077);

    
    
    //EXTRACT NUMBER TO CREATE FOLDER
    std::string str(argv[1]);
    const char* NAME=argv[1];
    cout << " tessst = " << argv[1] << endl; 
    //  cout << " Name = " << NAME << endl;
    int address = 0;
    sscanf(NAME, "%*[^0-9]%d ", &address);
    
   //  Making directory for results
        const std::string baseFolderName = "RESULTS_";
        std::ostringstream FolderName;
    FolderName << baseFolderName << address;
        const char * FolderNamechar=FolderName.str().c_str(); // convert stremstring to string, then to char.
        mkdir(FolderNamechar,0777);
    cout << "           " << endl;

    cout << " AFTER MKDIR " << endl;
    
    
    
    
    
    
    
    /**************************************************************************/
    // Always  steps in the main:
    // 1. Define Islands
    // 2. Define Matrices of interactions
    // 3. Perform interactions
    // 4. Print results : analysis in Python
    /**************************************************************************/
    
    vector < vector <Island> > ISLANDS (5);
    
    for( int l=0;l <N; l++){
        
        ISLANDS.clear(); // reset to zero
        ISLANDS.resize(5);
        
        // Test to store different daugthers in a vector:
        //	std::vector<Island*> List;
        //	List.push_back(new Island);
        //	List.push_back(new Doctor);
        
        
        // 1. Define Islands
        
     //   cout << " number_docs = "   << number_docs  << endl;
        
        //Doctors:
        ISLANDS[0].resize(number_docs);
        //Nurses:
        ISLANDS[1].resize(number_nurses);
        //Patients:
        ISLANDS[2].resize(number_patients);
        //Tray:
        ISLANDS[3].resize(number_trays);
        //Wall:
        ISLANDS[4].resize(number_walls);
        
        set_type_vector_multiple_island(ISLANDS,CARRYING_CAPA_READ); //set type and maximum caryring capacity
        
        
    
        // Contaminate one patient
        
        ISLANDS[2][0].set_number_bacteria_and_time(CARRYING_CAPA_READ[2],0);
        ISLANDS[2][0].set_status_of_island(1);
        

        // 2. Define Matrices of interactions
        vector < vector  <double> > MATRIX_INTER;
        vector <double > MATRIX_CLEAN;
        vector <double > TIME_DISTRIB_WALL;

        define_MATRIX_EFFECTIVE_INTERACTIONS(MATRIX_NUMBER_INTER_8H,MATRIX_INTER, ISLANDS);
        define_MATRIX_EFFECTIVE_CLEAN (NUMBER_CLEAN_8H, MATRIX_CLEAN, ISLANDS,TIME_DISTRIB,TIME_DISTRIB_WALL);



        
        
        
       // 3. Perform interactions over N days.

        N_days_interactions(number_of_days,ISLANDS, MATRIX_PROBA_8H,MATRIX_INTER, MATRIX_CLEAN, LEVEL_CLEAN_8H, TIME_DISTRIB );



        // 4. Print results : analysis in Python, for the analysis in Python
//
//
//
//    // Dirty way of writing in the files in the created folder:

        char basis[100];
        char filename[100];
        sprintf(basis, "results_");
        sprintf(filename, "_%d.txt", l);
        //use string, then put them together in sstream:
        const std::string base_folder =FolderName.str();
        const std::string inter= "/";
        const std::string file= string(filename);
        const std::string basis_string= string (basis);
        std::ostringstream total_path;
        total_path<<base_folder<<inter<<basis_string<<address<<filename;
        const char* Total_path_char=total_path.str().c_str(); // convert stremstring to string, then to char.
        cout << " Total path_string   ==  " << total_path.str() << endl;
        std::string total_path_string=total_path.str();
        char path_char_array[100];
        strcpy(path_char_array,Total_path_char); //convert const char* into char - make sure not to overflow it over 100!

        
        
            vector <double>    TIME;
            define_TIME_grid ( TIME, 0, 24.*number_of_days, 1000 );
           print_in_file ( TIME, ISLANDS , path_char_array );
         //   print_docs_in_file ( TIME, ISLANDS , path_char_array );
       //  ISLANDS[0][1].show_TIME_AND_NUMBER_BACTERIA_MEMORY(); 


    }
    return 0.;
    
}





