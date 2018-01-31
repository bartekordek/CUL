#include "CUL/ListFactory.hpp"

using namespace CUL;

void someFunction()
{
    ListVector<int> someVector;
    someVector.pushBack( 2 );

    //auto ptr = CUL::ListFactory::createVectorListPtr<double>();
    auto ptr = std::unique_ptr<CUL::IList<double>>( CUL::ListFactory::createVectorListPtr<double>() );
    ptr->find( 0 );
   // auto result1 = std::make_unique<CUL::IList<double>>( ptr );


    //std::unique_ptr<CUL::IList<double>> result2( ptr );
}