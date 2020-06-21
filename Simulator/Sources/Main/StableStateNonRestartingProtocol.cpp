// File 	   : Main/StableStateNonRestartingProtocol.cpp

// Description : 

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <time.h>

#include "Graph/Graph.h"
#include "RoutingAlgebras/Extensions/Extensions.h"
#include "RoutingAlgebras/Orders/Orders.h"
#include "DominantPathsProtocols/NonRestartingProtocol/NonRestartingRoutingState.h"
#include "DominantPathsProtocols/NonRestartingProtocol/NonRestartingProtocolCode.h"
#include "DominantPathsProtocols/NonRestartingProtocol/NonRestartingRoutingSimulator.h"
#include "Utils/AugmentedStd.h"

using namespace Graph;
using namespace RoutingAlgebras;
using namespace DominantPathsProtocols;

template < typename S, typename Ord, typename Ext >
void RunnerStableStateNonRestartingProtocol ( 
	std::string fNetwork 	,	 
	std::string fCriterion  )
{
	std::string fileNameNetwork 	= "../NetworkDataSets/" + fNetwork + ".txt";

	std::ifstream fileNetwork   	= std::ifstream( fileNameNetwork );
	if( fileNetwork.fail()  	) 
	{	exit(1);				}

	std::cout << "> Test Network             = " <<  fNetwork   << std::endl;
	std::cout << "> Optimality Criterion     = " <<  fCriterion << std::endl;
	std::cout << "> Destination Announcement " 					<< std::endl;

	std::cout << std::endl;

	std::string fileNameStableState = "../Results/" + fNetwork + "/" + fCriterion + "/StableState.csv";

	std::ofstream fileStableState   = std::ofstream( fileNameStableState );
	if( fileStableState.fail()  )
	{	exit(1); 		   		}

	int u, v, V; 
	S attrWeight;	

	fileNetwork >> V;
	
	Graph < S > graph( V );
	while( fileNetwork >> u >> v >> attrWeight )
	{	graph.addEdge( u, v, attrWeight ); 	   }

	NonRestartingProtocol::RoutingState < S > routingState( graph.V );

	std::vector  < std::mt19937 > gens;

	for( int t = 0 ; t < graph.V ; t ++ )
	{	gens.push_back( std::mt19937( 0 ) ); }

	for( int s = 0 ; s < graph.V ; s ++ )
	{	fileStableState << ", " << s;	}
	fileStableState << "\n";
	
	int simsCompleted = 0;
	int simsTotal 	  = graph.V;

	for( int t = 0 ; t < graph.V ; t ++ )
	{
		std::cout << "\r... Progress = " << simsCompleted << " of out " << simsTotal << " simulations completed.";
		std::cout.flush();

		NonRestartingProtocol::DestinationAnnouncement 	< S, Ord, Ext >(  graph, routingState, gens[t], t );
		NonRestartingProtocol::RoutingSimulator 		< S, Ord, Ext >(  graph, routingState, gens 	  );

		fileStableState << t;

		for( int s = 0 ; s < graph.V ; s ++ )
		{
			fileStableState << ", ";

			for( auto item  = routingState.dom[s][t].begin() ; 
					  item != routingState.dom[s][t].end()   ; item ++ )
			{	
				fileStableState << " " << item->first;
			}
		}

		fileStableState << "\n";

		simsCompleted ++;
	}

	std::cout << "\r... Progress = " << simsCompleted << " of out " << simsTotal << " simulations completed.";
	std::cout.flush();

	std::cout << "\n" << std::endl;
	std::cout << "... Save results file to " << fileNameStableState << "." << std::endl;

	std::cout << std::endl;

	return;
}

int main( int argc, char *argv[] )
{
	std::cout << "\n-------- Stable State of the Non-Restarting Protocol --------\n" << std::endl;

	int opt;

	std::string fNetwork, fCriterion;

	while( ( opt = getopt( argc, argv, "n:c:t:" ) ) != -1 ) 
	{
		switch( opt )
		{	case 'n':
				fNetwork     = std::string( optarg );
				break;
			case 'c':
				fCriterion 	 = std::string( optarg );
				break;		
			default	:
				break;
		}
	}

	if(	fNetwork.empty() or fCriterion.empty() ) 
	{	return 0;	}
	
	if( 	 fCriterion.compare( "ShortestWidestPaths" )  == 0 )
	{	RunnerStableStateNonRestartingProtocol < std::pair < int, int >, SWO,  WL > ( fNetwork, fCriterion );	
	}
	else if( fCriterion.compare( "WidestShortestPaths" )  == 0 )
	{	RunnerStableStateNonRestartingProtocol < std::pair < int, int >, WSO,  WL > ( fNetwork, fCriterion );	
	}
	else if( fCriterion.compare( "DominantHopsLengthsPaths" 	) == 0 )
	{	RunnerStableStateNonRestartingProtocol < std::pair < int, int >, POHL, HL > ( fNetwork, fCriterion );	
	}
	else if( fCriterion.compare( "DominantWidthHopsPaths" 		) == 0 )
	{	RunnerStableStateNonRestartingProtocol < std::pair < int, int >, POWH, WH > ( fNetwork, fCriterion );	
	}
	else if( fCriterion.compare( "DominantWidthLengthsPaths" 	) == 0 )
	{	RunnerStableStateNonRestartingProtocol < std::pair < int, int >, POWL, WL > ( fNetwork, fCriterion );	
	}	
	else if( fCriterion.compare( "DominantWidthHopsLengthPaths" ) == 0 )
	{	RunnerStableStateNonRestartingProtocol < std::tuple < int, int, int >, POWHL, WHL > ( fNetwork, fCriterion );	
	}	
}
