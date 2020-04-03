# 1D convection-diffusion solver

This repository contains a MATLAB code and a c++ code to solve 1D convection diffusion problem using Galerkin and Petrov-Galerkin methods.

The MATLAB file is stand alone, meaning it will solve and plot the data and can even compare both solutions simultaneously.

The C++ file generates Result.dat that contains three columns- the galerkin or petrov-gakerkin solution (based on user choice), the exact solution and the coordinate matrix. The data in Result.dat can be plotted with the MATLAB file Plot.m provided in the 
repository.

I deliberately avoided the use of any external library as I am new to C++ programming and wanted to code something simple from scratch (as a learning exercise). However, if anyone is strong with MATLAB, consider using #Armadillo library which is very similar to MATLAB in functionality. Also, #Eigen is a good option and offers a wide range of matrix operations.


<a href="https://www.codecogs.com/eqnedit.php?latex=\begin{equation}&space;u&space;\approx&space;\~{u}&space;=&space;\sum_{i=1}^{n}&space;N_{i}u_i&space;\end{equation}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\begin{equation}&space;u&space;\approx&space;\~{u}&space;=&space;\sum_{i=1}^{n}&space;N_{i}u_i&space;\end{equation}" title="\begin{equation} u \approx \~{u} = \sum_{i=1}^{n} N_{i}u_i \end{equation}" /></a>
