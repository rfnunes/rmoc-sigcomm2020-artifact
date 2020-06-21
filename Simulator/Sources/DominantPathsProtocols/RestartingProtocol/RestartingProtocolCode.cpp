// file : Algorithms/DominantPathsVectoringProtocols/RestartingProtocol/RestartingProtocolCode.cpp

// My Libraries
#include "DominantPathsProtocols/RestartingProtocol/RestartingProtocolCode.h"

namespace Algorithms
{
	std::uniform_real_distribution < double > dist(0.01, 1);

	// Function    : Destination Announcement

	// Description : Initiates a computation instance.

	template < 	typename S, typename Ord, typename Ext	>
	void DestinationAnnouncement( 
		const Graph 	   < S > 	& graph 		,
			  RoutingState < S >	& routingState 	,
			  std::mt19937 		 	& gen			,
		const int 				 	& t   			)
	{
		// Insert 
		routingState.dom[t][t].insert( { { { Ord :: Neutral, 0 }, 1 	    } , 
										   { INT_MAX, 			  INT_MAX } } );

		// Advertises elected aroute
		Advertisement < S > outAdv;
		outAdv.insert( { { Ord :: Neutral, 0 }, 1 } );

		for( auto it  = graph.adjListIn[t].begin() 	; 
				  it != graph.adjListIn[t].end() 	; it ++ )
		{
			int 	  w = it->first;
			bool active = it->second.first;
		
			if( active )
			{
				std::pair < int, int > l  = { w, t };
				double at = dist( gen );
				routingState.routeQueue.push( { l, { at, { t, outAdv } } } );
			}
		}
	}

	template < 	typename S, typename Ord, typename Ext	>
	void IntermediateNodeDestinationAnnouncement(	
		const Graph 		< S > 	& graph 		,
			  RoutingState 	< S > 	& routingState 	,
			  std::mt19937  		& gen			,
		const double 				& ct 			,
		const int 					& u 			,
		const int 					& v 			,
		const int 					& t 			, 
		const Advertisement < S >	& inAdv 		)
	{
	
		Ord ord;
		Ext ext;

		if( u == t )
		{	
			return;	
		}

		S 	weight = graph.adjListOut[u].at(v).second;

		S   attr;
		int hopCount1;
		int nextLabel1;

		for( auto 	item  = inAdv.begin() 	; 
		  			item != inAdv.end() 	; item ++ )		
		{
			attr 	   = item->first.first;
			hopCount1  = item->first.second;
			nextLabel1 = item->second;
		}

		hopCount1 ++;
		S 	cand1 = ext( weight, attr );
			
		if( hopCount1 >= 15 or cand1 == Ext :: Null )
		{	
			return;	
		}

		bool isDominant = true;

		Advertisement < S > outAdv;

		for( auto 	item  = routingState.dom[u][t].begin() 	; 
		  			item != routingState.dom[u][t].end() 	; )
		{
			S 	cand2 	  	= item->first.first.first;
			int hopCount2 	= item->first.first.second;

			if( 	 ord( cand2, cand1 ) or ( cand2 == cand1 and hopCount2 <= hopCount1 ) )
			{
				isDominant = false;
				goto EndTest;
			}
			else if( ord( cand1, cand2 ) or ( cand1 == cand2 and hopCount1 <  hopCount2 ) )
			{
				item = routingState.dom[u][t].erase( item );
			}
			else
			{
				item ++;
			}
		}

		EndTest:
		if( isDominant == true )
		{
			int label1 = routingState.label[u][t] ++;

			routingState.dom[u][t].insert(   { { { cand1, hopCount1 }, label1     }, 
												 {  v, 				   nextLabel1 } } );

			outAdv.insert ( { { cand1, hopCount1 }, label1 } );
		}

		if( not outAdv.empty() )
		{	
			double qt;

			for( auto it  = graph.adjListIn[u].begin() 	; 
				  	  it != graph.adjListIn[u].end() 	; it ++ )
			{
				int 	  w = it->first;
				bool active = it->second.first;
			
				if( active )
				{
					std::pair < int, int > l = { w, u };
					if( routingState.routeQueue.count(l) == 1 )	
					{	
						qt = routingState.routeQueue.at(l).first; 	
					}
					else												
					{	
						qt = 0; 										
					}
					double at = std::max( qt, ct + dist(gen) );					
					routingState.routeQueue.push( { l, { at, { t, outAdv } } } );
				}
			}
		}
		return;
	}

