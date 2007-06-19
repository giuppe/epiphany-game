/*=========================================================================*
                  cmdline.h  -  handle command line arguments
                             -------------------
    begin                : Sun Mar 17 2002
    copyright            : (C) 2002 by Christian Neise
    email                : C.Neise at users.sourceforge.net
 *=========================================================================*/

/*=========================================================================*
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as       *
 *   published by the Free Software Foundation; either version 2 of        *
 *   the License, or (at your option) any later version.                   *
 *                                                                         *
 *=========================================================================*/

#include <string>
#include <vector>
#include <sstream>

/* If you use gcc 3.2 or higher you may want to remove the comment below */
// #define USE_GCC_NEW_VERSION

#ifdef USE_GCC_NEW_VERSION
#include <ext/functional>
#else
#include <functional>
// if the compiler complains here, read the comment above
#endif

/*! \mainpage C++ Command Line Library
 *
 * This library provides a easy framework for parsing command lines.
 *
 * Homepage is: <a href="http://cmdl.sourceforge.net"><tt>http://cmdl.sourceforge.net</tt></a>.
 *
 * Author is: Christian Neise (cneise at users.sourceforge.net)
 */

/**
 Class CmdLine parses the command line for options and arguments.
 In CmdLineException is thrown in case of command line usage errors.
 @short Provides two classes for handling command line options and arguments (and errors).
 @author Christian Neise (cneise at users.sourceforge.net)
 @version Version 0.3
 */
namespace cmdl {


/**
 CmdLineExceptions are thrown in case of command line usage error.
 They are thrown when parsing the command line using
 Cmdline::GetSingleValue(), CmdLine::Call() or CmdLine::Done().
 @short handles command line usage errors.
 @see CmdLine
 */

class CmdLineException : public std::exception
{
   public:
   /*!
    *  Error codes used with a CmdLineException:
    * <ul>
    *  <li><b>unknown_option:</b>\n
    *      The option was not used in call of CmdLine::Call() or CmdLine::GetSingleValue().
    *      The exception is thrown in CmdLine::Done().
    *  <li><b>invalid_argument:</b>\n
    *      Conversion from argument (of <tt>const char *</tt>) to needed type failed.
    *  <li><b>too_many_arguments:</b>\n
    *      The command line option may only have one (resp. 0) arguments.
    *  <li><b>no_multiple_use:</b>\n
    *      The option may not be used multiple times.
    *  <li><b>argument_expected:</b>\n
    *      The option must have an argument.
    *  <li><b>option_expected:</b>\n
    *      The commandline must start with an option.
    *  </ul>
    */
      enum error_t
      {
         unknown_option = 0,
         invalid_argument = 1,
         too_many_arguments = 2,
         no_multiple_use = 3,
         argument_expected = 4,
         option_expected = 5
      };

      /**
       * Command line exceptions are usually thrown by members of class
       * CmdLine. If a user defined class is used with CmdLine::Call or
       * CmdLine::GetSingleValue, then the user defined
       * <tt>istream& operator >>(istream& in, your_class_t)</tt> may throw
       * a CmdLineException indicating an invalid argument.
       * However, it is recommended to set the istream's status instead:
       * in.clear( ios::failbit ). Then CmdLine's member functions will
       * throw the CmdLineException.
       */
      CmdLineException(const std::string& strOption, error_t nError)
            : m_strOption(strOption),  m_nError(nError) { /*empty*/}


       virtual ~CmdLineException() throw();
            
      /**
        @return code of the error occurred.
        @see error_t
        */
      error_t get_error_code() const { return m_nError; }

      /**
        @return the command line option the error occurred with.
        */
      const std::string& get_option(){ return m_strOption; }

      /**
       * Translates the error code (given in the constructor)
       * to an englisch error message. Informs the user which option
       * the error occured with.
       *
       * @return error message (in english).
       */
      virtual const char *what() const throw();

   private:
      /**
       * the command line option the error occurred with.
       */
      std::string m_strOption;
      /**
       * the error code.
       */
      error_t m_nError;
      /**
       * the error message constructed by what().
       */
      mutable std::string m_strError;
};








/**
 CmdLine provids a framework to extract values from the command line.
 User either GetSingleValue() to retrieve an argument given to an option.
 Or use Call() to map the usage of command line options and arguments
 (like "-h", "--help" or "--set-values 117 118") to function calls.
 @short parses the command line for options and arguments.
 @version Version 0.3
 @see CmdLineException
 */

class CmdLine
{
   public:
      /**
         These options are given to Call():

         cmdMultiple: allow multiple us of an option resp. multiple arguments for an option.

         Note, that the following command lines are equivalent:
         <pre>
         --set-ints 1 2 3
         --set-ints 1 --set-ints 2 --set-ints 3
         </pre>
         Both forms are allowed if option cmdMultiple is used with Call().
       */
      enum option_t
      {  cmdLineDefault = 0,
         cmdMultiple = 1
      };

