#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon May 20 09:54:00 2024

Last edit: Mon Jun 24 10:55:00 2024

@author: Blanca Berbel 
"""

#---------------------------------------------------------------#
#							    								#
# TIME INTERVALS + ISI							  				#
#							    								#
#---------------------------------------------------------------#


import os 
import spikes_utils as s_u


# Directorio de trabajo: el anterior

separador =  os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])

# Parámetros sin ritmo bifásico

file_solapan = open(dir + "/overlapping", 'w')
file_no_dispara = open(dir + "/no_firing", 'w')
file_conectadas = open(dir + "/connected", 'w') #nuevo

# Neurona acoplada eléctricamente 

gap_with = "Z1"

# For all the parameters studied in a simulation 
# Parameters: here we are only vari P1

P_ini = 0.0000
P_end = 0.0395

step = 0.0005

P1 = P_ini
P2 = 0.0000

while (P1 < P_end):

	#print(P1)

	#Archivos que contienen los spikes
	nX = dir + "/S_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2) 
	nY = dir + "/S_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)
	nZ = dir + "/S_" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2) 			

	#Time vector for neurons:
	timeX_10, timeX_01, nspikes_X = s_u.get_times_spikes(nX)

	timeY_10, timeY_01, nspikes_Y = s_u.get_times_spikes(nY)

	timeZ_10, timeZ_01, nspikes_Z = s_u.get_times_spikes(nZ)



	#Correct order (1st X 2nd Y)
	timeY_10, timeY_01 = s_u.get_first_neuron(timeX_10, timeY_10, timeY_01)
	#timeZ_10, timeZ_01 = s_u.get_first_neuron(timeX_10, timeZ_10, timeZ_01) 

	#Time intervals definition: 

	periodX = s_u.get_period(timeX_10, dir + "/TIME_INTERVALS/Period_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
	periodY = s_u.get_period(timeY_10, dir + "/TIME_INTERVALS/Period_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
	periodZ = s_u.get_period(timeZ_10, dir + "/TIME_INTERVALS/Period_" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 

	burstX = s_u.get_burst(timeX_10, timeX_01, dir + "/TIME_INTERVALS/Burst_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
	burstY = s_u.get_burst(timeY_10, timeY_01, dir + "/TIME_INTERVALS/Burst_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
	burstZ = s_u.get_burst(timeZ_10, timeZ_01, dir + "/TIME_INTERVALS/Burst_" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))

	HypX = s_u.get_Hyp(timeX_10, timeX_01, dir + "/TIME_INTERVALS/Hyp_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
	HypY = s_u.get_Hyp(timeY_10, timeY_01, dir + "/TIME_INTERVALS/Hyp_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
	HypZ = s_u.get_Hyp(timeZ_10, timeZ_01, dir + "/TIME_INTERVALS/Hyp_" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))

	intervalXY = s_u.get_interval_LPPD(timeX_10, timeY_10, dir + "/TIME_INTERVALS/Interval_XY_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
	intervalXZ = s_u.get_interval_LPPD(timeX_10, timeZ_10, dir + "/TIME_INTERVALS/Interval_X" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))

	intervalYX = s_u.get_interval_PDLP(timeX_10, timeY_10, dir + "/TIME_INTERVALS/Interval_YX_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
	intervalYZ = s_u.get_interval_PDLP(timeZ_10, timeY_10, dir + "/TIME_INTERVALS/Interval_Y" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))

	intervalZX = s_u.get_interval_PDLP(timeZ_10, timeX_10, dir + "/TIME_INTERVALS/Interval_" + gap_with + "X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
	intervalZY = s_u.get_interval_LPPD(timeZ_10, timeY_10, dir + "/TIME_INTERVALS/Interval_" + gap_with + "Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 

	delayXY = s_u.get_delay_LPPD(timeX_01, timeY_10, dir + "/TIME_INTERVALS/Delay_XY_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
	delayXZ = s_u.get_delay_LPPD(timeX_01, timeZ_10, dir + "/TIME_INTERVALS/Delay_X" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))  
	
	delayYX = s_u.get_delay_PDLP(timeX_10, timeY_01, dir + "/TIME_INTERVALS/Delay_YX_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))    
	delayYZ = s_u.get_delay_PDLP(timeZ_10, timeY_01, dir + "/TIME_INTERVALS/Delay_Y" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))    

	delayZX = s_u.get_delay_LPPD(timeZ_01, timeZ_01, dir + "/TIME_INTERVALS/Delay_" + gap_with + "X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))    
	delayZY = s_u.get_delay_LPPD(timeZ_01, timeY_10, dir + "/TIME_INTERVALS/Delay_" + gap_with + "Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2))    

	isiX = s_u.get_ISI_2(nspikes_X, burstX, dir + "/TIME_INTERVALS/AA2_ISI_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
	isiY = s_u.get_ISI_2(nspikes_Y, burstY, dir + "/TIME_INTERVALS/AA2_ISI_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
	isiZ = s_u.get_ISI_2(nspikes_Z, burstZ, dir + "/TIME_INTERVALS/AA2_ISI_" + gap_with + "_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 
	
	P1 = round(P1 + step, 4) 





file_solapan.close()
file_no_dispara.close()
file_conectadas.close()