	template < 	typename S, typename Ord, typename Ext	>
	void LinkFailure( 
			  Graph 		< S > 			  	& graph 		,
			  RoutingState 	< S > 			  	& routingState  ,
			  std::vector  	< std::mt19937 > 	& gens			,
	  	const int 								& u  			,
		const int 								& v  			)
	{
		graph.deactivate( u, v );

		for( int t = 0 ; t < graph.V ; t ++ )
		{
			if( u == t )
			{	
				continue;	
			}

			Advertisement < S > outAdv;

			for( auto 	item  = routingState.dom[u][t].begin() 	; 
		  				item != routingState.dom[u][t].end() 	; )
			{	
				int label   = item->first.second;

				int nextHop = item->second.first;

				if( nextHop == v )
				{
					item = routingState.dom[u][t].erase( item );

					outAdv.insert( { { Ext :: Null, 15 }, label } );
				}
				else
				{
					item ++;
				}
			}

			if( not outAdv.empty() )
			{
				double qt;

				for( auto it  = graph.adjListIn[u].begin() 	; 
					  	  it != graph.adjListIn[u].end() 	; it ++ )
				{
					int 	  w = it->first;
					bool active = it->second.first;
				
					if( active )
					{
						std::pair < int, int > l = { w, u };
						if( routingState.routeQueue.count(l) == 1 )	
						{	
							qt = routingState.routeQueue.at(l).first; 	
						}
						else												
						{	
							qt = 0; 										
						}
						double at = std::max( qt, dist(gens[t]) );					
						routingState.routeQueue.push( { l, { at, { t, outAdv } } } );
					}
				}
			}
		}
		return;
	}

	template < 	typename S, typename Ord, typename Ext	>
		void IntermediateNodeLinkFailure(	
			const Graph 		< S > 	& graph 		,
				  RoutingState 	< S > 	& routingState 	,
				  std::mt19937  		& gen			,
			const double 				& ct 			,
			const int 					& u 			,
			const int 					& v 			,
			const int 					& t 			, 
			const Advertisement < S >	& inAdv 		)
	{
		if( u == t )
		{	
			return;	
		}

		Advertisement < S > outAdv; 

		for( auto 	item  = routingState.dom[u][t].begin() 	; 
		  			item != routingState.dom[u][t].end() 	; )
		{
			int label     = item->first.second;

			int nextHop   = item->second.first;
			int nextLabel = item->second.second;

			if( nextHop == v and inAdv.count( { { Ext :: Null, 15 }, nextLabel } ) > 0 )
			{
				item = routingState.dom[u][t].erase( item );

				outAdv.insert( { { Ext :: Null, 15 }, label } );
			} 
			else
			{
				item ++;
			}
		}

		if( not outAdv.empty() )
		{
			double qt;

			for( auto it  = graph.adjListIn[u].begin() 	; 
				  	  it != graph.adjListIn[u].end() 	; it ++ )
			{
				int 	  w = it->first;
				bool active = it->second.first;
			
				if( active )
				{
					std::pair < int, int > l = { w, u };
					if( routingState.routeQueue.count(l) == 1 )	
					{	
						qt = routingState.routeQueue.at(l).first; 	
					}
					else												
					{	
						qt = 0; 										
					}
					double at = std::max( qt, ct + dist( gen ) );					
					routingState.routeQueue.push( { l, { at, { t, outAdv } } } );
				}
			}
		}
		return;
	}
}

#include "DominantPathsProtocols/RestartingProtocol/ProtocolCodeInstances.h"

