
class chromosome{
  private:
  public:  
     double weights[num_weights];
     chromosome();
//     chromosome(const chromosome&);
     void mutate();
     void copy(chromosome);
     double get_weight(int);
     void print();
     void initialize();
};
  
  chromosome::chromosome(){
    for(int i =0; i < num_weights; i++){
      weights[i] = 0;  // random(-0.1,0.1);
    }
  } 

  void chromosome::initialize(){
    for(int i =0; i < num_weights; i++){
          weights[i] += 2.0*( ((rand() % 100) / 100.0) - 0.5) ;
    }
  }
 

  void chromosome::print(){
    for(int i =0; i < 10; i++){ //num_weights; i++){
       cout << weights[i] << " ";
    }
    cout << "\n";
  }
  
  void chromosome::copy(chromosome source){
    for(int i =0; i < num_weights; i++){
      weights[i] = source.weights[i];
    }
  }
    
  double chromosome::get_weight(int i){
    return(weights[i]);
  }   

  void chromosome::mutate() {
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

class genome{
  private:
    chromosome maternal;
    chromosome paternal;
  public:
    genome();
    genome(chromosome,chromosome);
    void mutate();
    void print();
    chromosome getGamete();
    chromosome getMaternal();
    chromosome getPaternal();
    double getWeight(int);
    void create(chromosome,chromosome);
    chromosome recomb_strand(chromosome,chromosome);
    chromosome recomb_swap(chromosome,chromosome);
};

  genome::genome(){
    maternal.initialize();
    paternal.initialize();
  }

  genome::genome(chromosome m, chromosome p){
      maternal.copy(m);
      paternal.copy(p);
  }
     
  void genome::create(chromosome m, chromosome p){
      maternal.copy(m);
      paternal.copy(p);
  }
    
  void genome::mutate(){
    maternal.mutate();
    paternal.mutate();
  }

  void genome::print(){
    maternal.print();
    paternal.print();
  }
  
  chromosome genome::getGamete(){
    if(rand()%100 < 50){
      return maternal;
    }
    else{
      return paternal;
    }
  }
  

  chromosome genome::recomb_strand(chromosome c1, chromosome c2) {
    chromosome c = chromosome();
    bool swapStrands = false;
    int count = 2;
    int base = rand()%2;

    if (base) { //if base is 1, swap c1 and c2.
        chromosome tmp = c2;
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



  chromosome genome::recomb_swap(chromosome c1, chromosome c2) {
    chromosome c = chromosome();
    int base = rand()%2;
    //50 - 50 of which one to take
    if (base) {
        chromosome tmp = c2;
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


  chromosome genome::getMaternal(){
    return maternal;
  }
  
  chromosome genome::getPaternal(){
    return paternal;
  }

  
  double genome::getWeight(int i){
    return((maternal.get_weight(i)+paternal.get_weight(i)));
  }
  
