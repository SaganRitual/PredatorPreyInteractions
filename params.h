/* Genome output
 * each fish output
 * processing
 * 50 rep
 */


const int treatment = 7;


/*0 - no recomb
 *1 - recomb swab
 *2 - recomb biological*/

const int recomb = 2;
double recomb_rate = .5;



const int recomb_food = 2;
double recomb_rate_food = .5;
const int food_gametes = 100; //every 100 time ticks 1 gamete

bool chance(double rate) {
    if ((double) rand() / RAND_MAX < rate) {
        return true;
    }
    return false;
}


bool predator = false;
double surviveAtTop = 0.85;
double step = 20;

const int width = 5000;
const int height = 5000;
const int input_size = 3;
const int output_size = 3;
const int time_steps = 3000;
const int max_generations = 1000;
//const int max_trials = 4; // 20;  trials are handled by qsub
const int food_amount = 10000;
int trial;
const int hidden_size = 5;

//const int num_weights = input_size * hidden_size + hidden_size*output_size;
const int num_weights = input_size * output_size;

const int sensing_range = 900;
const int sensing_range_food = 1200;
const int food_range = 8;
int num_gametes_per_food = 2;

const int pop_size = 100;


bool dataCollection = false;
bool useFitness = false;
bool food_present = true;

double mutation_rate = .1;  // percent
double mutation_size = 2;  // range is -0.5*mutation_size to 0.5*mutation_size
double mean = 0; //Mean for normal distribution
double stddev = 1; //Standar devation for normal distribution

bool normal_dist = true;

boost::mt19937 rng(static_cast<unsigned int>(time(NULL)));
/*According to the docs, mean and std dev distr(mean, stddev)*/
boost::normal_distribution<> distribution(mean, stddev);
boost::variate_generator< boost::mt19937, boost::normal_distribution<> > dist(rng, distribution);



