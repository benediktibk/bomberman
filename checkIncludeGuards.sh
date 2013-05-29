#!/bin/bash

headerFiles=$(find . -path ./physic/Box2D -prune -o -iname "*.h")

for headerFile in ${headerFiles}
do
	if [ $headerFile != "./physic/Box2D" ]; then
		firstLine=$(head --lines 1 ${headerFile})
		secondLine=$(head --lines 2 ${headerFile} | tail --lines 1)
		ifndef=${firstLine:0:7}
		define=${secondLine:0:7}

		if [ $ifndef != "#ifndef" ]; then
			echo "wrong value in first line of file ${headerFile}: ${ifndef}"
			exit 1
		fi

		if [ $define != "#define" ]; then
			echo "wrong value in first line of file ${headerFile}: ${ifndef}"
			exit 1
		fi

		includeGuardOne=${firstLine:8:${#firstLine}}
		includeGuardTwo=${secondLine:8:${#secondLine}}

		if [ $includeGuardOne != $includeGuardTwo ]; then
			echo "the include guards do not match in file ${headerFile}"
			exit 1
		fi

		includeGuard=$includeGuardOne;

		echo ${firstLine}
		echo ${secondLine}
	fi
done