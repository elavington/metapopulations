
The first draft of the code is in C++, to simulate the evolution of the metapopulation in time. 
It produces a .txt file (A). This .txt file is then read and the analysis+ plotting is done in Python3 (B)

A. Producting results (C++): 

main.cpp -> reads parameter file and define the sequence of interactions

interactions.cpp : defines routines for interactions
random.cpp:  define a few routines for the MC approach
islands.cpp: define the island class and associated procedures

each .cpp file is accompagnied by the header prototyping the functions


B. Analyzing + producing Results (Python):


