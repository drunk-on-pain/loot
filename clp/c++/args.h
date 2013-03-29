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

/*!
    \file
*/

#ifndef ARGS_H
#define ARGS_H

namespace sd {
namespace args {

/*!
    Defines constants which describe how many values are to be expected for one 
    `sd::args::option`.
*/
enum value_constraint
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
enum option_requirement
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
enum requirement_error
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
        Invalid `value_constraint` specified.
    */
    invalid_value_constraint_error
};


} // namespace args
} // namespace sd

#endif // ARGS_H
