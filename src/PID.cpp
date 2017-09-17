#include "PID.h"
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

std::vector<float> PID::GetParamters(string file_name){
  string line;
  string lastline;
  std::vector<float> parameter_vector;


  //get the last line
  this->parameter_file.open(file_name);
  while (getline (this->parameter_file,line))
  {
     lastline=line;
  }

  //split the last line into parameter_vector
  std::istringstream iss(lastline);
  std::string token;

  while(std::getline(iss, token, ',')) {
      parameter_vector.push_back(stof(token));
  }
  for(int i =0; i< parameter_vector.size(); i++){
    cout << parameter_vector[i] << endl;
  }
  return parameter_vector;

}
void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  this->p_error = 0.0;
  this->i_error = 0.0;
  this->d_error = 0.0;
}

void PID::UpdateError(double cte) {
  this->d_error = cte - this->p_error;
  this->p_error = cte;
  this->i_error += cte;
//  steer = -tau_p*cte  - tau_d * v - tau_i * int_cte
  cout<< "CTE=" << cte << "," <<  p_error << "," << d_error << "," << i_error << std::endl;
}

double PID::ComputeSteer(){
  double steer = (-this->Kp*this->p_error)  - (this->Kd * this->d_error) - (this->Ki * this->i_error);
  cout << "original steer = " << steer << endl;
  if (steer < -1.0){
    steer = -1.0;
  }else if(steer > 1.0){
    steer = 1.0;
  }
  return steer;
}

double PID::TotalError() {
}
