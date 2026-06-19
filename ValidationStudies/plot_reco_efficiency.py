#!/usr/bin/env python3
"""Plot reconstruction efficiency vs true neutrino and deposited energy."""

from __future__ import annotations

import os
from pathlib import Path

import numpy as np
import uproot

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib.pyplot as plt


ROOT_FILE = Path(
    "/home/leoperes/ntuples_grid_newVertex/00a_newVertex/"
    "atm_all_Honda_hA_BR_solmax_NuFIT4p1_E40_cosZ20_1p5M.root"
)
OUTDIR = Path(__file__).resolve().parent / "plots" / "reco_efficiency"

NEUTRINO_ENERGY_BINS = np.logspace(np.log10(0.1), np.log10(100.0), 61)
DEPOSITED_ENERGY_BINS = np.logspace(np.log10(0.1), np.log10(100.0), 61)
NEUTRINO_PDGS = {12, 14, 16}


def _basket_array(branch, basket_index):
    """Read one basket, avoiding a high-level uproot array hang seen locally."""
    basket = branch.basket(basket_index)
    interpretation = branch.interpretation

    if interpretation.__class__.__name__ == "AsDtype":
        return basket.array(interpretation, library="np")

    library = uproot.interpretation.library._libraries["np"]
    return interpretation.basket_array(
        basket.data,
        basket.byte_offsets,
        basket,
        branch,
        {},
        0,
        library,
        {},
    )


def iter_baskets(tree, branch_names):
    """Yield branch arrays basket-by-basket for branches with shared baskets."""
    branches = {name: tree[name] for name in branch_names}
    num_baskets = min(branch.num_baskets for branch in branches.values())

    for basket_index in range(num_baskets):
        yield {
            name: _basket_array(branch, basket_index)
            for name, branch in branches.items()
        }


def read_branch_entries(branch):
    """Read one branch into entry-ordered Python objects."""
    entries = []
    for basket_index in range(branch.num_baskets):
        entries.extend(_basket_array(branch, basket_index))
    return entries


def neutrino_energy_from_momentum(momentum):
    """Return |p_nu| from the MCNuMomentum nested 3-vector."""
    energy = np.empty(len(momentum), dtype=float)
    for idx, vectors in enumerate(momentum):
        vec = np.asarray(vectors[0], dtype=float)
        energy[idx] = np.linalg.norm(vec)
    return energy


def deposited_energy(pdg_codes, kinetic_energies):
    """Sum kinetic energy of generated non-neutrino particles event-by-event."""
    energy = np.empty(len(pdg_codes), dtype=float)
    for idx, (pdgs, kinetic) in enumerate(zip(pdg_codes, kinetic_energies)):
        pdgs = np.asarray(pdgs)
        kinetic = np.asarray(kinetic, dtype=float)
        visible = ~np.isin(np.abs(pdgs), list(NEUTRINO_PDGS))
        energy[idx] = kinetic[visible].sum()
    return energy


def histogram_tree(tree, variable, bins):
    counts = np.zeros(len(bins) - 1, dtype=float)

    if variable == "nu_energy":
        for arrays in iter_baskets(tree, ["MCNuMomentum"]):
            values = neutrino_energy_from_momentum(arrays["MCNuMomentum"])
            counts += np.histogram(values, bins=bins)[0]
    elif variable == "deposited_energy":
        pdg_codes = read_branch_entries(tree["MCPdgCode"])
        kinetic_energies = read_branch_entries(tree["MCKineticEnergy"])
        if len(pdg_codes) != len(kinetic_energies):
            raise RuntimeError(
                "MCPdgCode and MCKineticEnergy have different entry counts: "
                f"{len(pdg_codes)} vs {len(kinetic_energies)}"
            )
        values = deposited_energy(pdg_codes, kinetic_energies)
        counts += np.histogram(values, bins=bins)[0]
    else:
        raise ValueError(f"Unknown variable: {variable}")

    return counts


def efficiency(numerator, denominator):
    eff = np.divide(
        numerator,
        denominator,
        out=np.full_like(numerator, np.nan, dtype=float),
        where=denominator > 0,
    )
    err = np.sqrt(
        np.divide(
            eff * (1.0 - eff),
            denominator,
            out=np.zeros_like(eff, dtype=float),
            where=denominator > 0,
        )
    )
    return eff, err


def plot_efficiency(bins, numerator, denominator, xlabel, output):
    eff, err = efficiency(numerator, denominator)
    centers = np.sqrt(bins[:-1] * bins[1:])
    xerr = np.vstack([centers - bins[:-1], bins[1:] - centers])

    fig, ax = plt.subplots(figsize=(8, 5))
    ax.errorbar(
        centers,
        eff,
        xerr=xerr,
        yerr=err,
        fmt="o",
        markersize=4,
        capsize=2,
        color="#1b6f8f",
        ecolor="#2f9e44",
    )
    ax.set_xscale("log")
    ax.set_xlim(bins[0], bins[-1])
    ax.set_xlabel(xlabel)
    ax.set_ylabel("Reconstruction efficiency")
    ax.set_ylim(0.0, 1.05)
    ax.grid(True, alpha=0.3)
    fig.tight_layout()
    fig.savefig(output)
    plt.close(fig)


def main():
    OUTDIR.mkdir(parents=True, exist_ok=True)
    root_file = uproot.open(ROOT_FILE)
    reco_tree = root_file["ana/Atm"]
    sim_tree = root_file["ana/AllEvents"]

    histograms = {}
    for variable, bins in [
        ("nu_energy", NEUTRINO_ENERGY_BINS),
        ("deposited_energy", DEPOSITED_ENERGY_BINS),
    ]:
        histograms[(variable, "reco")] = histogram_tree(reco_tree, variable, bins)
        histograms[(variable, "sim")] = histogram_tree(sim_tree, variable, bins)

    plot_efficiency(
        NEUTRINO_ENERGY_BINS,
        histograms[("nu_energy", "reco")],
        histograms[("nu_energy", "sim")],
        r"True neutrino energy $E_\nu$ [GeV]",
        OUTDIR / "reco_efficiency_vs_neutrino_energy.png",
    )
    plot_efficiency(
        DEPOSITED_ENERGY_BINS,
        histograms[("deposited_energy", "reco")],
        histograms[("deposited_energy", "sim")],
        "Deposited energy from generated particles [GeV]",
        OUTDIR / "reco_efficiency_vs_deposited_energy.png",
    )

    for variable, bins in [
        ("nu_energy", NEUTRINO_ENERGY_BINS),
        ("deposited_energy", DEPOSITED_ENERGY_BINS),
    ]:
        reco = histograms[(variable, "reco")]
        sim = histograms[(variable, "sim")]
        eff, err = efficiency(reco, sim)
        table = np.column_stack([bins[:-1], bins[1:], reco, sim, eff, err])
        np.savetxt(
            OUTDIR / f"{variable}_efficiency.dat",
            table,
            header="bin_low bin_high n_reco n_sim efficiency stat_uncertainty",
        )

    print(f"Wrote plots and tables to {OUTDIR}")


if __name__ == "__main__":
    main()
