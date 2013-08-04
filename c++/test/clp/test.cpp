/*
    Copyright (C) 2012  Robert Lohr

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

#include <clp/args.h>
#include <clp/error.h>
#include <clp/option.h>
#include <clp/parser.h>

#include <gtest/gtest.h>

#include <ostream>
#include <sstream>

using namespace loot::clp;


TEST(ArgsTest, OneMandatoryArgNoValue)
{
    option o("s", "long");
    o.constraint  = value_constraint::no_values;
    o.type        = option_type::mandatory_option;
    
    char *argv[2] = {(char*)"ignored", (char*)"-s"};
    
    parser p;
    p.add_option(o);
    
    result r = p.parse(2, argv);

    EXPECT_EQ(r.errors.size(), 0);
    EXPECT_EQ(p.has_option("s"), true);
}

TEST(ArgsTest, OneOptionalArgNoValue)
{
    option o("s", "long");
    o.constraint  = value_constraint::no_values;
    o.type        = option_type::optional_option;

    char *argv[2] = {(char*)"ignored", (char*)"--not-required"};

    parser p;
    p.add_option(o);

    result r = p.parse(2, argv);

    EXPECT_EQ(r.errors.size(), 0);
    EXPECT_EQ(p.has_option("s"), false);
}

TEST(ArgsTest, MultipleOptionsInitializerList)
{
    char *argv[4] = {
            (char*)"ignored",
            (char*)"--not-required",
            (char*)"-s",
            (char*)"--fun"};

    parser p = { option("s", "long"), option("f", "fun") };
    result r = p.parse(4, argv);

    // Default is unlimited number of values. Our fake command line only supplies options
    // and an application name
    EXPECT_EQ(r.errors.size(), 2);
    EXPECT_EQ(p.has_option("s"), true);
    EXPECT_EQ(p.has_option("f"), true);
    EXPECT_EQ(p.has_option("fun"), true);
    EXPECT_EQ(p.has_option("sunshine"), false);
}

TEST(ArgsTest, ExactlyOneValue)
{
    char *argv[4] = {
            (char*)"ignored",
            (char*)"-s",
            (char*)"CoolValue",
            (char*)"IgnoredValue"};
    parser p = { option(
            "s",
            "long",
            option_type::mandatory_option,
            value_constraint::exact_num_values,
            1,
            "") };
    result r = p.parse(4, argv);

    EXPECT_EQ(r.good(), true);
    EXPECT_EQ(p.has_option("s"), true);
    EXPECT_EQ(p.values_from_option("s").at(0), "CoolValue");
    EXPECT_EQ(p.values_from_option("long").at(0), "CoolValue");
}

TEST(ArgsTest, TwoValues)
{
    char *argv[5] = {
            (char*)"ignored",
            (char*)"-s",
            (char*)"FirstValue",
            (char*)"SecondValue",
            (char*)"IgnoredValue"};
    parser p = { option(
            "s",
            "long",
            option_type::mandatory_option,
            value_constraint::exact_num_values,
            2,
            "") };
    result r = p.parse(5, argv);

    EXPECT_EQ(r.good(), true);
    EXPECT_EQ(p.has_option("s"), true);

    std::vector<std::string> values = p.values_from_option("s");
    EXPECT_EQ(values.empty(), false);
    EXPECT_EQ(values.size(), 2);
    EXPECT_EQ(values.at(0), "FirstValue");
    EXPECT_EQ(values.at(1), "SecondValue");
}

TEST(ArgsTest, UnlimitedValuesDelimitedByOption)
{
    char *argv[6] = {
            (char*)"ignored",
            (char*)"-s",
            (char*)"FirstValue",
            (char*)"SecondValue",
            (char*)"ThirdValue",
            (char*)"--some-option"};
    parser p = { option(
            "s",
            "long",
            option_type::mandatory_option,
            value_constraint::unlimited_num_values,
            2,
            "") };
    result r = p.parse(6, argv);

    EXPECT_EQ(r.good(), true);
    EXPECT_EQ(p.has_option("s"), true);

    std::vector<std::string> values = p.values_from_option("s");
    EXPECT_EQ(values.empty(), false);
    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values.at(0), "FirstValue");
    EXPECT_EQ(values.at(1), "SecondValue");
    EXPECT_EQ(values.at(2), "ThirdValue");
}

TEST(ArgsTest, UnlimitedValuesDelimitedByEnd)
{
    char *argv[5] = {
            (char*)"ignored",
            (char*)"-s",
            (char*)"FirstValue",
            (char*)"SecondValue",
            (char*)"ThirdValue"};
    parser p = { option(
            "s",
            "long",
            option_type::mandatory_option,
            value_constraint::unlimited_num_values,
            2,
            "") };
    result r = p.parse(5, argv);

    EXPECT_EQ(r.good(), true);
    EXPECT_EQ(p.has_option("s"), true);

    std::vector<std::string> values = p.values_from_option("s");
    EXPECT_EQ(values.empty(), false);
    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values.at(0), "FirstValue");
    EXPECT_EQ(values.at(1), "SecondValue");
    EXPECT_EQ(values.at(2), "ThirdValue");
}

TEST(ArgsTest, UnlimitedButno_values)
{
    char *argv[2] = {
            (char*)"ignored",
            (char*)"-s"};
    parser p = { option(
            "s",
            "long",
            option_type::mandatory_option,
            value_constraint::unlimited_num_values,
            2,
            "") };
    result r = p.parse(2, argv);

    EXPECT_EQ(r.good(), false);
    EXPECT_EQ(p.has_option("s"), true);

    std::vector<std::string> values = p.values_from_option("s");
    EXPECT_EQ(values.empty(), true);
}

TEST(ArgsTest, TwoOptionsOneUnlimitedErrorOneno_values)
{
    char *argv[3] = {
            (char*)"ignored",
            (char*)"-s",
            (char*)"--no-values"};
    parser p = {
            option( "s",
                    "long",
                    option_type::mandatory_option,
                    value_constraint::unlimited_num_values,
                    2,
                    ""),
            option( "n",
                    "no-values",
                    option_type::mandatory_option,
                    value_constraint::no_values,
                    0,
                    "")};
    result r = p.parse(3, argv);

    EXPECT_EQ(r.good(), false);
    EXPECT_EQ(r.errors.size(), 1);
    EXPECT_EQ(r.errors.at(0).opt.short_name, "s");

    EXPECT_EQ(p.has_option("no-values"), true);

    std::vector<std::string> values = p.values_from_option("no-values");
    EXPECT_EQ(values.empty(), true);
}

TEST(ArgsTest, ManyOptions)
{
    char *argv[9] = {
            (char*)"ignored",
            (char*)"--ip",
            (char*)"192.168.0.1",
            (char*)"-p",
            (char*)"1234",
            (char*)"-f",
            (char*)"file1.txt",
            (char*)"file2.txt",
            (char*)"file3.txt"};
    parser p = {
            option( "i",
                    "ip",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    ""),
            option( "p",
                    "port",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    ""),
            option("f", "files") };
    result r = p.parse(9, argv);

    EXPECT_EQ(r.good(), true);

    EXPECT_EQ(p.has_option("i"), true);
    EXPECT_EQ(p.has_option("ip"), true);
    std::vector<std::string> values = p.values_from_option("i");
    EXPECT_EQ(values.size(), 1);
    EXPECT_EQ(values.at(0), "192.168.0.1");

    EXPECT_EQ(p.has_option("p"), true);
    EXPECT_EQ(p.has_option("port"), true);
    values = p.values_from_option("port");
    EXPECT_EQ(values.size(), 1);
    EXPECT_EQ(values.at(0), "1234");

    EXPECT_EQ(p.has_option("f"), true);
    EXPECT_EQ(p.has_option("files"), true);
    values = p.values_from_option("files");
    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values.at(0), "file1.txt");
    EXPECT_EQ(values.at(1), "file2.txt");
    EXPECT_EQ(values.at(2), "file3.txt");
}

TEST(ArgsTest, ManyOptionsMixedRequirements)
{
    char *argv[9] = {
            (char*)"ignored",
            (char*)"--ip",
            (char*)"192.168.0.1",
            (char*)"-p",
            (char*)"1234",
            (char*)"-f",
            (char*)"file1.txt",
            (char*)"file2.txt",
            (char*)"file3.txt"};
    parser p = {
            option( "i",
                    "ip",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    ""),
            option( "p",
                    "port",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    ""),
            option("f", "files"),
            option( "u",
                    "userandpass",
                    option_type::optional_option,
                    value_constraint::exact_num_values,
                    2,
                    "")};
    result r = p.parse(9, argv);

    EXPECT_EQ(r.good(), true);

    std::vector<std::string> values = p.values_from_option("files");
    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values.at(0), "file1.txt");
    EXPECT_EQ(values.at(1), "file2.txt");
    EXPECT_EQ(values.at(2), "file3.txt");
}

TEST(ArgsTest, ManyOptionsMixedRequirementsError)
{
    char *argv[4] = {
            (char*)"ignored",
            (char*)"--userandpass",
            (char*)"user",
            (char*)"password"};
    parser p = {
            option( "i",
                    "ip",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    ""),
            option( "p",
                    "port",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    ""),
            option("f", "files"),
            option( "u",
                    "userandpass",
                    option_type::optional_option,
                    value_constraint::exact_num_values,
                    2,
                    "")};
    result r = p.parse(4, argv);

    EXPECT_EQ(r.good(), false);
    EXPECT_EQ(r.errors.size(), 2);

    EXPECT_EQ(p.has_option("i"), false);
    EXPECT_EQ(p.has_option("ip"), false);
    EXPECT_EQ(p.has_option("p"), false);
    EXPECT_EQ(p.has_option("port"), false);
    EXPECT_EQ(p.has_option("f"), false);
    EXPECT_EQ(p.has_option("files"), false);
    EXPECT_EQ(p.has_option("u"), true);
    EXPECT_EQ(p.has_option("userandpass"), true);

    std::vector<std::string> values = p.values_from_option("i");
    EXPECT_EQ(values.empty(), true);

    values = p.values_from_option("port");
    EXPECT_EQ(values.empty(), true);

    values = p.values_from_option("f");
    EXPECT_EQ(values.empty(), true);

    values = p.values_from_option("u");
    EXPECT_EQ(values.empty(), false);
    EXPECT_EQ(values.at(0), "user");
    EXPECT_EQ(values.at(1), "password");
}

TEST(ArgsTest, ExactNumMoreValuesAvailable)
{
    char *argv[7] = {
            (char*)"ignored",
            (char*)"-s",
            (char*)"FirstValue",
            (char*)"SecondValue",
            (char*)"ThirdValue",
            (char*)"FourthValue",
            (char*)"FifthValue"};
    parser p = {
            option( "s",
                    "long",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    3,
                    "") };
    result r = p.parse(7, argv);

    EXPECT_EQ(r.good(), true);

    EXPECT_EQ(p.has_option("s"), true);
    EXPECT_EQ(p.has_option("long"), true);

    std::vector<std::string> values = p.values_from_option("s");
    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values.at(0), "FirstValue");
    EXPECT_EQ(values.at(1), "SecondValue");
    EXPECT_EQ(values.at(2), "ThirdValue");
}

TEST(ArgsTest, NoValueMoreValuesAvailable)
{
    char *argv[7] = {
            (char*)"ignored",
            (char*)"-s",
            (char*)"FirstValue",
            (char*)"SecondValue",
            (char*)"ThirdValue",
            (char*)"FourthValue",
            (char*)"FifthValue"};
    parser p = {
            option( "s",
                    "long",
                    option_type::mandatory_option,
                    value_constraint::no_values,
                    6,
                    "") };
    result r = p.parse(7, argv);

    EXPECT_EQ(r.good(), true);

    EXPECT_EQ(p.has_option("s"), true);
    EXPECT_EQ(p.has_option("long"), true);

    std::vector<std::string> values = p.values_from_option("s");
    EXPECT_EQ(values.size(), 0);
}

TEST(ArgsTest, NoOptionName)
{
    char *argv[7] = {
            (char*)"ignored",
            (char*)"-s",
            (char*)"FirstValue",
            (char*)"SecondValue",
            (char*)"ThirdValue",
            (char*)"FourthValue",
            (char*)"FifthValue"};
    parser p = {
            option( "",
                    "",
                    option_type::optional_option,
                    value_constraint::no_values,
                    6,
                    "") };
    result r = p.parse(7, argv);

    EXPECT_EQ(r.good(), false);
    EXPECT_EQ(r.errors.size(), 1);

    error err = r.errors.at(0);
    EXPECT_EQ(err.reason, requirement_error::option_has_no_names_error);
}

TEST(ArgsTest, PrintArgsEmpty)
{
    parser p;
    
    std::stringbuf str;
    std::ostream strm(&str);
    
    p.print_help(strm, false);
    EXPECT_EQ(str.str(), "");
    
    strm.clear();
    p.print_help(strm, true);
    EXPECT_EQ(str.str(), "");
}

TEST(ArgsTest, PrintArgsOneOption)
{
    parser p = {
            option( "i",
                    "ip",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    "Ip address of host")
                };
    
    std::stringbuf str;
    std::ostream strm(&str);
    
    std::stringbuf comp;
    std::ostream compstrm(&comp);
    
    compstrm << "Options" << std::endl
         << "-i / --ip   Ip address of host"    << std::endl
         << "            (1 value(s) expected)" << std::endl
         << std::endl;
    
    
    p.print_help(strm, true);
    EXPECT_EQ(str.str(), comp.str());
    

    std::stringbuf str2;
    std::ostream strm2(&str2);

    std::stringbuf comp2;
    std::ostream compstrm2(&comp2);
    
    compstrm2 << "Options" << std::endl
         << "-i / --ip   Ip address of host"    << std::endl
         << "            (1 value(s) expected)" << std::endl;
    p.print_help(strm2, false);
    EXPECT_EQ(str2.str(), comp2.str());
}

TEST(ArgsTest, PrintArgsMix)
{
    parser p = {
            option( "i",
                    "ip",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    "Fisch"),
            option( "p",
                    "port",
                    option_type::mandatory_option,
                    value_constraint::exact_num_values,
                    1,
                    "Misch"),
            option("f", "files"),
            option( "u",
                    "userandpass",
                    option_type::optional_option,
                    value_constraint::exact_num_values,
                    2,
                    "Tisch"),
            option( "r",
                    "",
                    option_type::optional_option,
                    value_constraint::no_values,
                    2,
                    "Random option"),
            option( "",
                    "empty",
                    option_type::optional_option,
                    value_constraint::no_values,
                    2,
                    ""),
            option( "",
                    "ldesc",
                    option_type::optional_option,
                    value_constraint::up_to_num_values,
                    5,
                    "Long description, no short value")};
    
    std::stringbuf str;
    std::ostream strm(&str);
    
    std::stringbuf comp;
    std::ostream compstrm(&comp);
    
    compstrm << "Options" << std::endl
         << "--empty              (no value expected)"              << std::endl
         << std::endl
         << "-f / --files         (unlimited number of values)"     << std::endl
         << std::endl
         << "-i / --ip            Fisch"                            << std::endl
         << "                     (1 value(s) expected)"            << std::endl
         << std::endl
         << "--ldesc              Long description, no short value" << std::endl
         << "                     (between 1 and 5 values)"         << std::endl
         << std::endl
         << "-p / --port          Misch"                            << std::endl
         << "                     (1 value(s) expected)"            << std::endl
         << std::endl
         << "-r                   Random option"                    << std::endl
         << "                     (no value expected)"              << std::endl
         << std::endl
         << "-u / --userandpass   Tisch"                            << std::endl
         << "                     (2 value(s) expected)"            << std::endl
         << std::endl;
    
    p.print_help(strm, true);
    EXPECT_EQ(str.str(), comp.str());
    
    
    std::stringbuf str2;
    std::ostream strm2(&str2);
    
    std::stringbuf comp2;
    std::ostream compstrm2(&comp2);
    
    compstrm2 << "Options" << std::endl
         << "--empty              (no value expected)"              << std::endl
         << "-f / --files         (unlimited number of values)"     << std::endl
         << "-i / --ip            Fisch"                            << std::endl
         << "                     (1 value(s) expected)"            << std::endl
         << "--ldesc              Long description, no short value" << std::endl
         << "                     (between 1 and 5 values)"         << std::endl
         << "-p / --port          Misch"                            << std::endl
         << "                     (1 value(s) expected)"            << std::endl
         << "-r                   Random option"                    << std::endl
         << "                     (no value expected)"              << std::endl
         << "-u / --userandpass   Tisch"                            << std::endl
         << "                     (2 value(s) expected)"            << std::endl;
    
    p.print_help(strm2, false);
    EXPECT_EQ(str2.str(), comp2.str());
}

