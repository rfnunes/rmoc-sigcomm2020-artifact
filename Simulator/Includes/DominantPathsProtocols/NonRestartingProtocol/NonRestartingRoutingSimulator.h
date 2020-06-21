// File : DominantPathsProtocols/NonRestartingProtocol/NonRestartingRoutingSimulator.h

// Description : 

#ifndef _NONRESTARTINGPROTOCOLROUTINGSIMULATOR_H_
#define _NONRESTARTINGPROTOCOLROUTINGSIMULATOR_H_

#include <random>
#include <vector>
 
#include "DominantPathsProtocols/NonRestartingProtocol/NonRestartingRoutingState.h"
#include "Graph/Graph.h"

using namespace Graph;

namespace DominantPathsProtocols
{	
	namespace NonRestartingProtocol
	{
		template < typename S, typename Ord, typename Ext >
		double RoutingSimulator( 	
			const Graph  < S > 			  & ,
			RoutingState < S > 			  & ,
			std::vector  < std::mt19937 > & );
	}
}

#endif