#include"genome.cpp"
#include"network.cpp"

/*Again, step within creature
 * 0 normal
 * 1 brownian
 * 2 random vector
 */

#define PI 3.14156

class creature{
  private:
    int food_collected;
    int num_gametes;
    double x,y;
    double speed;
    double last_x, last_y;
    double avgx, avgy;
    double avg_speed;
    double foodx, foody;
    double varx,vary,varspeed;
    double inputs[input_size];
    double outputs[output_size];
    network brain;
    double fitness;
    int step_num;
    bool dead;  // dead creatures continue to move to collect data, but don't produce gametes
    double rnd_vector;
	int closest_food;
  public:
    genome g;
    creature();
    void reset();
    void create(creature,creature);
    void create(chromosome,chromosome);
    void copy(creature);
    void set_dead(bool b){dead = b;}
    bool step(double,double,vector<chromosome *>  *,int);
    bool step_random(double,double,vector<chromosome *> *);
    void fitness_to_gametes(vector<chromosome *> *);
    double getX() {return x;}
    double getY() {return y;}
    double getSpeed() {return speed;}  
    void print() {g.print();}
    int get_num_gametes() {return num_gametes;}
    void removeGamete() {num_gametes--;}
    double get_avg_speed(){return avg_speed;}
    double get_avg_x(){return avgx;}
    double get_avg_y(){return avgy;}
    double get_food(){return food_collected;}
    double get_var_x(){return varx;}
    double get_var_y(){return vary;}
    double get_var_speed(){return varspeed;}
    void display();
    void runbrain();
    void set_inputs();
    void mutate();
	void set_closest_food(int);
	int get_closest_food();
    chromosome getMaternal() {return g.getMaternal();}
    chromosome getPaternal() {return g.getPaternal();}
};  

  creature::creature(){
      rnd_vector = -1;
      reset();
  }
  
	void creature::set_closest_food(int f) {
		closest_food = f;
	}

	int creature::get_closest_food() {
		return closest_food;
	}

  void creature::reset(){
	closest_food = -1;
    food_collected = 0;
    num_gametes = 0;
//    g.mutate();
    brain.set_weights(g);  
    x = last_x = rand()%width;
    y = last_y = rand()%height;

    for(int i = 0; i < output_size; i++){  // zero outputs for recurrance
      outputs[i] = 0;
    }

    fitness = 0;
    avgx = avgy = avg_speed = 0;
    step_num = 0;
    dead = false;
  }

  void creature::create(creature c1,creature c2){
     g.create(c1.getMaternal(),c2.getPaternal());
     reset();
  }  

  void creature::mutate(){
    g.mutate();
  }
  
  void creature::create(chromosome c1,chromosome c2){
     g.create(c1,c2);
  }  

  void creature::copy(creature c1){
    g.create(c1.getMaternal(),c1.getPaternal());
  }

  double range_random(double bottom, double top) {
    double created_random = bottom + (((double)rand())*(top-bottom))/(RAND_MAX+1.0);
    return created_random;
  }

  bool creature::step_random(double fx, double fy, vector<chromosome *> *vg) {
     double distance_food;
     foodx = fx;
     foody = fy;
     last_x = x;
     last_y = y;
     distance_food = sqrt((foodx-x)*(foodx-x) + (foody-y)*(foody-y));

     speed =  ( sqrt( (last_x-x)*(last_x-x) + (last_y-y)*(last_y-y) ));
     avgx += x/time_steps;
     avgy += y/time_steps;
     avg_speed += ( speed / time_steps);
     step_num++;
     if(food_present && (distance_food < food_range)){
	if(!dead){ // dead creatures don't collect food or generate gametes
//cout << "  " << distance_food << endl;
	        food_collected++;
		chromosome *temp;
		for(int i = 0; i < num_gametes_per_food; i++){
	  	  temp = new chromosome();
		  temp->copy(g.getGamete());
		  vg->push_back(temp);
        	}
        	num_gametes+=num_gametes_per_food;
	}
//      cout << "Food: " << x << "," << y << "    " << foodx <<","<< foody << endl;
        return true;
     }
    return false;

  }



