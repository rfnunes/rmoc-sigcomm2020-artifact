// File 	   : Main/TransientBehaviourNonRestartingProtocol.cpp

// Description : 

#include <iomanip> 
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

using namespace DominantPathsProtocols;
using namespace Graph;
using namespace RoutingAlgebras;

# define ANNOUNCEMENT 0
# define FAILURE 1

template < typename S, typename Ord, typename Ext >
void RunnerTransientBehaviourNonRestartingProtocol( 
	std::string fNetwork 			, 
	std::string fCriterion   		,
	int fEvent 						)
{
	// 
	std::string fileNameNetwork 	= "../NetworkDataSets/" + fNetwork + ".txt";

	std::ifstream fileNetwork   	= std::ifstream( fileNameNetwork );
	if( fileNetwork.fail()  ) 
	{	exit(1);			}

	std::cout << "> Test Network             = " <<  fNetwork   << std::endl;
	std::cout << "> Optimality Criterion     = " <<  fCriterion << std::endl;
	if( fEvent == ANNOUNCEMENT )
	{	std::cout << "> Destination Announcement " 				<< std::endl;	}
	if( fEvent == FAILURE 	   )
	{	std::cout << "> Link Failure " 							<< std::endl;	}

	std::cout << std::endl;

	// 
	int u, v, V; 
	S attrWeight;	

	fileNetwork >> V;
	
	Graph < S > graph( V );
	while( fileNetwork >> u >> v >> attrWeight )
	{	graph.addEdge( u, v, attrWeight ); 	   }

	if( fEvent == ANNOUNCEMENT )
	{
		std::string fileNameTerminationTimes = "../Results/" + fNetwork + "/" + fCriterion + "/DestinationAnnouncementTerminationTimes.csv" ;

		std::ofstream fileTerminationTimes   = std::ofstream( fileNameTerminationTimes );
		if( fileTerminationTimes.fail() )
		{	exit(1); 	}

		for( int t = 0 ; t < graph.V ; t ++ )
		{	fileTerminationTimes << ", " << t;	}
		fileTerminationTimes << "\n";

		int simulationsCompleted = 0;
		int simulationsTotal 	 = 1 * graph.V ;

		for( int i = 0 ; i < 1 ; i ++ )
		{
			unsigned seed = rand();

			fileTerminationTimes << seed;

			std::vector < std::mt19937 > gens;
			std::mt19937 gen = std::mt19937( seed );
			
			gens.clear();
			for( int t = 0 ; t < graph.V ; t ++ )
			{	gens.push_back( std::mt19937( gen() ) ); }

			for( int t = 0 ; t < graph.V ; t ++ )
			{
				std::cout << "\r... Progress = " << simulationsCompleted << " of out " << simulationsTotal << " simulations completed.";
				std::cout.flush();

				NonRestartingProtocol::RoutingState < S > routingState( graph.V );
				
				NonRestartingProtocol::DestinationAnnouncement 			  	     < S, Ord, Ext >(  graph, routingState, gens[t], t ); 
				double terminationTime = NonRestartingProtocol::RoutingSimulator < S, Ord, Ext >(  graph, routingState, gens 		);
			
				fileTerminationTimes << ", " << std::setprecision(4) << terminationTime;
			
				simulationsCompleted ++;
			}

			fileTerminationTimes << "\n";
		}

		std::cout << "\r... Progress = " << simulationsCompleted << " of out " << simulationsTotal << " simulations completed.";
		std::cout.flush();

		std::cout << "\n" << std::endl;
		std::cout << "... Save results file to " << fileNameTerminationTimes << "." << std::endl;

		std::cout << std::endl;
	}
	
	if( fEvent == FAILURE )
	{		
		std::string fileNameTerminationTimes = "../Results/" + fNetwork + "/" + fCriterion + "/LinkFailureTerminationTimes.csv" ;

		std::ofstream fileTerminationTimes   = std::ofstream( fileNameTerminationTimes );
		if( fileTerminationTimes.fail() )
		{	exit(1); 	}

		NonRestartingProtocol::RoutingState < S > initialState( graph.V );

		std::vector  < std::mt19937 > gens;

		for( int t = 0 ; t < graph.V ; t ++ )
		{	gens.push_back( std::mt19937( 0 ) ); }

		for( int t = 0 ; t < graph.V ; t ++ )
		{	NonRestartingProtocol::DestinationAnnouncement < S, Ord, Ext >(  graph, initialState, gens[t], t 	); 
			NonRestartingProtocol::RoutingSimulator 	   < S, Ord, Ext >(  graph, initialState, gens 			);
		}

		for( u = 0 ; u < graph.V ; u ++ )
		{	for( auto it  = graph.adjListOut[u].begin() ;
					  it != graph.adjListOut[u].end()	; it ++ )
			{	v = it->first;
				fileTerminationTimes << ", " << std::make_pair(u, v) ;	
			}
		}
		fileTerminationTimes << "\n";

		int simulationsCompleted = 0;
		int simulationsTotal 	 = 1 * graph.E ;

		for( int i = 0 ; i < 1 ; i ++ )
		{			
			unsigned seed = rand();

			fileTerminationTimes << seed;

			std::mt19937 gen = std::mt19937( seed );

			for( u = 0 ; u < graph.V ; u ++ )
			{
				for( auto it  = graph.adjListOut[u].begin() ;
					  	  it != graph.adjListOut[u].end()	; it ++ )
				{
				 	v = it->first;

					gens.clear();
					for( int t = 0 ; t < graph.V ; t ++ )
					{	gens.push_back( std::mt19937( gen() ) ); }

					std::cout << "\r... Progress = " << simulationsCompleted << " of out " << simulationsTotal << " simulations completed.";
					std::cout.flush();

					NonRestartingProtocol::RoutingState < S > routingState = initialState;

					NonRestartingProtocol::LinkFailure 						   		  < S, Ord, Ext >(  graph, routingState, gens, u, v ); 
					double terminationTime = NonRestartingProtocol::RoutingSimulator  < S, Ord, Ext >(  graph, routingState, gens 		);

					fileTerminationTimes << ", " << std::setprecision(4) << terminationTime;
			
					simulationsCompleted ++;

					graph.activate( u, v );
				}
			} 
			fileTerminationTimes << "\n";
		}
	}
}

