// file : DominantPathsProtocols/RestartingProtocol/RestartingRoutingSimulator.h

#ifndef _RESTARTINGROUTINGSIMULATOR_H_
#define _RESTARTINGROUTINGSIMULATOR_H_

#include <random>
#include <vector>

#include "DominantPathsProtocols/RestartingProtocol/RestartingRoutingState.h"
#include "Graph/Graph.h"

using namespace Graph;

namespace Algorithms
{	
	template < 	typename S, typename Ext, typename Ord	>	
	double RoutingSimulator( 	
		const Graph  < S > 			  & ,
		RoutingState < S > 			  & ,
		std::vector  < std::mt19937 > & ,
		const int 					  & );
}

#endif