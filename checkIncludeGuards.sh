#!/bin/bash

headerFiles=$(find . -path ./physic/Box2D -prune -o -path ./build -prune -o -iname "*.h")

for headerFileWithPath in ${headerFiles}
do
	if	[ $headerFileWithPath != "./physic/Box2D" ] &&
		[ $headerFileWithPath != "./build" ]; then
		echo "checking ${headerFileWithPath}"

		firstLine=$(head --lines 1 ${headerFileWithPath})
		secondLine=$(head --lines 2 ${headerFileWithPath} | tail --lines 1)
		ifndef=${firstLine:0:7}
		define=${secondLine:0:7}

		if [ "${ifndef}" != "#ifndef" ]; then
			echo "wrong value in first line: ${ifndef}"
			exit 1
		fi

		if [ $define != "#define" ]; then
			echo "wrong value in first line: ${ifndef}"
			exit 1
		fi

		includeGuardOne=${firstLine:8:${#firstLine}}
		includeGuardTwo=${secondLine:8:${#secondLine}}

		if [ $includeGuardOne != $includeGuardTwo ]; then
			echo "the include guards do not match"
			exit 1
		fi

		includeGuardReal=$includeGuardOne;

		headerFileWithoutPath=${headerFileWithPath##*/}
		headerFile=${headerFileWithoutPath%.h}
		path=${headerFileWithPath%/*}
		subProject=${path##*/}
		subProjectUpperCase=$(echo $subProject | tr  "[:lower:]" "[:upper:]")
		fileNameUpperCase=$(echo $headerFile | tr  "[:lower:]" "[:upper:]")
		includeGuardShouldBe="${subProjectUpperCase}_${fileNameUpperCase}_H"

		if [ $includeGuardReal != $includeGuardShouldBe ]; then
			echo "the include guards do not match the specified pattern"
			exit 1
		fi
	fi
done