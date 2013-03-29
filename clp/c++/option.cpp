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

#include "option.h"
#include "args.h"

namespace sd { 
namespace args {

option::option()
    : option("", "", optional_option, unlimited_num_values, 0)
{
}

option::option(const std::string& short_name, const std::string& long_name)
    : option(short_name, long_name, optional_option, unlimited_num_values, 0)
{
}

option::option(
        const std::string& short_name,
        const std::string& long_name,
        option_requirement requirement,
        value_constraint   constraint,
        unsigned int       num_expected_values)
{
    this->short_name          = short_name;
    this->long_name           = long_name;
    this->requirement         = requirement;
    this->constraint          = constraint;
    this->num_expected_values = num_expected_values;
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
    requirement         = other.requirement;
    constraint          = other.constraint;
    num_expected_values = other.num_expected_values;
    return *this;
}

option&
option::operator=(option&& temp)
{
    short_name          = std::move(temp.short_name);
    long_name           = std::move(temp.long_name);
    requirement         = temp.requirement;
    constraint          = temp.constraint;
    num_expected_values = temp.num_expected_values;
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
    return (short_name == name || long_name == name);
}

} // namespace Sundown
} // namespace Args
