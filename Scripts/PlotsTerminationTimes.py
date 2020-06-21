# File : Scripts/PlotsTerminationTimes.py

import matplotlib.pyplot   as plt
import numpy as np
import sys


# labelsWidthLength 	= 	{ 	0 : r'\hspace{-20pt} \textbf{Widest-shortest \newline \hspace{-2pt} order} \hspace{1pt}'	,
# 							1 : r'\hspace{-20pt} \textbf{Shortest-widest \newline \hspace{-2pt} order} \hspace{1pt}'	,
# 							2 : r'\hspace{-20pt} \textbf{Product order on \newline \hspace{-2pt} width-lengths} \hspace{1pt}'	
# 						}

# colorAttributes 	= 	{ 	0 : r'lime'			,
# 							1 : r'darkviolet'	,
# 							2 : r'green'		
# 						}

# labelsAttributes 	= 	{ 	0 : r'\textbf{Hops-lengths}		\hspace{8pt}' 						,
# 							1 : r'\textbf{Width-hops}		\hspace{16pt}' 							,
# 							2 : r'\textbf{Width-lengths} 	\hspace{1pt}'							,
# 							3 : r'\hspace{-20pt} \textbf{Width-hops- \newline lengths} \hspace{43pt}'
# 						}

# colorAttributes 	= 	{ 	0 	: r'black'  ,
# 							1 	: r'red'	,
# 							2 	: r'green'	,
# 							3	: r'blue' 	
# 						}

if(  ):

	... = [	"WidthLength/WidestShortestPaths" 					, 
							"WidthLength/ShortestWidestPaths" 					,
							"WidthLength/DominantWidthLengthsPaths" 			]
else:
	... = [	"HopsLength/DominantHopCountLengthsPaths" 			, 
			"WidthHops/DominantWidthHopCountsPaths" 			, 
			"WidthLength/DominantWidthLengthsPaths"  			, 
			"WidthHopsLength/DominantWidthHopCountLengthsPaths" ]

for i, OptimalityCriterion in enumerate( OptimalityCriteria ):

	for Event in [ "DestinationAnnouncement", "LinkFailures" ]:

		if(  ) 




		with open ( "Results/%s/%s%s.csv" % ( OptimalityCriterion, Event, Metric ) ) as file:

			terminationTimes = np.genfromtxt( file, delimiter=',', dtype = np.float32 )

			terminationTimes = np.delete( terminationTimes, 0, 0 )
			terminationTimes = np.delete( terminationTimes, 0, 1 )

			terminationTimes = terminationTimes.flatten()
			terminationTimes.sort()

			CCDF = np.zeros( shape = terminationTimes.shape , 
							 dtype = np.float32 			)
			for	j in range( terminationTimes.size ):
				CCDF[j] = 1.0 - float(j) / CCDF.size

			x = terminationTimes
			y = CCDF

			plt.plot( x, y, drawstyle='steps-post', linewidth = 4, color = color[ i ] )

			labels.append( label[ i ] + r'$\textbf{(%.1f ms)}$' % np.mean(x) )

	plt.rc('text', usetex=True)
	plt.legend( labels, 							handlelength = 0.85,			fontsize = 13 )

	# ## '$\mathbf{Termination \, time \, (ms) }$'

	# plt.xlabel(r'$\mathbf{Termination \, time \, (ms) }$', 			labelpad = 10, 	fontsize = 16 )

	ax = plt.gca()
	ax.xaxis.set_label_coords(0.5, -0.1)
	plt.xticks(																		fontsize = 16 )
	plt.xlim( 0, 18 )
	plt.ylabel(r'$\mathbf{CCDF}$', 						  			labelpad = 10, 	fontsize = 16 )
	plt.yticks(									 									fontsize = 16 )
	plt.ylim( 0, 1  )
	plt.tight_layout()
	plt.grid( True, which = "both" )
	plt.savefig( "Plots/%s.pdf")
	plt.close()

# plt.savefig("Plots/TimeToPropagateUnreachability.pdf")
# plt.savefig("Plots/TerminationTimes_LinkFailure_WidthLengthsCriteria.pdf")
# plt.savefig("Plots/TerminationTimes_DestinationAnnouncement_WidthLengthsCriteria.pdf")
# plt.savefig("Plots/TerminationTimes_LinkFailure.pdf")
# plt.close()
