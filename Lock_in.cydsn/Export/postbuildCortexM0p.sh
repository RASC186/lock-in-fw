#!/bin/sh
# This script allows a 3rd party IDE to use cymcuelftool.exe to perform
# the post processing that is necessary to update the *.elf file
# generated by the linker into a complete memory image to use in
# programming the PSoC.
# NOTE: Please provide the path to the CyElfTool.
if [ "$4" == "cmsis" ]; then
for f in "$5/cymcuelftool.exe"
do
cp -f "$f" "$3/cymcuelftool.exe"
LAST_EXIT=$?
if [ $LAST_EXIT != 0 ]; then
    exit $LAST_EXIT
fi
done

OUT_FILE_NAME=$(basename "$1")
CURRENT_LINK_FILE_NAME="${OUT_FILE_NAME%.*}""_link.axf"
CURRENT_LINK_FILE=$(dirname "$1")/"$CURRENT_LINK_FILE_NAME"

mv -f "$1" "$CURRENT_LINK_FILE"
LAST_EXIT=$?
if [ $LAST_EXIT != 0 ]; then
    exit $LAST_EXIT
fi
"$3/cymcuelftool.exe" --sign "$CURRENT_LINK_FILE" --output "$1"
LAST_EXIT=$?
if [ $LAST_EXIT != 0 ]; then
    exit $LAST_EXIT
fi
    exit
fi

if [ "$2" == "eclipse" ]; then
mv -f "$1" "$1_link.out"
LAST_EXIT=$?
if [ $LAST_EXIT != 0 ]; then
    exit $LAST_EXIT
fi
./cymcuelftool.exe --sign "$1_link.out" --output "$1"
LAST_EXIT=$?
if [ $LAST_EXIT != 0 ]; then
    exit $LAST_EXIT
fi
    exit
fi

