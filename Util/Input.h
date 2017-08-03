#pragma once
#include <kvs/CommandLine>
#include <kvs/Indent>
#include <iostream>


class Input
{
private:
    kvs::CommandLine m_commandline;

public:
    int repeats; ///< number of repetitions
    int dims; ///< dimensions

    Input( int argc, char** argv ):
        repeats(1),
        dims(32)
    {
        m_commandline = kvs::CommandLine( argc, argv );
        m_commandline.addHelpOption();
        m_commandline.addOption( "repeats","Number of repetitions (default: 1).", 1, false );
        m_commandline.addOption( "dims","Dimensions (default: 32).", 1, false );
    }

    bool parse()
    {
        if ( !m_commandline.parse() ) { return false; }
        if ( m_commandline.hasOption("repeats") ) repeats = m_commandline.optionValue<int>("repeats");
        if ( m_commandline.hasOption("dims") ) dims = m_commandline.optionValue<int>("dims");
        return true;
    }

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const
    {
        os << indent << "Number of repetitions : " << repeats << std::endl;
        os << indent << "Dimensions : " << dims << std::endl;
    }
};
