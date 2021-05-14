#include "ising2d.h"
#include "ising2d_class.cpp"
#include "ising2d_functions.cpp"

int main()
{
  Ising2d    ising(1,0.1);
  srand(time(NULL));
	ising.create_random_spin();
  for (int i = 0;i<TLOOP;i++)
  {
    vector<double> avgValues;
    ising.set_temperature();
    ising.get_screen();
    avgValues = monte_carlo_moves(ising);
    vTemp.push_back(ising.get_temperature());
    avgEnergy.push_back(avgValues[0]);
    avgMagnetization.push_back(avgValues[1]);
    vSpecific.push_back(avgValues[2]);
    vSusceptibility.push_back(avgValues[3]);
    //ising.print_spins();
  }
  save_energy(ising, vTemp,avgEnergy);
  save_magnetization(ising, vTemp,avgMagnetization);
  save_specific_heat(ising, vTemp,vSpecific);
  save_magnetic_susceptibility(ising, vTemp,vSusceptibility);
return 0;
}