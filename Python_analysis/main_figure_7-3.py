#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Mar 15 17:28:12 2022

Last edit: Tue Dec 17 13:50:06 2024

@author: Blanca Berbel
"""

import os
import rhythm_utils as r_u
from itertools import combinations

t1 = 4000
t2 = 4100

P1 = 0.0120
P2 = P1

# Working directory

separador = os.path.sep
dir_actual = os.path.dirname(os.path.abspath(__file__))
dir = separador.join(dir_actual.split(separador)[:-1])

while P1 < 0.0121:
    t = []
    V_LP = []
    V_PY = []
    V_AB = []
    V_PD1 = []
    V_PD2 = []

    file = open(dir + "/V_g_" + "{:.4f}".format(P1) + "_g_" + "{:.4f}".format(P2), "r")

    contenido = file.readlines()

    for i in range(0, len(contenido)):
        dato1 = contenido[i].find("\t")
        dato2 = contenido[i].find("\t", dato1 + 1)
        dato3 = contenido[i].find("\t", dato2 + 1)
        dato4 = contenido[i].find("\t", dato3 + 1)
        dato5 = contenido[i].find("\t", dato4 + 1)
        dato6 = contenido[i].find("\n", dato5 + 1)

        valor1 = float(contenido[i][0:dato1])
        valor2 = float(contenido[i][dato1 + 1 : dato2])
        valor3 = float(contenido[i][dato2 + 1 : dato3])
        valor4 = float(contenido[i][dato3 + 1 : dato4])
        valor5 = float(contenido[i][dato4 + 1 : dato5])
        valor6 = float(contenido[i][dato5 + 1 : dato6])

        if t1 < valor1 < t2:
            t.append(valor1)
            V_LP.append(valor2)
            V_PY.append(valor3)
            V_AB.append(valor4)
            V_PD1.append(valor5)
            V_PD2.append(valor6)

    name_fig = (
        dir
        + "/RHYTHM/TR_ABPD2_g_"
        + "{:.4f}".format(P1)
        + "_g_"
        + "{:.4f}".format(P2)
        + "_"
        + "{:.2f}".format(t[0])
        + ".png"
    )

    if not os.path.exists(name_fig):
        r_u.get_maps_BR_3N(t, V_LP, V_PY, V_AB, V_PD1, V_PD2, P1, P2, name_fig)

    file.close()

    P1 = round(P1 + 0.0005, 4)
    print(P1)
    P2 = P1
