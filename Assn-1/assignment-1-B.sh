#! /bin/bash#!

choice=0

while [ $choice -ne 6 ]
do
echo "------------"
echo -e "Press \n1 to create employee database\n2 to view employee database\n3 to insert record\n4 to delete record\n5 to modify record\n6 to exit"
echo "------------"
read choice
filename='employee.txt'
case $choice in
	"1" )
		echo "Creating the employee database"
		#read the filename
		#enable interpretation of backslash escapes. -e flag
		echo -e "\n Enter name of the new file or exisitng file -\c"
		read filename
		#Check that filename is not empty
		#n option can be used to remove the '\n' (newline character) from the output.
		#wc -m : prints the count of characters from a file.
		len=$(echo -n $filename | wc -m)
		if test $len -gt 0;then
			touch $filename
			echo -e "\n File with name $filename is created"
		else
			echo -e "\n Filename cannot be empty"
		fi
		;;
	"2" )	
		echo "Emp_Id		Name		Designation"
		cat $filename | while read p
		do
			echo "$p"
		done  
		
                echo "Viewed" ;;
	"3" )
		echo "Inserting a new record"
			
		echo -e "Enter Emp_Id: \c"
		#read emp_id
		
		#validation
		while true
		do
			read emp_id
			#len=$(echo -n $emp_id | wc -m)
			if [ $emp_id -gt 100 ] && [ $emp_id -lt 999 ];then
				break
			else
				echo "This field must be in range 100-999,please re-enter empId"
			fi
		done

		echo -e "Enter Name: \c"
		#read name
		
		#validation
		while true
		do
			read name
			if [[ "$name" =~ [^a-zA-Z] ]]; then
				echo "Invalid format for name, only alphabets are allowed.Please re-enter"
			else
				break
			fi
		done
		
		echo -e "Enter Designation: \c"
		
		#validation
		while true
		do
			read designation
			if [[ "$designation" =~ [^a-zA-Z] ]]; then
				echo "Invalid format for designation, only alphabets are allowed.Please re-enter"
			else
				break
			fi
		done
		

		data="$emp_id		$name		$designation" 
		
		echo "$data"
		echo "$data" >> $filename;;
		
	"4" )	echo "Deleting Record"
		echo "Enter Emp_Id to delete:"
		
		#validation
		while true
		do
			read emp_id
			#len=$(echo -n $emp_id | wc -m)
			if [ $emp_id -gt 100 ] && [ $emp_id -lt 999 ];then
				break
			else
				echo "This field must be in range 100-999,please re-enter empId"
			fi
		done
		#grep v outputs the lines which do NOT match
		#grep i Ignore case distinctions on Linux and Unix
		grep -v -i "$emp_id" $filename > temp
		mv temp $filename
		echo "Delete Successful";;
	"5" )
		#validation
		while true
		do
			echo "Enter empId of employee to modify"
			read emp_id
			#len=$(echo -n $emp_id | wc -m)
			if [ $emp_id -gt 100 ] && [ $emp_id -lt 999 ];then
				break
			else
				echo "This field must be in range 100-999,please re-enter empId"
			fi
		done

		record=$(grep -i "$emp_id" $filename)
		len=$(echo -n $record |wc -m)

		if [ "$len" -eq 0 ]
		then
			echo "No records Found"
		else
			echo "$record"

			array=($record)
						
			emp_id="${array[0]}"
			name="${array[1]}"
			designation="${array[2]}"

			echo "------------------------------------"
			echo "1. Name"
			echo "2. Designation"
			echo "------------------------------------"
			echo -e "Enter some character : \c"
			read choice
			echo "------------------------------------"

			case $choice in

					"1" )
						echo -e "Enter Name: \c"
						#validation
						while true
						do
							read name
							if [[ "$name" =~ [^a-zA-Z] ]]; then
								echo "Invalid format for name, only alphabets are allowed.Please re-enter"
							else
								break
							fi
						done
					;;
					"2" )
						echo -e "Enter Designation: \c"
						#validation
						while true
						do
							read designation
							if [[ "$designation" =~ [^a-zA-Z] ]]; then
								echo "Invalid format for designation, only alphabets are allowed.Please re-enter"
							else
								break
							fi
						done
					;;

					* )
						echo "Invalid Input" ;;
			esac		


			data="$emp_id		$name		$designation" 
			echo "$data"

			sed -i "/$emp_id/c $data" $filename
						
		fi
		#SED is a powerful text stream editor. Can do insertion, deletion, search and replace(substitution).
		#-i option sed command replaces the text in the original file itself rather than displaying it on the terminal.
		echo "Modified" ;;
	6 )
       	echo "Thank You!" ;;
      	* )
       	echo "Invalid Choice, please enter the right choice!" ;;
esac
done
