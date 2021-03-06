/*-----------------------------------------------------------------------*\
|    ___                   ____  __  __  ___  _  _______                  |
|   / _ \ _ __   ___ _ __ / ___||  \/  |/ _ \| |/ / ____| _     _         |
|  | | | | '_ \ / _ \ '_ \\___ \| |\/| | | | | ' /|  _| _| |_ _| |_       |
|  | |_| | |_) |  __/ | | |___) | |  | | |_| | . \| |__|_   _|_   _|      |
|   \___/| .__/ \___|_| |_|____/|_|  |_|\___/|_|\_\_____||_|   |_|        |
|        |_|                                                              |
|                                                                         |
|   Author: Alberto Cuoci <alberto.cuoci@polimi.it>                       |
|   CRECK Modeling Group <http://creckmodeling.chem.polimi.it>            |
|   Department of Chemistry, Materials and Chemical Engineering           |
|   Politecnico di Milano                                                 |
|   P.zza Leonardo da Vinci 32, 20133 Milano                              |
|                                                                         |
|-------------------------------------------------------------------------|
|                                                                         |
|   This file is part of OpenSMOKE++ Suite.                               |
|                                                                         |
|   Copyright(C) 2015, 2014, 2013  Alberto Cuoci                          |
|   Source-code or binary products cannot be resold or distributed        |
|   Non-commercial use only                                               |
|   Cannot modify source-code for any purpose (cannot create              |
|   derivative works)                                                     |
|                                                                         |
\*-----------------------------------------------------------------------*/

#include "math/native-dae-solvers/MultiValueSolver"

class OpenSMOKE_Reactor1D_DaeSystem
{
public:

	OpenSMOKE_Reactor1D_DaeSystem() {};

	void assign(CVI::Reactor1D *reactor);

private:

	CVI::Reactor1D *ptReactor;

protected:

	unsigned int ne_;

	void MemoryAllocation()
	{
	}

	virtual void Equations(const Eigen::VectorXd& y, const double t, Eigen::VectorXd& f)
	{
		ptReactor->Equations(t, y.data(), f.data());
	}

	void Jacobian(const Eigen::VectorXd &y, const double t, Eigen::MatrixXd &J)
	{
	};

	void Print(const double t, const Eigen::VectorXd &y)
	{
		ptReactor->Print(t, y.data());
	}
};

void OpenSMOKE_Reactor1D_DaeSystem::assign(CVI::Reactor1D *reactor)
{
	ptReactor = reactor;
}

#include "math/native-dae-solvers/interfaces/Band_OpenSMOKEppDae.h"

