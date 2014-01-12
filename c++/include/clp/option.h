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

#ifndef OPTION_H
#define OPTION_H

#include "../config.h"
#include "args.h"

#include <string>

namespace loot {
namespace clp {
        

/*!
    A `loot::clp::option` represents one argument on the command line. An argument is
    anything starting with a single hyphen ("-"), which is the short version of the option
    or a double-hyphen ("--") for the long version. As indicated, each option can contain
    a short and a long name, without the need for both being given at the same time. 
    Options may also require the presence of values but may also go without. The number of 
    values is very flexible, from an exact number of values to an unlimited number of 
    values to "up-to but no exact match necessary".
*/
class LOOT_LIB_EXPORT option
{
public:
    /*!
        Create a new option with default values. This means:

        - No short and long name
        - Unlimited number of values expected
        - Option is not mandatory

        Not specifying any name afterwards will result in
        `loot::clp::option_has_no_names_error`.
    */
    option();
    
    /*!
        Create a new option with a short and a long name. Defaults for values are as
        follows:

        - Unlimited number of values expected
        - Option is not mandatory

        This method is only available if the comiler supports delegating constructors.
        
        @param[in] short_name
        Short name for this option.
        
        @param[in] long_name
        Long name for this option.
    */
    #ifdef HAS_CXX11_DELEG_CONSTRUCTOR
    option(const std::string& short_name, const std::string& long_name);
    #endif

    /*!
        Create a new option by specifying all available values.
        
        @param[in] short_name
        Short name for this option.
        
        @param[in] long_name
        Long name for this option.

        @param[in] type
        Defines whether this option is mandatory or optional or some special type.
        
        @param[in] constraint
        Defines if there are any values expected for this option and how to interpret
        `num_expected_values`.

        @param[in] num_expected_values
        The number of values that are exected for this option to be provided on the
        command line. Interpretation depends on the value of `constraint`.
     
        @param[in] description
        User defined description that is displayed when printing the list of options.
    */
    option(
            const std::string& short_name,
            const std::string& long_name,
            option_type        type,
            value_constraint   constraint,
            unsigned int       num_expected_values,
            const std::string& description);
    
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
        `loot::clp::unlimited_num_ values` or `loot::clp::no_values` is specified as
        `constraint` then this value is ignored.
    */
    unsigned int num_expected_values;
    
    /*!
        Defines if there are any values expected for this option and how to interpret
        `num_expected_values`.
    */
    value_constraint constraint;
    
    /*!
        Defines how to treat this option when it comes to parsing.
    */
    option_type type;
    
    /*!
        User defined description that is displayed when printing the list of options.
    */
    std::string description;

};

} // namespace clp
} // namespace loot

#endif // option_H
