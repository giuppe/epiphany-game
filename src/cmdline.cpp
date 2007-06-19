/***************************************************************************
                          cmdline.cpp  -  description
                             -------------------
    begin                : Mon Mar 18 2002
    copyright            : (C) 2002 by Christian Neise
    email                : CNeise at users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                               
 *   This program is free software; you can redistribute it and/or modify 
 *   it under the terms of the GNU  General Public License as      
 *   published by the Free Software Foundation; either version 2 of        
 *   the License, or (at your option) any later version.                 
 *                                                                         
 ***************************************************************************/



#include "cmdline.h"


#include <cstring>
#include <cassert>

#include <algorithm>

namespace cmdl
{
     struct option_equal : std::binary_function< const char *, const char *, bool>
      {
         bool operator() (const char *A, const char *B) const
         {
            if (!A || !B) return false; // handled options are never found
            return strcmp(A,B) == 0;
         }
      };
}


using namespace std;
using namespace cmdl;


CmdLineException::~CmdLineException() throw()
{}


const char *CmdLineException::what() const throw()
{
   if (m_strError.empty())
   {
      ostringstream err;
      err << "Command line error: ";
      switch (m_nError)
      {
         case unknown_option:
              err << "unknown command line option: \"" << m_strOption << "\""; break;
         case invalid_argument:
              err << "invalid argument for option \"" << m_strOption << "\"."; break;
         case too_many_arguments:
              err << "too many arguments for option \"" << m_strOption << "\"."; break;
         case no_multiple_use:
              err << "multiple use of option \"" << m_strOption << "\" not allowed."; break;
         case argument_expected:
              err << "argument expected for option \"" << m_strOption << "\"."; break;
         case option_expected:
              err << "expected command line option, but found \"" << m_strOption << "\"."; break;
         default: err << "unknown error using option \"" << m_strOption << "\".";
      }
      m_strError = err.str();
   }
   return m_strError.c_str();
}



CmdLine::CmdLine( char c_option_char )
           : m_c_option_char(c_option_char)
{ /*empty*/ }


void CmdLine::Init( int argc, char *argv[])
{
   m_CharPtrList.clear();
   m_CharPtrList.reserve(argc);

   // the command line must start with an option
   if ( argc && **argv != m_c_option_char )
      throw CmdLineException(*argv, CmdLineException::option_expected);

   // copy pointers to command line arguments into ChrPtrList
   while (argc--)
   {
      m_CharPtrList.push_back( *argv );
      argv++;
      // i wonder why this does not work, when building the release version
      // (using gcc  2.95.3 on SuSE Linux 7.3):
      //  m_CharPtrList.push_back( *argv++);
   }

}


const char *CmdLine::getSingleArgForOption( const char *pOpt )
{
   // find first argument for option pOpt
   CharPtrList_t::iterator found = m_CharPtrList.begin();
   const char * return_value = FindFirstArgForOption( pOpt, found);

   // was the option used?
   if (return_value == NULL)
      return NULL; // no

   assert( found != m_CharPtrList.end());

   // is the first argument the only argument?
   if ( ++found != m_CharPtrList.end() && !IsOption(found))
       throw CmdLineException(pOpt, CmdLineException::too_many_arguments);

   // does the same option occur once more?
   if (m_CharPtrList.end() != find_if( found,
                                       m_CharPtrList.end(),
                                       bind1st( option_equal(), pOpt ) ) )
       throw CmdLineException(pOpt, CmdLineException::no_multiple_use);

   return return_value;
}


bool CmdLine::OptionSetNoArgs(const char *pOpt )
{
   CharPtrList_t::iterator found = find_if( m_CharPtrList.begin(),
                                            m_CharPtrList.end(),
                                            bind1st( option_equal(), pOpt ) );
   if (found == m_CharPtrList.end())
      return false; // pOpt not set
   else
   {
      // mark option as used
      *found = NULL;

      // check if argument given
      if (++found != m_CharPtrList.end() && !IsOption(found))
         throw CmdLineException(pOpt, CmdLineException::too_many_arguments);

      return true; // pOpt was set
   }
}


//
// Find the first argument for an option.
//
// Example: Assume pOpt points to "-S":
//          testprog -S 1 2 --another-option -S 3
//                      ^ return value
const char *CmdLine::FindFirstArgForOption( const char *pOpt, CharPtrList_t::iterator &found)
{
   found = find_if( found,
                    m_CharPtrList.end(),
                    bind1st( option_equal(), pOpt ) );

   // check if option was found
   if ( found == m_CharPtrList.end())
      return NULL; // no, not found

   // mark option as handled / switch to argument-candidate
   *found++ = NULL;

   // is the argument-candidate really an argument?
   if ( found == m_CharPtrList.end() ||  IsOption( found ) )
   { // No
      throw CmdLineException(pOpt, CmdLineException::argument_expected);
   }

   const char * return_value = *found;

   // mark argument as handeld
   *found = NULL;

   return return_value;
}

// Find the first resp. next argument for an option
//
// in this function this two cases are handled
// A) testprog -S   1    --another-option -S 2
//             NULL NULL
// B) testprog -S   1    2
//             NULL NULL
//
// Note: FindFirstArgForOption was called befor and the iterator found
//       points to char-pointer, which was the former pointer to "1".
//       Note also, that the char-pointers to "-S" and to "1" have been set to NULL.
const char* CmdLine::GetNextArgForOption (const char *pOpt, CharPtrList_t::iterator &found)
{
   if (found == m_CharPtrList.end())
      return NULL;

   if ( *found && IsOption(found))
   {  // (possibly) case A)
      return FindFirstArgForOption( pOpt, found);
   }
   else
   {
      if (++found != m_CharPtrList.end())
      {
         if (!IsOption(found))
         {  // case B)
            const char* return_value = *found;
            *found = NULL;
            return return_value;
         }
         else
         {  // (possibly) case A)
            return FindFirstArgForOption( pOpt, found );
         }
      }
      else
         return NULL;
   }
}

void CmdLine::Done()
{
// check for unknown options,
// i.e. check for *unused* options (which are not set to NULL)

   CharPtrList_t::iterator unused = find_if( m_CharPtrList.begin(),
                                             m_CharPtrList.end(),
                                             bind2nd(not_equal_to<const char*>(), 0));
   if (unused != m_CharPtrList.end())
      throw CmdLineException(*unused, CmdLineException::unknown_option);
}