int main( int argc, char *argv[] )
{
	std::cout << "\n-------- Transient Behaviour of the Non-Restarting Protocol --------\n" << std::endl;

	int opt;

	std::string 		   fNetwork   ,
						   fCriterion ;
	int					   fEvent = -1;

	while( ( opt = getopt( argc, argv, "n:c:e:" ) ) != -1 ) 
	{
		switch( opt )
		{	case 'n':
				fNetwork 	 = std::string( optarg );
				break;
			case 'c':
				fCriterion 	 = std::string( optarg );
				break;
			case 'e':
				fEvent 		 = atoi( optarg );
				break;
			default:
				break;
		}
	}

	if(	fNetwork.empty() 				or 
		fCriterion.empty()  		    or
	  ( fEvent != 0 and fEvent != 1 )	) 
	{	return 0;	}
	
	if( 	 fCriterion.compare( "ShortestWidestPaths" )  == 0 )
	{	RunnerTransientBehaviourNonRestartingProtocol < std::pair < int, int >, SWO,  WL > ( fNetwork, fCriterion, fEvent );	
	}
	else if( fCriterion.compare( "WidestShortestPaths" )  == 0 )
	{	RunnerTransientBehaviourNonRestartingProtocol < std::pair < int, int >, WSO,  WL > ( fNetwork, fCriterion, fEvent );	
	}
	else if( fCriterion.compare( "DominantHopsLengthPaths" 	) == 0 )
	{	RunnerTransientBehaviourNonRestartingProtocol < std::pair < int, int >, POHL, HL > ( fNetwork, fCriterion, fEvent );	
	}
	else if( fCriterion.compare( "DominantWidthHopsPaths" 		) == 0 )
	{	RunnerTransientBehaviourNonRestartingProtocol < std::pair < int, int >, POWH, WH > ( fNetwork, fCriterion, fEvent );	
	}
	else if( fCriterion.compare( "DominantWidthLengthPaths" 	) == 0 )
	{	RunnerTransientBehaviourNonRestartingProtocol < std::pair < int, int >, POWL, WL > ( fNetwork, fCriterion, fEvent );	
	}	
	else if( fCriterion.compare( "DominantWidthHopsLengthPaths" ) == 0 )
	{	RunnerTransientBehaviourNonRestartingProtocol < std::tuple < int, int, int >, POWHL, WHL > ( fNetwork, fCriterion, fEvent );	
	}	
}
