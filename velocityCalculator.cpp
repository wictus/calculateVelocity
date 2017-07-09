#include "velocityCalculator.h"


velocityCalculator::velocityCalculator()
{

}

void velocityCalculator::addPosition(const double position)
{
  fPositions.push_back(position);  
}

void velocityCalculator::setPrefix(const std::string& prefix)
{
  fPrefix = prefix;
}

void velocityCalculator::setSuffix(const std::string& suffix)
{
  fSuffix = suffix;
}

void velocityCalculator::loadData(const std::string& topOrBottom)
{
  if(0!= fDataFromFiles.size())
    fDataFromFiles.clear();
  if(0!= fDataPerThreshold.size() )
    fDataPerThreshold.clear();
  std::ifstream file;
  std::ostringstream strs;
    
  for( auto position: fPositions )
  {
    
    strs << position;
    std::string sPosition = strs.str();
    file.open( fPrefix+sPosition+fSuffix+"/_"+ topOrBottom+"_meanTimes"+sPosition+fSuffix+".txt" );
    if(!file.good())
    {
      std::cout<< "Bad path to file: " << fPrefix+sPosition+fSuffix+"/_"+ topOrBottom+"_meanTimes"+sPosition+fSuffix+".txt" 
      << " check your suffixes and prefixes \n";
      std::exit(2);
    }
    strs.str(std::string() );
    
    double threshold, meanTime, meanTimeError;
    std::pair<double, std::pair<double, double> > positionData;
    while (file >> threshold >> meanTime >> meanTimeError )
    {
      positionData = std::make_pair<>(position, std::make_pair<>(meanTime, meanTimeError) ); 
      fDataFromFiles.push_back(std::make_pair<>(threshold,positionData));
      if( std::find(fThresholds.begin(), fThresholds.end(), threshold) == fThresholds.end() )
	fThresholds.push_back(threshold);
    
    }
    
    
    
    file.close();
    
  }
  /*  example of accessing data
  for( auto element: fDataFromFiles )
    std::cout<< element.first << "\t" << element.second.first << "\t" << element.second.second.first << std::endl;
  */
  
  
  for( auto threshold: fThresholds )
  {
    std::vector<std::pair<double,std::pair<double,double> > > dataFromOneThreshold;
    for( auto element: fDataFromFiles )
    {
      
	if(threshold == element.first)
	  dataFromOneThreshold.push_back( std::make_pair<>(element.second.first, element.second.second) );
	
    }
    fDataPerThreshold[threshold] = dataFromOneThreshold;
    dataFromOneThreshold.clear();
  }
  
}

void velocityCalculator::plotVelocities()
{
  loadData(fNameOfStrip);
  
  for(auto threshold: fThresholds)
  {
    TCanvas* c = new TCanvas();
    TGraph* graph = new TGraph();
    int i = 0;
    for(auto position: fDataPerThreshold[threshold] )
    {
      graph->SetPoint(i++, position.first, position.second.first);
    } 
    std::stringstream sThr;
    sThr << threshold;
    graph->SetMarkerStyle(20);
    graph->Draw("AP");
    graph->Fit("pol1");
    TF1* fit = graph->GetFunction("pol1");
    fitsForThresholds.push_back(std::make_pair<>(threshold, std::make_pair<>(fit->GetParameter(1), fit->GetParError(1))));
    gStyle->SetOptFit(1);
    c->SaveAs( (sThr.str()+"mV_TOP.png").c_str() );
    sThr.str(std::string(""));
    delete graph;
    delete c;
  }
  
  
}

void velocityCalculator::setNameOfStrip(const std::string& name)
{
  fNameOfStrip = name;
}


void velocityCalculator::calculateVelocities()
{
  for( auto fit: fitsForThresholds )
  {
    velocitiesForThresholds.push_back(std::make_pair<>(fit.first, std::make_pair<>( 1.0/fit.second.first *2*100, fit.second.second *2 / fit.second.first *100 ) ) ); 
  }
}

void velocityCalculator::plotVelocityVsThreshold()
{
  TCanvas* c = new TCanvas();
  TGraphErrors* graph = new TGraphErrors();
  int i = 0;
  for( auto velocity: velocitiesForThresholds )
  {
      std::cout << velocity.second.first << std::endl;
      graph->SetPoint(i, velocity.first, fabs(velocity.second.first) );
      graph->SetPointError(i,0, velocity.second.second);
      i++;
  }
  graph->SetMarkerStyle(20);
  graph->GetXaxis()->SetRangeUser(0,250);
  graph->GetXaxis()->SetTitle("Threshold [mV]");
  graph->GetYaxis()->SetTitle("Velocity [cm/ns]");
  graph->GetYaxis()->SetRangeUser(0,15);  
  graph->Fit("pol1");
  graph->Draw("AP");
  
  c->SaveAs("thrVsV.png");
}

