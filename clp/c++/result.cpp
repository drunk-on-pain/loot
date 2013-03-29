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

#include "result.h"

namespace sd {
namespace args {

result::result()
{
}

result::result(const result& other)
{
    *this = other;
}

result::result(result&& temp)
{
    *this = std::move(temp);
}

result&
result::operator =(const result& other)
{
    errors = other.errors;
    return *this;
}

result&
result::operator =(result&& temp)
{
    errors = std::move(temp.errors);
    return *this;
}

bool
result::good() const
{
    return errors.empty();
}

} // namespace sd
} // namespace args
