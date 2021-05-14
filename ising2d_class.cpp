#include "ising2d.h"

Ising2d::Ising2d(int L, double T)
         {
           cout<<"Please eneter the lattice size:"<<endl;
           cin>>L;
           this->L = L;
           this->T = T;
           vector< vector<int> > grid(0,vector<int>(0,1));

         }
void Ising2d::set_temperature()
{
 this->T = T + 0.05;
}

void Ising2d::get_screen()
{
  cout<<"working on temperature:"<<T<<endl;
}
double Ising2d::get_temperature()
{
  return T;
}

vector< vector<int> > Ising2d::get_spin()
{
  return grid;
}

Ising2d::~Ising2d()
    {
      cout<<"*********"<<endl;
      
    }         

double Ising2d::random_uniform()
    {
    	int randomNumber = rand();
    return (double)(randomNumber)/RAND_MAX;
    }    


void Ising2d::create_random_spin()
    {

        for (int i = 0; i < L; ++i)
        {
            vector<int> spin;
            for (int j = 0; j < L; ++j)
                {
                    double vDouble = random_uniform();
                    if (vDouble > 0.5)
                          spin.push_back(1);
                    else
                        spin.push_back(-1);
                }
        grid.push_back(spin);
         }
   }  

void Ising2d::get_thermalization()
{
      for(int i = 0; i < warm; i++)
      {
        update_spin();
      }
}


vector<int> Ising2d::get_neighbor(int row, int col)
{               
    vector<int> neighbor;                             //   UN
    int LN, RN, UN,DN;                               //     2
    LN = row - 1;                                    // LN0----1RN
       RN = row + 1;                         	     //     3
       UN = col - 1;                                 //     DN   
       DN = col + 1;
       LN = ( LN < 0 ? L - 1 : LN ); //L is global variable of lattice size
       RN = ( RN > L - 1 ? 0 : RN );
       UN = ( UN < 0 ? L - 1 : LN );
       DN = ( DN > L - 1 ? 0 : DN );
       neighbor.push_back(LN);
       neighbor.push_back(RN);
       neighbor.push_back(UN);
       neighbor.push_back(DN);    
    return neighbor;  //This will return the positions of neighbors not the spin   
    }                                                        
                                         

void Ising2d::print_spins()
{
    for (int row = 0; row < grid.size(); row++)
    {
        for (int col = 0; col < grid[row].size(); col++)
        {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void Ising2d::update_spin()
{
    float Ha, Hb,dH,r;
    double eng;
    int row, col,left,right,up,down;
    bool accept = false;
    vector<int> neighbor;                    //     UN
    row = int(random_uniform()*L);       //      2
    col = int(random_uniform()*L);       // LN 0----1 RN
    neighbor = get_neighbor(row,col);   //        3 
    left = grid[neighbor[0]][col];          //        DN 
    right = grid[neighbor[1]][col];
    up = grid[row][neighbor[2]];
    down = grid[row][neighbor[3]];
    Hb = grid[row][col]*(left + right + up +down);
    Ha = -grid[row][col]*(left + right + up +down);
    dH = Ha - Hb;
    eng = exp(-dH/T);
    //cout<<"exp: and random"<<eng <<r <<endl;
    r = random_uniform();
    if(dH < 0 || r < eng)
    {
      accept = true;
    }

    if(accept)
    {
      grid[row][col] = -grid[row][col];
    }                                                                                
}    


double Ising2d::get_mean(const vector<double> &array)
{
 double sArray = 0;
 for (int i = 0; i < array.size(); ++i)
     sArray = sArray + array[i];
 return (double)(sArray/double(array.size()));
}

double Ising2d::get_mean_deviation(const vector<double> &array)
{
    double mu = get_mean(array);
    double sArray = 0;
    int aSize = array.size();
    for (int i = 0; i < aSize ; i++)
        sArray = sArray + (array[i] - mu)*(array[i] - mu);
    sArray = sArray/float(aSize);
    return (double)(sqrt(sArray));
}       

double Ising2d::get_spin_energy()
       {
        int row, col, left, right, up, down, sEnergy = 0;
        vector<int> neighbor;
        for(row = 0; row < L; row++)
        {
          for(col = 0; col < L; col++)
          {
            neighbor = get_neighbor(row,col); 
            left = grid[neighbor[0]][col];
            right = grid[neighbor[1]][col];
            up = grid[row][neighbor[2]];
            down = grid[row][neighbor[3]];
              sEnergy = sEnergy + grid[row][col]*(left + right + up + down);
          }
        }
        return (sEnergy);
       }


double Ising2d::get_spin_magnetization()
       {
        int row, col, sMagnetization = 0;
        for(row = 0; row < L; row++)
        {
          for(col = 0; col < L; col++)
          {
              sMagnetization = sMagnetization + grid[row][col];
          }
        }
        return (sMagnetization);
       }


double Ising2d::get_avg_energy(vector<double> &array)
       {
        double energy;
        energy = get_mean(array);
        return energy;
       }

double Ising2d::get_avg_magnetization(vector<double> &array)
       {
        double magnetization;
        magnetization = get_mean(array);
        return magnetization;
       }       

double Ising2d::get_specific_heat(vector<double> &array)
        {
          double sHeat; 
          sHeat = get_mean_deviation(array);
          return sHeat;
        }
double Ising2d::get_magnetic_susceptibility(vector<double> &array)
        {
          double mSusceptibility;
          mSusceptibility = get_mean_deviation(array);
          return mSusceptibility;
        }



void Ising2d::save_files(const vector<double> &arrayL, const vector<double> &arrayR, string fileName, string title)
{
  ofstream outFile;
  string outFileName = fileName;
  outFile.open(outFileName);
  outFile <<"temperature(K)"<<" "<<title<<endl;
  for(int i = 0; i < arrayL.size(); i++)
  {
    outFile << arrayL[i] <<" "<<arrayR[i]<<endl;
  }
  outFile.close();
}

