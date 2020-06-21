// file : DominantPathsProtocols/NonRestartingProtocol/RestartingRoutingSimulatorInstances.h

// My Libraries
#include "RoutingAlgebras/Orders/Orders.h"
#include "RoutingAlgebras/Extensions/Extensions.h"
#include "Utils/AugmentedStd.h"

using namespace RoutingAlgebras;

namespace Algorithms
{
	template double RoutingSimulator < std::pair < int, int >, DHLP,  HL 		> ( 
		const Graph   	< std::pair < int, int > > 			&, 
		RoutingState 	< std::pair < int, int > > 			&,
		std::vector 	< std::mt19937 > 					&, 
		const 			int									& );

	template double RoutingSimulator < std::pair < int, int >, DWHP,  WH 		> ( 
		const Graph   	< std::pair < int, int > > 			&, 
		RoutingState 	< std::pair < int, int > > 			&,
		std::vector 	< std::mt19937 > 					&, 
		const 			int									& );

	template double RoutingSimulator < std::pair < int, int >, DWLP,  WL 		> ( 
		const Graph   	< std::pair < int, int > > 			&, 
		RoutingState 	< std::pair < int, int > > 			&,
		std::vector 	< std::mt19937 > 					&, 
		const 			int									& );

	template double RoutingSimulator < std::tuple < int, int, int >, DWHLP, WHL > ( 
		const Graph   	< std::tuple < int, int, int > > 	&, 
		RoutingState 	< std::tuple < int, int, int > > 	&,
		std::vector 	< std::mt19937 > 					&, 
		const 			int									& );
}
