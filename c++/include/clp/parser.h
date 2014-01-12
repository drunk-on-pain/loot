/*
    Copyright (c) 2012, Robert Lohr
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    The views and conclusions contained in the software and documentation are those
    of the authors and should not be interpreted as representing official policies,
    either expressed or implied, of the FreeBSD Project.
*/

#ifndef PARSER_H
#define PARSER_H

#include "../config.h"
#include "option.h"
#include "result.h"

#include <map>
#include <vector>
#include <utility>
#include <ostream>
#include <initializer_list>

namespace loot {
namespace clp {


/*!
    Performs the task of parsing the command line while looking for any of the options
    specified.
*/
class LOOT_LIB_EXPORT parser
{
    typedef std::map<option, std::pair<std::vector<std::string>, bool>> opt_map;
public:
    /*!
        Creates an new `loot::clp::parser` with no associated `loot::clp::option` instances.
    */
    parser();

    /*!
        Creates a new `loot::clp::parser` with a list of `loot::clp::option` instances.
        Only available if the compiler support initializer_list syntax.

        @param[in] args
        List of options creates by the bracket initializer (`{}`).
     */
    #ifdef HAS_CXX11_INITIALIZER_LISTS
    parser(std::initializer_list<option> args);
    #endif

    /*!
        Add an `loot::clp::option` for validation and, in case values are expected, to have
        its values read.

        @param[in] opt
        The option to add. Only one option is retained. The criteria for finding
        duplicates is based on the short name and the long name. If either of those values
        is already bound to another option the new value is ignored.

        @return
        Returns `true` if the option is added or `false` otherwise.
    */
    bool add_option(const option& opt);

    /*!
        Add an `loot::clp::option` for validation and, in case values are expected, to have
        its values read.

        @param[in] temp
        Temporary option to add. Only one option is retained. The criteria for finding
        duplicates is based on the short name and the long name. If either of those values
        is already bound to another option the new value is ignored.

        @return
        Returns `true` if the option is added or `false` otherwise.
    */
    bool add_option(option&& temp);

    /*!
        Parses the command line with respect to `options`.

        @param[in] argc
        The number of arguments that can be found on the command line.

        @param[in] argv
        Pointer to the first element of an array of character string pointers
        which contains the whole command line.

        @return
        Returns a `loot::clp::result` which conveys whether the parsing finished with
        success or if an error occurred.
    */
    result parse(int argc, char* argv[]);

    /*!
        Query the parser for the values to a given option.

        @param[in] name
        Long or short name of the option for which values are queried (excluding the
        option switch [e.g. "--"]).

        @return
        Returns a list of values (if any). The values are in the order as specified on the
        command line. If the option cannot be found, has no values or
        `loot::clp::parser::parse(int &, char **)` has not been called before, an empty
        list is returned.
    */
    std::vector<std::string> values_from_option(const std::string& name) const;

    /*!
        Query the parser whether an option was found on the command line.

        @param[in] name
        Long or short name of the option (excluding the option switch [e.g. "-"]).

        @return
        Returns `true` if the option was found or `false` otherwise.
    */
    bool has_option(const std::string& name) const;
    
    /*!
        Print an abstract of the options added to the parser. This method is automatically
        invoked if an option with type `option_type::help_option` is detected.
        
        @param[in] out
        Output stream to write the help to.
     
        @param[in] newline
        Set to `true` to add a new line after each option creating more space between 
        them. Set to `false` to create a more condensed output.
    */
    void print_help(std::ostream& out, bool newline) const;

private:
    /*!
        Read values from the command line until another option is found or the number of
        values to read is reached.

        @param[in] start
        The index at which to start reading from the arguments array.

        @param[in] count
        The number of values that shall/can be read.

        @param[in] argv
        The arguments array as passed to main(...).

        @param[out]
        The values that are read are stored in this list.

        @return
        Return the number of values that have been read. This value is never
        negative.
    */
    unsigned int read(
    		int   start,
    		int   count,
    		char* argv[],
            std::vector<std::string> &values) const;

    /*!
        Tests whether an argument is to be seen as an option.

        @param[in] arg
        The argument that shall be tested. It is interpreted as an option if it starts
        with "`-`" or "`--`".

        @return
        If it is not an option zero (`0`) is returned. Otherwise the position at which the
        actual name of the option starts (eluding the hyphen[s]). This value is either one
        (`1`) or two (`2`).
    */
    int is_option(const std::string& arg) const;

    /*!
        Find an option either by its short or long name.

        @param[in] name
        The name of the option without the option switch.

        @return
        If the option was found on the command line a valid iterator is returned. If not
        then the iterator will point to the end of the `opt_map`.
    */
    opt_map::const_iterator find_option(const std::string& name) const;

    /**
        Reads all the values for the options provided and evaluates, whether the
        requirement of that option, regarding the values, is met.

        @param[in] argc
        The number of arguments that can be found on the command line. after parsing is
        done, this contains the number of remaining arguments.

        @param[in] argv
        Pointer to the first element of an array of character string pointers which
        contains the whole command line.

        @return
        Returns a list of errors that came up while reading and evaluating values.
    */
    result evaluate_values(int argc, char *argv[]);

    opt_map options;

};


} // namespace clp
} // namespace loot

#endif // PARSER_H
