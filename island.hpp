//
//  island.hpp
//  FAB
//
//  Created by Pierre Cristofari on 09/04/2017.
//  Copyright © 2017 Pierre Cristofari. All rights reserved.
//

#ifndef island_hpp
#define island_hpp

#include <stdio.h>

/*
 *  island.h
 *  FAB
 *
 *  Created by Pierre Cristofari on 06/02/2017.
 *  Copyright 2017 __MyCompanyName__. All rights reserved.
 *
 */
#include <vector>
#include <string>
using namespace std;
using std::vector;



#ifndef DEF_ISLAND
#define DEF_ISLAND

class Island{
    
public:
    
    Island(); // constructor
    void clean();
    void set_number_bacteria_and_time ( double new_n, double t0);
    void  add_number_bacteria ( double add );
    double get_timer();
    double get_number_bacteria();
    int get_type_of_island();
    int get_status_of_island();
    void set_type_of_island (int type);
    void calculate_expansion_bacteria (double newtime);
    void set_status_of_island(int stat);
    void set_maximum_carrying_capacity( double capa);
    
    double calculate_bacteria(double temps);
    double calculate_bacteria_TEST(double temps);
    
    void memorize();
    void show_NUMBER_BACTERIA_MEMORY();
    void show_TIME_MEMORY();
    void show_TIME_AND_NUMBER_BACTERIA_MEMORY();
    
    
    
protected:
    
    double number_bacteria; // used to be double
    double timer;
    double tdoublement;
    int status; // 1 or 0  : 1 means active carrier, no way to clean it/him
    int type_of_island;
    double maximum_carrying_capacity;
    vector < double > NUMBER_BACTERIA_MEMORY;
    vector < double > TIME_MEMORY;
    
};




#endif



#ifndef DEF_DOCTOR
#define DEF_DOCTOR

class Doctor: public Island{
public:
    Doctor(); // constructor
protected:
    int type_of_island;
};


#endif

//
//class Nurse: public Island{
//	public:
//	Nurse(); // constructor
//	protected:
//	int type_of_island=1;
//
//}
//
//
//class Patient: public Island{
//	public:
//	Patient(); // constructor
//	protected:
//	int type_of_island;
//
//}
//
//class Tray: public Island{
//	public:
//	Tray(); // constructor
//	protected:
//	int type_of_island;
//
//}
//
//class Wall: public Island{
//	
//	public: 
//	Wall(); // constructor
//	protected:
//	int type_of_island;
//}



#endif /* island_hpp */
