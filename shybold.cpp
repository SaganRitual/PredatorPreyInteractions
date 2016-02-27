#include<iostream>
#include<cstdlib>
#include<ctime>
#include<curses.h>
#include<boost/random.hpp>
#include<boost/random/normal_distribution.hpp>
#include<boost/any.hpp>


using namespace std;

#include"params.h"
#include"population.cpp"

//predator pred;
//food fd;
//int day;
int generation;
//int opportunity;
bool predation;
bool foodPresent;
bool display;
int steps;
int member;
    

/*For the normal distribution*/
//String gen_file_name, base_gen_file_name;
//PrintWriter output_gen;

int main(int argc, char* argv[]){
   /*To get the number call dist();*/

           if(argc < 2){
	cout << "Needs trial number as input.\n";
	return 1;
  }
  population *p;
  trial = atoi(argv[1]);
  srand(time(NULL)*trial);
//  for(trial = 5; trial < max_trials; trial++){ 
      p = new population();
      for(int i =0; i < max_generations; i ++){
//        cout<< "trial: "<< trial << " gen: " << i << "\n";
        p->run(i);  // runs all creatures in the pop then generates the next generation
      }
      p->close_datafiles(); // averages
      //p->collectdata();  // swim tracks
//p->print();
//  }

}
