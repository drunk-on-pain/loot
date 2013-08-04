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

#include <clp/option.h>
#include <clp/args.h>

namespace loot {
namespace clp {

option::option()
    : option(
            "",
            "",
            option_type::optional_option,
            value_constraint::unlimited_num_values,
            0,
            "")
{
}

option::option(const std::string& short_name, const std::string& long_name)
    : option(
            short_name,
            long_name,
            option_type::optional_option,
            value_constraint::unlimited_num_values,
            0,
            "")
{
}

option::option(
        const std::string& short_name,
        const std::string& long_name,
        option_type        type,
        value_constraint   constraint,
        unsigned int       num_expected_values,
        const std::string& description)
{
    this->short_name          = short_name;
    this->long_name           = long_name;
    this->type                = type;
    this->constraint          = constraint;
    this->num_expected_values = num_expected_values;
    this->description         = description;
}

option::option(const option& other)
{
    *this = other;
}

option::option(option&& temp)
{
    *this = std::move(temp);
}

option&
option::operator=(const option& other)
{
    short_name          = other.short_name;
    long_name           = other.long_name;
    type                = other.type;
    constraint          = other.constraint;
    num_expected_values = other.num_expected_values;
    description         = other.description;
    return *this;
}

option&
option::operator=(option&& temp)
{
    short_name          = std::move(temp.short_name);
    long_name           = std::move(temp.long_name);
    type                = temp.type;
    constraint          = temp.constraint;
    num_expected_values = temp.num_expected_values;
    description         = std::move(temp.description);
    return *this;
}

bool
option::operator==(const option& other) const
{
    return (short_name == other.short_name) && (long_name == other.long_name);
}

bool
option::operator<(const option& other) const
{
    return (short_name + long_name) < (other.short_name + other.long_name);
}

bool
option::is_name_known(const std::string& name) const
{
    return name.empty() ? false : (short_name == name || long_name == name);
}

} // namespace clp
} // namespace loot
