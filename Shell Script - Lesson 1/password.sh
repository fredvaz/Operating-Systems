#!/bin/sh
# This is some secure program that uses security.

VALID_PASSWORD="secret" #this is our password.

echo "Please enter the password:"
read PASSWORD

if [ "$PASSWORD" == "$VALID_PASSWORD" ]; then
	echo "You have access!"
else
	echo "ACCESS DENIED!"
fi
