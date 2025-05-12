#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 21 09:27:00 2024

Last edit: Mon Oct 18 11:17:00 2024  

@author: Blanca Berbel 
"""

#-----------------------------------------------------------#
#                                                           #
# Interval trend and variability                            #
#                                                           #
#-----------------------------------------------------------#

import os 
import matplotlib.pyplot as plt
import spikes_utils as s_u
import numpy as np


# Working directory
separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])

# Conducntance value
P_ini = 0.0015 #0.0015, 0.0065, 0.0200

P1 = P_ini
P2 = 0.0000

burstX = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Burst_X_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 

periodY = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Period_Y_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 

intervalXY = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Interval_XY_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 

intervalYX = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA_Interval_YX_gZ1X_" + '{:.4f}'.format(P1) + "_gZ2Y_" + '{:.4f}'.format(P2)) 

media_burstX = np.mean(burstX)

media_periodY= np.mean(periodY)

media_intervalXY = np.mean(intervalXY)

media_intervalYX = np.mean(intervalYX)


# Figure
plt.rcParams['figure.dpi'] = 300
plt.rcParams["figure.figsize"] = (20, 10) 

# subfigures
fig, (ax1, ax2) = plt.subplots(2, 1)

 
minimo = min(len(periodY), len(burstX), len(intervalXY), len(intervalYX))
cycles = range(1, minimo + 1)

# Subfigure 1
ax1.plot(cycles, intervalXY[:minimo], marker='o', linestyle='-', color='indigo', label=r'$X{-}Y_{interval}$')
ax1.plot(cycles, burstX[:minimo], marker='o', linestyle='-', color='blueviolet', label=r'$X_{burst}$')

ax1.axhline(y=media_intervalXY, color='black', linestyle='--', label=r'$\overline{X{-}Y_{interval}}\,=\,$' + f'{media_intervalXY:.2f}')
ax1.axhline(y=media_burstX, color='black', linestyle=':', label=r'$\overline{X_{burst}}\,=\,$' + f'{media_burstX:.2f}') #'--'

ax1.set_ylabel(r'$time\,(s)$', fontsize = 18)

ax1.yaxis.set_tick_params(labelsize=14)
ax1.set_xlim(200, 350) 
ax1.set_xticklabels([])
ax1.legend(fontsize=18, loc='upper right') #
ax1.grid(True)


# Subfigure 2
ax2.plot(cycles, periodY[:minimo], marker='o', linestyle='-', color='orange', label=r'$Y_{period}$')
ax2.plot(cycles, intervalYX[:minimo], marker='o', linestyle='-', color='salmon', label=r'$Y{-}X_{interval}$')

ax2.axhline(y=media_periodY, color='black', linestyle='--', label=r'$\overline{Y_{period}}\,=\,$' + f'{media_periodY:.2f}')
ax2.axhline(y=media_intervalYX, color='black', linestyle=':', label=r'$\overline{Y{-}X_{interval}}\,=\,$' + f'{media_intervalYX:.2f}') #'--'

ax2.set_ylabel(r'$time\,(s)$', fontsize = 18)
ax2.set_xlabel(r'$\#\,cycles$', fontsize = 18)
ax2.set_xlim(200, 350) 
ax2.xaxis.set_tick_params(labelsize=14)
ax2.yaxis.set_tick_params(labelsize=14)
ax2.legend(fontsize=18, loc='upper right') #12
ax2.grid(True)

plt.tight_layout()
plt.savefig(dir + "/TENDENCIAS/time_interval_tendencies.png")
plt.show()
