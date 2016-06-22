/*----------------------------------------------------------------------*\
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
|   Copyright(C) 2016  Alberto Cuoci                                      |
|   Source-code or binary products cannot be resold or distributed        |
|   Non-commercial use only                                               |
|   Cannot modify source-code for any purpose (cannot create              |
|   derivative works)                                                     |
|                                                                         |
\*-----------------------------------------------------------------------*/

#ifndef OpenSMOKE_Capillary_H
#define OpenSMOKE_Capillary_H

// OpenSMOKE++ Definitions
#include "OpenSMOKEpp"

// CHEMKIN maps
#include "maps/Maps_CHEMKIN"

// CHEMKIN maps
#include "PorousMedium.h"

// 1D grid
#include "grids/adaptive/Grid1D.h"

// Numerical parameters
#include "math/multivalue-dae-solvers/parameters/DaeSolver_Parameters.h"

namespace CVI
{
	//!  A class to solve the reaction-diffusion equations in capillaries
	/*!
	This class provides the tools to solve the reaction-diffusion equations in capillaries
	*/

	class Capillary
	{
	public:

		/**
		*@brief Default constructor
		*@param thermodynamicsMap		reference to the thermodynamic map
		*@param kineticsMap			reference to the kinetic map
		*@param transportMap			reference to the transport map
		*@param heterogeneousMechanism		reference to the heterogeneous mechanism
		*@param grid				reference to 1D grid
		*/
		Capillary(	OpenSMOKE::ThermodynamicsMap_CHEMKIN<double>& thermodynamicsMap,
				OpenSMOKE::KineticsMap_CHEMKIN<double>& kineticsMap,
				OpenSMOKE::TransportPropertiesMap_CHEMKIN<double>& transportMap,
				CVI::HeterogeneousMechanism& heterogeneousMechanism,
				OpenSMOKE::Grid1D& grid);

		/**
		*@brief Sets the conditions along the gas side
		*@param T_gas		gas side temperature [K]
		*@param P_gas		gas side pressure [Pa]
		*@param omega_gas	gas side mass fractions
		*/
		void SetGasSide(const double T_gas, const double P_gas, const Eigen::VectorXd& omega_gas);

		/**
		*@brief Sets the initial conditions in the porous medium
		*@param T_initial	initial temperature [K]
		*@param P_initial	initial pressure [Pa]
		*@param D_initial	initial diameter [m]
		*@param omega_initial	initial mass fractions
		*/
		void SetInitialConditions(const double T_initial, const double P_initial, const double D_initial, const Eigen::VectorXd& omega_initial);

		/**
		*@brief Sets the total time of integration
		*@param time_total total time of integration [s]
		*/
		void SetTimeTotal(const double time_total);

		/**
		*@brief Sets the interval time for solving successive DAE systems
		*@param time_interval interval time [s]
		*/
		void SetDaeTimeInterval(const double time_interval);

		/**
		*@brief Sets the interval time for writing Tecplot output
		*@param time_interval interval time [s]
		*/
		void SetTecplotTimeInterval(const double time_interval);

		/**
		*@brief Sets steps video
		*@param steps_video number of steps to update info on the screen
		*/
		void SetStepsVideo(const int steps_video);

		/**
		*@brief Sets steps file
		*@param steps_file number of steps to update info on file
		*/
		void SetStepsFile(const int steps_file);

		/**
		*@brief Returns the differential equations
		*@param t current time [s]
		*@param y current solution
		*@param dy current time derivatives
		*/
		void Equations(const double t, const double* y, double* dy);

		/**
		*@brief Solves the reactor equations
		*@param dae_parameters parameters governing the solution of the DAE system
		*@return the returned value is >0 in case of success, otherwise is <0
		*/
		int SolveFromScratch(DaeSMOKE::DaeSolver_Parameters& dae_parameters);

		/**
		*@brief Prints info on the screen
		*@param t current time [s]
		*@param y current vector of unknowns
		*/
		void Print(const double t, const double* y);

		/**
		*@brief Returns the total number of equations of the DAE system
		*/
		unsigned int NumberOfEquations() const { return ne_; }

		/**
		*@brief Returns the block dimension (Jacobian is tridiagonal-block)
		*/
		unsigned int BlockDimensions() const { return block_; }

		/**
		*@brief Returns the upper band size
		*/
		unsigned int UpperBand() const { return band_size_; }

		/**
		*@brief Returns the lower band size
		*/
		unsigned int LowerBand() const { return band_size_; }

		/**
		*@brief Returns if an equation is differential or algebraic
		*@param v the vector containg if an equation is differential (1.) or algebraic (0.)
		*/
		void AlgebraicDifferentialVector(double* v);

