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

#include "error.h"

namespace sd {
namespace args {

error::error()
{
    reason = unspecified_error;
}

error::error(const option& opt, requirement_error reason)
{
    this->opt    = opt;
    this->reason = reason;
}

error::error(const error& other)
{
    *this = other;
}

error::error(error&& temp)
{
    *this = std::move(temp);
}

error&
error::operator =(const error& other)
{
    opt    = other.opt;
    reason = other.reason;
    return *this;
}

error&
error::operator =(error&& temp)
{
    opt    = std::move(temp.opt);
    reason = temp.reason;
    return *this;
}

} // namespace sd
} // namespace args
