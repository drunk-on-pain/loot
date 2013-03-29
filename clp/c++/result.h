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

#ifndef RESULT_H
#define RESULT_H

#include "error.h"

#include <vector>

namespace sd {
namespace args {


/*!
    `sd::args::result` is the result to a call of `sd::args::parser::parse(int, char**)`.
    It resembles the result of the parsing and in case of errors it contains all the
    `sd:.args::option` instances that failed the validation and why they failed, thus
    client code can easily figure out which option(s) caused the error and provide quality
    messages to users.
*/
class result
{
public:
    /*!
        Contains all the errors and associated miserable options instances that failed
        validation for inspection by client code. The options are inside an instance
        of `sd::args::error` which also contains a reason for the error.
    */
    std::vector<error> errors;

    /*!
        Default constructor.
    */
    result();

    /*!
        Copy-constructor.

        @param[in] other
        Source instance to copy values from.
    */
    result(const result& other);

    /*!
        Move-constructor.

        @param[in] temp
        Temporary instance to move values from.
    */
    result(result&& temp);

    /*!
        Assignment-operator.

        @param[in] other
        Source instance to copy values from.

        @return
        Returns the current instance that is now a copy of `other`.
    */
    result& operator=(const result& other);

    /*!
        Move-assignment-operator.

        @param[in] temp
        Temporary instance to move values from.

        @return
        Returns the current instance that is now a copy of `temp`.
    */
    result& operator=(result&& temp);

    /*!
        Convenience method which states whether the parsing was successful or drew up
        violations against the option requirements. One could als call `errors.size()` and
        check for a zero return value (or similar).

        @return
        Returns `true` if no violations were found or `false` if parsing found errors.
        Errors can be evaluated by iterating the `errors` member.
    */
    bool good() const;

};


} // namespace args
} // namespace sd

#endif // RESULT_H
