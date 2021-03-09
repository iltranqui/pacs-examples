/*
 * MultiCityPopulation.hpp
 *
 *  Created on: Apr 12, 2020
 *      Author: forma
 */

#ifndef EXAMPLES_SRC_MULTICITY_MULTICITYPOPULATION_HPP_
#define EXAMPLES_SRC_MULTICITY_MULTICITYPOPULATION_HPP_
#include <array>
#include "MultiCitiesModelTraits.hpp"
namespace apsc
{
  namespace multicity
  {
    template<int NumCities>
    using MultiCityPopulationVariables =typename MultiCityModelTraits<NumCities>::PopulationVariableType;

    template<int NumCities>
       using MultiCityPopVectorType =typename MultiCityModelTraits<NumCities>::VectorType;


    template<class MP>
    decltype(auto) Np(MP const & N)
    {
      return N.transpose().rowwise().sum();
    }

     template<class MP>
     decltype(auto) Nr(MP const & N)
     {
       return N.rowwise().sum();
     }

     template<class MP>
     std::array<double,2> totalPop(MP const & N)
     {
       return {N.sum(),Nr(N).sum()};
     }
     //! A general template for initialization`
     template<int NumCities>
     struct InitializePopulation
     {
       virtual MultiCityPopulationVariables<NumCities> initialize()=0;
       virtual ~InitializePopulation<NumCities>()=default;
     };
     //! The two city case of the article
     struct initialize2Cities: public InitializePopulation<2>
     {
       MultiCityPopulationVariables<2>
       initialize() override
  	{
	 MultiCityPopulationVariables<2> N;
	 N<<25000,0,0,25000;
  	 return N;
  	}
     };

  }
}




#endif /* EXAMPLES_SRC_MULTICITY_MULTICITYPOPULATION_HPP_ */
