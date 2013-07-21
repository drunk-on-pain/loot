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

#ifndef RESULT_H
#define RESULT_H

#include "error.h"

#include <vector>

namespace loot {
namespace clp {


/*!
    `loot::clp::result` is the result to a call of `loot::clp::parser::parse(int, char**)`.
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
        of `loot::clp::error` which also contains a reason for the error.
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


} // namespace clp
} // namespace loot

#endif // RESULT_H
