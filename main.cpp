#include <iostream>
#include "velocityCalculator.h"


int main(int argc, char **argv) {
    
  //velocityCalculator
  velocityCalculator calculator;
  
  //set positions
  for(double i = 50; i < 451;i+=100)
    calculator.addPosition(i);
    
  //set prefix and suffix
  calculator.setPrefix("../ThresholdScan7x19x500_colimator");
  calculator.setSuffix("_200-450");
  calculator.setNameOfStrip("BOTTOM");
  
  //plot velocities
  calculator.plotVelocities();
  //calcualte velocities
  calculator.calculateVelocities();
  //plot velocity vs threshold
  calculator.plotVelocityVsThreshold();
  //calculate effective velocity
  
    return 0;
}
