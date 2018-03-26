//
//  island.cpp
//  FAB
//
//  Created by Pierre Cristofari on 09/04/2017.
//  Copyright © 2017 Pierre Cristofari. All rights reserved.
//

#include "island.hpp"
/*
 *  island.cpp
 *  FAB
 *
 *  Created by Pierre Cristofari on 06/02/2017.
 *  Copyright 2017 __MyCompanyName__. All rights reserved.
 *
 */
#include "constants.h"
#include "interactions.hpp"
#include "island.hpp"
#include "random.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <math.h>



using namespace std;
using std::vector;




Island::Island(){
    
    timer=0.;
    number_bacteria=0.;
    TIME_MEMORY.resize(0);
    NUMBER_BACTERIA_MEMORY.resize(0);
    TIME_MEMORY.push_back(timer);
    NUMBER_BACTERIA_MEMORY.push_back(number_bacteria);
    tdoublement=8.;
    status=0;
    
}


void Island::set_number_bacteria_and_time ( double new_n, double t0){
    if (new_n<=pow(10., 0)) {
        number_bacteria=0;}
    else {
        if (new_n <= maximum_carrying_capacity) {
            number_bacteria=new_n;  }
        else {number_bacteria= maximum_carrying_capacity;}
        
        if (t0>=timer) {
            timer=t0;}
    }
    memorize();
}


void Island::clean(){
    number_bacteria=0.; }



void  Island::add_number_bacteria ( double add ){
    number_bacteria=number_bacteria+add; }

double Island::get_timer(){
    return timer; }

double Island::get_number_bacteria(){
    return number_bacteria;}

int Island::get_type_of_island(){
    return type_of_island; }

int Island::get_status_of_island(){
    return status;}


void Island::set_type_of_island( int type){
    type_of_island=type;}

void Island::set_status_of_island (int stat){
    status=stat;}

void Island::set_maximum_carrying_capacity( double capa){
    maximum_carrying_capacity=capa; }




void Island::calculate_expansion_bacteria (double newtime){
    //if (newtime>=timer){
    double newnumberbacteria=number_bacteria*pow(2.,(newtime-timer)/tdoublement );
    
    if (newnumberbacteria < maximum_carrying_capacity) {
        number_bacteria=newnumberbacteria; 		}
    else {number_bacteria=maximum_carrying_capacity; }
    
    //}
    timer=newtime;
}


// Memorize first version ok:
void Island::memorize(){
    //if (number_bacteria== NUMBER_BACTERIA_MEMORY[NUMBER_BACTERIA_MEMORY.size()-1]) {}
    //else {
    
    if (timer==TIME_MEMORY[TIME_MEMORY.size()-1]) {
        TIME_MEMORY[TIME_MEMORY.size()-1]=timer;
        NUMBER_BACTERIA_MEMORY[NUMBER_BACTERIA_MEMORY.size()-1]=number_bacteria;
    }
    else {
        if (timer>TIME_MEMORY[TIME_MEMORY.size()-1])	{
            TIME_MEMORY.push_back(timer);
            NUMBER_BACTERIA_MEMORY.push_back(number_bacteria);
        }
    }
    //}
}


// CHANTIER :
//void Island::memorize(){
//
//	if (number_bacteria=! NUMBER_BACTERIA_MEMORY[NUMBER_BACTERIA_MEMORY.size()-1]) {
//
//		if (timer==TIME_MEMORY[TIME_MEMORY.size()-1]) {
//		TIME_MEMORY[TIME_MEMORY.size()-1]=timer;
//		NUMBER_BACTERIA_MEMORY[NUMBER_BACTERIA_MEMORY.size()-1]=number_bacteria;
//		}
//		else {
//			if (timer>TIME_MEMORY[TIME_MEMORY.size()-1])	{
//				TIME_MEMORY.push_back(timer);
//				NUMBER_BACTERIA_MEMORY.push_back(number_bacteria);
//			}
//		}
//	}
//		else {
//							TIME_MEMORY[TIME_MEMORY.size()-1]=timer;
//				NUMBER_BACTERIA_MEMORY[NUMBER_BACTERIA_MEMORY.size()-1]=number_bacteria;
//
//
//			}
//}



