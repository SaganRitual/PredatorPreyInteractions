#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;
#include"creature.cpp"
#include"food.cpp"
/*gen_random is now an integer
 * 0 cooresponds to a non-random run
 * 1 cooresponds to brownian motion
 * 2 cooresponds to random vector until it hits the a side,
 * then another random vector, etc.*/

string to_string(int);
int gen_random = 0;

class population{

  private:
    vector<creature *> the_pop;
    double foodx, foody;
    int food_counter;
    int closest_food;  // keeps track of the closest food to the creature
    vector<chromosome *> gamete_pool;
    double avg_speed,avg_x,avg_y,avg_food;
    double popavg_speed,popavg_x,popavg_y, popavg_food;
    vector<food *> food_list;
    vector<food *> tmp_food_list;
    vector<foodchromosome *> food_gamete_pool;
    vector<foodchromosome *> food_breeding_gamete_pool;
    ofstream avgoutputfile;
    ofstream avgavgoutputfile;
    ofstream avgfoodlessoutputfile;
    ofstream avgavgfoodlessoutputfile;
    ofstream avgbrownoutputfile;
    ofstream avgrandomoutputfile;
    ofstream avgavgbrownoutputfile;
    ofstream avgavgrandomoutputfile;
    ofstream genomefile;
    ofstream foodgenomefile;
//    ofstream avgoutputfilefoodless;
    double x_values[time_steps];
    double y_values[time_steps];
    double speed_values[time_steps];
  public:
    
