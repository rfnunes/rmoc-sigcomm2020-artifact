// test : TestFiles/Algorithms/TestDominantPathsRestartingVectoringProtocol.cpp

// Public Library
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <time.h>

// My Library
#include "Algorithms/DominantPathsVectoringProtocols/Restarting/RestartingProtocolCode.h"
#include "Algorithms/DominantPathsVectoringProtocols/Restarting/RestartingRoutingState.h"
#include "Algorithms/DominantPathsVectoringProtocols/Restarting/RestartingRoutingSimulator.h"
#include "Graph/Graph.h"
#include "RoutingAlgebras/Extensions/Extensions.h"
#include "RoutingAlgebras/Orders/Orders.h"
#include "Utils/AugmentedStd.h"

using namespace Algorithms;
using namespace Graph;
using namespace RoutingAlgebras;

int main()
{
	std::cout << "\n------------------------ Test Dominant-Paths Restarting Vectoring Protocol ------------------------ " << std::endl;

	std::ifstream fileNetwork 	= std::ifstream( "TestNetworks/Rocketfuel/AS1239/WidthLength.txt" );
	// std::ifstream fileNetwork 	= std::ifstream( "TestNetworks/TestNetwork1.txt" );
	if( fileNetwork.fail()  )
	{	exit(1);			}

	int u, v, V; 
	std::pair < int, int > w;	

	fileNetwork >> V;
	Graph < std::pair < int, int > > graph( V );
	while( fileNetwork >> u >> v >> w )
	{	graph.addEdge( u, v, w ); 	}
	
	RoutingState < std::pair < int, int > > routingState( graph.V );

	std::vector  < std::mt19937 > 	  			gens;

	for( int t = 0 ; t < graph.V ; t ++ )
	{	gens.push_back(std::mt19937(std::time(0)));		}

	int t = 0;
	
	std::cout << "> Destination Announcement    :   Destination  = " << t << ", "  << std::endl;

	DestinationAnnouncement < std::pair < int, int >, DWLP, WL >(  graph, routingState, gens[t], t 	);
	RoutingSimulator 		< std::pair < int, int >, DWLP, WL >(  graph, routingState, gens   , 0  );

	std::cout << "\n----- Stable State ----- \n" << std::endl;
	for( int u = 0 ; u < graph.V ; u ++ )
	{
		std::cout << "  \t> Elected Attributes at Node " << u << "."   << std::endl;
		std::cout << "     \t\t< Destination = " 		 << t << " > " << std::endl;
		std::cout << "     \t\t\t< ";
		for( auto item  = routingState.dom[u][t].begin() ; 
				  item != routingState.dom[u][t].end()   ; item ++ )
		{	
			if(   item != routingState.dom[u][t].begin() )
			{	std::cout << "\n     \t\t\t  "; 		}

			std::pair < int, int > elec = item->first.first.first;
			int hopCount 				= item->first.first.second;
			int label 					= item->first.second;

			int nextHop					= item->second.first;
			int nextLabel				= item->second.second;

			std::cout << "< Attribute = " 	<< elec 	 	<< ", "   ;
			std::cout <<   	"Hop Count = "  << hopCount   	<< ", "   ;
			std::cout <<	"Label = "   	<< label   		<< ";  "  ;

			std::cout <<	"Next Hop = "   << nextHop   	<< ", "   ;
			std::cout <<   	"Next Label = " << nextLabel 	<< " > "  ;

		}
		std::cout << ">\n " << std::endl;	
	}

	// std::cout << "> Link Failure 				:   Link   		 = ( " << 273 << ", " << 79 << " )" << std::endl;

	// LinkFailure 			< std::pair < int, int >, DWLP, WL >(  graph, routingState, gens, 273, 79  );
	// RoutingSimulator 		< std::pair < int, int >, DWLP, WL >(  graph, routingState, gens, 1	    );

	// std::cout << "\n----- Stable State ----- \n" << std::endl;
	// for( int u = 0 ; u < graph.V ; u ++ )
	// {
	// 	std::cout << "  \t> Elected Attributes at Node " << u << "."   << std::endl;
	// 	std::cout << "     \t\t< Destination = " 		 << t << " > " << std::endl;
	// 	std::cout << "     \t\t\t< ";
	// 	for( auto item  = routingState.dom[u][t].begin() ; 
	// 			  item != routingState.dom[u][t].end()   ; item ++ )
	// 	{	
	// 		if(   item != routingState.dom[u][t].begin() )
	// 		{	std::cout << "\n     \t\t\t  "; 		}

	// 		std::pair < int, int > elec = item->first.first.first;
	// 		int hopCount 				= item->first.first.second;
	// 		int label 					= item->first.second;

	// 		int nextHop					= item->second.first;
	// 		int nextLabel				= item->second.second;

	// 		std::cout << "< Attribute = " 	<< elec 	 	<< ", "   ;
	// 		std::cout <<   	"Hop Count = "  << hopCount   	<< ", "   ;
	// 		std::cout <<	"Label = "   	<< label   		<< ";  "  ;

	// 		std::cout <<	"Next Hop = "   << nextHop   	<< ", "   ;
	// 		std::cout <<   	"Next Label = " << nextLabel 	<< " > "  ;


	// 	}
	// 	std::cout << "> " << std::endl;	
	// }

	std::cout << std::endl;
	std::cout << "------------------------------------------------------------------------ \n" 		<< std::endl;

}