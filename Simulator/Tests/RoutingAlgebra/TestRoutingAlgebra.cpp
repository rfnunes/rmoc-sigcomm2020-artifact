// file: test/RoutingAlgebra/TestRoutingAlgebra.cpp

// Public Library
#include <iostream>

// Project Library
#include "RoutingAlgebra/Orders/Orders.h"
#include "RoutingAlgebra/Extensions/Extensions.h"
#include "Utils/AugmentedStd.h"

using namespace RoutingAlgebra;

int main()
{
	std::cout << "---------- Testing Routing Algebras ----------" << std::endl;
	
	std::cout << std::endl;

	{
	std::cout << "--- Example 1 = DominantWidthLengthsPaths = < < int, int >, ProductOrderWidthsLengths, WidthLengthsExtension > --- " << std::endl;

	std::pair < int, int > wl1, wl2;
	DWLP  ord;
	WL    ext;


	std::cout << std::endl;

	std::cout << "> Neutral Attribute = " 	<< (DWLP::Neutral) 				<< std::endl; 
	std::cout << "> Null Attribute    = " 	<< (DWLP::Null) 	 			<< std::endl; 

	std::cout << std::endl;

	std::cout << "> wl1 = "           		<< wl1                  		<< std::endl; 
	std::cout << "> wl1 == wl1     ? " 		<< (wl1 == wl1)          		<< std::endl;
	std::cout << "> wl1 != wl1     ? " 		<< (wl1 != wl1)          		<< std::endl;
	std::cout << "> wl1 <  wl1     ? " 		<< (wl1 <  wl1)          		<< std::endl;
	std::cout << "> wl1 + Neutral  = " 		<< ( ext(wl1, DWLP::Neutral ) 	<< std::endl;	
	std::cout << "> wl1 + Null     = " 		<< ( ext(wl1, DWLP::Null ) 		<< std::endl;	
	
	std::cout << std::endl;

	std::cout << "> wl2 = " 				<< wl2 							<< std::endl;
	std::cout << "> wl1 == wl2     ? " 		<< (wl1 == wl2) 				<< std::endl;
	std::cout << "> wl1 != wl2     ? " 		<< (wl1 != wl2) 				<< std::endl;
	std::cout << "> wl1 +  wl2     = " 		<< (wl1 +  wl2)					<< std::endl;	
	std::cout << "> wl1 <  wl2     ? " 		<< (wl1 <  wl2) 				<< std::endl;
	std::cout << "> wl2 <  wl1     ? " 		<< (wl2 <  wl1) 	 			<< std::endl;
	
	std::cout << std::endl;
	}

	std::cout << " ------------------------------------------------------------------------ " << std::endl;

	return 0;
}