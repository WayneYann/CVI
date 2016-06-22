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
|   Copyright(C) 2015, 2014, 2013  Alberto Cuoci                          |
|   Source-code or binary products cannot be resold or distributed        |
|   Non-commercial use only                                               |
|   Cannot modify source-code for any purpose (cannot create              |
|   derivative works)                                                     |
|                                                                         |
\*-----------------------------------------------------------------------*/

#ifndef OpenSMOKE_Grammar_CVI_HeterogeneousMechanism_H
#define OpenSMOKE_Grammar_CVI_HeterogeneousMechanism_H

#include "dictionary/OpenSMOKE_DictionaryManager.h"
#include "dictionary/OpenSMOKE_DictionaryGrammar.h"
#include "dictionary/OpenSMOKE_DictionaryKeyWord.h"

namespace CVI
{
	class Grammar_CVI_HeterogeneousMechanism : public OpenSMOKE::OpenSMOKE_DictionaryGrammar
	{
	protected:

		virtual void DefineRules()
		{
			AddKeyWord(OpenSMOKE::OpenSMOKE_DictionaryKeyWord("@HomogeneousReactions",
				OpenSMOKE::SINGLE_BOOL,
				"Homogeneous reactions true/false",
				true));

			AddKeyWord(OpenSMOKE::OpenSMOKE_DictionaryKeyWord("@HeterogeneousReactions",
				OpenSMOKE::SINGLE_BOOL,
				"Heterogeneous reactions true/false",
				true));

			AddKeyWord(OpenSMOKE::OpenSMOKE_DictionaryKeyWord("@GraphiteDensity",
				OpenSMOKE::SINGLE_MEASURE,
				"Graphite density",
				true));

			AddKeyWord(OpenSMOKE::OpenSMOKE_DictionaryKeyWord("@HeterogeneousReactionRatesMultiplier",
				OpenSMOKE::SINGLE_DOUBLE,
				"Heterogeneous reaction rates multiplier",
				false));

			AddKeyWord(OpenSMOKE::OpenSMOKE_DictionaryKeyWord("@HeterogeneousMechanism",
				OpenSMOKE::SINGLE_STRING,
				"Heterogeneous mechanism: Huttinger | Ziegler | Vignoles |  Huttinger-extended | Ziegler-extended | Vignoles-extended",
				true));

			AddKeyWord(OpenSMOKE::OpenSMOKE_DictionaryKeyWord("@HydrogenInhibition",
				OpenSMOKE::SINGLE_STRING,
				"Hydrogen inhibition type: none | Becker",
				true));
		}
	};
}

#endif /* OpenSMOKE_Grammar_CVI_HeterogeneousMechanism_H */