      /**
         Command line options (like "--help" or "-R") start usually with c_option_char.
         Some developers may want to use '/' here.
      */
      CmdLine( char c_option_char = '-' );

      /**
         Initialize command the line parser.
         argc and argv are usually taken from <tt>main(int argc, char *argv[])</tt>.
         To skip the program name (the first element of argv),
         use: <tt>Init(--argc, ++argv)</tt>.
         If the first char-pointer found in argv is not an option
         (i.e. it does not start with m_c_option_char), a CmdLineException
         is thrown.

         Note: the strings found in argv are <i>not</i> copied. So argv must
               exist as long as the CmdLine object.
      */
      void Init(int argc, char *argv[]);

      /**
         Check if all options given at the command line
         were parsed. Unparsed options are unknown (i.e. unsused) options.
         Throws a CmdLineException, if such an option is found.
         Should be called after handling all options using GetSingleValue()
         or Call().
      */
      void Done();

      //
      // Retrieving single arguments given to command line options
      //

      /**
        Retrieve a single variable of type T given to command line option pszOpt.
        T may be any type an <tt>istream &operator <<(istream&, &T)</tt> exists for.
        If pszOpt was not used at the command line, tDest is not changed.
        If no or two or more arguments are used for the given option,
        then a CmdLineException is thrown.

         Example:
         If you call <tt>GetSingleValue("-s", myStringObj)</tt> then
         <ul>
         <li> the command line is: <tt>-s "a String"</tt> would set myStringObj to "a String".
         <li> any command line not using -s would leave myStringObj untouched.
         <li> when using multiple arguments for -s
              (like <tt>-s "first" "second"</tt>), then a CmdLineException is thrown.
         <li> the same applies for multiple use of option -s (like <tt>-s "first" -s "second"</tt>).
         </ul>

         Throws a CmdLineException in case of a command line error
         (i.e. using -s without an argument or with two or more arguments).

        @return true, if pszOpt was given at the command line, else false.
      */
      template <class T>
      bool GetSingleValue( const char* pszOpt, T& tDest)
      {
         const char *arg = getSingleArgForOption( pszOpt );
         if (arg)
         {
            transform( arg, tDest, pszOpt );
            return true;
         }
         else
            return false;
      }

       /**
        Set bDest to true if pszOpt was given at the command line,
        else do not modify bDest. Note that the option must not have an argument.
        @return true if options was used, else false.
      */
      bool GetSingleValue( const char* pszOpt, bool &bDest)
      {
         bool bOptionSet = OptionSetNoArgs( pszOpt );

         if ( OptionSetNoArgs( pszOpt ) )
             throw CmdLineException(pszOpt, CmdLineException::no_multiple_use);

         if (bOptionSet) bDest = true;

         return bOptionSet;
      }

      //
      // Calls a function if a option was given
      //

      /**
         Call a function of type void f() for the given command line option pszOpt.
         If used with option cmdMultiple, multiple calls to f() are done - one for
         each occurrence of pszOpt.
         Else multiple uses of pszOpt leads to throwing a CmdLineException.

         Example:<br>
         Commande line is: -h -h
         <pre>
         Call( "-h", PrintHelp)
                       => a CmdLineException is thrown
         Call( "-h", PrintHelp, cmdLineDefault)
                       => Print help twice
         </pre>
        @return number of occurences of pszOpt in the command line.
      */
      unsigned short Call( const char* pszOpt, void (*function)(), char options = cmdLineDefault)
      {
         unsigned short argc = 0;
         while (OptionSetNoArgs( pszOpt ))
         {
            function();
            ++argc;
            if ( !( options & cmdMultiple ) && OptionSetNoArgs( pszOpt ) )
                throw CmdLineException(pszOpt, CmdLineException::no_multiple_use);
         }
         return argc;
      }

