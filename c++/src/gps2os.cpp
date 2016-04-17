#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "core_dll.h"
#include "osgb_dll.h"
//#include "high_precision_osgb_dll.h"

int main(void)
{
	// Disclaimer
	std::cout << std::endl;
	std::cout << "This is an alpha release and should not be used in real life situations." <<std::endl;
	std::cout << "This software comes with NO WARRENTY. Use at your own risk!" <<std::endl;
	system("pause");
	std::cout << std::endl;
	
	// Get precision level
	std::string input = "";
	int prec=0;
	
	while (true){
		std::cout << "Would you like 6 figure or 8 figure grid reference?" << std::endl;
		std::getline(std::cin,input);
		
		std::stringstream myStream(input);
		
		if(input.length()==0)
		{
			prec = 3;
			break;
		}
		
		if (myStream>>prec){
			if (prec==6||prec==8)
			{
				prec = prec/2;
				break;
			}
		}
		
		std::cout << "Invalid number, please try again" << std::endl;
	}
	
	std::string prec_str;
	if (prec==3){
		prec_str="4 D.P.";
		std::cout << std::setprecision(4);
	}else{if(prec==4){
		prec_str="5 D.P.";
		std::setprecision(5);
	}else{if(prec==5){
		prec_str="7 D.P.";
		std::setprecision(7);
	}else{
		std::cout << "Error: prec value is invalid in main()"<<std::endl;
		return 1;
	}}}
	
	// Get latitude
	double phi,lambda;
	while (true){
		std::cout << "Enter latitude to at least " << prec_str << std::endl;
		std::getline(std::cin,input);
		
		std::stringstream myStream(input);
		if (myStream>>phi){
			if (phi>49.5&&phi<62)
				break;
			else {
				std::cout << "Latitude does not correspond to a point in the UK" << std::endl;
				continue;
			}
		}
		
		std::cout << "Invalid number, please try again" << std::endl;
	}
	
	// Get longitude
	double ew_flag=0.0;
	while (true){ 
		std::cout << "Is the longitude [E]ast or [W]est?" << std::endl;
		std::getline(std::cin,input);
		
		std::stringstream myStream(input);
		if(input.length()==0)
		{
			ew_flag = -1.0;
			break;
		}
		
		if (input.length()==1){
			if (input.compare("E")==0||input.compare("e")==0){
				ew_flag = 1.0;
				break;
			}else{if(input.compare("W")==0||input.compare("w")==0){
				ew_flag = -1.0;
				break;
			}}
		}	
		std::cout << "Please type 'E' or 'W' " << std::endl;
	}
	
	while (true) {
		std::cout << "Enter longitude to at least " << prec_str << std::endl;
		std::getline(std::cin,input);
		
		std::stringstream myStream(input);
		if (myStream>>lambda){
			if (lambda<0.0){
				std::cout << "Please enter a positive value" << std::endl;
				continue;
			}
			lambda = lambda*ew_flag;
			if(lambda>-10.0 && lambda < 4.0)
				break;
			std::cout << "Longitude does not correspond to a point in the UK" << std::endl;
			continue;
		}
		std::cout << "Invalid number, please try again" << std::endl;
		
	}
	
	// Print out the lat-long that we are solving for as a check to the user
	system("CLS");
	
	std::string ew_tag = "E";
	if (lambda<0.0)
		ew_tag = "W";
	
	std::cout << std::endl;
	std::cout << std::fixed  << "The OS grid reference for:  N "<< phi << "  " << 
		ew_tag <<" " << fabs(lambda) << std::endl;
	std::cout << std::endl;
	
	// Find OS grid
	double h = 0;
	std::string os = gps2os(phi,lambda,h,prec);
	
	// Print out result
	std::string stars="****************";
	if(prec==4){
		stars=stars+"**";
	}else{if(prec==5){
		stars=stars+"****";
	}}
	
	std::cout << stars << std::endl;
	std::cout << "  " << os  << std::endl;
	std::cout << stars << std::endl << std::endl;
	
	system("pause");
	
    return 0;
};


