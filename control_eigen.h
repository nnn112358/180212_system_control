#pragma once


#include "Eigen/Dense"
#include "Eigen/Core"
#include <iostream>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>


using namespace Eigen;
using namespace std;


void Euler(MatrixXd dX, MatrixXd &X, MatrixXd u, double tt, double dt, MatrixXd A, MatrixXd B, MatrixXd C, MatrixXd D);

void RungeKutta(MatrixXd dX, MatrixXd &X, MatrixXd u, double tt, double dt, MatrixXd A, MatrixXd B, MatrixXd C, MatrixXd D);


string serialize(const MatrixXd& M);