      /**
         Call a function of type <tt>void f(const T&)</tt> for the given command line
         option pszOpt. T may be any type a <tt>istream &operator <<(istream&, &T)</tt>
         exists for.

         If used with option cmdMultiple multiple calls to f() are
         done - one for each argument of given to pszOpt.

         If pszOpt was given at the command line, this function
         creates a string object from pszOpts argument and
         calls f(string_object).

         If pszOpt is given more than once, then
         <ul>
         <li> by default a CmdLineException is thrown.
         <li> if options is set to cmdMultiple f(string_object) is called for each argument of pszOpt.
         </ul>

         Example:
            Command line:
            <pre>        -s Str1 Str2 -n 3 -s Str3                </pre>
            Calling:
            <pre>        Call("-s", MyStringFunction)</tt>        </pre>
            MyStringFunction would be called three time with
         arguments <tt>string(Str1)</tt>, <tt>string(Str2)</tt> and <tt>string(Str3)</tt>.
         @return number of command line arguments given to option pszOpt.
      */
      template <class T>
      unsigned short Call( const char *pszOpt, void (*function)(const T& strDest), char options = cmdLineDefault)
      {
         unsigned short argc=0;
         CharPtrList_t::iterator found = m_CharPtrList.begin();
         const char *arg=GetNextArgForOption(pszOpt, found);
         while ( arg )
         {
            T targ;
            transform<T>( arg, targ, pszOpt);
            function( targ );

            arg=GetNextArgForOption(pszOpt, found);
            ++argc;

            if ( arg && !( options & cmdMultiple ))
                throw CmdLineException(pszOpt, CmdLineException::too_many_arguments);
         }
         return argc;
      }

      /**
        * Calls a member function of the given object for each command line
        * argument of option pszOpt;
        * Example:
        * <pre>
        * typedef list<string> stringlist_t;
        * stringlist_t stringlist;
        * aCmdLineObj.Call("-add-to-list", stringlist, &stringlist_t::push_back, CmdLine::cmdMultiple);
        * </pre>
        */
      template <class C, class T>
      unsigned short Call( const char *pszOpt, C& object, void (C::*function)(const T& strDest), char options = cmdLineDefault)
      {
         unsigned short argc=0;
         CharPtrList_t::iterator found = m_CharPtrList.begin();
         const char *arg=GetNextArgForOption(pszOpt, found);
         while ( arg )
         {
            T targ;
            transform<T>( arg, targ, pszOpt);

#ifdef USE_GCC_NEW_VERSION
            __gnu_cxx::mem_fun1_ref( function )( object, targ );
#else                        
            mem_fun1_ref( function )( object, targ );
            // if the compiler complains here, read the comment at the top of this file
#endif            

            arg=GetNextArgForOption(pszOpt, found);
            ++argc;

            if ( arg && !( options & cmdMultiple ))
                throw CmdLineException(pszOpt, CmdLineException::too_many_arguments);
         }
         return argc;
      }


   private:
      /** A list of const char*
       */
      typedef std::vector <const char*> CharPtrList_t;

      /** Stores the complete commandline. Holds pointers to the
          command line options and arguments, but does not allocate
          memory for these pointers.
          @see Init()
       */
      CharPtrList_t m_CharPtrList;

      /** Command line options start with this character -
          usually '-' (unix) or '/' (windows).
          May be changed when calling the constructor.
       */
      char m_c_option_char;

      /** cast a const char* into a string
        */
      void transform( const char * from, std::string& to, const char * )
      {
          to = from;
      }

      /** cast a const char* into T using >>
        */
      template <class T>
      void transform( const char * from, T& to, const char * pszOpt)
      {
         std::string strValue( from );
         std::istringstream in(strValue);
         in >> to;
         if ( in.fail() || in.bad() || in.peek() > 0)
                throw CmdLineException(pszOpt, CmdLineException::invalid_argument);
      }

      /**
         Check if the given element of m_CharPtrList is an unhandled command line
         option (and not a handled option or an argument for an option).

         Note: Handled options are marked by setting to NULL.
         @return true if *it is an unhandled option, else false.
       */
      bool IsOption( CharPtrList_t::iterator it ){ return !*it || **it == m_c_option_char; }

      /** find the first argument for an option,
          mark the option and the argument as handled (by setting them to NULL).
          The iterator is set to the argument.
          If the option was used without an argument, a CmdLineException is thrown.
          @return char-Pointer to argument, it argument is found resp. NULL, if option was not used.
          @see CmdLineException
          */
      const char *FindFirstArgForOption( const char *pszOpt, CharPtrList_t::iterator &);

      /** returns non null if a next (first) arg for the given option was found
          */
      const char* GetNextArgForOption (const char *pszOpt, CharPtrList_t::iterator &);

      /** checks if the given option was set at the command line with no args.
          If so, marks the option as used.
          If the option was used with an argument, a CmdLineException is thrown.
          @return true, if the given option was used at the command line - else false.
          @see CmdLineException
          */
      bool OptionSetNoArgs(const char *pszOpt );

      /** Throws an exception if multiple or no arguments were found.
          @return pointer to a single argument for the given option.
          */
      const char *getSingleArgForOption( const char *pszOpt );
};




} // namespace cmdl
