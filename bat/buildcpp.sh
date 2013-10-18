#!/bin/bash
# compile cpp project
#	1. create and copy src directory structure
#	2. move all of cpp files from subfolder(or sub subfolder) to root
#	3. run g++ compiler to compile all of cpp files in root folder

# sample command: buildcpp.sh rethinkdb /d/root/projects/rethinkdb linz

project_name=$1
project_path=$2
compile_symbol=$3

cpp_src_path=$project_path/src
cpp_build_path=$project_path/build
cpp_build_instance_path=$cpp_build_path/$compile_symbol
	
copy_folder() {
	# create build folder
	if [ ! -e $cpp_build_path ]
	then
		mkdir $cpp_build_path
	fi
	
	# delete existing build instance folder
	if [ -e $cpp_build_instance_path ]
	then
		rm -r $cpp_build_instance_path
	fi
	# create new build instance folder
	cp -r $cpp_src_path $cpp_build_instance_path
	
	echo "copy folders done"
}

move_cpps() {
	# for each folder and subfoder
	# do	
	#		move cpp(cc) files to root
	# done
	find $cpp_build_instance_path -mindepth 2 -name "*.cc" -exec cp {} $cpp_build_instance_path \;
	# find $cpp_build_instance_path -mindepth 2 -name "*.hpp" -exec cp {} $cpp_build_instance_path \;
	echo "copy files done"
}

compile_cpps() {
	# collect all of .cc files in root
	cpp_files=$( find $cpp_build_instance_path -maxdepth 1 -name "*.cc" -exec echo {} \; )
	# echo "cpp files=$cpp_files" > output.txt
	exe_filename=$cpp_build_instance_path/$project_name
	
	compile_command="g++ $cpp_files -Wall -ansi -o $exe_filename"
	echo "compile_command=$compile_command"
	
	compile_output=$( $compile_command )
	# echo "compile_output=$compile_output"
	
	echo "compile cpps done"
}



# Main thread
copy_folder
move_cpps
compile_cpps 
 