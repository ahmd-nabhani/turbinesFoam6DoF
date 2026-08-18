# turbinesFoam6DoF

An extended version of [turbinesFoam](https://github.com/turbinesFoam/turbinesFoam) developed for OpenFOAM to simulate floating offshore wind turbine (FOWT) dynamics with prescribed 6DoF motions (surge, sway, heave).

**Developer:** Ahmad Nabhani  
**Core Contributor:** Josep M. Bergadà  

---

## 🌟 Key Features & Modifications

* **Prescribed 6DoF Motion:** Supports sinusoidal translational dynamics (Surge, Sway, Heave) with customizable amplitude, frequency, and phase offset.
* **Non-Accumulative Velocity Kinematics:** Instantaneous motion velocities are updated per time step without non-physical velocity accumulation across PIMPLE/PISO iterations.
* **Robust Hydrodynamic Bounds:** Implemented numerical safeguards inside `calcEndEffects()` and angle-of-attack trigonometric calculations to prevent floating-point exceptions (`FOAM_SIGFPE`) under large platform displacement.
* **Live Motion Diagnostics:** Real-time terminal readout of instantaneous overall platform displacement $[x, y, z]$ and velocity $[v_x, v_y, v_z]$.

---

## 🛠️ Installation & Building

1. Clone or place this repository in your OpenFOAM user directory.
2. Source your OpenFOAM environment (e.g., `openfoam2412`).
3. Compile the library:
   ```bash
   ./Allwclean
   ./Allwmake




   ⚙️ Usage Example
In your simulation case:

1. system/controlDict
Code snippet
libs
(
    "libturbinesFoam6DoF.so"
);

2. system/fvOptions
Add the motion block under axialFlowTurbineALSourceCoeffs:

Code snippet
turbine
{
    type            axialFlowTurbineALSource;
    active          on;

    axialFlowTurbineALSourceCoeffs
    {
        // ... standard ALM parameters ...

        motion
        {
            active      true;

            surge
            {
                active      true;
                amplitude   4.0;     // [m] Amplitude
                frequency   0.1;     // [Hz] Frequency
                phase       0.0;     // [rad] Phase shift
            }
            sway
            {
                active      false;
                amplitude   0.0;
                frequency   0.0;
                phase       0.0;
            }
            heave
            {
                active      true;
                amplitude   0.5;
                frequency   0.2;
                phase       1.5708;  // [rad] (pi/2 offset)
            }
        }
    }
}


## 📖 Citation
If you use this code in your research or academic work, please cite the following paper:

Ahmad Nabhani, Josep M. Bergada (2026). Influence of turbulence length scale and platform surge motion on wake dynamics in tandem floating wind turbines. Physics of Fluids, 38(6), 065124.

DOI: 10.1063/5.0326805

BibTeX
Code snippet
@article{Nabhani2026_PoF,
  author  = {Ahmad Nabhani and Josep M. Bergada},
  title   = {Influence of turbulence length scale and platform surge motion on wake dynamics in tandem floating wind turbines},
  journal = {Physics of Fluids},
  volume  = {38},
  number  = {6},
  pages   = {065124},
  year    = {2026},
  month   = {06},
  doi     = {10.1063/5.0326805},
  url     = {[https://doi.org/10.1063/5.0326805](https://doi.org/10.1063/5.0326805)}
}

## 📄 License

This project is licensed under the **GNU General Public License v3.0 (GPL-3.0)**, matching the upstream `turbinesFoam` and OpenFOAM licensing terms.

See the [LICENSE](LICENSE) file for details.
