#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Mar 15 09:15:15 2022

Last edit: Tue Apr 5 16:06:06 2022

@author: Blanca Berbel
"""

import numpy as np
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
from scipy import stats


def get_R2(P, I):
    while len(P) != len(I):
        if len(P) > len(I):
            P.pop(-1)
        else:
            I.pop(-1)

    X = np.array([P]).reshape((-1, 1))
    Y = np.array(I)

    model = LinearRegression().fit(X, Y)

    R2 = model.score(X, Y)

    return R2


def get_R2_with_p_value(P, I):
    while len(P) != len(I):
        if len(P) > len(I):
            P.pop(-1)
        else:
            I.pop(-1)

    X = np.array([P]).reshape((-1, 1))
    Y = np.array(I)

    model = LinearRegression().fit(X, Y)

    Y_pred = model.predict(X)

    SS_res = np.sum((Y - Y_pred) ** 2)
    SS_tot = np.sum((Y - np.mean(Y)) ** 2)

    R2 = 1 - (SS_res / SS_tot)
    n = len(Y)
    k = 1
    F = (R2 / k) / ((1 - R2) / (n - k - 1))
    return R2, p_value


def get_R2_with_p_value_pearson(P, I):
    R2, p_value = stats.pearsonr(P, I)
    return R2, p_value


def get_X_Y_pred(P, I):
    while len(P) != len(I):
        if len(P) > len(I):
            P.pop(-1)
        else:
            I.pop(-1)

    X = np.array([P]).reshape((-1, 1))
    Y = np.array(I)

    model = LinearRegression().fit(X, Y)

    Y_pred = model.predict(X)

    return X, Y_pred


def get_n_burst(P, I):
    n_burst = []
    for i in range(0, (min(len(P), len(I)))):
        n_burst.append(i + 1)

    return n_burst


def get_maps_invariants(P, I, X, Y_pred, R2, K1, K2, label_x, label_y, carpeta):
    plt.rcParams["figure.dpi"] = 80
    plt.rcParams["text.usetex"] = True
    plt.rcParams["figure.figsize"] = (25, 15)

    n_burst = get_n_burst(P, I)

    fig = plt.figure()

    cmp = plt.get_cmap("viridis")

    plt.scatter(
        P,
        I,
        s=5,
        c=n_burst,
        marker="s",
        cmap=cmp,
        vmin=None,
        vmax=None,
        alpha=1,
        linewidths=2,
        edgecolors=None,
    )
    plt.plot(X, Y_pred, linestyle="solid", c="r", linewidth=2, label=str(R2.round(4)))

    plt.rc("xtick", labelsize=20)
    plt.rc("ytick", labelsize=20)
    plt.title(
        label_y
        + " vs "
        + label_x
        + " for $g^{s}_{LPPD}$ = "
        + "{:.4f}".format(K1)
        + " and $Vs_{PD}$ = "
        + "{:.4f}".format(K2),
        fontsize=25,
    )
    plt.xlabel(label_x, fontsize=25)
    plt.ylabel(label_y + " duration", fontsize=25)
    plt.legend(loc="upper right", fontsize=15)
    plt.colorbar()

    plt.show()
    plt.savefig(carpeta + "/" + label_y + " vs " + label_x + ".png", dpi=fig.dpi)

    return


def get_maps_invariants_P1(P, I, X, Y_pred, R2, K1, label_x, label_y, carpeta):
    plt.rcParams["figure.dpi"] = 80
    plt.rcParams["text.usetex"] = True
    plt.rcParams["figure.figsize"] = (25, 15)

    n_burst = get_n_burst(P, I)

    fig = plt.figure()

    cmp = plt.get_cmap("viridis")

    plt.scatter(
        P,
        I,
        s=5,
        c=n_burst,
        marker="s",
        cmap=cmp,
        vmin=None,
        vmax=None,
        alpha=1,
        linewidths=2,
        edgecolors=None,
    )
    plt.plot(X, Y_pred, linestyle="solid", c="r", linewidth=2, label=str(R2.round(4)))

    plt.rc("xtick", labelsize=20)
    plt.rc("ytick", labelsize=20)
    plt.title(
        label_y + " duration vs " + label_x + " for $Vs_{LP}$ = " + "{:.4f}".format(K1),
        fontsize=25,
    )
    plt.xlabel(label_x, fontsize=25)
    plt.ylabel(label_y + " duration", fontsize=25)
    plt.legend(loc="upper right", fontsize=15)
    plt.colorbar()

    plt.show()

    return
