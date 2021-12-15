#!/bin/sh
# Author 	: Akash Kulkarni
# Roll no. 	: 33241
# Batch	: K - 10
#
# Operating Systems Lab (OSL)
#
# Assignment 1B : Write a program to implement an address book with options given below
#		a. Create address
#		b. View address book
#		c. Insert a record
#		d. Delete a record
#		e. Modify a record
#		f. Exit
#=============================================================================================


echo "Welcome to address book"

echo "	1) Create a new Address Book
	2) View Address Book
	3) View A Record
	4) Insert A Record
	5) Delete A Record
	6) Modify A Record
	7) Exit"
	
while [ 1 ]
do
	
echo "Enter your choice : "
read choice

case $choice in 


# create db
1) echo "Creating a new address book"
echo "Enter a name for address book : "
read bookName
touch $bookName
;;

#view all
2) echo "Viewing Address Book"
echo -e "\nId\tName\tCity"
## -e escape character
cat $bookName
;;

# view single
3) echo "Viewing A Single Record "
echo "Enter the Student Id to be viewed : "
read viewId; 
if [ `grep -c "$viewId" $bookName` -gt 0 ]
	then 
		echo -e "\nId\tName\tCity" 
		grep -w "$viewId" $bookName
		
else
	echo -e "Record for Student Id does not exist "
fi
;;


# insert record
4) echo "Inserting Record in Book"
echo "Enter a Student Id : "
read id
echo "Enter Student Name : "
read name
echo "Enter the City Name : " 
read city

if [ `grep -ci "$id.*$name" $bookName` -gt 0 ]
then 
	echo -e "\nRecord with student id already exists !!"
else
	echo -e "$id\t$name\t$city" >> $bookName
	sort $bookName > mytempDB
	mv mytempDB $bookName
	echo "Record for $name inserted."

fi
;;

# delete record
5) echo "Deleting a Record"
echo "Enter the Student Id of record to be deleted : "
read id
if [ `grep -c "$name.*$phone" $bookName` -gt 0 ]
then 
	sed -i "/$id/d" $bookName
	sort $bookName > mytempDB
	mv mytempDB $bookName
	echo -e "\nRecord deleted successfully !!"
else
	echo -e "\nRecord not found !!"
fi
;;

6) echo "Modifying the records "
read -p "Enter Student Id : " oldId
read -p "Enter Student Name : " oldName

if [ `grep -c "$oldId.$oldName" $bookName` -gt 0 ]
	then 
		echo -e "\nId\tName\tCity"
		grep -i "$oldId.$oldName" $bookName
		
		echo -e "What do you want to modify?"
		echo "1. Student Id"
		echo "2. Student Name"
		echo -e "3. Student City\n"
		
		read -p "Enter your choice: " choice
		case $choice in
		1)	
			read -p "Enter new id : " newId
			sed -i "s/$oldId/$newId/" $bookName
			;;
		2)
			read -p "Enter new name: " newName
			sed -i "s/$oldId.*$oldName/$oldId\t$newName/" $bookName
			;;

		3)	
			read -p "Enter old city : " oldCity
			read -p "Enter new city: " newCity
			sed -i "s/$oldId.*$oldCity/$oldId\t$oldName\t$newCity/" $bookName
			;;

		*)
			echo -e "\nEnter valid choice"
			;;
		esac
		echo -e "Modification Successful"
		echo -e "\nId\tName\tCity"
		grep -i "$oldId" $bookName
else
	echo -e "\nRecord not found !!"
fi
;;


7) echo "Exit"
exit;;

*) echo "Invalid Choice"
;;

esac

done
	
