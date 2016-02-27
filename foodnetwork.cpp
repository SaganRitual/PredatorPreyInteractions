#include<cmath>

class foodnetwork{
  private:
    double weights[num_weights];
  public:
    foodnetwork();
    void set_weights(foodgenome);
    void run_hidden(double[], double[]);
    void run(double[], double[]);
    void get_weights(ofstream outfile);
};  

  foodnetwork::foodnetwork(){   // genome g){
    for(int i = 0; i < num_weights; i++){
      weights[i] = 0; 
    }
  }

  void foodnetwork::set_weights(foodgenome g){
    for(int i = 0; i < num_weights; i++){
      weights[i] = g.getWeight(i);  //   g.getWeight(i); // randomGaussian();
    }
  }     


  void foodnetwork::get_weights(ofstream outfile) {
    for(int i = 0; i < num_weights; i++) {
        outfile << weights[i];
        //No comma at the end
        if (i == num_weights -1) {
            outfile << ", ";
        }
    }
    outfile << endl;
  }

  void foodnetwork::run_hidden(double inputs[], double outputs[]){
    double hidden[hidden_size];
    hidden[0] = 1; // bias
    for(int h = 1; h < hidden_size; h++){
      hidden[h] = 0;
      for(int i = 0; i < input_size; i++){
        hidden[h] += (inputs[i] * weights[(h*input_size) + i] );  
      } 
      hidden[h] = -1.0 + 2.0 * (1.0/(1.0+pow(2.7183,-1*hidden[h])));
    }
    for(int o = 0; o < output_size; o++){
      outputs[o] = 0; //1.0 * weights[o*(input_size+1)]; // bias
      for(int i = 0; i < hidden_size; i++){
        outputs[o] += (hidden[i] * weights[(input_size*hidden_size) + (o*hidden_size) + i] );  
      }
      outputs[o] = -1.0 + 2.0 * (1.0/(1.0+pow(2.7183,-1*outputs[o])));
    }
  }
  

  void foodnetwork::run(double inputs[], double outputs[]){
    for(int o = 0; o < output_size; o++){
      outputs[o] = 0; //1.0 * weights[o*(input_size+1)]; // bias
      for(int i = 0; i < input_size; i++){
        outputs[o] += (inputs[i] * weights[(o*input_size) + i] );  
      }
      outputs[o] = -1.0 + 2.0 * (1.0/(1.0+pow(2.7183,-1*outputs[o])));
    }
  }
  

