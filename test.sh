#!/bin/bash
exit 1
/server &
/test localhost
if [ !$? ]; then
   exit 0
else
   exit 1
fi

