#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 10 14:15:46 2022

Last edit: Thu Jan 11 13:19:00 2024

@author: Blanca Berbel
"""


def get_times(name):
    archive = open(name, "r")

    time = 0.0

    time_10 = []
    time_01 = []

    n_line = []

    for line in archive.readlines():
        n_line = line.split()
        if len(n_line) == 1:
            if (
                float(time) > 100
            ):  # Elimination of the first 100 seconds to avoid transient effects
                time_01.append(float(time))
        elif len(n_line) > 0:
            if n_line[2] == "1":
                if (
                    float(n_line[0]) > 100
                ):  # Elimination of the first 100 seconds to avoid transient effects
                    time_10.append(float(n_line[0]))
            else:
                time = n_line[0]

    if len(time_10) > 0:
        if len(time_01) > 0:
            if (
                time_01[0] < time_10[0]
            ):  # Forcing the first record to be the beginning of the burst
                time_01.pop(0)

    archive.close()

    return time_10, time_01


def get_times_spikes(name):
    archive = open(name, "r")

    time = 0.0

    time_10 = []
    time_01 = []

    n_line = []

    cont = 0
    v_cont = []

    for line in archive.readlines():
        n_line = line.split()
        if len(n_line) == 1:
            if (
                float(time) > 100
            ):  # Elimination of the first 100 seconds to avoid transient effects
                time_01.append(float(time))
                v_cont.append(int(cont))
        elif len(n_line) > 0:
            if n_line[2] == "1":
                if (
                    float(n_line[0]) > 100
                ):  # Elimination of the first 100 seconds to avoid transient effects
                    time_10.append(float(n_line[0]))
                    cont = 1
            else:
                time = n_line[0]
                cont += 1

    if len(time_10) > 0:
        if len(time_01) > 0:
            if (
                time_01[0] < time_10[0]
            ):  # Forcing the first record to be the beginning of the burst
                time_01.pop(0)

    archive.close()

    return time_10, time_01, v_cont


def get_times_restofspikes(name):
    archive = open(name, "r")

    time = 0.0

    time_10 = []
    time_bet = []
    times = []
    time_01 = []

    n_line = []

    cont = 0
    v_cont = []

    for line in archive.readlines():
        n_line = line.split()
        if len(n_line) == 1:
            if (
                float(time) > 100
            ):  # Elimination of the first 100 seconds to avoid transient effects
                time_01.append(float(time))
                times.pop(-1)
                time_bet.append(times)
                times = []
                v_cont.append(int(cont))
        elif len(n_line) > 0:
            if n_line[2] == "1":
                if (
                    float(n_line[0]) > 100
                ):  # Elimination of the first 100 seconds to avoid transient effects
                    time_10.append(float(n_line[0]))
                    cont = 1
            else:
                time = n_line[0]
                if float(n_line[0]) > 100:
                    times.append(float(time))
                cont += 1

    if len(time_10) > 0:
        if len(time_01) > 0:
            if (
                time_01[0] < time_10[0]
            ):  # Forcing the first record to be the beginning of the burst
                time_01.pop(0)

    archive.close()

    return time_10, time_01, time_bet, v_cont


def get_first_neuron(timeLP_10, timePD_10, timePD_01):
    if len(timeLP_10) > 0:
        if len(timePD_10) > 0:
            if len(timePD_01) > 0:
                while timePD_10[0] < timeLP_10[0]:
                    # print("PD era la primera")
                    timePD_10.pop(
                        0
                    )  # Forcing LP to be the first neuron of the sequence
                    timePD_01.pop(0)
    return timePD_10, timePD_01


def get_out_times(timeLP_10, timeLP_01, timePD_10, timePD_01):
    if len(timeLP_10) > 0:
        if len(timePD_10) > 0:
            if len(timePD_01) > 0:
                for i in range(
                    0,
                    min(len(timeLP_10), len(timeLP_01), len(timePD_10), len(timePD_01))
                    - 2,
                ):
                    if abs(timeLP_10[i + 1] - timePD_01[i]) > 0.5:
                        timeLP_10.pop(i + 1)  # línea nueva
                        timeLP_01.pop(i + 1)  # línea nueva
                        break
                    elif abs(timePD_10[i + 1] - timeLP_01[i]) > 0.5:
                        timePD_10.pop(i + 1)
                        timePD_01.pop(i + 1)
                        break
    return timeLP_10, timeLP_01, timePD_10, timePD_01


def ordenar_vectores_full_CPG(
    timeAB_10,
    timeAB_01,
    timePD1_10,
    timePD1_01,
    timePD2_10,
    timePD2_01,
    timeLP_10,
    timeLP_01,
    timePY_10,
    timePY_01,
):
    while (
        timeAB_10
        and timeAB_01
        and timePD1_10
        and timePD1_01
        and timePD2_10
        and timePD2_01
        and timeLP_10
        and timeLP_01
        and timePY_10
        and timePY_01
    ):
        if timeAB_10[0] >= timeLP_10[0]:
            timeLP_10.pop(0)
            timeLP_01.pop(0)
        elif timeLP_10[0] >= timePY_10[0]:
            timePY_10.pop(0)
            timePY_01.pop(0)
        else:
            break

    if (
        not timeAB_10
        or not timeAB_01
        or not timePD1_10
        or not timePD1_01
        or not timePD2_10
        or not timePD2_01
        or not timeLP_10
        or not timeLP_01
        or not timePY_10
        or not timePY_01
    ):
        return [], [], [], [], [], [], [], [], [], []

    return (
        timeAB_10,
        timeAB_01,
        timePD1_10,
        timePD1_01,
        timePD2_10,
        timePD2_01,
        timeLP_10,
        timeLP_01,
        timePY_10,
        timePY_01,
    )


def no_dispara(P1, P2, timeLP_10, timeLP_01, timePD1_10, timePD1_01, file_no_dispara):
    for i in range(
        0, min(len(timeLP_10), len(timeLP_01), len(timePD1_10), len(timePD1_01)) - 1
    ):
        if timeLP_10[i] > timePD1_10[i]:
            file_no_dispara.write(
                "{:.4f}".format(P1)
                + "\t"
                + "{:.4f}".format(P2)
                + "\t"
                + "{:.4f}".format(timeLP_10[i])
                + "\n"
            )
            timePD1_10.pop(i)
            timePD1_01.pop(i)
            break
        if timeLP_10[i + 1] < timePD1_10[i]:
            file_no_dispara.write(
                "{:.4f}".format(P1)
                + "\t"
                + "{:.4f}".format(P2)
                + "\t"
                + "{:.4f}".format(timePD1_10[i])
                + "\n"
            )
            timeLP_10.pop(i + 1)
            timeLP_01.pop(i + 1)
            break
    return


def solapan(P1, P2, timeLP_10, timeLP_01, timePD1_10, timePD1_01, file_solapan):
    for i in range(
        0, min(len(timeLP_10), len(timeLP_01), len(timePD1_10), len(timePD1_01)) - 2
    ):
        if (timeLP_10[i] or timeLP_01[i]) > timePD1_10[i]:
            file_solapan.write(
                "{:.4f}".format(P1)
                + "\t"
                + "{:.4f}".format(P2)
                + "\t"
                + "{:.4f}".format(timeLP_01[i])
                + "\t"
                + "{:.4f}".format(timePD1_10[i])
                + "\n"
            )
            timePD1_10.pop(i)
            timePD1_01.pop(i)
    return


def neurons_connec(P1, P2, timeLP_10, timePD_10, file_conect):
    connect = False

    for i in range(0, min(len(timeLP_10), len(timePD_10))):
        if -0.3 < (timeLP_10[i] - timePD_10[i]) < 0.3:
            connect = True

    if connect == True:
        file_conect.write("{:.4f}".format(P1) + "\t" + "{:.4f}".format(P2) + "\n")

    return


def get_period(time_10, name_new):
    archive_new = open(name_new, "w")

    period = []

    for i in range(0, len(time_10) - 1):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(time_10[i + 1]) + "\t")
        archive_new.write("{:.4f}".format(time_10[i]) + "\t")
        archive_new.write("{:.4f}".format(time_10[i + 1] - time_10[i]) + "\n")
        period.append(round(time_10[i + 1] - time_10[i], 4))

    archive_new.close()

    return period


def get_burst(time_10, time_01, name_new):
    archive_new = open(name_new, "w")

    burst = []

    minimo = min(len(time_10), len(time_01))

    for i in range(0, minimo):  # antes había un 1
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(time_01[i]) + "\t")
        archive_new.write("{:.4f}".format(time_10[i]) + "\t")
        archive_new.write("{:.4f}".format(time_01[i] - time_10[i]) + "\n")
        burst.append(round(time_01[i] - time_10[i], 4))

    archive_new.close()

    return burst


def get_Hyp(time_10, time_01, name_new):
    archive_new = open(name_new, "w")

    Hyp = []

    minimo = min(len(time_10), len(time_01))

    for i in range(0, minimo - 1):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(time_10[i + 1]) + "\t")
        archive_new.write("{:.4f}".format(time_01[i]) + "\t")
        archive_new.write("{:.4f}".format(time_10[i + 1] - time_01[i]) + "\n")
        Hyp.append(round(time_10[i + 1] - time_01[i], 4))

    archive_new.close()

    return Hyp


def get_interval_LPPD(timeLP_10, timePD_10, name_new):
    archive_new = open(name_new, "w")

    intervalLPPD = []

    minimo = min(len(timeLP_10), len(timePD_10))

    for i in range(0, minimo):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(timePD_10[i]) + "\t")
        archive_new.write("{:.4f}".format(timeLP_10[i]) + "\t")
        archive_new.write("{:.4f}".format(timePD_10[i] - timeLP_10[i]) + "\n")
        intervalLPPD.append(round(timePD_10[i] - timeLP_10[i], 4))

    archive_new.close()

    return intervalLPPD


def get_interval_PDLP(timeLP_10, timePD_10, name_new):
    archive_new = open(name_new, "w")

    intervalPDLP = []

    minimo = min(len(timeLP_10), len(timePD_10))

    for i in range(0, minimo - 1):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(timeLP_10[i + 1]) + "\t")
        archive_new.write("{:.4f}".format(timePD_10[i]) + "\t")
        archive_new.write("{:.4f}".format(timeLP_10[i + 1] - timePD_10[i]) + "\n")
        intervalPDLP.append(round(timeLP_10[i + 1] - timePD_10[i], 4))

    archive_new.close()

    return intervalPDLP


def get_delay_LPPD(timeLP_01, timePD_10, name_new):
    archive_new = open(name_new, "w")

    delayLPPD = []

    minimo = min(len(timeLP_01), len(timePD_10))

    for i in range(0, minimo):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(timePD_10[i]) + "\t")
        archive_new.write("{:.4f}".format(timeLP_01[i]) + "\t")
        archive_new.write("{:.4f}".format(timePD_10[i] - timeLP_01[i]) + "\n")
        delayLPPD.append(round(timePD_10[i] - timeLP_01[i], 4))

    archive_new.close()

    return delayLPPD


def get_delay_PDLP(timeLP_10, timePD_01, name_new):
    archive_new = open(name_new, "w")

    delayPDLP = []

    minimo = min(len(timeLP_10), len(timePD_01))

    for i in range(0, minimo - 1):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(timeLP_10[i + 1]) + "\t")
        archive_new.write("{:.4f}".format(timePD_01[i]) + "\t")
        archive_new.write("{:.4f}".format(timeLP_10[i + 1] - timePD_01[i]) + "\n")
        delayPDLP.append(round(timeLP_10[i + 1] - timePD_01[i], 4))

    archive_new.close()

    return delayPDLP


def get_depo(timeA_10, timeB_10, name_new):
    archive_new = open(name_new, "w")

    depo = []

    minimo = min(len(timeA_10), len(timeB_10))

    for i in range(0, minimo):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(timeA_10[i]) + "\t")
        archive_new.write("{:.4f}".format(timeB_10[i]) + "\t")
        archive_new.write("{:.4f}".format(timeA_10[i] - timeB_10[i]) + "\t")
        archive_new.write("\n")

        depo.append(round(timeA_10[i] - timeB_10[i], 4))

    archive_new.close()

    return depo


def get_hype(timeA_01, timeB_01, name_new):
    archive_new = open(name_new, "w")

    hype = []

    minimo = min(len(timeA_01), len(timeB_01))

    for i in range(0, minimo):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{:.4f}".format(timeA_01[i]) + "\t")
        archive_new.write("{:.4f}".format(timeB_01[i]) + "\t")
        archive_new.write("{:.4f}".format(timeA_01[i] - timeB_01[i]) + "\t")
        archive_new.write("\n")

        hype.append(round(timeA_01[i] - timeB_01[i], 4))

    archive_new.close()

    return hype


def get_time_interval(archivo_tiempo):
    archivo = open(archivo_tiempo, "r")
    contenido = archivo.readlines()
    lista_intervalo = []
    for i in range(1, len(contenido)):
        datos = contenido[i].split("\t")
        lista_intervalo.append(float(datos[3]))
    archivo.close()

    return lista_intervalo


def get_time_de(archivo_tiempo):
    archivo = open(archivo_tiempo, "r")
    contenido = archivo.readlines()
    lista_intervalo = []
    for i in range(1, len(contenido)):
        datos = contenido[i].split("\t")
        lista_intervalo.append(float(datos[2]))
    archivo.close()

    return lista_intervalo


def get_nspikes(archivo_ISI):
    archivo = open(archivo_ISI, "r")
    contenido = archivo.readlines()
    lista_nspikes = []
    for i in range(1, len(contenido)):
        datos = contenido[i].split("\t")
        lista_nspikes.append(int(datos[1]))
    archivo.close()

    return lista_nspikes


def get_ISI(nspikes, burst, name_new):
    archive_new = open(name_new, "w")

    ISI = []

    minimo = min(len(nspikes), len(burst))

    for i in range(0, minimo):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{}".format(nspikes[i]) + "\t")
        archive_new.write("{:.4f}".format(burst[i]) + "\t")
        archive_new.write("{:.4f}".format(float(burst[i] / nspikes[i])) + "\n")
        ISI.append(round(burst[i] / nspikes[i], 4))

    archive_new.close()

    return ISI


def get_ISI_2(nspikes, burst, name_new):
    archive_new = open(name_new, "w")

    ISI = []

    minimo = min(len(nspikes), len(burst))

    for i in range(0, minimo):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{}".format(nspikes[i]) + "\t")
        archive_new.write("{:.4f}".format(burst[i]) + "\t")
        if nspikes[i] > 1:
            archive_new.write(
                "{:.4f}".format(float(burst[i] / (nspikes[i] - 1))) + "\n"
            )
            ISI.append(round(burst[i] / (nspikes[i] - 1), 4))
        else:
            archive_new.write("{:.4f}".format(0) + "\n")
            ISI.append(0)

    archive_new.close()

    return ISI


def get_ISI_3(nspikes, burst, name_new):
    archive_new = open(name_new, "w")

    ISI = []

    minimo = min(len(nspikes), len(burst))

    for i in range(0, minimo):
        archive_new.write("{}".format(i) + "\t")
        archive_new.write("{}".format(nspikes[i]) + "\t")
        archive_new.write("{:.4f}".format(burst[i]) + "\t")
        archive_new.write("{:.4f}".format(float((nspikes[i] - 1) / burst[i])) + "\n")
        ISI.append(round((nspikes[i] - 1) / burst[i], 4))

    archive_new.close()

    return ISI