    int gen;
    population();
    void run(int);
    void reset_food();
    void update_food();
    void next_gen();
    void collectdata();
    void step_creature(int,int);
    void set_closest_food(creature *c);
    void calc_stats();
    void calc_stats_foodless();
    void calc_stats_random();
    void calc_stats_brownian();
    void print();
    void close_datafiles();
    void food_fitness();
	void predation(creature *c, int);
	int set_closest_creature(double cx, double cy);
//    void end_of_trial();
//    void resetCurrent();
//    void step();
//    void setCreaturesFoodVector();
//    void collectData();
//    void next_generation();
//    void prepare_gen_data();

    
};

  population::population(){
    avg_speed = avg_x = avg_y = avg_food = 0;
    popavg_x = popavg_y = popavg_speed = popavg_food = 0;
    string avgoutfilename;
    string avgavgfilename;
    string avgavgoutfilename_random;
    string avgavgoutfilename_brown;
    string avgoutfilename_random;
    string avgoutfilename_brown;
    string outfilename_genome;
    string outfilename_food;

    outfilename_food = "foodGenome_";
    outfilename_food += to_string(trial);
    outfilename_food += ".txt";
    foodgenomefile.close();
    foodgenomefile.open(outfilename_food.c_str());
      foodgenomefile << "gen, food_num, survival, ";
      for (int i = 0; i < num_weights; i++) {
          foodgenomefile << "weight" << i;
                if (num_weights-1!=i) {
                    foodgenomefile << ",";
                }
      }
    foodgenomefile << "\n";
    outfilename_genome = "genome";
    outfilename_genome += to_string(trial);
    outfilename_genome += ".txt";

    genomefile.close();
    genomefile.open(outfilename_genome.c_str());
    genomefile << "generation, creature, food, ";

      for (int i = 0; i < num_weights; i++) {
          genomefile << "weight" << i ;
                if (num_weights-1!=i) {
                    genomefile << ",";
                }
      }
      genomefile << "\n";

    avgoutfilename = "foodaverages";
    avgoutfilename += to_string(trial);
    avgoutfilename += ".txt";

    avgavgfilename = "foodavgavg";
    avgavgfilename += to_string(trial);
    avgavgfilename += ".txt";

    avgavgoutputfile.close();
    avgavgoutputfile.open(avgavgfilename.c_str());
    avgavgoutputfile << "popavg_speed, popavg_x, popavg_y, popavg_food" << endl;
    

    avgoutputfile.close();
    avgoutputfile.open(avgoutfilename.c_str());
    avgoutputfile << "trial, generation, creature, treatment, food/nofood, network,  x, var x, y, var y, speed, var speed, food collected\n"; 

// foodless files
    string avgfoodlessoutfilename;
    string avgavgfoodlessfilename;
    avgfoodlessoutfilename = "foodlessaverages";
    avgfoodlessoutfilename += to_string(trial);
    avgfoodlessoutfilename += ".txt";

    avgavgfoodlessfilename = "foodlessavgavg";
    avgavgfoodlessfilename += to_string(trial);
    avgavgfoodlessfilename += ".txt";

    avgavgoutfilename_brown = "brownainavgavg";
    avgavgoutfilename_brown += to_string(trial);
    avgavgoutfilename_brown += ".txt";

    avgavgbrownoutputfile.close();
    avgavgbrownoutputfile.open(avgavgoutfilename_brown.c_str());
    avgavgbrownoutputfile << "popavg_speed, popavg_x, popavg_y, popavg_food" << endl;
    
    avgoutfilename_brown = "brownainaverages";
    avgoutfilename_brown += to_string(trial);
    avgoutfilename_brown += ".txt";
    
    avgbrownoutputfile.close();
    avgbrownoutputfile.open(avgoutfilename_brown.c_str());
    avgbrownoutputfile << "trial, generation, treatment, food/nofood, network, x, var x, y, var y, speed, var speed, food collected\n"; 

    avgoutfilename_random = "randomaverages";
    avgoutfilename_random += to_string(trial);
    avgoutfilename_random += ".txt";

    avgrandomoutputfile.close();
    avgrandomoutputfile.open(avgoutfilename_random.c_str());
    avgrandomoutputfile << "trial, generation, treatment, food/nofood, network, x, var x, y, var y, speed, var speed, food collected\n"; 

    avgavgoutfilename_random = "randomavgavg";
    avgavgoutfilename_random += to_string(trial);
    avgavgoutfilename_random += ".txt";

    avgavgrandomoutputfile.close();
    avgavgrandomoutputfile.open(avgavgoutfilename_random.c_str());
    avgavgrandomoutputfile << "popavg_speed, popavg_x, popavg_y, popavg_food" << endl;


    avgavgfoodlessoutputfile.close();
    avgavgfoodlessoutputfile.open(avgavgfoodlessfilename.c_str());
    avgavgfoodlessoutputfile << "popavg_speed, popavg_x, popavg_y, popavg_food" << endl;
    


    avgfoodlessoutputfile.close();
    avgfoodlessoutputfile.open(avgfoodlessoutfilename.c_str());
    avgfoodlessoutputfile << "trial, generation, treatment, food/nofood, network, x, var x, y, var y, speed, var speed, food collected\n"; 
 
   reset_food();
  }
  
  void population::print(){
    /*the_pop[0].print();
cout << endl;
    the_pop[1].print();
cout << endl;
    the_pop[2].print();
cout << endl;
    the_pop[3].print();*/
  }

  void population::close_datafiles(){
    avgavgoutputfile.close();
    avgoutputfile.close();
    avgavgfoodlessoutputfile.close();
    avgfoodlessoutputfile.close();
    avgrandomoutputfile.close();
    avgbrownoutputfile.close();
    avgavgrandomoutputfile.close();
    avgavgbrownoutputfile.close();
    genomefile.close();
    foodgenomefile.close();
  }

  void population::reset_food(){
        food *f;
        /*for (int i = 0; i < food_list.size(); i++) {
            //std::cout << "okay" << std::endl;
            //delete food_list[i];
            //std::cout << "okay okay" << std::endl;
            //food_list[i] = NULL;
        }*/
        
        food_list.clear();
	    food_counter = 0;  // used for falling food, to add some occasionally
        
        switch(treatment){
		case 1:
			for(int i = 0; i < food_amount; i++){
            			f = new food();
				f->anywhere();
            			food_list.push_back(f);
			}
			break;
		case 2:
			for(int i = 0; i < food_amount; i++){
            			f = new food();
				        f->top();
            			food_list.push_back(f);
			}
			break;
		case 3:
			for(int i = 0; i < food_amount; i++){
            			f = new food();
			        	f->bottom();
            			food_list.push_back(f);
			}
			break;
		case 5:
            		f = new food();
			        f->falling();
            		food_list.push_back(f);
			break;
        case 6: //random food movement
			for(int i = 0; i < food_amount; i++){
            			f = new food();
			        	f->anywhere();
            			food_list.push_back(f);
            }
            break;
        case 7: //NN food movement
            if (gen == 0) {
                for(int i = 0; i < food_amount; i++) {
                    f = new food();
                    f->anywhere();
                    food_list.push_back(f);
                    tmp_food_list.push_back(f);
                }
            } else {
				for (int i = 0; i < food_list.size(); i++) {
                    if (food_list[i] != NULL) {
					    delete food_list[i];
					    food_list[i] = NULL;
				    }
                }

                food_list.clear();
				for (int i = 0; i < tmp_food_list.size(); i++) {
                    if (tmp_food_list[i] != NULL) {
					    delete tmp_food_list[i];
					    tmp_food_list[i] = NULL;
				    }
                }
                tmp_food_list.clear();
                for(int i = 0; i < food_amount; i++) {
                    int first = (int)random()%food_breeding_gamete_pool.size();
                    int second = (int)random()%food_breeding_gamete_pool.size();
                    f = new food(*(food_breeding_gamete_pool[first]), *(food_breeding_gamete_pool[second]));
                    f->anywhere();
                    f->mutate();
                    food_list.push_back(f);
                    tmp_food_list.push_back(f);
                }
            }
            break;
		default:
			cout << "Unknown food case!" << endl;
        }
  } 


	int population::set_closest_creature(double cx, double cy) {
    	double d,dmin,x,y;
		int closest_c = 0;
		
       	dmin = (the_pop[0]->getX() - cx)*(the_pop[0]->getX() - cx) + (the_pop[0]->getY() - cy)*(the_pop[0]->getY() -cy);
		
		for (int i = 1; i < the_pop.size(); i++) {
       		if (the_pop[i] != NULL) {
           		d = (the_pop[i]->getX() - cx)*(the_pop[i]->getX() - cx) + (the_pop[i]->getY() - cy)*(the_pop[i]->getY() -cy);
           		if (d < dmin) {
                	dmin = d;
		        	closest_c = i;
           		}
           	}
		}

		return closest_c;
	}

	void population::update_food(){
		if(treatment == 5){
			for(int i = 0; i < food_list.size(); i++){
		     	if(food_list[i]->fall() == 0){
                    food_list[i] = NULL;
		   	        food_list.erase(food_list.begin()+i);
			    }	
			}
			if(food_counter % 2 == 0 && food_counter < 2*food_amount){  // every other timestep add a food
            	food *f = new food();
			    f->falling();
            	food_list.push_back(f);
			}
			food_counter++;
		} else if (treatment == 6) {
        	for (int i = 0; i < food_list.size(); i++) {
            	food_list[i]->move();
        	}
    	} else if (treatment == 7) {
		    	
        	for (int i = 0; i < food_list.size(); i++) {
                int closest_creature = set_closest_creature(food_list[i]->getX(), food_list[i]->getY());
            	food_list[i]->NNMove(the_pop[closest_creature]->getX(),the_pop[closest_creature]->getY());
        	}
    	}
	}

	void population::set_closest_food(creature *c){
		double cx = c->getX();
		double cy = c->getY();
    	double d,dmin;
       	closest_food = 0;
       	if(food_list.size() == 0){
	    	closest_food = -1;
            return;
       	}
        //printf("%f %f X and Y Creature\n", cx, cy);
       	dmin = sqrt((food_list[0]->x - cx)*(food_list[0]->x - cx) + (food_list[0]->y - cy)*(food_list[0]->y -cy));
        //printf("%f\n", dmin);
       	for(int i = 1; i < food_list.size(); i++){
       		if (food_list[i] != NULL) {
           		d = sqrt((food_list[i]->x - cx)*(food_list[i]->x - cx) + (food_list[i]->y - cy)*(food_list[i]->y -cy));
                //printf("%f\n", d);
           		if(d < dmin){
                	dmin = d;
		        	closest_food = i;
           		}
           	}
       	}
        //printf("set food %d min %f\n", closest_food, dmin);
		c->set_closest_food(closest_food);
	}

	void population::calc_stats(){
 //   double avg_fish_x, avg_fish_y, avg_fish_speed;
    	double var_fish_x, var_fish_y, var_fish_speed;
    	avg_x = avg_y = avg_speed = 0;
    	var_fish_x = var_fish_y = var_fish_speed = 0;
    	for(int i = 0; i < time_steps; i++){
			avg_x += x_values[i];	
			avg_y += y_values[i];	
			avg_speed += speed_values[i];	
    	}
    	avg_x /= time_steps;
    	avg_y /= time_steps;
    	avg_speed /= time_steps;
    	for(int i = 0; i < time_steps; i++){
			var_fish_x += ((x_values[i]-avg_x)*(x_values[i]-avg_x))/time_steps;
			var_fish_y += ((y_values[i]-avg_y)*(y_values[i]-avg_y))/time_steps;
			var_fish_speed += ((speed_values[i]-avg_speed)*(speed_values[i]-avg_speed))/time_steps;
    	}
    	popavg_x += avg_x;  
    	popavg_y += avg_y;
    	popavg_speed += avg_speed;
    	avgoutputfile << avg_x << ", "<< var_fish_x << ", ";
    	avgoutputfile << avg_y << ", "<< var_fish_y << ", ";
    	avgoutputfile << avg_speed << ", "<< var_fish_speed << ", ";
 	}

	void population::food_fitness() {
         
     	for (int i = 0; i < tmp_food_list.size(); i++) {
            int tmp_food = tmp_food_list[i]->survival_time/food_gametes;

            foodgenomefile << gen << ", ";
            foodgenomefile << i << ", ";
            foodgenomefile << tmp_food_list[i]->survival_time << ",";

      		for (int w = 0; w < num_weights; w++) {
          		foodgenomefile << tmp_food_list[i]->getWeight(w);
                if (w != num_weights-1) {
                    foodgenomefile << ",";
                }
          	}
            foodgenomefile << "\n";

        	while(tmp_food--) {
            	food_gamete_pool.push_back(tmp_food_list[i]->getGamete());
        	}
        	delete tmp_food_list[i];
        	tmp_food_list[i] = NULL;   
    	}


		for (int i = 0; i < food_list.size(); i++) {
			if (food_list[i] == NULL) {
				delete food_list[i];
				food_list[i] = NULL;
			}
		}

    	tmp_food_list.clear();
    	food_list.clear();

	}
	

	void population::predation(creature *c, int t) {
		double distance_to_p = double(c->getY())/height;
        if (predator && (t % (int)(time_steps/step) == 0)) {
            if (pow(distance_to_p*surviveAtTop/(time_steps/step),4) < (random()%1000/1000.0)) {
			    c->set_dead(true);
            }
        }
	}
	
  	void population::run(int generation){

    	double distance_to_p,dx,dy; // predator
	    food_present = true;
	    avg_speed = avg_x = avg_y = avg_food = 0;
   	 	gen = generation; // used for nn move
      	reset_food();
	
		if (generation == 0) {
    		for(int c = 0; c < pop_size; c++){
      			the_pop.push_back(new creature());
			}
		}
			
    	for(int c = 0; c < pop_size; c++){
			the_pop[c]->reset();
       	}
      	for(int t = 0; t < time_steps; t++){

        	for (int c = 0; c < the_pop.size(); c++) {
        		set_closest_food(the_pop[c]);
				step_creature(c, gen_random);
         	}
			if(treatment > 4){  // falling food
		        update_food();
	    	}
      	} // end of timesteps

      	food_fitness();

		for (int c = 0; c < the_pop.size(); c++) {
      		avgoutputfile << trial << ", " << generation << ", " << c << ", "  << treatment << ", Food, Network, ";
      		popavg_food += the_pop[c]->get_food();
      
      		genomefile << generation << ", " << c << ", " << the_pop[c]->get_food() << ", ";
      		for (int i = 0; i < num_weights; i++) {
        		genomefile << (the_pop[c]->g).getWeight(i);
                if (num_weights-1!=i) {
                    genomefile << ",";
                }
      		}
            genomefile <<  "\n";
		}

    	vector<foodchromosome *> tmp = food_breeding_gamete_pool;
    	food_breeding_gamete_pool = food_gamete_pool;
    	food_gamete_pool.clear();
    
    	for (int i = 0; i < tmp.size(); i++) {
        	delete tmp[i];
        	tmp[i] = NULL;
    	}
     
    	popavg_x /= pop_size;
    	popavg_y /= pop_size;
    	popavg_speed /= pop_size;
    	popavg_food /= pop_size;
    	avgavgoutputfile << popavg_speed << ", " << popavg_x <<", " << popavg_y << ", " <<  popavg_food << endl;
    	//cout << popavg_speed << ", " << popavg_x <<", " << popavg_y << ", " <<  popavg_food << endl;
    	next_gen();
	}
  
	void population::step_creature(int c, int gen_random) {
    	if(the_pop[c]->get_closest_food() == -1){ // no food left
	    	food_present = false;
       		the_pop[c]->step(0,0,&gamete_pool, gen_random);
	    	food_present = true;  // for the next time
     	} else{
        	if (food_list.size() > 0) {
			    closest_food = the_pop[c]->get_closest_food();
                //printf("C %f %f\n", the_pop[c]->getX(), the_pop[c]->getY());
                //printf("F %f %f\n", food_list[closest_food]->x, food_list[closest_food]->y);
                //printf("%d\n", closest_food);
            	if (food_list[closest_food] != NULL) {
                	if(the_pop[c]->step(food_list[closest_food]->x,food_list[closest_food]->y,&gamete_pool, gen_random)){
                        food_list.erase(food_list.begin()+closest_food);

	                } 
                } else {
                //    printf("What the hell?\n");
                }
            }
         }
	}

	void population::next_gen(){
     	double avg_gametes=0;
        double all_food = 0;
     	
        for(int i = 0; i < pop_size; i++){
            all_food += the_pop[i]->get_food();
     		avg_gametes+= the_pop[i]->get_num_gametes();
			delete the_pop[i];
			the_pop[i] = NULL;
     	}

        cout << "Avg Gametes: " << avg_gametes/(double)the_pop.size() << " Total Food: " << all_food << "\n";

		the_pop.clear();
		
     	int p1,p2;
     	chromosome *tempc;

     	if(gamete_pool.size() == 0){
        	cout << "No gametes" << endl;
        	for(int i = 0; i < 2*pop_size; i++){
            	tempc = new chromosome();
	     		gamete_pool.push_back(tempc);
        	}
     	}

     	while(gamete_pool.size() < 2*pop_size){ // fill gamete pool if necessary
			tempc = new chromosome();
			tempc->copy(*gamete_pool[random() % gamete_pool.size()]);
			gamete_pool.push_back(tempc);
     	}


     	std::random_shuffle(gamete_pool.begin(),gamete_pool.end());

     	for(int i = 0; i < pop_size; i++){
        	creature *c = new creature();
			p1 = gamete_pool.size()-1;  // last
        	p2 = gamete_pool.size()-2;  // second to last
			
        	c->create(*gamete_pool[p1],*gamete_pool[p2]);
        	c->mutate();
			the_pop.push_back(c);
        	gamete_pool.pop_back();    
        	gamete_pool.pop_back();    
     	}

     	for (int i = 0; i < gamete_pool.size(); i++) {
        	delete gamete_pool[i];
         	gamete_pool[i] = NULL;
     	}

     	gamete_pool.clear();
	} 

  
 
  string to_string(int i){
      string answer = "";
      answer += char(48+i/1000);
      i %= 1000;
      answer += char(48+i/100);
      i %= 100;
      answer += char(48+i/10);
      i %= 10;
      answer += char(48+i);
      return answer;
  }

