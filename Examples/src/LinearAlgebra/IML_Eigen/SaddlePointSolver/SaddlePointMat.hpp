/*
 * SaddlePointMat.hpp
 *
 *  Created on: Jul 9, 2020
 *      Author: forma
 */

#ifndef EXAMPLES_SRC_LINEARALGEBRA_IML_EIGEN_SADDLEPOINTSOLVER_SADDLEPOINTMAT_HPP_
#define EXAMPLES_SRC_LINEARALGEBRA_IML_EIGEN_SADDLEPOINTSOLVER_SADDLEPOINTMAT_HPP_
#include "BasicType.hpp"
#include <Eigen/Sparse>
namespace FVCode3D
{
  //! Class for assembling a saddle point matrix.
  /*!
   * @class SaddlePointMat
   * This class implements a generic saddle point matrix. It consists of 3 block matrices
   * M, B and T. It will be build up through an object of type SaddlePoint_StiffMatrix
   * that is the assembler of the numerical method and it overloads the *(Vector) operator
   * to use the blocks matrix to compute the matrix-vector product. In this way we avoid
   * to store the whole system matrix and we use the same 3 blocks (without any copy of them)
   * to make everything we need: matrix-vector product, building and inverting the preconditioner.
   * Clearly, this class is interesting only with an iterative system solving the system.
   * Constructors, assignement, destructor and so on are all defaulted.
   * The matrix will always contain the blocks in this form
   * \f[
   * \begin{bmatrix}
   * M & B^T\\
   * B & T
   * \end{bmatrix}
   * \f]
   *  being \f$T=-K\f$ and \f$K\f$ a symmetric non-negative definite matrix.
   * However, if isSymUndef is set to false, it operates like the un-symmetric matrix
   * \f[
   * \begin{bmatrix}
   * M & B^T\\
   * -B & -T
   * \end{bmatrix}=
   * \begin{bmatrix}
   * M & B^T\\
   * -B & K
   * \end{bmatrix}=
   * \f]
  */
  class SaddlePointMat
  {
  public:
      using Scalar=double;
      //! @name Constructor & Destructor
      //@{
      //! Empty-Constructor
      SaddlePointMat()=default;

      //! Construct a saddle point matrix
      /*!
       * @tparam SMAT anything convertible to a SpMat
       * @param Mmat M matrix
       * @param Bmat B matrix
       * @param Tmat T matrix
       * @param isSymUndef true: symmetric form
       */
      template <typename SMAT>
      SaddlePointMat(SMAT&& Mmat, SMAT&& Bmat, SMAT&& Tmat,bool isSymUndef=true):
        isSymUndef{isSymUndef},
        M{std::forward<SpMat>(Mmat)},
        B{std::forward<SpMat>(Bmat)},
        T{std::forward<SpMat>(Tmat)} {}

    //! Construct a saddle point matrix
      /*!
       * @param Mdim M block dimension
       * @param Brow B block row
       * @param Bcol B block col
       */
     SaddlePointMat(const UInt Mdim,const UInt Brow, bool isSymUndef=true):
                  isSymUndef(isSymUndef), M(Mdim,Mdim), B(Brow,Mdim), T(Brow,Brow) {}

          //@}

      //! @name Methods
      //!@{
      //! Sets the saddle point matrix
      /*!
       * @tparam SMAT anything convertible to a SpMat
       * @param Mmat M matrix
       * @param Bmat B matrix
       * @param Tmat T matrix
       */
     template <typename SMAT>
      void Set(SMAT&& Mmat, SMAT&& Bmat, SMAT&& Tmat)
          {
                  M = std::forward<SpMat>(Mmat);
                  B = std::forward<SpMat>(Bmat);
                  T = std::forward<SpMat>(Tmat);
          }

          //! Set the flag isSymUndef
      /*!
       * @param coeff The flag to be set 1=is  Sym Undef -1 is UnSym pdef
       */
      void Set_isSymUndef(const int coeff)
          {
                  isSymUndef = coeff;
          }

          //! Compress the block matrices
      /*!
       * Compress the block matrices M, B and T
       */
      void makeCompressed()
          {
                  M.makeCompressed();
                  B.makeCompressed();
                  T.makeCompressed();
                  };
      //!@}

      //! @name Get Methods
      //!@{
      //! Get M block (read only)
      /*!
       * @return A const reference to the M block
       */
      const SpMat & getM() const
          {return M;}

      //! Get M block
      /*!
       * @return A reference to the M block
       */
      SpMat & getM()
          {return M;}

      //! Get B block (read only)
      /*!
       * @return A const reference to the B block
       */
      const SpMat & getB() const
          {return B;}

      //! Get B block
      /*!
       * @return A reference to the B block
       */
      SpMat & getB()
          {return B;}

      //! Get T block (read only)
      /*!
       * @return A const reference to the T block
       */
      const SpMat & getT() const
          {return T;}

      //! Get T block
      /*!
       * @return A reference to the T block
       */
      SpMat & getT()
          {return T;}
      //!@}

     //! @name Methods
     //!@{
          //! Resize the system
     /*!
      *
      * @param Mdim number or wows
      * @param Brow number of columns
      */
      void resize(const UInt Mdim,const UInt Brow)
          {
                  M.resize(Mdim,Mdim);
                  B.resize(Brow,Mdim);
                  T.resize(Brow,Brow);
          }
      /*!
       * Frobenius norm of the matrix sqared
       *
       * @return the norm squared
       */
      Real squaredNorm()const
      {
        return M.squaredNorm()+2*B.squaredNorm()+T.squaredNorm();
      }
      /*!
        * Frobenius norm of the matrix
        *
        * @return the norm
        */
      Real norm(){return std::sqrt(this->squaredNorm());}
          //! Get the number of non zero
      /*!
       * @return the number of non zero
       */
      UInt nonZeros() const { return M.nonZeros()+2*B.nonZeros()+T.nonZeros(); }
      //!@}

      //! @name Operators
      //!@{
          //! Overload of matrix-vector product operator using the blocks
      /*!
       * @param x A const reference to the vector
       * @return The Vector resulting from the matrix-vector product
       */
      Vector operator * (const Vector & x) const
          {
        Vector result(M.rows()+B.rows());
        result.head(M.rows()) = M*x.head(M.cols()) + B.transpose()*x.tail(B.rows());
        if (isSymUndef==true)
          result.tail(B.rows())= B*x.head(M.cols()) + T*x.tail(B.rows());
        else
          result.tail(B.rows())= -(B*x.head(M.cols()) + T*x.tail(B.rows()));
        return result;
          }
      //! Clears matrix and frees memory
      void clear();
      /*!
       * @return the full matrix
       */
       SpMat fullMatrix() const;
      //!@}

      //! A flag indicating if it is sym-undef or defpos-unsym
         bool  isSymUndef=true;
  private:
    //@toto LF Store as references
          //! The M block matrix
          SpMat     M;
          //! The B block matrix
          SpMat    B;
          //! The T block matrix
          SpMat    T;
  };


}





#endif /* EXAMPLES_SRC_LINEARALGEBRA_IML_EIGEN_SADDLEPOINTSOLVER_SADDLEPOINTMAT_HPP_ */
