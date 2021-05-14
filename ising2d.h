#ifndef ISING_2D
#define ISING_2D

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctime>    
#include <cstdlib>
#include <vector>
#include <fstream>
#define TLOOP 38
#define nTherma 50
#define warm 90000

using namespace std;

vector<double> vTemp;
vector<double> avgEnergy;
vector<double> avgMagnetization;
vector<double> vSpecific;
vector<double> vSusceptibility;

vector<double> monte_carlo_moves();
void save_energy(vector<double> &arrytemp, vector<double> &arryenergy);
void save_magnetization(const vector<double> &arrytemp, const vector<double> &arrymagnetization);
void save_specific_heat(const vector<double> &arrytemp, const vector<double> &arryspecific);
void save_magnetic_susceptibility(const vector<double> &arrytemp, const vector<double> &arrysusceptibility);

class Ising2d
{
	private:
	int L;
	double T;
	vector< vector<int> > grid;
	

public:
	Ising2d(int l, double t);
	~Ising2d();
	double get_temperature();
	vector< vector<int> > get_spin();
	void create_random_spin();
	vector<int> get_neighbor(int row, int col);
	void print_spins();
	double random_uniform();
	double get_mean(const vector<double> &array);
	double get_mean_deviation(const vector<double> &array);
	void save_files(const vector<double> &arrayL,const vector<double> &arrayR,string fileName, string title);
	void update_spin();		
	void get_thermalization();
	double get_spin_energy();
	double get_spin_magnetization();
	double get_avg_magnetization(vector<double> &array);
	double get_avg_energy(vector<double> &array);
	double get_specific_heat(vector<double> &array);
	double get_magnetic_susceptibility(vector<double> &array);
	void set_temperature();
	void get_screen();
};


#endif
