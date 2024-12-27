#include "CUL/Filesystem/PathDialog.hpp"
#include "Filesystem/IMPORT_nfd.hpp"

using namespace CUL;
using namespace FS;

PathDialog& PathDialog::getInstance()
{
    static PathDialog s_instance;
    return s_instance;
}

PathDialog::PathDialog()
{
    NFD_Init();
}

CUL::String PathDialog::pickFolder()
{
    CUL::String resultPath;

    nfdchar_t* outPath{nullptr};
    // Unused for now.
    // nfdfilteritem_t filterItem = {};
    nfdresult_t result = NFD_PickFolder(&outPath, nullptr);
    if(result == NFD_OKAY)
    {
        resultPath = outPath;
    }
    else if(result == NFD_CANCEL)
    {
    }
    else
    {
    }

    if(outPath)
    {
        NFD_FreePath(outPath);
    }

    return resultPath;
}

CUL::String PathDialog::saveDialog(const Filter& inFilter)
{
    CUL::String resultPath;
    nfdfilteritem_t filter;
    filter.name = inFilter.Name.getChar();
    filter.spec = inFilter.Spec.getChar();

    nfdchar_t* outPath{nullptr};
    nfdresult_t result = NFD_SaveDialog(&outPath, &filter, 1, nullptr, nullptr);
    if(result == NFD_OKAY)
    {
        resultPath = outPath;
    }
    else if(result == NFD_CANCEL)
    {
    }
    else
    {
    }

    if (outPath)
    {
        NFD_FreePath(outPath);
    }

    return resultPath;
}

CUL::String PathDialog::openDialog( const Filter& inFilter )
{
    CUL::String resultPath;
    nfdfilteritem_t filter;
    filter.name = inFilter.Name.getChar();
    filter.spec = inFilter.Spec.getChar();

    nfdchar_t* outPath{ nullptr };
    nfdresult_t result = NFD_OpenDialog( &outPath, &filter, 1, nullptr );
    if( result == NFD_OKAY )
    {
        resultPath = outPath;
    }
    else if( result == NFD_CANCEL )
    {
    }
    else
    {
    }

    if( outPath )
    {
        NFD_FreePath( outPath );
    }

    return resultPath;
}

PathDialog::~PathDialog()
{
    NFD_Quit();
}