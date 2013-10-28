#!/bin/bash
# looks up the keyword and begins with the specified file through all of included files within it
# logic:
#	1. lookup the keyword in the base file
#	2. output the filename and code line No. if keyword is looked up.
#	3. collect included filenames which are waiting for the next lookup
#	4. lookup the keyword in the included custom files
# command sample: lookup.sh get_random_machine_name clustering/administration/main/command_line.cc buffer.txt

keyword=$1
base_file=$2
buffer_file=$3
root_path="/d/root/Git/Cpp/rethinkdb/src"

echo "keyword = '$keyword'"
echo "base_file = '$base_file'"
echo "buffer_file = '$buffer_file'"
echo ""

function lookup_file {
	local filename=$1
	echo "===file: $filename"
	grep -n "$keyword" $root_path/$filename
}

# lookup in base file first
lookup_file $base_file

# collect all included files in base file
awk '/#include \"/{print $2}' $root_path/$base_file > $buffer_file
# lookup in each included files in base file
# for file_path in $(cat $buffer_file)
# do
	# lookup_file $file_path
# done
while read file_path;
do
	file_path="${file_path%\"}"
	file_path="${file_path#\"}"
	lookup_file $file_path
done <$buffer_file

# rm $buffer_file


