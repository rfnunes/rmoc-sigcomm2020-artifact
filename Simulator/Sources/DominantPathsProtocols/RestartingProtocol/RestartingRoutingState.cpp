// file : Algorithms/DominantPathsProtocols/RestartingProtocol/RestartingRoutingState.cpp

// Project Library
#include "DominantPathsProtocols/RestartingProtocol/RestartingRoutingState.h"

namespace Algorithms
{	
	template < class S >
	Route < S > :: Route(	int t,
							Advertisement < S > adv )
	{	
		this->t = t;
		this->adv = adv;
	};

	template < class S >
	Route < S > :: Route(	const Route < S > & other )
	{
		t   = other.t;
		adv = other.adv;
	};

	template < class S >
	Route < S > & Route < S >::operator= ( Route < S > other )
	{
		swap(  * this, other );
		return * this;
	};

	template < class S >
	RoutingState < S > :: RoutingState( int V )
	{	
		routeQueue = AugmentedPriorityQueue < 
									std::pair < int, int >, 
									double, 
									Route < S > > ( V * V );
	};

	template < class S >
	RoutingState <  S > :: RoutingState( const RoutingState < S > & other )
	{
		dom 	  	= other.dom;
		label 		= other.label;
		routeQueue  = other.routeQueue;
	}

	template < class S >
	RoutingState <  S > & RoutingState < S >::operator=( RoutingState < S > other )
	{
		swap(  * this, other );
		return * this;
	};

	template struct Route  			< std::pair  < int, int > >;
	template struct Route  			< std::tuple < int, int, int > >;
	template struct RoutingState 	< std::pair  < int, int > >;
	template struct RoutingState 	< std::tuple < int, int, int > >;
}