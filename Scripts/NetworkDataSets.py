## File : Scripts/NetworkDataSets.py

## Description : A script transforming Rocketfuel topologies into the
##               network data sets that serve as input to the simulator.

# Public Library
import networkx 			as nx
import matplotlib.pyplot 	as plt
import random
import re

print ( "\n-------- Transforming Rocketfuel Topologies into Test Networks --------" )

for ASN in ['1221', '1239', '1755', '3257', '3967', '6461']:


    fileNameWeights   = 'RocketfuelTopologies/AS%s/weights.intra'   % ASN
    fileNameLatencies = 'RocketfuelTopologies/AS%s/latencies.intra' % ASN

    graph = nx.Graph()

    with open( fileNameWeights ) as fileWeight, open( fileNameLatencies ) as fileLatencies: 
      
        pattern = '[0-9]'

        for lineWeight, lineLatencies in zip(fileWeight, fileLatencies):
     
            argsWeight    = lineWeight.rstrip().split(" ")
            argsLatencies = lineLatencies.rstrip().split(" ")

            node1  = argsWeight[0]
            node2  = argsWeight[1]

            width  = int( 100 * (1 / float( argsWeight[2] ) ) )  
            length = int( float( argsLatencies[2] ) )          
 
            graph.add_edge( node1, node2, Width = width, Length = length )

    graph = max( nx.biconnected_component_subgraphs( graph ), key = len )
    graph = nx.convert_node_labels_to_integers( graph )
    graph = graph.to_directed()

    print ( "\n> Test Network pertaining to AS %s" % ASN )
    print ( "\tNumber of Nodes: %d" % graph.number_of_nodes() )
    print ( "\tNumber of Links: %d" % graph.number_of_edges() )
    print ( "\tNumber of Distinct Widths: %d"  % len( set([ width for _, _, width in graph.edges.data('Width') ]) ) )

    for Attribute in [ ['Hops' , 'Length'], ['Width', 'Hops'], ['Width', 'Length'], ['Width', 'Hops', 'Length'] ]:

        fileNameTestNetwork = "NetworkDataSets/Rocketfuel/AS%s/%s.txt" % ( ASN, ''.join(Attribute) )
        fileTestNetwork = open ( fileNameTestNetwork, "w+" )

        print ( "\n\t... Saving to File '%s' " % fileNameTestNetwork )

        string2file = '%4s\n' % str( graph.number_of_nodes() )
        fileTestNetwork.write( string2file )

        for u, v, data in graph.edges( data = True ):
        	
            string2file  = '%4s %4s' % ( str(u), str(v) )

            if( 'Width'  in Attribute ):
                string2file += ' %4s' % str( data['Width'] )

            if( 'Hops'   in Attribute ):
                string2file += ' %4s' % '1'

            if( 'Length' in Attribute ):
                string2file += ' %4s' % str( data['Length'] )

            string2file += '\n'

            fileTestNetwork.write( string2file )

        fileTestNetwork.close()

print ( "\n---------------------------------------------------------- " )
