#include <stdio.h>
#include <sys/resource.h>

#include <set>
#include <string>

#include "clustering/administration/main/command_line.hpp"

#include "utils.hpp"

int main(int argc, char *argv[]) {
	printf("Bonjour world\n");
	
	startup_shutdown_t startup_shutdown;
	
	std::set<std::string> subcommands_that_look_like_flags;
	subcommands_that_look_like_flags.insert("--version");
	subcommands_that_look_like_flags.insert("-v");
	subcommands_that_look_like_flags.insert("--help");
	subcommands_that_look_like_flags.insert("-h");
	
	if (argc == 1 || (argv[1][0] == '-' && subcommands_that_look_like_flags.count(argv[1]) == 0)) {
		//printf("In block if\n");
		return main_rethinkdb_porcelain(argc, argv);
	}
}
