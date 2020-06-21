// test : TestFiles/DominantPathsProtocols/TestNonRestartingProtocol.cpp

// Public Libraries
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <time.h>

// My Libraries
#include "DominantPathsProtocols/NonRestartingProtocol/RoutingState.h"
#include "DominantPathsProtocols/NonRestartingProtocol/ProtocolCode.h"
#include "DominantPathsProtocols/NonRestartingProtocol/RoutingSimulator.h"
#include "Graph/Graph.h"
#include "RoutingAlgebras/Extensions/Extensions.h"
#include "RoutingAlgebras/Orders/Orders.h"
#include "Utils/AugmentedStd.h"

using namespace DominantPathsProtocols;
using namespace Graph;
using namespace RoutingAlgebras;

int main()
{
	std::cout << "\n------------------------ Test Non-Restarting Protocol ------------------------ " << std::endl;

	std::ifstream fileNetwork 	= std::ifstream( "../NetworkDataSets/Network1.txt" );
	if( fileNetwork.fail() )
	{	exit(1);		}

	int u, v, V; 
	std::pair < int, int > w;	

	fileNetwork >> V;
	Graph < std::pair < int, int > > graph( V );
	while( fileNetwork >> u >> v >> w )
	{	graph.addEdge( u, v, w ); 	}

	std::cout << "\n> The network of Figure 1 in the paper. The attribute of each link is a pair width-length.\n" << std::endl;
	std::cout << graph << std::endl;
	std::cout << std::endl;
	
	{
		NonRestartingProtocol::RoutingState < std::pair < int, int > > routingState( graph.V );

		std::vector  < std::mt19937 > gens;
		for( int t = 0 ; t < graph.V ; t ++ )
		{	gens.push_back( std::mt19937( std::time( 0 ) ) );	}

		int t = 0;
		
		std::cout << "> (1) Stable state of a vectoring protocol operating according to shortest-widest order for destination $0$.\n"  << std::endl;

		NonRestartingProtocol::DestinationAnnouncement < std::pair < int, int >, SWP, WL >(  graph, routingState, gens[t], t 	);
		NonRestartingProtocol::RoutingSimulator < std::pair < int, int >, SWP, WL >(  graph, routingState, gens 		);

		for( int u = 0 ; u < graph.V ; u ++ )
		{
			std::cout << "  \t> Elected attribute at node " << u << ". " << std::endl;
			std::cout << "     \t\t\t< ";
			for( auto item  = routingState.dom[u][t].begin() ; 
					  item != routingState.dom[u][t].end()   ; item ++ )
			{	
				if(   item != routingState.dom[u][t].begin() )
				{	std::cout << "\n     \t\t\t  "; 		}

				std::pair < int, int > elec = item->first.first;
				int hops 					= item->first.second;
				
				int label 					= item->second.first;
				int nextHop					= item->second.second.first;
				int nextLabel				= item->second.second.second;

				std::cout << "< Attribute = " << elec 	 	<< ", "   ;
				std::cout <<   	    "Hops = " << hops   	<< ", "   ;
				std::cout <<	   "Label = " << label   	<< ";  "  ;

				std::cout <<    "Next Hop = " << nextHop   	<< ", "   ;
				std::cout <<  "Next Label = " << nextLabel 	<< " > "  ;
			}
			std::cout << ">\n " << std::endl;	
		}
	}

	{
		NonRestartingProtocol::RoutingState < std::pair < int, int > > routingState( graph.V );

		std::vector  < std::mt19937 > gens;
		for( int t = 0 ; t < graph.V ; t ++ )
		{	gens.push_back( std::mt19937( std::time( 0 ) ) );	}

		int t = 0;
		
		std::cout << "> (2) Stable state of a vectoring protocol operating according to product order on width-lengths for destination $0$.\n"  << std::endl;

		NonRestartingProtocol::DestinationAnnouncement < std::pair < int, int >, DWLP, WL >(  graph, routingState, gens[t], t 	);
		NonRestartingProtocol::RoutingSimulator 		  < std::pair < int, int >, DWLP, WL >(  graph, routingState, gens 		);

		for( int u = 0 ; u < graph.V ; u ++ )
		{
			std::cout << "  \t> Elected attributes at node " << u << ". " << std::endl;
			std::cout << "     \t\t\t< ";
			for( auto item  = routingState.dom[u][t].begin() ; 
					  item != routingState.dom[u][t].end()   ; item ++ )
			{	
				if(   item != routingState.dom[u][t].begin() )
				{	std::cout << "\n     \t\t\t  "; 		}

				std::pair < int, int > elec = item->first.first;
				int hops 					= item->first.second;
				
				int label 					= item->second.first;
				int nextHop					= item->second.second.first;
				int nextLabel				= item->second.second.second;

				std::cout << "< Attribute = " << elec 	 	<< ", "   ;
				std::cout <<   	    "Hops = " << hops   	<< ", "   ;
				std::cout <<	   "Label = " << label   	<< ";  "  ;

				std::cout <<    "Next Hop = " << nextHop   	<< ", "   ;
				std::cout <<  "Next Label = " << nextLabel 	<< " > "  ;
			}
			std::cout << ">\n " << std::endl;	
		}
	}

	std::cout << "------------------------------------------------------------------------ \n" 		<< std::endl;

}