
class foodchromosome{
  public:  
     double weights[num_weights];
     foodchromosome();
//     foodchromosome(const foodchromosome&);
     void mutate();
     void copy(foodchromosome);
     double get_weight(int);
     void print();
     void initialize();
};
  
  foodchromosome::foodchromosome(){
    for(int i =0; i < num_weights; i++){
      weights[i] = 0;  // random(-0.1,0.1);
    }
  } 

  void foodchromosome::initialize(){
    for(int i =0; i < num_weights; i++){
          weights[i] += 2.0*( ((rand() % 100) / 100.0) - 0.5) ;
    }
//    weights[1] = 100;
//    weights[11] = 100;
  }
 

  void foodchromosome::print(){
    for(int i =0; i < 10; i++){ //num_weights; i++){
       cout << weights[i] << " ";
    }
    cout << "\n";
  }
  
  void foodchromosome::copy(foodchromosome source){
    for(int i =0; i < num_weights; i++){
      weights[i] = source.weights[i];
    }
  }
    
  double foodchromosome::get_weight(int i){
    return(weights[i]);
  }   

  void foodchromosome::mutate() {
        if (normal_dist) {
            for(int i =0; i < num_weights; i++){
                if(chance(mutation_rate)) {
                    /*dist is from the boost normal dist*/
                    /*I tested it dist(), the probs are as expected and it seems to be working correctly*/
                    weights[i] += dist();
                }
            }
        } else {
            for(int i =0; i < num_weights; i++){
                if((rand()%100) < mutation_rate){
                    weights[i] += mutation_size*( ((rand() % 100) / 100.0) - 0.5) ;
                }
            }
        }

  }

class foodgenome{
  private:
    foodchromosome maternal;
    foodchromosome paternal;
  public:
    foodgenome();
    foodgenome(foodchromosome,foodchromosome);
    void mutate();
    void print();
    foodchromosome getGamete();
    foodchromosome getMaternal();
    foodchromosome getPaternal();
    double getWeight(int);
    void create(foodchromosome,foodchromosome);
    foodchromosome recomb_strand(foodchromosome,foodchromosome);
    foodchromosome recomb_swap(foodchromosome,foodchromosome);

};

  foodchromosome foodgenome::recomb_strand(foodchromosome c1, foodchromosome c2) {
    foodchromosome c = foodchromosome();
    bool swapStrands = false;
    int count = 2;
    int base = rand()%2;

    if (base) { //if base is 1, swap c1 and c2.
        foodchromosome tmp = c2;
        c2 = c1;
        c1 = tmp;
    }

    for(int i = 0; i < num_weights; i++) {
        if (chance(recomb_rate)) {
            swapStrands = !swapStrands;
            count++;
        }
        if (swapStrands) { // non-base chrome
            c.weights[i] = c2.weights[i];
        } else {   //base chrome
            c.weights[i] = c1.weights[i];
        }
    }
    return c;
  };



  foodchromosome foodgenome::recomb_swap(foodchromosome c1, foodchromosome c2) {
    foodchromosome c = foodchromosome();
    int base = rand()%2;
    //50 - 50 of which one to take
    if (base) {
        foodchromosome tmp = c2;
        c2 = c1;
        c1 = tmp;
    }

    for(int i = 0; i < num_weights; i++) {
        if (chance(recomb_rate)) { //get other chrome value
            c.weights[i] = c2.weights[i];
        } else {  //get base chrome value
            c.weights[i] = c1.weights[i];
        }
    }
    return c;
  };







  foodgenome::foodgenome(){
    maternal.initialize();
    paternal.initialize();
  }

  foodgenome::foodgenome(foodchromosome m, foodchromosome p){
      maternal.copy(m);
      paternal.copy(p);
  }
     
  void foodgenome::create(foodchromosome m, foodchromosome p){
      maternal.copy(m);
      paternal.copy(p);
  }
    
  void foodgenome::mutate(){
    maternal.mutate();
    paternal.mutate();
  }

  void foodgenome::print(){
    maternal.print();
    paternal.print();
  }
  
  foodchromosome foodgenome::getGamete(){
    if(rand()%100 < 50){
      return maternal;
    }
    else{
      return paternal;
    }
  }
  
  foodchromosome foodgenome::getMaternal(){
    return maternal;
  }
  
  foodchromosome foodgenome::getPaternal(){
    return paternal;
  }

  
  double foodgenome::getWeight(int i){
    return((maternal.get_weight(i)+paternal.get_weight(i)));
  }
  
