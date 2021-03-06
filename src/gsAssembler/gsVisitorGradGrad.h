/** @file gsVisitorGradGrad.h

    @brief Stiffness (grad-grad) Visitor

    This file is part of the G+Smo library.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    Author(s): A. Mantzaflaris
*/


#pragma once


#include <gsAssembler/gsVisitorMass.h>
namespace gismo
{


/** 
    @brief The visitor computes element grad-grad integrals
    
    \ingroup Assembler
*/
template <class T>
class gsVisitorGradGrad : public gsVisitorMass<T> // inherit to reuse functionality
{
public:
    typedef gsVisitorMass<T> Base;

public:
/** @brief Visitor for stiffness (grad-grad) integrals
 * 
 * This visitor assemble the element-wise bilinear form:
 * \f[ ( \nabla u , \nabla v )_{K} \f].
 * Where \f[ v$ \f]  is the test function and \f[u \f] is trial function.
 */
    gsVisitorGradGrad(const gsPde<T> & pde)
    { }

    /*
    static void initialize(const gsBasis<T> & basis, 
                           gsQuadRule<T> & rule, 
                           unsigned & evFlags ) // replace with geoEval ?
    {
        gsVector<index_t> numQuadNodes( basis.dim() );
        for (int i = 0; i < basis.dim(); ++i)
            numQuadNodes[i] = basis.degree(i) + 1;
        
        // Setup Quadrature
        rule = gsGaussRule<T>(numQuadNodes);// harmless slicing occurs here

        // Set Geometry evaluation flags
        evFlags = NEED_MEASURE|NEED_GRAD_TRANSFORM;
        //gsGeometryEvaluator<T>::ptr geoEval ( // -- TODO: Initialize inside visitor
        //this->m_patches.patch(patchIndex).evaluator( evFlags ) );
        
    }
    */

    void initialize(const gsBasis<T> & basis,
                    const index_t patchIndex,
                    const gsOptionList & options, 
                    gsQuadRule<T>    & rule,
                    unsigned         & evFlags )
    {
        // Setup Quadrature
        rule = gsQuadrature::get(basis, options); // harmless slicing occurs here

        // Set Geometry evaluation flags
        evFlags = NEED_MEASURE|NEED_GRAD_TRANSFORM;
    }


    // Evaluate on element.
    inline void evaluate(gsBasis<T> const       & basis,
                         gsGeometryEvaluator<T> & geoEval,
                         // todo: add element here for efficiency
                         gsMatrix<T>            & quNodes)
    {
        // Compute the active basis functions
        // Assumes actives are the same for all quadrature points on the current element
        basis.active_into(quNodes.col(0) , actives);
        const index_t numActive = actives.rows();
 
        // Evaluate basis functions on element
        basis.deriv_into(quNodes, basisData);

        // Compute geometry related values
        geoEval.evaluateAt(quNodes);

        // Initialize local matrix
        localMat.setZero(numActive, numActive);
    }

    inline void assemble(gsDomainIterator<T>    & element, 
                         gsGeometryEvaluator<T> & geoEval,
                         gsVector<T> const      & quWeights)
    {
        for (index_t k = 0; k < quWeights.rows(); ++k) // loop over quadrature nodes
        {
            // Multiply quadrature weight by the geometry measure
            const T weight = quWeights[k] * geoEval.measure(k);
        
            // Compute physical gradients at k as a Dim x NumActive matrix
            geoEval.transformGradients(k, basisData, basisPhGrads);

            localMat.noalias() += weight * ( basisPhGrads.transpose() * basisPhGrads );
        }
    }

    //Inherited from gsVisitorMass
    //void localToGlobal( ... )

private:

    // Gradient values
    gsMatrix<T>  basisPhGrads;
    using Base:: basisData;
    using Base::actives;
    
    // Local matrix
    using Base::localMat;
};


} // namespace gismo

