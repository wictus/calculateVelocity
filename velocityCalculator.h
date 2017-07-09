#ifndef VELOCITYCALCULATOR
#define VELOCITYCALCULATOR

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TAxis.h"

class velocityCalculator
{
public:
  velocityCalculator();
  void addPosition(const double position);
  void setPrefix(const std::string& prefix);
  void setSuffix(const std::string& suffix);
  void setNameOfStrip(const std::string& name);
  void plotVelocities();
  void calculateVelocities();
  void plotVelocityVsThreshold();
private:
  void loadData(const std::string& topOrBottom);
  std::vector<std::pair<double, std::pair<double, std::pair<double, double> > > > fDataFromFiles;
  std::vector<double> fPositions;
  std::vector<double> fThresholds;
  std::map<double, std::vector<std::pair<double,std::pair<double,double> > > > fDataPerThreshold; 
  std::string fPrefix="";
  std::string fSuffix="";
  std::vector<std::pair<double,std::pair<double,double> > > fitsForThresholds;
  std::vector<std::pair<double, std::pair<double, double> > > velocitiesForThresholds;
  std::string fNameOfStrip;
};

#endif //VELOCITYCALCULATOR