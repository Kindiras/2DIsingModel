#include "ising2d.h"
using namespace std;

vector<double> monte_carlo_moves(class Ising2d &isd)
{
  vector<double> sEnergy;
  vector<double> sMagnetization;
  vector<double> avgValues; 
  for(int i = 0; i < nTherma; i++)
      {
        isd.get_thermalization();
        sEnergy.push_back(isd.get_spin_energy());
        sMagnetization.push_back(isd.get_spin_magnetization());
      }
        avgValues.push_back(isd.get_avg_energy(sEnergy));
        avgValues.push_back(isd.get_avg_magnetization(sMagnetization));
        avgValues.push_back(isd.get_specific_heat(sEnergy));
        avgValues.push_back(isd.get_magnetic_susceptibility(sMagnetization));
  return avgValues; 
  }


void save_energy(Ising2d isd, vector<double> &arrytemp, vector<double> &arryenergy)
        {
         isd.save_files(arrytemp,arryenergy,"Results/Energy.txt","Energy");
        }

void save_magnetization(Ising2d isd, const vector<double> &arrytemp, const vector<double> &arrymagnetization)
        {
         isd.save_files(arrytemp,arrymagnetization,"Results/Magnetization.txt","Magnetization");
        }

void save_specific_heat(Ising2d isd, const vector<double> &arrytemp, const vector<double> &arryspecific)
       {
         isd.save_files(arrytemp,arryspecific,"Results/SpecificHeat.txt","Specific Heat");
       }
void save_magnetic_susceptibility(Ising2d isd, const vector<double> &arrytemp, const vector<double> &arrysusceptibility)
      {
        isd.save_files(arrytemp,arrysusceptibility,"Results/MagneticSusceptibility.txt","Suceptibility");
      }
