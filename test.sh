#!/bin/bash
/server &
/test localhost
if [ !$? ]; then
   exit 0
else
   exit 1
fi

