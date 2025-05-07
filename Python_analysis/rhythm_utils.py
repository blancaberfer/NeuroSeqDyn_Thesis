#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Mar 15 17:23:19 2022

Last edit: Mon Sep 30 11:55:06 2023

@author: Blanca Berbel
"""

import matplotlib.pyplot as plt


def get_maps_BR_2N(t, V_X, V_Y, P1, P2, work_path):
    plt.rcParams["figure.dpi"] = 300
    plt.rcParams["figure.figsize"] = (5, 2)

    plt.plot(t, V_X, color="firebrick", linewidth=0.6, linestyle="-", label="X")
    plt.plot(t, V_Y, color="royalblue", linewidth=0.6, linestyle="-", label="Y")

    plt.rc("xtick")
    plt.rc("ytick")
    plt.title("Biphasic Rhythm X-Y")
    plt.xlabel("Time (s)")
    plt.ylabel("V (mV)")
    plt.legend(loc="upper left", fontsize=7.5)
    plt.tight_layout()

    plt.savefig(
        work_path
        + "/RHYTHM/BR_gZ1X_"
        + "{:.4f}".format(P1)
        + "_gZ2Y_"
        + "{:.4f}".format(P2)
        + "_"
        + "{:.4f}".format(t[0])
        + ".png",
        dpi=300,
    )

    plt.close()

    return


def get_maps_BR_3N(t, V_LP, V_PY, V_AB, V_PD1, V_PD2, P1, P2, name_fig):
    plt.rcParams["figure.dpi"] = 300
    plt.rcParams["figure.figsize"] = (7.2, 2)

    plt.plot(t, V_LP, color="firebrick", linewidth=0.4, linestyle="-", label=r"$LP$")
    plt.plot(t, V_PY, color="royalblue", linewidth=0.4, linestyle="-", label=r"$PY$")
    plt.plot(t, V_AB, color="#198848", linewidth=0.6, linestyle="-", label=r"$AB$")
    plt.plot(t, V_PD1, color="#C8C4FF", linewidth=0.6, linestyle="-.", label=r"$PD1$")
    plt.plot(t, V_PD2, color="#DC81BD", linewidth=0.6, linestyle="--", label=r"$PD2$")

    plt.rc("xtick", labelsize=5)
    plt.rc("ytick", labelsize=5)
    plt.xlabel("t (s)", fontsize=8)
    plt.ylabel("V (mV)", fontsize=8)
    plt.legend(loc="upper right", fontsize=10)
    plt.tight_layout()

    plt.savefig(name_fig, dpi=300)
    plt.close()

    return
