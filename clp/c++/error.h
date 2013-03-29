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

#ifndef ERROR_H
#define ERROR_H

#include "args.h"
#include "option.h"

namespace sd {
namespace args {


/*!
    Used to indicate a validation error for one option. Instances of this class are
    created by `sd::args::result` containing a copy of the `sd::args::option` that failed
    and an associated error reason.
*/
class error
{
public:
    /*!
        Default-constructor. Create an empty instance with a `sd::args::unspecified_error`
        error type.
    */
    error();

    /*!
        Create a new error instance with an option and a reason.

        @param[in] opt
        The option which is the reason for an error.

        @param[in] reason
        One of the predefined error reasons that describe why the option failed
        validation.
    */
    error(const option& opt, requirement_error reason);

    /*!
        Copy-constructor.

        @param[in] other
        Source instance to copy values from.
    */
    error(const error& other);

    /*!
        Move-constructor.

        @param[in] temp
        Temporary instance to move values from.
    */
    error(error&& temp);

    /*!
        Assignment-operator.

        @param[in] other
        Source instance to copy values from.

        @return
        Returns the current instance that is now a copy of `other`.
    */
    error& operator=(const error& other);

    /*!
        Move-assignment-operator.

        @param[in] temp
        Temporary instance to move values from.

        @return
        Returns the current instance that is now a copy of `temp`.
    */
    error& operator=(error&& temp);

    /*!
        Copy of the option for which the requirements are not met by the command line
        parameters, thus causing an error.
    */
    option opt;

    /*!
        Reason why the option failed the validation test.
    */
    requirement_error reason;

};


} // namespace Args
} // namespace Sundown

#endif // ERROR_H
