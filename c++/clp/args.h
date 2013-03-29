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

/*!
    \file
*/

#ifndef ARGS_H
#define ARGS_H

namespace loot {
namespace clp {

/*!
    Defines constants which describe how many values are to be expected for one 
    `loot::clp::option`.
*/
enum class value_constraint
{
    /*!
        The number of values provided must match exactly the number expected.
    */
    exact_num_values = 1,
    /*!
        The number of values provided must at least be one and can be any number up to a
        maximum of n.
    */
    up_to_num_values,
    /*!
        The number of values provided is only limited by the number the operating system
        can handle but must at least be one.
    */
    unlimited_num_values,
    /*!
        No values are expected for an option.
    */
    no_values
};

/*!
    Defines constants which describe how options are expected to appear on the command
    line.
*/
enum class option_requirement
{
    /*!
        The option must be present.
    */
    mandatory_option = 1,
    /*!
        The option may be present but does not have to be.
    */
    optional_option
};

/*!
    Defines constants which describe the reason why an option failed the validation test.
*/
enum class requirement_error
{
    /*!
        Can be used as a default value indicating an uninitialized state.
    */
    unspecified_error = 0,
    /*!
        Option has not been found on the command line.
    */
    option_not_found_error,
    /*!
        Not enough values found for the given option.
    */
    not_enough_values_error,
    /*!
        The option has not been given a name when it was created.
    */
    option_has_no_names_error,
    /*!
        Invalid `loot::clp::value_constraint` specified.
    */
    invalid_value_constraint_error
};


} // namespace clp
} // namespace loot

#endif // ARGS_H
