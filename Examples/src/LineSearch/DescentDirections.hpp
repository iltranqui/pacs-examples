/*
 * DescentDirections.hpp
 *
 *  Created on: Dec 28, 2020
 *      Author: forma
 */

#ifndef EXAMPLES_SRC_LINESEARCH_DESCENTDIRECTIONS_HPP_
#define EXAMPLES_SRC_LINESEARCH_DESCENTDIRECTIONS_HPP_
#include "DescentDirectionBase.hpp"
#include <limits>
namespace apsc
{
  /*!
   * Implements the gradient search
   */
  class GradientDirection : public DescentDirectionBase
  {
  public:
    /*!
     *  Returns - gradient as descent direction
     * @param values The current values.
     * @return The descent direction.
     */
    apsc::LineSearch_traits::Vector operator()
    (apsc::OptimizationCurrentValues const & values) override
    {
      return -values.currentGradient;
    }
  };
  /*!
   *  Implements the classic BFGS quasi-Newton algorithm.
   */
  class BFGSDirection: public DescentDirectionBase
  {
  public:
    apsc::LineSearch_traits::Vector operator()
    (apsc::OptimizationCurrentValues const & values) override;
    /*!
     * You need to reset if you run another problem or you start from a different initial point.
     * @note This is done inside LineSearchSolver
     */
    void reset() override;
  private:
    apsc::OptimizationCurrentValues previousValues;
    Eigen::MatrixXd H;
    bool firstTime{true};
    double const smallNumber=std::sqrt(std::numeric_limits<double>::epsilon());
  };

  /*!
   * Implements BFGS with the direct computation of the approximate inverse of
   * the Hessian.
   */
  class BFGSIDirection: public DescentDirectionBase
  {
  public:
    apsc::LineSearch_traits::Vector operator()
    (apsc::OptimizationCurrentValues const & values) override;
    void reset() override;
  private:
    apsc::OptimizationCurrentValues previousValues;
    Eigen::MatrixXd H;
    bool firstTime{true};
    double const smallNumber=std::sqrt(std::numeric_limits<double>::epsilon());
  };
  /*!
   * Bazrzilain-Borwein
   */
  class BBDirection: public DescentDirectionBase
  {
  public:
    apsc::LineSearch_traits::Vector operator()
    (apsc::OptimizationCurrentValues const & values) override;
    void reset() override
    {firstTime=true;};
  private:
    apsc::OptimizationCurrentValues previousValues;
    bool firstTime{true};
    double const smallNumber=std::sqrt(std::numeric_limits<double>::epsilon());
  };
  /*!
   * Non-linear CG with Polak-Ribiere formula
   */
  class CGDirection: public DescentDirectionBase
  {
  public:
    apsc::LineSearch_traits::Vector operator()
    (apsc::OptimizationCurrentValues const & values) override;
    void reset() override
    {firstTime=true;};
  private:
    apsc::OptimizationCurrentValues previousValues;
    bool firstTime{true};
    //! I need to keep track of previous descent direction
    apsc::LineSearch_traits::Vector prevDk;
  };

}// end namespace




#endif /* EXAMPLES_SRC_LINESEARCH_DESCENTDIRECTIONS_HPP_ */
