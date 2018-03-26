//
//  interactions.cpp
//  FAB
//
//  Created by Pierre Cristofari on 09/04/2017.
//  Copyright © 2017 Pierre Cristofari. All rights reserved.
//

/*
 *  interactions.cpp
 *  FAB
 *
 *  Created by Pierre Cristofari on 07/02/2017.
 *  Copyright 2017 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include "interactions.hpp"
#include "island.hpp"
#include "random.hpp"
#include "math.h"

using namespace std;
using std::vector;

//All interactions between the different islands:

//Doctors:
int const number_of_island_type=5;

// per 8 hours:
//double const MATRIX_PROBA_INTERACTIONS[number_of_island_type][number_of_island_type]={{0.04,0.08,0.2,0.,0.02},{0.08,0.15,0.18,0.05,0.02},{0.2,0.18,0.05,0.1,0.02},{0.,0.05,0.1,0.11,0.},{0.02,0.02,0.02,0.,0.}};
//double const MATRIX_PROBA_INTERACTIONS[number_of_island_type][number_of_island_type]={{0.04,0.08,0.17,0.,0.106},{0.08,0.15,0.17,0.05,0.106},{0.17,0.17,0.05,0.1,0.106},{0.,0.05,0.1,0.1,0.},{0.106,0.106,0.106,0.,0.}};


// Typical value in one day (no matter the number of islands)
//double const MATRIX_NUMBER_INTERACTIONS[number_of_island_type][number_of_island_type]={{10,16,12,0,4},{16,48,24,6,12},{12,24,4,1,1.5},{0,6,1,2,0},{4,12,1.5,0,0}};
//double const MATRIX_NUMBER_INTERACTIONS[number_of_island_type][number_of_island_type]={{10,16,13.93,0,4.68},{16,48,32.4,6,13.25},{13.93,32.4,4,1,1.5},{0,6,1,2,0},{4.68,13.25,1.5,0,0}};

// per 8 hours:
//double const NUMBER_CLEAN[number_of_island_type]={2,2,1.5,1,1};// 24 16 2 1 0.033
//double const LEVEL_CLEAN[number_of_island_type]={0.6,0.6,0.6,0.9,0.9}; //0.9 0.99





//double const LEVEL_CLEAN[number_of_island_type]={0.5,0.6,0.5,0.9,0.98}; //0.9 0.99


void define_TIME_grid ( vector <double> &TIME, double begin, double end, int step ){
    TIME.resize(step);
    TIME[0]=begin; TIME[step-1]=end;
    for (int i=1; i<step; i++) {
        TIME[i]=TIME[0]+i/(step-1.)*TIME[step-1];
    }
    
}





void set_type_vector_multiple_island (std::vector < vector<Island> > & ISLANDS, std::vector<double> & MAXIMUM_CAPA){
    for (int i=0; i<ISLANDS.size(); i++) {
        for (int j=0; j<ISLANDS[i].size(); j++) {
            ISLANDS[i][j].set_type_of_island(i);}
    }
    
    for (int i=0; i<ISLANDS.size(); i++) {
        for (int j=0; j<ISLANDS[i].size(); j++) {
            int type_temp=ISLANDS[i][j].get_type_of_island();
            ISLANDS[i][j].set_maximum_carrying_capacity(MAXIMUM_CAPA[type_temp]);}
    }
    
    
    
    
    
    
}





void define_MATRIX_EFFECTIVE_INTERACTIONS (vector < vector< double> > MATRIX_NUMBER, vector < vector< double> > &MATRIX , vector < vector <Island> > &ISLANDS ){
    
    //To take into account that the intial Matrices are given for 8 hours:
    double factor_all_day=3.;
    
    MATRIX.resize(number_of_island_type);
    for (int j=0; j<number_of_island_type; j++) {MATRIX[j].resize(number_of_island_type);}
    
    
    
    for (int j=0; j<number_of_island_type; j++) {
        for (int i=0; i<number_of_island_type; i++) {
            
            if( i==j) {MATRIX[i][j]=combinaison(ISLANDS[i].size(), 2)*factor_all_day*MATRIX_NUMBER[i][j]; }
            if(i>j) {MATRIX[i][j]=ISLANDS[i].size()*ISLANDS[j].size()*factor_all_day*MATRIX_NUMBER[i][j];}
            if (i<j) {MATRIX[i][j]=-1; }
        }
    }
}


void show_2D_vector_matrix ( vector < vector< double> > &MATRIX){
    // Make sure it is a N*N Matrix :
    for(int i=0; i< MATRIX.size(); i++){
        MATRIX[i].resize(MATRIX.size());  }
    
    for (int i=0; i< MATRIX.size(); i++){
        for (int j=0; j< MATRIX[i].size(); j++){
            cout << MATRIX[j][i]<< "		" ; }
        cout <<endl;
    }
}

void show_1D_vector (   vector< double> &MATRIX){
    for (int i=0; i<MATRIX.size(); i++) {
        cout << MATRIX[i] << endl;
    }
}



void define_MATRIX_EFFECTIVE_CLEAN (vector<double > NUMBER_CLEAN, vector < double > &CLEAN, vector < vector <Island> > &ISLANDS, vector<double > &TIME_DISTRIB, vector<double > &TIME_DISTRIB_WALL)
{
    CLEAN.resize(number_of_island_type);
    double factor_all_day=3.;
    
    for (int i=0; i<number_of_island_type; i++) {
        CLEAN[i]=NUMBER_CLEAN[i]*factor_all_day*ISLANDS[i].size();
    }
    
 //TIME dsitrib defines "a profile" over 8 hours
//    double sum=0;
//    for (int i=0; i<TIME_DISTRIB.size();  i++){
//        sum=sum+TIME_DISTRIB[i];}
//    
//    
//    vector<double > INTEGRAL;
//    
//    INTEGRAL.resize(TIME_DISTRIB.size(), 0.);
//    INTEGRAL[0]=TIME_DISTRIB[0];
//    for (int i=1; i<TIME_DISTRIB.size();  i++){
//        INTEGRAL[i]=INTEGRAL[i-1]+TIME_DISTRIB[i]*(i+1-i);}
//    
//    // FOR WALLS :
//    TIME_DISTRIB_WALL.resize(CLEAN[4], 0.);
//
//    
//    // TIME_DISTRIB_WALL carries the timing of cleaning of the walls, randomly drawn, for a slice of time from 0 to 8 hours 
//    double temp=0;
//    int p=0;
//    for (int i=0; i<TIME_DISTRIB_WALL.size();  i++){
//        temp=frand(0, INTEGRAL[INTEGRAL.size()-1]+1);
//        
//        p=0;
//       double add=TIME_DISTRIB[0];
//        while (add<INTEGRAL[INTEGRAL.size()-1] && add<temp){
//            p=p+1;
//            add=add+TIME_DISTRIB[p];
//                }
//        
//        double dist_encadrement=INTEGRAL[p]-INTEGRAL[p-1];
//        double dist=temp-INTEGRAL[p-1];
//        
//   //     cout <<" temp =  " << temp<<  "   add =    "<< add <<  endl;
//       
//        
//        TIME_DISTRIB_WALL[i]=p+dist/dist_encadrement; // return time between 0 and 7 hours.
//        cout << " TIME_DISTRIB_WALL[i]  = " << TIME_DISTRIB_WALL[i] << endl; 
//        }
//    

}












void island_to_island_interaction(vector <vector <double> > MATRIX_PROBA , Island & D1, Island & D2, double timing){
    double proba_interaction= MATRIX_PROBA[D1.get_type_of_island()][D2.get_type_of_island()];
    
    
    D1.calculate_expansion_bacteria(timing);
    D2.calculate_expansion_bacteria(timing);
    
    double n1=D1.get_number_bacteria();
    double n2= D2.get_number_bacteria();
    
    int type1=D1.get_type_of_island();
    int type2=D2.get_type_of_island();
    
    
        double random=frand(0,1);
        
        
        if (random<proba_interaction) { 		//cout << " SUCESSFUL INTERACTION   btw type : "<<  D1.get_type_of_island()<< "		and type : " <<D2.get_type_of_island() << endl;
            if (n1<n2) {
                D1.set_number_bacteria_and_time(n1+0.01*(n2-n1),timing); 		}
            else {		D2.set_number_bacteria_and_time(n2+.01*(n1-n2),timing); }
        }
    
    
}




//void island_to_island_interaction(Island & D1, Island & D2, double timing){
//	double proba_interaction= MATRIX_PROBA_INTERACTIONS[D1.get_type_of_island()][D2.get_type_of_island()];
//
//	//forbid interaction bewteen
//
//	D1.calculate_expansion_bacteria(timing);
//	D2.calculate_expansion_bacteria(timing);
//
//
//	// ADD INTERDICTION OF INTERACTION
//
//
//	//double maximum=max (D1.get_number_bacteria(), D2.get_number_bacteria());
//	//
//	double n1=D1.get_number_bacteria();
//	double n2= D2.get_number_bacteria();
//
//	double random=frand(0,1);
//
//
//	if (random<proba_interaction) { 		//cout << " SUCESSFUL INTERACTION   btw type : "<<  D1.get_type_of_island()<< "		and type : " <<D2.get_type_of_island() << endl;
//		if (n1<n2) {
//			D1.set_number_bacteria_and_time(n1+0.001*D2.get_number_bacteria(),timing); 		}
//		else {		D2.set_number_bacteria_and_time(n2+.001*D1.get_number_bacteria(),timing); }
//	}
//
//
//}









void clean_one_island (vector <double> LEVEL_CLEAN, Island &D1, double temps){
    if(D1.get_status_of_island()==0){
        int type=D1.get_type_of_island();
        double n1=D1.get_number_bacteria();
        D1.set_number_bacteria_and_time((1-LEVEL_CLEAN[type])*n1,temps);
        D1.memorize();
    }
}




void one_day_interaction(vector < vector<Island> > &ISLANDS,  vector < vector <double> > MATRIX_PROBA , vector < vector <double> > &MATRIX_INTER, vector <double> &CLEAN,vector <double> LEVEL_CLEAN, vector<double> TIME_DISTRIB , int number_day ){
    // this sets interactions over one day
    
    double total_number_of_interactions=0;
    for (int i=0;i<number_of_island_type; i++) {
        for (int j=0; j<i+1; j++) {
            total_number_of_interactions=total_number_of_interactions+MATRIX_INTER[i][j]; }
    }
    int total_number_of_events=total_number_of_interactions;
    
 // TIME FOR CLEANING WALLS, taking into account the new profile.
    double sum=0;
    for (int i=0; i<TIME_DISTRIB.size();  i++){
        sum=sum+TIME_DISTRIB[i];}

    vector<double > INTEGRAL;
    INTEGRAL.resize(TIME_DISTRIB.size(), 0.);
    INTEGRAL[0]=TIME_DISTRIB[0];
    for (int i=1; i<TIME_DISTRIB.size();  i++){
        INTEGRAL[i]=INTEGRAL[i-1]+TIME_DISTRIB[i]*(i+1-i);}
    
    
    double total_number_of_wall_cleaning=CLEAN[4];
  //  cout << " total number of wall cleaning " << total_number_of_wall_cleaning << endl;
    
    vector <double> TIME_OF_CLEAN_WALL_24HOURS (total_number_of_wall_cleaning,0.);

    double temp=0;
    int p=0;
    for (int i=0; i<TIME_OF_CLEAN_WALL_24HOURS.size();  i++){
        temp=frand(0, INTEGRAL[INTEGRAL.size()-1]);
        p=0;
        double add=TIME_DISTRIB[0];
        while (add<INTEGRAL[INTEGRAL.size()-1] && add<temp){
            p=p+1;
            add=add+TIME_DISTRIB[p];        }
    

        double dist_encadrement=1.;
        double dist=1.;
        if (p==0){
             dist_encadrement=INTEGRAL[0]-0;
             dist=INTEGRAL[0]-temp;}
        else{
             dist_encadrement=INTEGRAL[p]-INTEGRAL[p-1];
             dist=temp-INTEGRAL[p-1];}
    
        TIME_OF_CLEAN_WALL_24HOURS[i]= (p+dist/dist_encadrement)*intrand(1, 3)+number_day*24.; // return time between 0 and 24 hours for each day.
    }
    
    


    
    
    std::sort (TIME_OF_CLEAN_WALL_24HOURS.begin(), TIME_OF_CLEAN_WALL_24HOURS.end());
//    cout << " TIME_OF_CLEAN_WALL_24HOURS  " << endl;
//show_1D_vector(TIME_OF_CLEAN_WALL_24HOURS);


   double total_number_of_clean=0;
    for (int i=0; i<number_of_island_type; i++) {
        total_number_of_events=total_number_of_events+CLEAN[i];
        total_number_of_clean=total_number_of_clean+CLEAN[i];}

//    cout << " total number of clean = " << total_number_of_clean << endl;
//    cout << " total number of events = " << total_number_of_events << endl;



    vector <double> TIME_OF_INTERACTIONS_NO_WALL;
    TIME_OF_INTERACTIONS_NO_WALL.resize(total_number_of_events-total_number_of_wall_cleaning); // in hours!
    for (int i=0; i<TIME_OF_INTERACTIONS_NO_WALL.size(); i++) {TIME_OF_INTERACTIONS_NO_WALL[i]=frand(24.*number_day, 24.*(number_day+1.)); }
    std::sort (TIME_OF_INTERACTIONS_NO_WALL.begin(), TIME_OF_INTERACTIONS_NO_WALL.end());


   vector <double> TIME_OF_INTERACTIONS=TIME_OF_INTERACTIONS_NO_WALL;
//
//    // Concatenate to get all times of all events in ONE array:
//    TIME_OF_INTERACTIONS.insert( TIME_OF_INTERACTIONS.end(), TIME_OF_CLEAN_WALL_24HOURS.begin(), TIME_OF_CLEAN_WALL_24HOURS.end());
//    std::sort (TIME_OF_INTERACTIONS.begin(), TIME_OF_INTERACTIONS.end());




 // TIME FOR ALL INTERACTIONS BUT REMOVING THE WALLS
    double count_doc=0;
    double count_nurse=0;
    double count_patient=0;
    double count_tray=0;
    double count_wall=0;

    int pwall=0;
    // Then proceed for the entire day:

  //  cout << " jsut before the loop TIME_OF_INTERACTIONS "  << endl;
    for (int p=0; p<TIME_OF_INTERACTIONS.size(); p++) {
        
   //      clean wall if this the time for wall cleaning
        
        if(TIME_OF_INTERACTIONS[p]==TIME_OF_CLEAN_WALL_24HOURS[pwall] and (pwall<TIME_OF_CLEAN_WALL_24HOURS.size()-1)){
            int m=intrand(0,ISLANDS[4].size()-1);
            clean_one_island(LEVEL_CLEAN, ISLANDS[4][m],TIME_OF_INTERACTIONS[p]);
            pwall=pwall+1;
        }
        
   //      resume classic procedure
        
        double    draw= frand(0.,total_number_of_events-total_number_of_wall_cleaning);

        double count=MATRIX_INTER[0][0];
        int i=0, j=0, k=0;
        // the following while breaks if draw goes over count or i=5
        //  cout << " THIS IS A NEW DRAW ________________ draw =  " <<draw <<  endl;
        while (draw>count && i<number_of_island_type && j<number_of_island_type) {
            i++; if (i==(number_of_island_type)){j++; i=j;  }
            if(i<number_of_island_type && j<number_of_island_type){
                count=count+MATRIX_INTER[i][j];
                //   cout << " MATRIX_INTER[i][j] = " << MATRIX_INTER[i][j] << endl;
            }
        }
        
        if (i==number_of_island_type) {i=number_of_island_type-1; } // if i has reached number_of_island_type, then we deacreae it

        while (draw>count && k<number_of_island_type){
            count=count+CLEAN[k]; k++;                    }

        //    cout << TIME_OF_INTERACTIONS[p] << " -> TIME" << endl;
        double temp=0;
        if(k==0){ // This is an interaction!
            // several islands suceptible of interacting.
            int m=intrand(0, ISLANDS[i].size()-1);
            int n=intrand(0, ISLANDS[j].size()-1);

            double n1_before= ISLANDS[i][m].get_number_bacteria();
            double n2_before= ISLANDS[j][n].get_number_bacteria();


            if(((i==2 && j==4)&& n==m) ||((i==4 && j==2)&& n==m) ){ } // Removing wall, patient interaction if not the same index.
            else{
                if ((i!=j)||(n!=m)) {
                    //   cout << " i = 4 , NEW INTERACTION  -  m =  " << m <<  endl;
                    //  if(i==4 && j== 2)
                    island_to_island_interaction(MATRIX_PROBA, ISLANDS[i][m],ISLANDS[j][n],TIME_OF_INTERACTIONS[p]);}
            }
        }
      //   If (k=!0) (Cleaning)
        else {
            if (k==1) {count_doc=count_doc+1; }
            if (k==2) {count_nurse=count_nurse+1; }
            if (k==3) {count_patient=count_patient+1; }
            if (k==4) {count_tray=count_tray+1; }
            if (k==5) {count_wall=count_wall+1; }
            int m=intrand(0,ISLANDS[k-1].size()-1);
            
//            if (k==1){
//                cout << "k ==1;   m = " << m << endl;
//            }
            clean_one_island(LEVEL_CLEAN, ISLANDS[k-1][m],TIME_OF_INTERACTIONS[p]);
            
//            cout << " -------CLEANING -----" << endl;
//            cout << " count doc = " << count_doc     << endl;
//            cout << " count nurses = " << count_nurse     << endl;
//            cout << " count patient = " << count_patient     << endl;
//            cout << " count tray = " << count_tray     << endl;
//            cout << " count wall = " << count_wall     << endl;

            
        }
    
    }
    
}










void N_days_interactions (int N, vector < vector<Island> > &ISLANDS, vector < vector <double> > MATRIX_PROBA, vector < vector <double> > MATRIX_INTER, vector <double> &CLEAN,vector <double> LEVEL_CLEAN,vector<double> TIME_DISTRIB){
    for (int i=0; i<N; i++) {
        
        if(i==30){  ISLANDS[2][0].set_number_bacteria_and_time(0.,i*24.); 
            ISLANDS[2][0].set_status_of_island(0);}
        
        cout << " Day = " << i << endl;
        one_day_interaction(ISLANDS, MATRIX_PROBA, MATRIX_INTER, CLEAN, LEVEL_CLEAN,TIME_DISTRIB , i);
        
    }
}







void print_in_file ( vector <double > &TIME, vector <vector <Island> > & ISLANDS , char filename0[] ){
    cout << " Printing results .... " << endl; 
    
    ofstream fwritefile(filename0);
    if (!fwritefile.is_open())
        cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
    else{		
        
        // première colonne TIME 
        // premiere ligne 'header" 
        // en colonnes le nombre de bacteries pour les différentes Islands 
        
        
        fwritefile << 0<<"		"; 
        
        for( int i=0; i<ISLANDS.size(); i++){
            for (int j=0; j< ISLANDS[i].size(); j++) {
                fwritefile<< ISLANDS[i][j].get_type_of_island()  <<"		";  	}
        }
        fwritefile<<endl; 
        
        for (int k=0; k< TIME.size(); k++){
            fwritefile << TIME[k] <<"		"; 
            
            for (int i = 0; i < ISLANDS.size(); i++){		 
                for (int j=0; j<ISLANDS[i].size(); j++) {				
                    fwritefile << ISLANDS[i][j].calculate_bacteria (TIME[k])<< "		";  
                }
            }
            fwritefile <<endl; 
        }
    }	
    
    fwritefile.close();	
    
    cout << " results Printed ! " << endl; 
    
}

void print_docs_in_file ( vector <double > &TIME, vector <vector <Island> > & ISLANDS , char filename0[] ){
    cout << " Printing results .... " << endl;
    
    ofstream fwritefile(filename0);
    if (!fwritefile.is_open())
        cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
    else{
        
        // première colonne TIME
        // premiere ligne 'header"
        // en colonnes le nombre de bacteries pour les différentes Islands
        
        
        fwritefile << 0<<"        ";
        
            for (int j=0; j< ISLANDS[0].size(); j++) {
                fwritefile<< ISLANDS[0][j].get_type_of_island()  <<"        ";      }
        fwritefile<<endl;
        
        for (int k=0; k< TIME.size(); k++){
            fwritefile << TIME[k] <<"        ";
            
                for (int j=0; j<ISLANDS[0].size(); j++) {
                    fwritefile << ISLANDS[0][j].calculate_bacteria (TIME[k])<< "        ";
                }
            fwritefile <<endl;
        }
    }
    
    fwritefile.close();

    cout << " results Printed ! " << endl;
}
