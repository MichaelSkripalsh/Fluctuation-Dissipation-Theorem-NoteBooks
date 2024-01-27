# Fluctuation Dissipation Theorem

This github repository is a collection of python jupyter notebooks (and some accompanying c code for c programmers)
that give a pedagogical introduction to the fluctuation dissipation theorem. The goal of these notebooks is to walk the reader starting from the simplest harmonic oscillator model to understanding the fluctuation dissipation theorem by writing (or at least following) python code that can give a more visual and creative picture of the fluctuation dissipation theorem. \\

This repository is organized in the following structure

\python_notebooks
  \src
  \code summaries
\c_code
\theory

\python_notebooks
  \src : contains the primary notebooks.
  \code summaries contains the same notebooks except without long explanatory text —to provide a quick code look up for those who are returning to the notebooks after reading the full notebooks first.

\c_code : contains harmonic oscillator simulations in c code (with python programs that analyze the results of the c code)

\theory : latex documents that outline the relevant theory used in these notebooks

#Brief
  There are N notebooks in this repository

Part 1
  1. Harmonic Oscillator
  2. Damped Harmonic Oscillator
  3. Forced Harmonic Oscillator
  4. Classical Fluctuation Dissipation Theorem

Part 2 
  5. Two dimensional Oscillator
  6. Oscillator in a magnetic field
  7. Oscillator in a monopole field
  8. Oscillator with fluctuating mass

  # Part 1 
    Walks readers through the harmonic oscillator starting with simulating the simplest harmonic oscillator model a classical, one dimensional, Hookian, undamped, unforced spring. By slowly adding more conditions such as damping, forces, etc. we eventually finish with the Fluctuation Dissipation Theorem

  #Part 2
  
    Gives supplementary programs that simulate two dimnesional oscillators, or oscillators in magnetic fields, or oscillators with mass fluctuations.

  #concluding note
  
    Finally, there is a folder titled c_programs which contains similar simulations in c. 
