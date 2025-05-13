#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 21 09:27:00 2024

Last edit: Tue Nov 12 08:53:00 2024  

@author: Blanca Berbel 
"""

#---------------------------------------------------------#
#                                                         #
# ISI trend as a measure of excitability                  #
#                                                         #
#---------------------------------------------------------#

import os 
import matplotlib.pyplot as plt
import spikes_utils as s_u
import numpy as np

# Directorio donde trabajar
separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])

# Parámetros de conductancias
P_poor = 0.0015
P_moderate = 0.0065
P_strong = 0.0200 

P2 = 0.0000

isiX_poor = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_X_gZ1X_" + '{:.4f}'.format(P_poor) + "_gZ2Y_" + '{:.4f}'.format(P2))
isiX_moderate = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_X_gZ1X_" + '{:.4f}'.format(P_moderate) + "_gZ2Y_" + '{:.4f}'.format(P2))
isiX_strong = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_X_gZ1X_" + '{:.4f}'.format(P_strong) + "_gZ2Y_" + '{:.4f}'.format(P2))

isiY_poor = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_Y_gZ1X_" + '{:.4f}'.format(P_poor) + "_gZ2Y_" + '{:.4f}'.format(P2))
isiY_moderate = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_Y_gZ1X_" + '{:.4f}'.format(P_moderate) + "_gZ2Y_" + '{:.4f}'.format(P2))
isiY_strong = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_Y_gZ1X_" + '{:.4f}'.format(P_strong) + "_gZ2Y_" + '{:.4f}'.format(P2))

isiZ_poor = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_Z1_gZ1X_" + '{:.4f}'.format(P_poor) + "_gZ2Y_" + '{:.4f}'.format(P2))
isiZ_moderate = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_Z1_gZ1X_" + '{:.4f}'.format(P_moderate) + "_gZ2Y_" + '{:.4f}'.format(P2))
isiZ_strong = s_u.get_time_interval(dir + "/TIME_INTERVALS/AA2_ISI_Z1_gZ1X_" + '{:.4f}'.format(P_strong) + "_gZ2Y_" + '{:.4f}'.format(P2))


media_isiX_poor = np.mean(isiX_poor)
media_isiX_moderate = np.mean(isiX_moderate)
media_isiX_strong = np.mean(isiX_strong)

media_isiY_poor = np.mean(isiY_poor)
media_isiY_moderate = np.mean(isiY_moderate)
media_isiY_strong = np.mean(isiY_strong)

media_isiZ_poor = np.mean(isiZ_poor)
media_isiZ_moderate = np.mean(isiZ_moderate)
media_isiZ_strong = np.mean(isiZ_strong)


# Figura
plt.rcParams['figure.dpi'] = 300
plt.rcParams["figure.figsize"] = (20, 5) 

 


minimo = min(len(isiX_poor), len(isiX_moderate), len(isiX_strong), len(isiY_poor), len(isiY_moderate), len(isiY_strong), len(isiZ_poor), len(isiZ_moderate), len(isiZ_strong))
cycles = range(1, minimo + 1)

plt.plot(cycles, isiZ_poor[:minimo], marker='o', linestyle='-', color='springgreen', label=r'$Z_{\overline{ISI}}\,for\,g^{ec}=\,$' + f'{P_poor:.4f}' + r'$\, \mu S$')
plt.plot(cycles, isiZ_moderate[:minimo], marker='o', linestyle='-', color='mediumseagreen', label=r'$Z_{\overline{ISI}}\,for\,g^{ec}=\,$' + f'{P_moderate:.4f}' + r'$\, \mu S$')
plt.plot(cycles, isiZ_strong[:minimo], marker='o', linestyle='-', color='seagreen', label=r'$Z_{\overline{ISI}}\,for\,g^{ec}=\,$' + f'{P_strong:.4f}' + r'$\, \mu S$')


plt.ylabel(r'$time\,(s)$', fontsize = 18)
plt.tick_params(labelsize=14)
plt.ylim(-0.05, 1.6)
plt.xlim(200, 300)

plt.xlabel(r'$\#\,cycles$', fontsize = 18)
plt.legend(fontsize=14, loc='upper right') 
plt.grid(True)


plt.tight_layout()
plt.savefig(dir + "/TENDENCIAS/isi_XYZ.png")
plt.show()
