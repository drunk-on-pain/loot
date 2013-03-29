/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef PARSER_H
#define PARSER_H

#include "option.h"
#include "result.h"

#include <map>
#include <vector>
#include <utility>
#include <initializer_list>

namespace sd {
namespace args {


/*!
    Performs the task of parsing the command line while looking for any of the options
    specified.
*/
class parser
{
    typedef std::map<option, std::pair<std::vector<std::string>, bool>> opt_map;
public:
    /*!
        Creates an new `sd::args::parser` with no associated `sd::args::option` instances.
    */
    parser();

    /*!
        Creates a new `sd::args::parser` with a list of `sd::args::option` instances.

        @param[in] args
        List of options creates by the bracket initializer (`{}`).
     */
    parser(std::initializer_list<option> args);

    /*!
        Add an `sd::args::option` for validation and, in case values are expected, to have
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
        Add an `sd::args::option` for validation and, in case values are expected, to have
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
        Returns a `sd::args::result` which conveys whether the parsing finished with
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
        `sd::args::parser::parse(int &, char **)` has not been called before, an empty
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


} // namespace args
} // namespace sd

#endif // PARSER_H