bool creature::step(double fx, double fy, vector<chromosome *> *vg, int gen_random){
     double distance_food = sqrt(pow(fx-x,2)+pow(fy-y,2));
     foodx = fx;
     foody = fy;
     last_x = x;
     last_y = y;
     set_inputs();
     runbrain();
     
     //printf("%f\n", food_range*outputs[0]);
     x += food_range*outputs[0];
     y += food_range*outputs[1];
   
    if(x < 0)
        x = 0;
     if(x > width)
        x = width;
     if (y < 0)
        y = 0;
     if (y > height)
        y = height;

     speed =  ( sqrt( (last_x-x)*(last_x-x) + (last_y-y)*(last_y-y) ));
     avgx += x/time_steps;
     avgy += y/time_steps;
     avg_speed += ( speed / time_steps);
     step_num++;

     fitness += 10.0/(1.0+(distance_food*distance_food));
     if(food_present && (distance_food < food_range)){
	    if(!dead){ // dead creatures don't collect food or generate gametes
	        food_collected++;
            chromosome *temp;
		    for(int i = 0; i < num_gametes_per_food; i++){
	  	        temp = new chromosome();
		  
                if (recomb == 0) {
                    temp->copy(g.getGamete());
                } else if (recomb == 1) {
                    temp->copy(g.recomb_swap(g.getMaternal(), g.getPaternal()));
                } else if (recomb == 2) {
                    temp->copy(g.recomb_strand(g.getMaternal(), g.getPaternal()));
                }          

                vg->push_back(temp);

            }
        	num_gametes+=num_gametes_per_food;
	    }
        return true;
     }
     return false;
  }

  void creature::fitness_to_gametes(vector<chromosome *> *vg){
     if(!useFitness){  // useFitness is a flag for fitness
        return;
     }
     chromosome *temp;
     cout << "fitness: " << food_collected << " " << fitness << "\n";
     while(fitness > 0){
        temp = new chromosome();
        if (recomb == 0) {
            temp->copy(g.getGamete());
          } else if (recomb == 1) {
              temp->copy(g.recomb_swap(g.getMaternal(), g.getPaternal()));
          } else if (recomb == 2) {
              temp->copy(g.recomb_strand(g.getMaternal(), g.getPaternal()));
          }
        vg->push_back(temp);
	    fitness--;
     }
  }
     
  
  void creature::runbrain(){
    brain.run(inputs,outputs); 
  }

  void creature::set_inputs(){
    inputs[0] = 1;  // bias
    double d = sqrt ( (foodx-x)*(foodx-x) + (foody-y)*(foody-y));
    if(food_present && (d < sensing_range)){
       inputs[1] = 10.0*(foodx - x)/double(sensing_range);  
       inputs[2] = 10.0*(foody - y)/double(sensing_range);   
    }
    else{
       inputs[1] = 0;  
       inputs[2] = 0;   
    }
       //inputs[1] = 10.0*(foodx - x)/double(sensing_range);  
       //inputs[2] = 10.0*(foody - y)/double(sensing_range);   
   
   /* inputs[3] = 0;  // predator x - doesn't matter
    inputs[4] = 0;  // predator
    if(predator){  
	inputs[4] = y;  // distance to predator at surface
    }
    inputs[5] =  1/(1+food_collected);
    inputs[6] =  x/double(width);
    inputs[7] =  y/double(height);
    inputs[8] = (width - x)/double(width);
    inputs[9] = (height-y)/double(height);
//    inputs[10] = 10*outputs[0];  // recurrent
//    inputs[11] = 10*outputs[1];  // recurrent
    */
  }

  void creature::display(){
    cout << x << " " << y << endl;
  }