double Island::calculate_bacteria(double temps){
    int compt=0;
    while (temps>=TIME_MEMORY[compt]&& compt<(TIME_MEMORY.size()-1)){compt++;}
    
    
    if (NUMBER_BACTERIA_MEMORY[compt-1]<=pow(10, -10)) {
        return 0.; 	}
    
    else {
        
        double new_number= NUMBER_BACTERIA_MEMORY[compt-1]*pow(2., (temps-TIME_MEMORY[compt-1])/tdoublement);
        
        
        //		if(temps>=8000){
        //		cout << " NUMBER_BACTRIA compt-1   = " << NUMBER_BACTERIA_MEMORY[compt-1] << endl;
        //		cout << "	pow(2., (temps-TIME_MEMORY[compt-1])/tdoublement) == " << pow(2., (temps-TIME_MEMORY[compt-1])/tdoublement) << endl;
        //		cout << " product = " << new_number << endl;
        //		}
        
        if (new_number<=maximum_carrying_capacity) {
            return new_number;
        }
        else {
            return maximum_carrying_capacity;
        }
        
        //	if (compt>1 && NUMBER_BACTERIA_MEMORY[compt]==NUMBER_BACTERIA_MEMORY[compt-1]) {
        //		return NUMBER_BACTERIA_MEMORY[compt]; }
        //	else {return NUMBER_BACTERIA_MEMORY[compt]*pow(2., (temps-TIME_MEMORY[compt])/tdoublement);
        //
        //
    }
    
    
}

double Island::calculate_bacteria_TEST(double temps){
    int compt=0;
    while (temps>=TIME_MEMORY[compt]&& compt<(TIME_MEMORY.size()-1)){compt++;}
    
    
    if (NUMBER_BACTERIA_MEMORY[compt-1]==0) {
        return 0.; 	}
    
    else {
        
        
        
        double new_number= NUMBER_BACTERIA_MEMORY[compt-1]*pow(2., (temps-TIME_MEMORY[compt-1])/tdoublement);
        
        
        
        cout << " NUMBER_BACTRIA compt-1   = " << NUMBER_BACTERIA_MEMORY[compt-1] << endl;
        cout << "	pow(2., (temps-TIME_MEMORY[compt-1])/tdoublement) == " << pow(2., (temps-TIME_MEMORY[compt-1])/tdoublement) << endl;
        cout << " product = " << new_number << endl;
        if (new_number<=maximum_carrying_capacity) {
            return new_number;
        }
        else {
            return maximum_carrying_capacity;
        }
        
    }
    
    //	if (compt>1 && NUMBER_BACTERIA_MEMORY[compt]==NUMBER_BACTERIA_MEMORY[compt-1]) {
    //		return NUMBER_BACTERIA_MEMORY[compt]; }
    //	else {return NUMBER_BACTERIA_MEMORY[compt]*pow(2., (temps-TIME_MEMORY[compt])/tdoublement);
    //	
    //	
    //	}	
    
    
}





void Island::show_NUMBER_BACTERIA_MEMORY(){
    for (int i=0; i<NUMBER_BACTERIA_MEMORY.size(); i++) {
        cout << NUMBER_BACTERIA_MEMORY[i] << "		"; 
    } cout << endl; 
    
}


void Island::show_TIME_MEMORY(){
    for (int i=0; i<TIME_MEMORY.size(); i++) {
        cout << TIME_MEMORY[i] <<  "		"; 
    } cout << endl; 
    
}


void Island::show_TIME_AND_NUMBER_BACTERIA_MEMORY(){
    for (int i=0; i<TIME_MEMORY.size(); i++) {
        cout << TIME_MEMORY[i]/(24.) <<  "		" << NUMBER_BACTERIA_MEMORY[i] << endl; 
    } cout << endl; 
    
}







// Doctor 

Doctor::Doctor(){}
