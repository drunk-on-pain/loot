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

#ifndef ERROR_H
#define ERROR_H

#include "args.h"
#include "option.h"

namespace loot {
namespace clp {


/*!
    Used to indicate a validation error for one option. Instances of this class are
    created by `loot::clp::result` containing a copy of the `loot::clp::option` that
    failed and an associated error reason.
*/
class error
{
public:
    /*!
        Default-constructor. Create an empty instance with a `loot::clp::unspecified_error`
        error type.
    */
    error();

    /*!
        Create a new error instance with an option and a reason.

        @param[in] opt
        The option which caused an error.

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


} // namespace clp
} // namespace loot

#endif // ERROR_H
