//
//  random.cpp
//  FAB
//
//  Created by Pierre Cristofari on 09/04/2017.
//  Copyright © 2017 Pierre Cristofari. All rights reserved.
//

#include "random.hpp"
/*
 *  random.cpp
 *  FAB
 *
 *  Created by Pierre Cristofari on 09/02/2017.
 *  Copyright 2017 __MyCompanyName__. All rights reserved.
 *
 */

#include <math.h>
#include <stdlib.h>

/*********** Fonction aléatoire entre a et b :  0 et 1  *****************/

double frand(double a, double b){
    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

// On suppose a<b
int intrand(int a, int b){
    return rand()%(b+1-a) +a;
}


/*********** Sale fonction G qui permettra d'obtenir le nombre de SNR   *****************/

int G ( double lambda1,  double x  ) // fonction réelle, la variable doit être entre 0 et 1 ;
{
    double v= -lambda1;
    double s=0;
    
    int p=0; // variable compteur
    while (s<x) { p=p+1;
        v=v+log(lambda1)-log(p);
        s=s+exp(v);
    }			// la boucle stop : donc variable est entre p-1 et p
    return p-1;
}


int combinaison(int n,  int p) {
    if (n==p) {return 1; }
    if(p>n){return 0;}
    else {
        
        int t[n]; //Tableau de n éléments
        t[0] = 1;
        for (int i = 1; i< n; i++) {
            t[i] = 1;
            for (int j = i - 1; j > 1; j--) //On part de le fin pour ne pas écraser les valeurs.
                t[j] = t[j] + t[j - 1]; //On fait les calculs nécessaires.
        }
        return t[p]; //On renvoie la valeur recherchée.
        
    }
}
