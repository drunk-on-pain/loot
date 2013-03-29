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

#ifndef OPTION_H
#define OPTION_H

#include "args.h"

#include <string>

namespace sd {
namespace args {
        

/*!
    A `sd::args::option` represents one argument on the command line. An argument is
    anything starting with a single hyphen ("-"), which is the short version of the option
    or a double-hyphen ("--") for the long version. As indicated, each option can contain
    a short and a long name, without the need for both being given at the same time. 
    Options may also require the presence of values but may also go without. The number of 
    values is very flexible, from an exact number of values to an unlimited number of 
    values to "up-to but no exact match necessary".
*/
class option
{
public:
    /*!
        Create a new option with default values. This means:

        - No short and long name
        - Unlimited number of values expected
        - Option is not mandatory

        Not specifying any name afterwards will result in
        `sd::args::option_has_no_names_error`.
    */
    option();
    
    /*!
        Create a new option with a short and a long name. Defaults for values are as
        follows:

        - Unlimited number of values expected
        - Option is not mandatory
        
        @param[in] short_name
        Short name for this option.
        
        @param[in] long_name
        Long name for this option.
    */
    option(const std::string& short_name, const std::string& long_name);
    
    /*!
        Create a new option by specifying all available values.
        
        @param[in] short_name
        Short name for this option.
        
        @param[in] long_name
        Long name for this option.

        @param[in] requirement
        Defines whether this option is mandatory or optional.
        
        @param[in] constraint
        Defines if there are any values expected for this option and how to interpret
        `num_expected_values`.

        @param[in] num_expected_values
        The number of values that are exected for this option to be provided on the
        command line. Interpretation depends on the value of `constraint`.
    */
    option(
            const std::string& short_name,
            const std::string& long_name,
            option_requirement requirement,
            value_constraint   constraint,
            unsigned int       num_expected_values);
    
    /*!
        Copy-constructor.
        
        @param[in] other
        Source instance to copy values from.
    */
    option(const option& other);
    
    /*!
        Move-constructor.

        @param[in] temp
        Temporary instance to move values from.
    */
    option(option&& other);

    /*!
        Assignment-operator.
        
        @param[in] other
        Source instance to copy values from.
        
        @return
        Returns the current instance that is now a copy of `other`.
    */
    option& operator=(const option& other);

    /*!
        Move-assignment-operator.

        @param[in] temp
        Temporary instance to move values from.

        @return
        Returns the current instance that is now a copy of `temp`.
    */
    option& operator=(option&& temp);
    
    /*!
        Comparison operator
        
        @param[in] other
        Other instance to compare against.
        
        @return
        Returns `true` if all values of both option instances match or `false` otherwise.
    */
    bool operator==(const option& other) const;
    
    /* !
		Lesser operator

		@param[in] other
		Other option to compare against.

		@return
		Returns \c true if the current values are lesser than the values of \c other.
    */
    bool operator<(const option& other) const;

    /*!
        Tests whether the provided value is known as short name or long name.
        
        @param[in] name
        The name to test (excluding the option switch [e.g. "-"]).
        
        @return
        Returns `true` if the name is known either as short name or long name. Returns
        `false` otherwise.
    */
    bool is_name_known(const std::string& name) const;
    
    /*!
        The short name of the option.
    */
    std::string short_name;
    
    /*!
        The long name of the option.
    */
    std::string long_name;
    
    /*!
        Specifies the number of values that are expected for this option. If 
        `sd::args::unlimited_num_ values` or `sd::args::no_values` is specified as
        `constraint` then this value is ignored.
    */
    unsigned int num_expected_values;
    
    /*!
        Defines if there are any values expected for this option and how to interpret
        `num_expected_values`.
    */
    value_constraint constraint;
    
    /*!
        Defines how to treat this option when it comes to being mandatory or optional.
    */
    option_requirement requirement;

};

} // namespace args
} // namespace sd

#endif // option_H
