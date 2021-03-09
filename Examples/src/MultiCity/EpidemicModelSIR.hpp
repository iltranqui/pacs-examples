/*
 * EpidemicModel.hpp
 *
 *  Created on: Apr 17, 2020
 *      Author: forma
 */

#ifndef EXAMPLES_SRC_MULTICITY_EPIDEMICMODELSIR_HPP_
#define EXAMPLES_SRC_MULTICITY_EPIDEMICMODELSIR_HPP_
#include "PopulationModel.hpp"
#include "MultiCityEpidemic.hpp"
namespace apsc
{
namespace multicity
{
  /*!
   * It represents the forcing term in the model SIS presented in the reference article
   * @tparam NumCities N. of cities
   * @tparam EpiData  Edidamic data
   */
template<int NumCities, template<int> class EpiData>
class EpidemicModelSIR
{
public:
   static int constexpr NCity=NumCities;
   using EpidemicDataType=EpiData<NumCities>;
  /*!
   * Main variables
   */
  /*{ */
  using VariableType= typename MultiCityModelTraits<NumCities,2>::EpidemicVariableType;
  using ForcingTermType= typename MultiCityModelTraits<NumCities,2>::EpidemicForcingTermType;
  using VectorType = typename MultiCityModelTraits<NumCities,2>::VectorType;
  using BlockType = typename MultiCityModelTraits<NumCities,2>::BlockType;
  using PopulationVariableType= typename MultiCityModelTraits<NumCities,2>::PopulationVariableType;
/*}*/
  /*!
   * Constructor
   * @param data  Epidemic data
   * @param n Population variable N
   */
  EpidemicModelSIR(EpiData<NumCities> const & data, PopulationVariableType & n):data_{data},N{n}{};
  EpidemicModelSIR()=delete;
  //! The operator returning the rhs.
  /*!
   *
   * @param t  time
   * @param V  EdidemicVariables S and I
   * @return   The forcing term
   */
  VariableType operator() (const double & t, const VariableType & V) const;
/*!
 * Update Epidemic data data
 * @param data  Epidemic data
 */
  void setData (const EpiData<NumCities> &data){data_ = data;}
  /*!
   * Update population variable (see note)
   *
   * @note An alternative is to aggregate a population variable as a reference. In this way we would eliminate
   * useless copies, but we need to change the constructor.
   *
   * @param n Population variable
   */
  void setN (const MultiCityPopulationVariables<NumCities> &n) {N = n;}

private:
  //! Epidemic data
  EpiData<NumCities> data_;
  //! Population variable (may become a reference: aggregation instead of composition)
  PopulationVariableType & N;
};
  // implementation
template<int NumCities, template<int> class EpiData>
typename EpidemicModelSIR<NumCities,EpiData>::VariableType
EpidemicModelSIR<NumCities,EpiData>::operator() (const double & t, const VariableType & V) const
{
  // Extract main variables from V
  BlockType S = apsc::multicity::extract<NumCities,0>(V);
  BlockType I = apsc::multicity::extract<NumCities,1>(V);;
  // The building block for forcing term
  BlockType FS;
  BlockType FI;
  // Get coefficients at time t
  auto d = data_.d(t);
  auto g = data_.g(t);
  auto r = data_.r(t);
  auto m = data_.m(t);
  auto ifract = data_.immuneFraction(t);
  // Set diagonal of m to -1,
  {
    // Remember that for misterious reasons m is transposed  w.r.t. r
    VectorType md=m.colwise().sum().transpose()-m.diagonal();
    m-=md.asDiagonal();
  }
  VectorType k    = data_.k(t);
  double gamma = data_.gamma(t);
  VectorType Np=apsc::multicity::Np(this->N);
  VectorType Nr=apsc::multicity::Nr(this->N);

  BlockType gM=m*g.asDiagonal();// gm term
  VectorType Npi;
  Npi=Np.cwiseInverse();// 1/Np
  //*** Block S
  {
    FS = -r.array()*S.array(); // rS term
    VectorType  rSsum = -FS.rowwise().sum();
    FS.diagonal()=rSsum; //rS term completed ckd
    BlockType Sdiag;
    Sdiag.fill(0.0);
    Sdiag.diagonal()=S.diagonal();
    FS         += Sdiag*gM.transpose(); // gmS term ckd
    //@note modification to extend to sir: the term (1-ifract)
    FS.array() +=-d*S.array()+gamma*(1.0-ifract)*I.array(); // -dS+gamma I term ckd
    FS         += d*Nr.asDiagonal(); // diagonal Dnr term
  }
  //** Block I
  {
    FI = -r.array()*I.array(); // rI term
    VectorType  rIsum = -FI.rowwise().sum();
    FI.diagonal()=rIsum;
    BlockType Idiag;
    Idiag.fill(0.0);
    Idiag.diagonal()=I.diagonal();
    FI        += Idiag*gM.transpose(); // gmS term ckd
    FI.array()-= (d+gamma)*I.array(); // -(d+gamma )I term ckd
  }
  // Common term
  for (int kk=0;kk<NumCities;++kk)
    {
      BlockType betak=data_.beta(t,kk);
      VectorType Ik = I.row(kk).transpose();
      BlockType SkN=S* k.asDiagonal() *Npi.asDiagonal()*Ik.asDiagonal();// kSI/Np
      SkN.array()*=  betak.array(); // kSIbeta/Np
      FS.array() -=  SkN.array(); // kbetaSI/Np
      FI.array() +=  SkN.array(); // kbetaSI
    }

  return apsc::multicity::join<NumCities>(FS,FI);

}

}// end namespace

}// end namespace apsc


#endif /* EXAMPLES_SRC_MULTICITY_EPIDEMICMODELSIR_HPP_ */
