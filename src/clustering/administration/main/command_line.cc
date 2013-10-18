#include "clustering/administration/main/command_line.hpp"

#include "arch/io/disk.hpp"
#include "clustering/administration/main/options.hpp"
#include "utils.hpp"

options::help_section_t get_file_options(std::vector<options::option_t> *options_out) {
	options::help_section_t help("File path options");
	options_out->push_back(options::option_t(options::names_t("--directory", "-d"),
											 options::OPTIONAL,
											 "rethinkdb_data"));
	help.add("-d [ --directory ] path", "specify directory to store data and metadata");
	options_out->push_back(options::option_t(options::names_t("--io-threads"),
											 options::OPTIONAL,
											 strprintf("%d", DEFAULT_MAX_CONCURRENT_TO_REQUESTS)));
	help.add("--io-threads n",
			 "how many simultaneous I/O operations can happen at the same time");
    options_out->push_back(options::option_t(options::names_t("--no-direct-io"),
                                             options::OPTIONAL_NO_PARAMETER));
	help.add("--no-direct-io", "disable direct I/O");
	return help;
}

void get_rethinkdb_porcelain_options(std::vector<options::help_section_t> *help_out,
									 std::vector<options::option_t> *options_out) {
	help_out->push_back(get_file_options(options_out));
/*	help_out->push_back(get_machine_options(options_out));
	help_out->push_back(get_network_options(false, options_out));
	help_out->push_back(get_web_options(options_out));
	help_out->push_back(get_cpu_options(options_out));
	help_out->push_back(get_service_options(options_out));
	help_out->push_back(get_setuser_options(options_out));
	help_out->push_back(get_help_options(options_out));
	help_out->push_back(get_log_optoins(options_out));
	help_out->push_back(get_config_file_options(options_out));*/
}

int main_rethinkdb_porcelain(int argc, char *argv[]) {
	std::vector<options::option_t> options;
	std::vector<options::help_section_t> help;
	get_rethinkdb_porcelain_options(&help, &options);

	return 0;
}

