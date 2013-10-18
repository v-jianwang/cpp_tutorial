#ifndef CLUSTERING_ADMINISTRATION_MAIN_OPTIONS_HPP_
#define CLUSTERING_ADMINISTRATION_MAIN_OPTIONS_HPP_

#include <map>
#include <string>
#include <vector>

namespace options {

// A list of values provided for some option. (Multiple values means that option was specified
// multiple times.) Also included is a string description the *source* of the option values (e.g. a
// command line or the name of a config file) to help make friendly error messages. Typically this 
// is a value in a 'std::map<std::string, values_t>', where the key is the option name.
struct values_t {
	explicit values_t(const std::string &_source, const std::vector<std::string> &_values)
		: source(_source), values(_values) { }
	
	// A string describing the source of the values. This shold be usable in a help message as the
	// object of prepositional phrase -- e.g. "the command line", which could be used in phrases
	// "from the command line" or "in the command line", or "the configuration file foo.cfg".
	std::string source;
	std::vector<std::string> values;
};

// Represents an option's names. Be sure to include dashes! Usage:
//
// 		names_t("--max-foobars")	// An option name.
//		names_t("--cores", "-c")	// An option name with an abbreviation
class names_t {
public:
	// Include dashes. For example, name might be "--blah".
	explicit names_t(const std::string &name) {
		names.push_back(name);
	}
	// Include the right amount of dashes. For example, official_name might
	// be "--help", and other_name might be "-h".	
	names_t(std::string official_name, std::string other_name) {
		names.push_back(official_name);
		names.push_back(other_name);
	}
private:
	friend class option_t;
	std::vector<std::string> names;
};

// Pass one of these to the option_t construct to tell what kind of argument you have.
enum appearance_t {
	// A mandatory argument that can be passed once.
	MANDATORY,
	// A mandatory argument that may be repeated.
	MANDATORY_REPEAT,
	// An optional argument, that may be passed zero or one times.
	OPTIONAL,
	// An optional argument, that may be repeated.
	OPTIOANL_REPEAT,
	// An optional argument, that doesn't tak a parameter. Userful for "--help".
	OPTIONAL_NO_PARAMETER
};

// A command line option with a name, specification of how many times it may appear, and whether it
// takes a parameter.
//
// Examples:
//     // An option that may be used at most once, with no parameter.
//     option_t(names_t("--help", "-h"), OPTIONAL_NO_PARAMETER)
//     // An option that may be used at most once, with a default value.  The user
//     // could pass --cores 3 or -c 3, but not a naked -c.
//     option_t(names_t("--cores", "-c"), OPTIONAL, strprintf("%d", get_cpu_count()));
//     // An option that must appear one or more times.
//     option_t(names_t("--join", "-j"), MANDATORY_REPEAT)
class option_t {
public:
	// Creates an option with the appropriate name and appearance specifier,
	// with a default value being the empty vector.
	explicit option_t(names_t names, appearance_t appearance);
	// Creates an option with the appropriate name and appearance specifier,
	// with the default value being a vector of size 1. OPTIONAL and 
	// OPTIONAL_REPEAT are the only value appearance specifiers.
	explicit option_t(names_t names, appearance_t appearance, std::string default_value);
	
private:
	friend std::map<std::string, values_t> default_values_map(const std::vector<option_t> &options);
	friend std::map<std::string, values_t> do_parse_command_line(
			const int argc, const char *const *const argv, const std::vector<option_t> &options,
			std::vector<std::string> *const unrecognized_out);
	friend const option_t *find_option(const char *const option_name, const std::vector<option_t> &options);
	friend void verify_option_counts(const std::vector<option_t> &options,
									 const std::map<std::string, values_t> &names_by_values);
	friend std::map<std::string, values_t> parse_config_file(const std::string &contents,
															 const std::string &filepath,
															 const std::vector<option_t> &options,
															 const std::vector<option_t> &options_superset);

	// Names for the option, e.g. "-j", "--join"
	std::vector<std::string> names;

	// How many times must the option appear? If an option appears zero times,
	// and if min_appearances is zero, then 'default_values' will be used as the 
	// value-list of the option. Typical combinations of (min_appearances,
	// max_appearances) are (0, 1) (with a default_value), (0, SIZE_MAX) (with or
	// without a default value), (1, 1) (for mandatory options), (1, SIZE_MAX)
	// (for mandatory options with repetition).
	//
	// It must be the case that 0 <= min_appearances <= max_appearances <= SIZE_MAX
	size_t min_appearances;
	size_t max_appearances;
	
	// True if an option doesn't take a parameter. For example, "--help" would 
	// take no parameter.
	bool no_parameter;
	
	// The value(s_ to use if no appearances of the command line option are
	// available. This is only relevant if min_appearances == 0.
	std::vector<std::string> default_values;
};

// Constructs a map of default option values.
std::map<std::string, values_t> defalut_values_map(const std::vector<option_t> &options);

// Parse the file contents, using filepath solely to help build error messages, retrieving some
// options. Ignore options that are in the superset, but not in the regular set.
std::map<std::string, values_t> parse_config_file(const std::string &contents,
												  const std::string &filepath,
												  const std::vector<option_t> &options,
												  const std::vector<option_t> &options_superset);

// A help_line_t is a syntax description and a blurb. When used in a help_section_t, the blurbs get
// aligned and word-wrapped.
struct help_line_t {
	help_line_t(const std::string &_syntax_description,
				const std::string &_blurb)
		: syntax_description(_syntax_description), blurb(_blurb) { }

	std::string syntax_description;
	std::string blurb;
};

// A help_section_t is a titled list of syntax descriptions and blurbs. When rendered with
// format_help, all the blurbs get aligned and word-wrapped.
struct help_section_t {
	help_section_t() { }
	explicit help_section_t(const std::string &_section_name)
		: section_name(_section_name) { }
	help_section_t(const std::string &_section_name, const std::vector<help_line_t> &_help_lines)
		: section_name(_section_name), help_lines(_help_lines) { }
	
	void add(const std::string &syntax_description, const std::string &blurb) {
		help_lines.push_back(help_line_t(syntax_description, blurb));
	}
	
	std::string section_name;
	std::vector<help_line_t> help_lines;
};


} // namespace options


#endif /* CLUSTERING_ADMINISTRATION_MAIN_OPTIONS_HPP_ */