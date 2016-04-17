#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "core_dll.h"
#include "osgb_dll.h"

int input_easting(int prec,double *out);

int main(void)
{
	// Disclaimer
	std::cout << std::endl;
	std::cout << "This is an alpha release and should not be used in real life situations." <<std::endl;
	std::cout << "This software comes with NO WARRENTY. Use at your own risk!" <<std::endl;
	system("pause");
	std::cout << std::endl;
	
	//Get precision level
	std::string input = "";
	int prec=0;
	
	while (true){
		std::cout << "Would you like to enter a 6 figure or an 8 figure grid reference?" << std::endl;
		std::getline(std::cin,input);
		
		if(input.length()==0){
			prec = 3;
			break;
		}
		
		std::stringstream myStream(input);
		if (myStream>>prec){
			if (prec==6||prec==8){
				prec = prec/2;
				break;
			}
		}
		
		std::cout << "Invalid number, please try again" << std::endl;
	}
	
	std::string prec_str;
	if (prec==3){
		prec_str="3 figure";
	}else{if(prec==4){
		prec_str="4 figure";
	}else{if(prec==5){
		prec_str="5 figure";
	}else{
		std::cout << "Error: prec value is invalid in main()"<<std::endl;
		return 1;
	}}}
	
	//Get OS letter code
	std::string let_code;
	while (true){ 
		std::cout << "Enter OS letter code" << std::endl;
		std::getline(std::cin,input);
		
		if (input.length()==2){
			transform(input.begin(), input.end(), input.begin(), toupper);
			if(test_os_letter_code(input)==0){
				let_code = input;
				break;
			} else {
				std::cout << "OS letter code was invalid" << std::endl;
				continue;
			}
		}	
		std::cout << "OS letter codes are two characters" << std::endl;
	}

	// Get easting	
	double east;
	while (true){
		std::cout << "Enter " << prec_str << " easting"  << std::endl;
		if (input_easting(prec, &east)==0)
			break;
	}
	
	//Get northing
	double north;
	while (true){
		std::cout << "Enter " << prec_str << " northing"  << std::endl;
		if (input_easting(prec, &north)==0)
			break;
	}
	
	double h = 0;
	char d_m_s[] ="d";

	//double north = 18.0;
	
	// Print out OS grid that we are solving for as a check to the user
	system("CLS");
	
	std::cout << std::endl;
	std::cout << "The GPS co-ordinates for:  "<< let_code << " " << 
		std::setw(prec) << std::setfill('0') << east <<" " << 
		std::setw(prec) << std::setfill('0') << north << std::endl;
	std::cout << std::endl;
	
	// Find GPS co-ordinates
	std::string gps = os2gps(let_code,east,north,h,d_m_s,prec);
	
	//Print result
	std::string stars="***********************";
	if(prec==4){
		stars=stars+"**";
	}else{if(prec==5){
		stars=stars+"****";
	}}
	
	std::cout << stars << std::endl;
	std::cout << "  " << gps << std::endl;
	std::cout << stars << std::endl;
	
	system("pause");
	
    return 0;
};

int input_easting(int prec,double *out){
	std::string input = "";
	std::getline(std::cin,input);
	double east;
	
	if (input.length()==prec){
		std::stringstream myStream(input);
		if (myStream>>east){
			if (east>=0.0 && east<pow(10,double(prec)))
				if (round(east)==east){
					*out = east;
					return 0;
				}
				else {
					std::cout << "Cannot be a decimal" << std::endl;
					return 1;						
				}
			else {
				std::cout << "Invalid entry" << std::endl;
				return 1;
			}
		}
	}
	
	std::cout << "Number of digits is not correct, please try again" << std::endl;
	
	return 1;
}