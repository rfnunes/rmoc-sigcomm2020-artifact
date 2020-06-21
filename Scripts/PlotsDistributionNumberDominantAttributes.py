# file : StableState/NumberDominantAttributes.py

from itertools 			 import izip
import matplotlib.pyplot as plt
import numpy 			 as np
import re
import sys

color = { 	0 	: r'black'  ,
			1 	: r'red'	,
			2 	: r'green'	,
			3	: r'blue' 	}

label = { 	0 : r'\textbf{Hops-lengths}		\hspace{8pt}' 						,
			1 : r'\textbf{Width-hops}		\hspace{16pt}' 						,
			2 : r'\textbf{Width-lengths} 	\hspace{1pt}'						,
			3 : r'\hspace{-20pt} \textbf{Width-hops- \newline lengths} \hspace{43pt}'}

x 		= []
y 		= []
labels  = []

for i, OptimalityCriterion in enumerate( [	"DominantHopCountLengthsPaths" 		, 
											"DominantWidthHopCountsPaths" 		, 
											"DominantWidthLengthsPaths"  		, 
											"DominantWidthHopCountLengthsPaths" ] ):

# for ASNumber in ['1221', '1239', '1755', '3257', '3967', '6461']:

	NumDom = []

	pattern = re.compile(r"<([\w ]+)>")

	# with open( "Results/Rocketfuel/AS%s/DominantWidthLengthsPaths/StableState.txt" % ASNumber ) as file:

	with open( "Results/Rocketfuel/AS1239/%s/StableState.txt" % OptimalityCriterion ) as file:
		for line in file:
			temp = [ tuple( s.split(' ') ) for s in pattern.findall( line ) ]
			NumDom.append( len(temp) )

	AvgNumDom  = sum( NumDom ) / float( len( NumDom ) )
	NumDomBins = np.bincount( NumDom )

	Ccdf = 1 - np.divide( np.cumsum( NumDomBins ), np.sum( NumDomBins ), dtype = np.float32 )

	x.append( np.arange( 0.5, Ccdf.size-1 ) )
	y.append( Ccdf[1:] )

	labels.append( label[i] + r'\textbf{(%.1f)}' % AvgNumDom )

plt.bar( x[0] - 0.375 , y[0], width = 0.2, color = color[0] )
plt.bar( x[1] - 0.125 , y[1], width = 0.2, color = color[1] )
plt.bar( x[2] + 0.125 , y[2], width = 0.2, color = color[2] )
plt.bar( x[3] + 0.375 , y[3], width = 0.2, color = color[3] )

plt.rc( 'text', usetex = True )
plt.legend( labels, fontsize = 13, handlelength = 0.85)

plt.xlabel(r'$\mathbf{Number \, of \, dominant \, attributes}$', 	fontsize  = 16, labelpad = 10)
plt.xticks(	np.arange( 0.5, 7 ), np.arange( 1, 8 ), 				fontsize  = 16 )
plt.xlim( 0, 7 )

ax = plt.gca()
ax.xaxis.set_label_coords(0.5, -0.1)

plt.ylabel(r'$\mathbf{CCDF}$', 	fontsize  = 16, labelpad = 10 	)
plt.yticks(						fontsize  = 16 					)
plt.ylim( 0, 1 )

plt.tight_layout()
plt.grid( True, which = "both" )
plt.savefig("Plots/NumberDominantAttributes.pdf")
plt.show()
plt.close()