		/**
		*@brief Returns the sparsity pattern of the Jacobian matrix
		*@param row  row indices of non-zero elements (0-based)
		*@param cols column indices of non-zero elements (0-based)
		*/
		void SparsityPattern(std::vector<unsigned int>& rows, std::vector<unsigned int>& cols);

		/**
		*@brief Transfer the current vector to the plug flow reactor unknowns
		*@param y vector of variables to be transferred
		*/
		void Recover_Unknowns(const double* y);

		/**
		*@brief Transfer the current derivatives to the provided vector
		*@param y vector where to transfer the derivatives
		*/
		void Recover_Residuals(double* dy);

		/**
		*@brief Current vector of unknowns
		*@param y vector the current unknowns are copied
		*/
		void UnknownsVector(double* v);

		/**
		*@brief Current vector of unknowns (corrected to ensure the physical constraints)
		*@param y vector the current unknowns are copied
		*/
		void CorrectedUnknownsVector(double* v);

		/**
		*@brief Returns the minimum constraints
		*@param v the minimum constraints for each variable
		*/
		void MinimumUnknownsVector(double* v);

		/**
		*@brief Returns the maximum constraints
		*@param v the maximum constraints for each variable
		*/
		void MaximumUnknownsVector(double* v);

	private:

		/**
		*@brief Allocates vectors and matrices
		*/
		void MemoryAllocation();

		/**
		*@brief Calculates the concentrations, density, molecular weight, transport properties and formation rates of gaseous species
		*/
		void Properties();

		/**
		*@brief Equations of conservation of mass fractions of species
		*/
		void SubEquations_MassFractions();

		/**
		*@brief Equation describing the evolution of diameter
		*/
		void SubEquations_Diameter();

		/**
		*@brief Calculates the diffusion fluxes
		*/
		void DiffusionFluxes();

		/**
		*@brief Calculates the spatial derivatives
		*/
		void SpatialDerivatives();

		/**
		*@brief Prints the current solution on a file
		*/
		void PrintSolution(const double t, const std::string name_file);

		/**
		*@brief Prints the diffusion coefficients of gaseous species on file
		*@param t current time [s]
		*@param name_file name of file where the coefficients will be written
		*/
		void PrintDiffusionCoefficients(const double t, const std::string name_file);

		/**
		*@brief Prints the fomation rates of species due to the homogeneous reactions on file
		*@param t current time [s]
		*@param name_file name of file where the formation rates will be written
		*/
		void PrintHomogeneousRates(const double t, const std::string name_file);

		/**
		*@brief Prints the fomation rates of species due to the heterogeneous reactions on file
		*@param t current time [s]
		*@param name_file name of file where the formation rates will be written
		*/
		void PrintHeterogeneousRates(const double t, const std::string name_file);

		/**
		*@brief Solves the system of DAE describing the 1D reactor
		*@param dae_parameters parameters governing the solution of the DAE system
		*@param t0 starting time [s]
		*@param tf final time [s]
		*@return the returned value is >0 in case of success, otherwise is <0
		*/
		int Solve(DaeSMOKE::DaeSolver_Parameters& dae_parameters, const double t0, const double tf);

		/**
		*@brief Sets the algebraic and differential equations
		*/
		void SetAlgebraicDifferentialEquations();

	protected:

		// References
		OpenSMOKE::ThermodynamicsMap_CHEMKIN<double>&			thermodynamicsMap_;		//!< reference to the thermodynamic map
		OpenSMOKE::KineticsMap_CHEMKIN<double>&				kineticsMap_;			//!< reference to the kinetic map
		OpenSMOKE::TransportPropertiesMap_CHEMKIN<double>&		transportMap_;			//!< reference to the trasport properties map
		CVI::HeterogeneousMechanism& 					heterogeneousMechanism_;	//!< reference to the heterogeneous mechanism
		OpenSMOKE::Grid1D&						grid_;				//!< reference to the 1D grid

		// Dimensions
		unsigned int ns_;					//!< total number of gaseous species
		unsigned int np_;					//!< total number of grid points
		unsigned int ne_;					//!< total number of equations
		unsigned int block_;					//!< block size
		unsigned int band_size_;				//!< lower and upper band sizes

		// Main variables
		Eigen::VectorXd			T_;		//!< current temperature [K]
		Eigen::VectorXd			P_;		//!< current pressure [Pa]
		std::vector<Eigen::VectorXd>	Y_;		//!< mass fractions
		std::vector<Eigen::VectorXd>	X_;		//!< mole fractions

