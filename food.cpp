#include "foodgenome.cpp"
#include "foodnetwork.cpp"
class food{
   public:
     double x;
     double y;
     double inputs[input_size];
     double outputs[output_size];
     int survival_time;
     foodnetwork brain;
     foodgenome g;
     int time;
     food();
     ~food();
      food(foodchromosome c1, foodchromosome c2);
      food(foodgenome g_);
    double getWeight(int);
     void set_inputs(double creatureX, double creatureY);
     void anywhere();
     void top();
     void bottom();
     void falling();
     void move();
     void NNMove(double, double);
     int fall();
     void mutate();
	double getX();
	double getY();
    int getTime();

    foodchromosome* getGamete();
};
void food::mutate() {
    g.mutate();
}
double food::getX() {
	return x;
}

double food::getY() {
	return y;
}

int food::getTime() {
    return survival_time;

}
food::~food() {

}

food::food(){
    survival_time = 0;
    x = (double)((double)rand()/RAND_MAX) * (double)width;
    y = (double)((double)rand()/RAND_MAX) * (double)height;
    g = foodgenome();
    brain = foodnetwork();
    brain.set_weights(g);
}

food::food(foodchromosome c1, foodchromosome c2) {
    survival_time = 0;
    x = random()%width;
    y = random()% height;
    g = foodgenome(c1, c2);
    brain = foodnetwork();
    brain.set_weights(g); 
}

foodchromosome* food::getGamete() {
    
    foodchromosome *temp = new foodchromosome();
    if (recomb_food == 0) {
        temp->copy(g.getGamete());
    } else if (recomb_food == 1) {
        temp->copy(g.recomb_swap(g.getPaternal(), g.getMaternal()));
    } else if (recomb_food == 2) {
        temp->copy(g.recomb_swap(g.getPaternal(), g.getMaternal()));
    }

    return temp;

}
void food::anywhere(){
   x = random()%width;
   y = random() % height;
}

void food::top(){
   x = random()%width;
   y = random() % 50;
}

void food::bottom(){
   x = random()%width;
   y = height - (random() % 50);
}

void food::falling(){
   x = random()%width;
   y = 0;  // starts at top then falls
}

void food::set_inputs(double creatureX, double creatureY) {
    inputs[0] = 1;
    
    double dist = sqrt(pow(x-creatureX,2)+pow(y-creatureY,2));

    if (dist < sensing_range_food) {
        inputs[1] = 10.0*(x-creatureX)/double(sensing_range_food);
        inputs[2] = 10.0*(y-creatureY)/double(sensing_range_food);
    }   else {
        inputs[1] = 0;
        inputs[2] = 0;
    }

}

double food::getWeight(int i) {
    return g.getWeight(i);
}

void food::NNMove(double creatureX, double creatureY) {
   set_inputs(creatureX, creatureY);
   brain.run(inputs, outputs);
   survival_time += 1;

   x += (food_range+1)*outputs[0];
   y += (food_range+1)*outputs[1];
   
   if(y > height){
       y = height;
   } else if (y < 0) {
       y = 0;
   }

   if (x > width) {
       x = width;
   } else if (x < 0) {
       x = 0;
   }
}

void food::move(){
   x += (random()%((food_range-1)*2))-(food_range-1);
   y += (random()%((food_range-1)*2))-(food_range-1);
   //std::cout << (random()%((food_range-1)*2))-(food_range-1) << std::endl;
   //x += (random()%(16)-8);
   //y += (random()%(16)-8);

   if(y > height){
       y = height;
   } else if (y < 0) {
       y = 0;
   }

   if (x > width) {
       x = width;
   } else if (x < 0) {
       x = 0;
   }

}

int food::fall(){
   y = y + 2;
   if(y > height){
      return 0;
   }
   return 1;
}

