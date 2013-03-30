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

#include "parser.h"

namespace loot {
namespace clp {

parser::parser()
{
}

parser::parser(std::initializer_list<option> args)
{
    auto iter = std::begin(args);
    while (iter != std::end(args)) {
        add_option(*iter);
        iter++;
    }
}

bool
parser::add_option(const option& opt)
{
    auto iter = std::begin(options);
    while (iter != std::end(options)) {
        if (iter->first.is_name_known(opt.short_name)
              || iter->first.is_name_known(opt.long_name)) {
            return false;
        }
        ++iter;
    }

    options[opt] = std::make_pair(std::vector<std::string>(), false);
    return true;
}

bool
parser::add_option(option&& temp)
{
    auto iter = std::begin(options);
    while (iter != std::end(options)) {
        if (iter->first.is_name_known(temp.short_name)
              || iter->first.is_name_known(temp.long_name)) {
            return false;
        }
        ++iter;
    }

    options[std::move(temp)] = std::make_pair(std::vector<std::string>(), false);
    return true;
}

result
parser::parse(int argc, char* argv[])
{
    // First we'll evaluate the values. This not only checks the value requirements but
    // also makes notes about which option was found. This information is then used to
    // check the option requirement.
    result r = evaluate_values(argc, argv);

    opt_map::const_iterator iter = std::begin(options);
    while (iter != std::end(options)) {
        if (iter->first.short_name.empty() && iter->first.long_name.empty()) {
            r.errors.push_back(error(
                    iter->first,
                    requirement_error::option_has_no_names_error));
        }

        option_requirement req = iter->first.requirement;
        if (option_requirement::mandatory_option == req && !iter->second.second) {
            r.errors.push_back(error(
                    iter->first,
                    requirement_error::option_not_found_error));
        }
        iter++;
    }

    return r;
}

result
parser::evaluate_values(int argc, char* argv[])
{
    result result;

    auto iter = std::begin(options);
    while (iter != std::end(options)) {
        // Skip the application name => c = 1
        for (int c = 1; c < argc; c++) {
            std::string arg(argv[c]);

            int start = is_option(arg);
            if (0 == start) {
                continue;
            }

            // Found an option; Do we know it?
            if (!iter->first.is_name_known(arg.substr(start))) {
                continue;
            }

            // ...sure we know that option!
            iter->second.second = true;

            if (value_constraint::no_values == iter->first.constraint) {
                break; // No need to continue; finding the option is enough.
            }

            // Read all values according to the configuration. Unlimited is the amount
            // of args on the command line minus the position of the current option.
            int count = value_constraint::unlimited_num_values == iter->first.constraint
                    ? argc - c - 1
                    : iter->first.num_expected_values;
            unsigned int values_read = read(c, count, argv, iter->second.first);

            switch (iter->first.constraint) {
                case value_constraint::exact_num_values:
                    if (values_read != iter->first.num_expected_values) {
                        result.errors.push_back(error(
                        		iter->first,
                                requirement_error::not_enough_values_error));
                    }
                    break;

                case value_constraint::up_to_num_values:
                case value_constraint::unlimited_num_values:
                    if (0 == values_read) {
                        result.errors.push_back(error(
                        		iter->first,
                                requirement_error::not_enough_values_error));
                    }
                    break;

                default:
                    result.errors.push_back(error(
                    		iter->first,
                            requirement_error::invalid_value_constraint_error));
                    break;
            }

            // Stop the loop that scans the arguments, we've read what was needed for
            // this particular option.
            break;
        } // for (int c = 0; c < argc; c++)
        iter++;
    } // while (iter != options.end())

    return result;
}

unsigned int
parser::read(int start, int count, char* argv[], std::vector<std::string>& values) const
{
    // Counter starts at zero for easily counting the number of arguments read. To start
    // with the first value after the option we have to add start to get to the option
    // itself and one to jump to the first value behind that option.
    for (int c = 0; c < count; c++) {
        std::string arg(argv[c + 1 + start]);
        if (is_option(arg)) {
            return c;
        }

        values.push_back(arg);
    }

    // If an option interrupts the reading the number read up until the option is returned
    // in the loop. count always states that as many values have been read as were allowed
    // to be read. The real meaning of the return value is interpreted by the caller.
    return count;
}

int
parser::is_option(const std::string& arg) const
{
    // Test for double dash first as testing for single dash first would return
    // the wrong starting position if it were a double dash since a double dash
    // starts with a single dash.
    if (arg.substr(0, 2) == "--") {
        return 2;
    }
    else if (arg.substr(0, 1) == "-") {
        return 1;
    }

    return 0;
}

std::vector<std::string>
parser::values_from_option(const std::string& name) const
{
    auto iter = find_option(name);
    if (iter != std::end(options)) {
        // No need to check the bool if the option was actually found. If not, the
        // associated list is empty anyway.
        return iter->second.first;
    }

    return std::vector<std::string>();
}

bool
parser::has_option(const std::string& name) const
{
    return (find_option(name) != std::end(options));
}

parser::opt_map::const_iterator
parser::find_option(const std::string& name) const
{
    return std::find_if(
            std::begin(options),
            std::end(options),
            [&name](const opt_map::value_type& item) -> bool {
        return item.first.is_name_known(name) && item.second.second;
    });
}

} // namespace clp
} // namespace loot