		// Properties
		Eigen::VectorXd			rho_gas_;		//!< density of gaseous phase [kg/m3]
		Eigen::VectorXd			mw_;			//!< molecular weight of gaseous phase [kg/kmol]
		Eigen::VectorXd			diameter_;		//!< graphite diameter [m]
		double				diameter_initial_;	//!< initial diameter [m]


		// Reactions	
		std::vector<Eigen::VectorXd>	omega_homogeneous_;			//!< formation rates of gaseous species [kg/m3/s] (only contribution from homogeneous reactions)
		std::vector<Eigen::VectorXd>	omega_heterogeneous_;			//!< formation rates of gaseous species [kg/m3/s] (only contribution from heterogeneus reactions)
		Eigen::VectorXd			omega_deposition_per_unit_volume_;	//!< deposition rate [kg/m3/s]
		Eigen::VectorXd			omega_deposition_per_unit_area_;	//!< deposition rate [kg/m2/s]

		// Diffusion
		std::vector<Eigen::VectorXd>	gamma_star_;			//!< mass diffusion coefficients [m2/s]
		std::vector<Eigen::VectorXd>	j_star_;			//!< mass diffusion fluxes [kg/m2/s]
		Eigen::VectorXd			jc_star_;			//!< correction mass diffusion flux [kg/m2/s]

		// Spatial derivatives
		std::vector<Eigen::VectorXd>	dX_over_dx_;		//!< spatial derivatives of mole fractions [1/m]
		std::vector<Eigen::VectorXd>	dY_over_dx_;		//!< spatial derivatives of mass fractions [1/m]
		std::vector<Eigen::VectorXd>	d2Y_over_dx2_;		//!< spatial 2nd derivatives of mass fraction [1/m2]
		std::vector<Eigen::VectorXd>	dgamma_star_over_dx_;	//!< spatial derivatives of mass diffusion coefficients [m2/s/m]
		Eigen::VectorXd			drho_gas_over_dx_;	//!< spatial derivatives of density of gaseous phase [kg/m3/m]

		// Time derivatives
		std::vector<Eigen::VectorXd>	dY_over_dt_;			//!< time derivatives of mass fractions	[1/s]
		Eigen::VectorXd			ddiameter_over_dt_;		//!< time derivative of porosity [1/s]

		// Gas side data
		Eigen::VectorXd					Y_gas_side_;			//!< mass fractions along the gas side
		double						T_gas_side_;			//!< temperature along the gas side [K]
		double						P_gas_side_;			//!< pressure along the gas side [Pa]

		// Algebraic/Differential equations
		std::vector<bool>				id_equations_;			//!< algebraic/differential equations

		// Time
		double time_total_;
		double dae_time_interval_;
		double time_smoothing_;

		// Tecplot
		int count_tecplot_;
		double tecplot_time_interval_;

		// Auxiliary vectors
		OpenSMOKE::OpenSMOKEVectorDouble	aux_Y;				//!< vector containing the mass fractions
		OpenSMOKE::OpenSMOKEVectorDouble	aux_X;				//!< vector containing the mole fractions
		OpenSMOKE::OpenSMOKEVectorDouble	aux_C;				//!< vector containing the concentration of gaseous species [kmol/m3]
		OpenSMOKE::OpenSMOKEVectorDouble	aux_R;				//!< vector containing the formation rates of gaseous species [kg/m3/s]
		OpenSMOKE::OpenSMOKEVectorDouble	aux_gamma;			//!< vector containing the mass diffusion coefficients
		Eigen::VectorXd						aux_eigen;			//!< auxiliary eigen vector
		
		// Output
		unsigned int n_steps_video_;					//!< number of steps for updating info on the screen
		unsigned int count_video_;					//!< counter of steps for updating info on the screen
		unsigned int n_steps_file_;					//!< number of steps for updating info on the file
		unsigned int count_file_;					//!< counter of steps for updating info on the file
		std::ofstream fMonitoring_;					//!< name of file to monitor integral quantities over the time

		// Output folders
		boost::filesystem::path output_folder_;				//!< name of output folder
		boost::filesystem::path output_matlab_folder_;			//!< name of output folder fot Matlab files
		boost::filesystem::path output_diffusion_folder_;		//!< name of output folder fot diffusion coefficient files
		boost::filesystem::path output_heterogeneous_folder_;		//!< name of output folder fot heterogeneous reaction files
		boost::filesystem::path output_homogeneous_folder_;		//!< name of output folder fot homogeneous reaction files

		double AreaAveraged(const Eigen::VectorXd& v);
		double AreaStandardDeviation(const double mean, const Eigen::VectorXd& v);
		void PrintLabelMonitoringFile();
	};
}

#include "Capillary.hpp"

#endif /* OpenSMOKE_Capillary_H */