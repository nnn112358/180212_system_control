#include "control_eigen.h"


void Euler(MatrixXd dX, MatrixXd &X, MatrixXd u, double tt, double dt, MatrixXd A, MatrixXd B, MatrixXd C, MatrixXd D) {
	MatrixXd f1 = A*X + B*u;
	X = X + f1*dt;
}

void RungeKutta(MatrixXd dX, MatrixXd &X, MatrixXd u, double tt, double dt, MatrixXd A, MatrixXd B, MatrixXd C, MatrixXd D) {
	MatrixXd k1 = A*X + B*u;
	MatrixXd k2 = A*(X + 0.5*k1*dt) + B*u;
	MatrixXd k3 = A*(X + 0.5*k2*dt) + B*u;
	MatrixXd k4 = A*(X + k3*dt) + B*u;
	MatrixXd k = (k1 + 2.0*k2 + 2.0*k3 + k4)*dt / 6.0;
	X = X + k;
}


string serialize(const MatrixXd& M) {
	stringstream strm;

	for (int i = 0; i<M.rows(); i++) {
		for (int j = 0; j<M.cols(); j++) {
			strm << M(i, j);

			// separator
			if (!(i == M.rows() - 1 && j == M.cols() - 1))
				strm << ",";
		}
		strm << "\n";
	}

	return strm.str();
}


